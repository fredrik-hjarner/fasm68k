;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; fasm68k - Motorola 68000 Instruction Set for fasmg                         ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; This is the main entry point that includes all components needed to        ;;
;; assemble 68000 code using fasmg's macro language (CALM).                   ;;
;;                                                                            ;;
;; Architecture:                                                              ;;
;;   1. fasmg standard library files (align, inline macros, xcalm, struct)    ;;
;;   2. Settings (diagnostics, autofixes, optimization)                       ;;
;;   3. Utilities (xxcalm helpers, debug, endianness, validation)             ;;
;;   4. Register definitions                                                  ;;
;;   5. Operand parsing (identifying addressing modes)                        ;;
;;   6. Directives (dc.b, dc.w, etc.)                                         ;;
;;   7. Instructions (68000 instruction set implementation)                   ;;
;;   8. Compatibility layers (incbin etc.) (for vasm, asm68k, etc.)           ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Include fasmg standard library files first                                 ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Put align into a namespace because we need the "align" keyword for 68k code.
; This way we can still use fasmg's align feature via fasm2.align if needed.
define fasm2?
namespace fasm2
    include "align.inc"
end namespace
include "macro/inline.inc"
include "xcalm.inc"
include "macro/struct.inc"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Define the m68k namespace and include core components                      ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; All 68k-specific elements will be relative to this namespace
define m68k m68k

; Settings that control assembler behavior
include "settings/diagnostics.inc"    ; Warning/error display settings
include "settings/autofixes.inc"      ; Automatic code fixes (e.g., even alignment)
include "settings/optimization.inc"   ; Code optimization settings
include "settings/settings.inc"       ; General assembler settings

; Utility functions and helpers
include "xxcalm.inc"                  ; Extended CALM utilities
include "debug/debug.inc"             ; Debug output helpers
include "endianness.inc"              ; Big-endian emit/load/store functions
include "validation/validate_instruction.inc"  ; Instruction validation
include "reverse_bits.inc"            ; Bit reversal for condition codes

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; ASSERTION UTILITIES                                                        ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; These utilities validate values during assembly to catch errors early.     ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Assert that a value is >= minimum (e.g., for checking displacement ranges)
macro calminstruction?.assert_min? value*, min*
        new @done
        check value >= min
        @ jyes @done
        ; TODO: TODO: Better error message.
        nice_err "Error: Value is less than minimum allowed"
    @ @done:
end macro

; Assert that a value is <= maximum (e.g., for checking immediate value ranges)
macro calminstruction?.assert_max? value*, max*
        new @done
        check value <= max
        @ jyes @done
        ; TODO: TODO: Better error message.
        nice_err "Error: Value exceeds maximum allowed"
    @ @done:
end macro

; Assert that the current address ($) is word-aligned (even address).
; The 68000 requires instructions to be on even addresses. Fetching an
; instruction from an odd address will cause an address error exception.
macro calminstruction.assert_word_aligned? err_msg:"Instruction placed on an odd address! Instructions are required to be word-aligned."
        check $ and 1
        jno done
        ; TODO: Maybe this could be toggled by a setting, yea probaly since you
        ;       may want to control whether it's an error or a warning at least.
        warn err_msg
    done:
end macro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Register Definitions                                                       ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Define all 68000 registers (d0-d7, a0-a7, pc, sr, ccr, usp) with their     ;;
;; proper encodings for use in instruction encoding.                          ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

include "registers.inc"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Operand Parsing                                                            ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; These files handle parsing operands and identifying addressing modes.      ;;
;; Examples: #$1234 (immediate), (a0) (address register indirect),            ;;
;;           $1000(a0,d0) (address register indirect with index), etc.        ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

include "parsing/utils.inc"            ; Parsing utility functions
include "parsing/parse_operand.inc"    ; Main operand parser
include "parsing/parse_reg_list.inc"   ; Register list parser (for MOVEM)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Directives                                                                 ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Assembler directives like dc.b/w/l (define constant), incbin (include      ;;
;; binary), rs.b/w/l (reserve space), even (align to word), etc.              ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

include "directives.inc"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Label Marking (Future Feature)                                             ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; This would run every time a label is defined (like mylabel:), adding a     ;;
;; .is_label property to that symbol.                                         ;;
;; Future: Add .is_label property to all labels for validation purposes.      ;;
;; This would allow checking if branch targets are labels (to prevent size    ;;
;; suffixes on labels in branch instructions like bra.w mylabel which should  ;;
;; be rejected since the suffix indicates displacement size, not label size). ;;
;; TODO: Can this interceptor be make with CALM?                              ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; struc (label) ? line&
;     define label.is_label
;     . line
; end struc

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; 68000 Instruction Set Implementation                                       ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Each file contains instruction encoders for different instruction types:   ;;
;;   - niladic: Instructions with no operands (nop, rts, rte)                 ;;
;;   - monadic: Instructions with one operand (clr, neg, not, jmp, jsr)       ;;
;;   - dyadic:  Instructions with two operands (add, sub, and, or, cmp)       ;;
;;   - variadic: Instructions with variable operands (movem, link)            ;;
;;   - move:    The MOVE instruction and its variants                         ;;
;;   - ori_andi_...: Immediate logical operations to SR/CCR                   ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

include "instructions/emit_ext_words.inc"  ; Extension word generation for complex addressing

include "instructions/niladic.inc"
include "instructions/monadic.inc"
include "instructions/dyadic.inc"
include "instructions/variadic.inc"
include "instructions/move.inc"
include "instructions/ori_andi_subi_addi_eori_cmpi.inc"

include "instructions/aliases.inc"  ; Instruction aliases (bhs = bcc, etc.)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Compatibility Layers                                                       ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Provides compatibility features for other assemblers (vasm, asm68k, etc.)  ;;
;; to make it easier to port existing codebases to fasm68k.                   ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

include "compat/compat.inc"