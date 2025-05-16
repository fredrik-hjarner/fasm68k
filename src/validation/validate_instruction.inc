include 'instruction_validation_structure.inc'

define m68k.size_to_str
namespace m68k.size_to_str
    define b            '.b'
    define w            '.w'
    define l            '.l'
    define _            ''
end namespace

define m68k.op_type_to_str
namespace m68k.op_type_to_str
    define dn           'Dn'
    define an           'An'
    define indir_an     '(An)'
    define an_post_incr '-(An)'
    define an_pre_decr  '(An)+'
    define an_displace  'd(An)'
    define an_idx       'd(An,Xn)'
    define abs_w        '(xxx).W'
    define abs_l        '(xxx).L'
    define pc_displace  'd(PC)'
    define pc_idx       'd(PC,Xn)'
    define imm          '#<data>'
    ; define reg_list              ; no support for this here (yet?)
    define ccr          'CCR'
    define sr           'SR'
    define usp          'USP'
    define _            ''
end namespace

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
        local thing_to_check
        arrange thing_to_check, =m68k.=valid_instructions.inst.size.op1.op2
        check defined thing_to_check
        jno invalid
        exit
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;; ALL THE REST OF THE CODE IS JUST TO CREATE A GOOD ERROR MESSAGE        ;;
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    invalid:
        ; So we first did a fast check but now that it failed and with produce
        ; an error we can take our time to do thing more accurately.

        ; First make strings available for all arguments.
        loc_arr_str  inst_str,  inst
        loc_arr_com  size_str,  =m68k.=size_to_str.size

        loc_arr_com  op1_str,   =m68k.=op_type_to_str.op1
        loc_arr_com  op2_str,   =m68k.=op_type_to_str.op2

        loc_com  inst_size_str,  '`' bappend inst_str bappend \
                                 size_str bappend '`'

        arrange  thing_to_check,  =m68k.=valid_instructions.inst
        check    defined thing_to_check
        jyes     check_size
    ; invalid_instruction:
        nice_err  'Unknown instruction ' bappend inst_str
        exit
    check_size:
        arrange  thing_to_check,  =m68k.=valid_instructions.inst.size
        check    defined thing_to_check
        jyes     check_op1
    ; invalid_size:
        nice_err  size_str bappend " is not a valid size for " bappend inst_str
        exit
    check_op1:
        arrange  thing_to_check,  =m68k.=valid_instructions.inst.size.op1
        check    defined thing_to_check
        jyes     op2
    ; invalid_op1:
        nice_err inst_size_str bappend \
            " does not support a 1st operand with type `" bappend \
            op1_str bappend '`'
    op2:
        nice_err inst_size_str bappend \
            " does not support a 2nd operand with type `" bappend \
            op2_str bappend '`'
end calminstruction