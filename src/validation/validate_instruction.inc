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
; TODO: Maybe change name to `validate_instruction`.
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

        local size_str
        arrange size_str, size
        stringify size_str

        local op1_str
        arrange op1_str, op1
        stringify op1_str

        local op2_str
        arrange op2_str, op2
        stringify op2_str

        err inst_str bappend ': Invalid: combination of operands: ' \
            bappend size_str bappend ' ' \
            bappend op1_str bappend ' ' \
            bappend op2_str bappend 13 bappend 10
        exit
    valid:
end calminstruction