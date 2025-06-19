;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Just a file where I can test things out.                                   ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

display 13, 10

include 'helpers.inc'

    ; ori.b #0,$FFFFFFFF.l
    ; ori.b #0,$FFFFFFFF
    ; jsr $FFFFFFFF.l
    ; jsr $FFFFFFFF

; define sr_alias sr

; parse_operand sr_alias

; display '@op1.type: ', @op1.type, 13, 10

; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; equ_0 equ 0
; equ_1 equ 1
; ; equ_imm_0 equ #0 ; You're not allowed to do this in vasm and clownassembler.
; ; equ_imm_1 equ #1 ; You're not allowed to do this in vasm and clownassembler.
; equ_equ_1 equ equ_1
; equ_1_plus_equ_1 equ equ_1+equ_1

; parse_operand #equ_1_plus_equ_1

; display '@op1.type: ', @op1.type, 13, 10

; parse_complex_operand $(pc)
; display @op1.type, 10
; parse_complex_operand <$(pc,d1)>
; display @op1.type, 10
; parse_complex_operand <$(pc,d1.w)>
; display @op1.type, 10
; parse_complex_operand <$(pc,d1.l)>
; display @op1.type, 10

; parse_complex_operand 1(a1)
; display @op1.type, 10
; parse_complex_operand <1(a1,d1)>
; display @op1.type, 10
; parse_complex_operand <1(a1,d1.w)>
; display @op1.type, 10
; parse_complex_operand <1(a1,d1.l)>
; display @op1.type, 10

; ori #1, d1
; Custom error: 
;     `ori` does not support a 2nd operand with type `Dn`. Try .b, .w, .l instead.
; btst.l d1, #1
; Custom error: 
;     `btst.l` does not support a 2nd operand with type `#<data>`. Try .b, ._ instead.
; btst.l a1, #1
; Custom error: 
;     `btst.l` does not support a 1st operand with type `An`.

; iterate p,  1
;     parse_operand #p#p#p#p#p#p#p#p#h
;     display @op1.type, 10
; end iterate

m68k.settings.optimize_cmp_to_cmpi = 1

cmp.w #1, ($1)
cmp.w #1, d1