* Make macro that "marks" all labels (label stuff interceptor thingie).
  I also need to mark labels create with the `label` instruction.
* I've seen d0.b/d0.w/d0.l used in some code but how does that work?
  I probaly should add support for that if it makes sense.
* Hm, could I do wrappers for all instructions that log the name and the
  parameters, then executes the instruction, then logs @op1/@op2 values??
  because that's be neat so I can easily disable/enable logging.
* Sometimes I require a label to be specified with label1.w/.l and sometimes
  I require it to have no .w/.l part, examine this and how other assemblers
  do/behave and what they allow and don't allow.
  I think that's because branch instructions are relative jumps,
  the label's address is never sent instead the assembler calculates the
  jump length and send that jump length.
* Experiment with `relativeto` to find out if I can use that more in parsing.
  for example if I can have an m68k.register element instead of separate
  data_reg and address_reg elements, or actually if I can have both.
* If `$` is part on an expression then that expression MUST be `compute`:ed
      before any `emit` is done since otherwise it will change the value of `$`!
      You can see some of my fix by searching for `pc_index` and
      `pc_displacement`.
* I could probably have a `iterate <size, size_bytes>` and have bcc, bra and bsr
      in it to save a bit of space/code duplication.
* Make sure to test very very large and very very negative number for immediate
      values, and other relevant types, to see if bahaviour is good.
* Find out all the cases for when CALMINSTRUCTIONS can explode in an
      unrecoverable error, then make "safe" wrapper or overrides which
      error in a controlled fashion which you then can follow by `jok`/`jerr`
      checks.
* I now support `$7FFF(a2)` but I should also support `($7FFF,a2)` and add a lot
      of test cases to test that.
* vasm m68k manual has info about some of it's optimizations.
* Crap, maybe it's possible to write `(d8,Xn,PC)`
  etc. as any permutation (example `(d8,PC,Xn)`).
  I need to implement that if other assemblers
  support that...
* It is extra important to validate all the instructions that have "i variants"
      such as cmp -> cmpi et cetera. Currently cmp is allowed to take "imm"
      which will be very confusing for the user, so I need to stop that
      and perhaps examine what happens when you put an imm into the cmp
      instruction if it is totally invalid or just sub-optimal because 
      the manual says "imm" is allowed actually!!!
* Move fasm2 directory into a dependencies directory?
* TODO: Check the real instruction reference instead since it is more reliable:
  https://www.nxp.com/docs/en/reference-manual/M68000PRM.pdf
  https://web.njit.edu/~rosensta/classes/architecture/252software/code.pdf
* addq (and subq?) without size suffix is not allowed on clownassembler but IS
      allowed on vasm. fasm68k should probably mimic vasm in this case.
* I should probably support % for binary numbers where I can, but allow to
      toggle that setting off and recommend users to not use it.
* Make a vs code extension that understands the CALM language.
      Also I'd be nice to show an extra set of line numbers that are relative to
      the current beginning calminstruction/macro (so it matches fasmg error
      message output format sort of).
* Make a `stringify_number` util takes handles negative values.
* Make util that contrain a number to be within a range, maybe.
* vasm actually excodes this differently (I tried with no-opts, not sure if that
      makes a difference though):
      `add.l #$00060000, d6`
* make my compat_binary_percent_prefix support these cases:
      BUTTON_UP=%00000001
      ESF_FM1 equ %00
            should be quite simple to implement really.
            No can't do that for the `equ` case.
* Find out exactly which instructions can have the .s size suffix!!
      I need to know that and it it to m68k_instructions.ts file!!
* I want to remove the aliases in the aliases.inc file. They hinder the
      `validate` function from knowing the size of the instruction. So
      bake the unsized instruction into the instructions itself.
* Figure this out and why it did not work:
      ```
            ; rseven word-aligns the `__rs` counter.
            ; calminstruction rseven?
            ;     local rs_counter
            ;     initsym rs_counter, __rs

            ;     local rs_str
            ;     loc_arr_str rs_str, __rs
            ;     display 'rseven: __rs: ', rs_str, 13, 10

            ;     arr_str rs_str, rs_counter
            ;     display 'rseven: rs: ', rs_str, 13, 10

            ;     compute __rs, __rs + (__rs mod 2)
            ; end calminstruction
      ```
* remove `op.type` and only use `op.type_token` and make a string if needed
      on the fly instead with stringify.

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; things that cause unrecoverable errors in fasmg                            ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

`check reg_groups_found = 1` when reg_groups_found is not a value.
`Error: invalid expression.`

---

dividing an expression that contains an element, right?

---

`arrange op1, m68k.split_operands_result.op1`
It does not work since it will try to resolve `m68k` `split` tokens separately.
That's really not an unrecoverable error, it's just a user error so to speak.

---




