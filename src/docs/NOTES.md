This file contains some notes for myself. These will probably not have too much
value for anyone else.

# Notes

`parse_operand` must be run on all operands before any byte is emitted! The
reason for this has to do with pc-relative addressing modes.

`move` and `movea` are actually encoded exactly the same way, so one might ask why
the `movea` mnemonic even exists, there seems to me to be zero reason.
Contrast this with the difference between `or` and `ori` which have different
encodings.

# Random notes

## auto-fix all instructions that can't take imm but have imm variants

So what are the concrete instructions:
 - [ ] (ori to ccr)
 - [ ] (ori to sr)
 - [x] or -> ori
 - [ ] (and to ccr)
 - [ ] (and to sr)
 - [x] and -> andi
 - [x] sub -> subi
 - [x] add -> addi
 - [ ] (eori to ccr)
 - [ ] (eori to sr)
 - [x] eor -> eori
 - [x] cmp -> cmpi

yep that's all of them.

## auto-fix all instructions that can't take an but have an variants

So what are the concrete instructions:
 - [x] move -> movea
 - [x] sub -> suba
 - [x] add -> adda
 - [x] cmp -> cmpa

yep that's all of them.

## fasmg performance

- matching tokens is faster than comparing strings.
- seems that sometimes nested namespaces can make code slower.
- 3rd argument to match makes the code slower
    `match x, x, ()`

## Some regexes for converting to fasm68k from other assemblers

### For macros

`([a-zA-z0-9_]+):([\t ]*)(macro)`

->

`$3$2$1`

### "Local" labels

`@([a-zA-Z0-9_]+):`

->

`.$1:`

---

`([\t ,]+)@([a-zA-Z0-9_]+)$`

->

`$1.$2`

### Binary numbers

`%([10]+)`

->

`$1b`

## This does not work in fasmg:

```
ErrorText:	dc.w .exception-ErrorText, .bus-ErrorText
		dc.w .address-ErrorText, .illinstruct-ErrorText
		dc.w .zerodivide-ErrorText, .chkinstruct-ErrorText
		dc.w .trapv-ErrorText, .privilege-ErrorText
		dc.w .trace-ErrorText, .line1010-ErrorText
		dc.w .line1111-ErrorText
.exception:	dc.b "ERROR EXCEPTION    "
```

This works though:

```
ErrorText:
        dc.w .exception-ErrorText, .bus-ErrorText
		dc.w .address-ErrorText, .illinstruct-ErrorText
		dc.w .zerodivide-ErrorText, .chkinstruct-ErrorText
		dc.w .trapv-ErrorText, .privilege-ErrorText
		dc.w .trace-ErrorText, .line1010-ErrorText
		dc.w .line1111-ErrorText
.exception:	dc.b "ERROR EXCEPTION    "
```

## Checking the new optimization/diagnostics/autofix settings work

- [x] diag_absolute_too_big
  - [x] 0 - disabled
  - [x] 1 - warn
  - [x] 2 - error
- [x] optimize_cmp_to_cmpi (only the warn/err msg since not fully implemented)
  - [ ] 0 - no opt - cant work right now
  - [x] 1 - opt withwarn
  - [x] 2 - opt without warn
- [ ] autofix_eor_to_eori (only the warn/err msg since not fully implemented)
  - [x] 0 - error
  - [x] 1 - autofix with warn
  - [x] 2 - autofix without warn
- [x] autofix_cmp_to_cmpa (only the warn/err msg since not fully implemented)
  - [x] 0 - error
  - [x] 1 - autofix with warn
  - [x] 2 - autofix without warn