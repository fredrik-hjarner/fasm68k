;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Just a file where I can test things out.                                   ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

display 13, 10

include 'helpers.inc'

    ; ori.b #0,$FFFFFFFF.l
    ; ori.b #0,$FFFFFFFF
    ; jsr $FFFFFFFF.l
    ; jsr $FFFFFFFF

define sr_alias sr

parse_operand sr_alias

display '@op1.type: ', @op1.type, 13, 10

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

equ_0 equ 0
equ_1 equ 1
; equ_imm_0 equ #0 ; You're not allowed to do this in vasm and clownassembler.
; equ_imm_1 equ #1 ; You're not allowed to do this in vasm and clownassembler.
equ_equ_1 equ equ_1
equ_1_plus_equ_1 equ equ_1+equ_1

parse_operand #equ_1_plus_equ_1

display '@op1.type: ', @op1.type, 13, 10