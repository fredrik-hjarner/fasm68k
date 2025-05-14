include 'instruction_validation_structure.inc'

; `validate` examines if an instruction uses a valid combination of
;     instruction, size and operands.
; Parameters:
;     instr: token
;         movep, stop, exg etc.
;     size: token
;         b | w | l | _
;     op1: token
;         an_displace, d, an, imm et cetera. _ means empty.
;     op2: token
;         an_displace, d, an, imm et cetera. _ means empty.
; Supposed to be `call`:ed.
calminstruction validate inst*, size*, op1*, op2*
        local tokens
        arrange tokens, inst.size.op1.op2

        local thing_to_check
        arrange thing_to_check, =m68k.=valid_instructions.tokens
        check defined thing_to_check
        jyes valid
    ; invalid:
        local inst_str
        arrange inst_str, inst
        stringify inst_str
        err inst_str bappend ': Invalid: ombination of operands' \
            bappend 13 bappend 10
        exit
    valid:
end calminstruction