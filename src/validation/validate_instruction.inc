include 'instruction_validation_structure.inc'

; TODO: These should be `:=` instead of `define`.
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
; TODO: This could be improved. For example when user user an instruction and
;       appends a size suffix when the instruction requires not size suffix then
;       an error like `{instr} does not have any size suffix` could be shown.
calminstruction validate inst*, size*, op1*, op2*
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;; CHECK VALIDITY                                                         ;;
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        local thing_to_check
        arrange thing_to_check, =m68k.=valid_instructions.inst.size.op1.op2
        check defined thing_to_check
        jno invalid
        exit
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;; ALL THE REST OF THE CODE IS JUST TO CREATE A GOOD ERROR MESSAGE        ;;
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    invalid:
        ; So we first did a fast check above but now that it failed and has
        ; produced an error we can take our time to do thing more accurately.

        ; Log what failed to match
        ; local thing_to_check_str
        ; arrange thing_to_check_str, thing_to_check
        ; stringify thing_to_check_str
        ; display '`' bappend thing_to_check_str bappend '`' bappend \
        ;     ' does not match any valid instruction.' bappend 10

        ; Make strings available for all arguments.
        loc_arr_str  inst_str,  inst
        loc_arr_com  size_str,  =m68k.=size_to_str.size
        loc_arr_com  op1_str,   =m68k.=op_type_to_str.op1
        loc_arr_com  op2_str,   =m68k.=op_type_to_str.op2
        loc_com      inst_size_str,  '`' bappend inst_str bappend \
                                     size_str bappend '`'

        ; So `inst.size.op1.op2` failed, I want to check if this combo would
        ; work any other sizes and inform the user of the sizes that would be
        ; valid.

        ; Loop through all sizes (b, w, l, _) and collect which ones would be
        ; valid (if any).

        local sizes_that_would_be_valid
        local tmp
    reset:
        take , sizes_that_would_be_valid ; reset/empty sizes_that_would_be_valid
        jyes reset

        arrange thing_to_check, =m68k.=valid_instructions.inst.=_.op1.op2
        check defined thing_to_check
        jno skip__
        arrange tmp, =_
        take sizes_that_would_be_valid, tmp
    skip__:
        arrange thing_to_check, =m68k.=valid_instructions.inst.=l.op1.op2
        check defined thing_to_check
        jno skip_l
        arrange tmp, =l
        take sizes_that_would_be_valid, tmp
    skip_l:
        arrange thing_to_check, =m68k.=valid_instructions.inst.=w.op1.op2
        check defined thing_to_check
        jno skip_w
        arrange tmp, =w
        take sizes_that_would_be_valid, tmp
    skip_w:
        arrange thing_to_check, =m68k.=valid_instructions.inst.=b.op1.op2
        check defined thing_to_check
        jno skip_b
        arrange tmp, =b
        take sizes_that_would_be_valid, tmp
    skip_b:

        local valid_sizes_str
        compute valid_sizes_str, ""
        ; TODO: Loop through sizes_that_would_be_valid with `take`
        take sizes_that_would_be_valid, sizes_that_would_be_valid
        jno invalid_for_all_sizes
        take tmp, sizes_that_would_be_valid
        stringify tmp
        compute valid_sizes_str, '. Try .' bappend tmp
    valid_sizes_loop:
        take tmp, sizes_that_would_be_valid
        jno done_valid_sizes_loop
        stringify tmp
        compute valid_sizes_str, valid_sizes_str bappend ', .' bappend tmp
        jump valid_sizes_loop
    done_valid_sizes_loop:
        compute valid_sizes_str, valid_sizes_str bappend ' instead'

    invalid_for_all_sizes:
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
            op1_str bappend '`' bappend valid_sizes_str
    op2:
        ; TODO: This can be a bit misleading.
        nice_err inst_size_str bappend \
            " does not support a 2nd operand with type `" bappend \
            op2_str bappend '`' bappend valid_sizes_str
end calminstruction