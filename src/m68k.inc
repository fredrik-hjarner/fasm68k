;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Need to include some fasm files first.                                     ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; calminstruction calminstruction?.display? line& ; TODO: remove
; end calminstruction

; I put align into a namespace because I will need the align keyword myself.
define fasm2?
namespace fasm2
    include "align.inc"
end namespace
include "macro/inline.inc"
include "xcalm.inc"
include "macro/struct.inc"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;                                                                            ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

define m68k m68k

include "settings/diagnostics.inc"
include "settings/autofixes.inc"
include "settings/optimization.inc"
include "settings/settings.inc"

include "xxcalm.inc"
include "debug/debug.inc"
include "endianness.inc"
include "validation/validate_instruction.inc"
include "reverse_bits.inc"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; ASSERTS                                                                    ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

macro calminstruction?.assert_min? value*, min*
        new @done
        check value >= min
        @ jyes @done
        ; TODO: TODO: Better error message.
        nice_err "Error: assert_min"
    @ @done:
end macro

macro calminstruction?.assert_max? value*, max*
        new @done
        check value <= max
        @ jyes @done
        ; TODO: TODO: Better error message.
        nice_err "Error: assert_max"
    @ @done:
end macro

macro calminstruction.assert_word_aligned? err_msg:"Instruction placed on an odd address! Instructions are required to be word-aligned."
        check $ and 1
        jno done
        ; TODO: Maybe this could be toggled by a setting, yea probaly since you
        ;       may want to control whether it's an error or a warning at least.
        warn err_msg
    done:
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

include "instructions/emit_ext_words.inc"

include "instructions/niladic.inc"
include "instructions/monadic.inc"
include "instructions/dyadic.inc"
include "instructions/variadic.inc"
include "instructions/move.inc"
include "instructions/ori_andi_subi_addi_eori_cmpi.inc"

include "instructions/aliases.inc"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Compatibility                                                              ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

include "compat/compat.inc"