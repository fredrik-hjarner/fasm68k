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