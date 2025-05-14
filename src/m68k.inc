;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Need to include some fasm files first.                                     ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; I put align into a namespace because I will need the align keyword myself.
define fasm2?
namespace fasm2
    include "align.inc"
end namespace
include "macro/inline.inc"
include "xcalm.inc"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;                                                                            ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

include "settings.inc"
include "endianness.inc"
include "xxcalm.inc"
include "compat/compat.inc"
include "validation/validate_instruction.inc"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; ASSERTS                                                                    ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

macro calminstruction?.assert_min? value*, min*
        new @done
        check value >= min
        @ jyes @done
        ; TODO: I'd like to have a setting that warns or errors, or something.
        err "Error: assert_min"
    @ @done:
end macro

macro calminstruction?.assert_max? value*, max*
        new @done
        check value <= max
        @ jyes @done
        ; TODO: I'd like to have a setting that warns or errors, or something.
        err "Error: assert_max"
    @ @done:
end macro

macro calminstruction?.assert_data_reg? value*
        new @done
        check value relativeto m68k.data_reg
        @ jyes @done
        ; TODO: I'd like to have a setting that warns or errors, or something.
        err "Error: assert_data_reg"
    @ @done:
end macro

macro calminstruction?.assert_word_aligned?
        new @done
        check ($ mod 2) = 0
        @ jyes @done
        err "Instruction placed on an odd address!" bappend \
                " Instructions are required to be word-aligned."
    @ @done:
end macro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;                                                                            ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

include "registers.inc"

include "parsing/utils.inc"
include "parsing/parse_operand.inc"
include "parsing/parse_reg_list.inc"

include "directives.inc"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Decorate or mark labels                                                    ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Define is_label on the label so I can identify what is and isn't a label.
; TODO: Can this interceptor be make with CALM?
; struc (label) ? line&
;     define label.is_label
;     . line
; end struc

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; 68000 instruction set                                                      ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

include "instructions/utils.inc"

include "instructions/niladic.inc"
include "instructions/monadic.inc"
include "instructions/dyadic.inc"
include "instructions/variadic.inc"
include "instructions/move.inc"
include "instructions/ori_andi_subi_addi_eori_cmpi.inc"

include "instructions/aliases.inc"