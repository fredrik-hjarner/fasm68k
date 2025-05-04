; Supposed to be called
; Side-effects:
;     xxcalm.ret - 0 if false
;                  1 if true
calminstruction m68k.is_one_token? source_text*
    local a
    local b

    ; check_zero_tokens:
        match ,source_text
        jno check_more_than_one
        compute xxcalm.ret, 0
        exit
    check_more_than_one:
        match a b,source_text
        jno is_one_token
        compute xxcalm.ret, 0
        exit
    is_one_token:
        compute xxcalm.ret, 1
end calminstruction

; Some temporary vars where return values are stored
; TODO: Think if there is a better cleaner way of doing this.
;       These should probably be removed.
namespace m68k
    define ret_imm
    define ret_reg
end namespace

; Supposed to be called.
; Side-effects:
;     m68k.ret_imm
;     m68k.ret_reg
;     xxcalm.ret - 0 if false
;                  1 if true
calminstruction m68k.parse_indirect_displacement operand*
        local tmp1
        local tmp2

        match tmp1(tmp2), operand
        jyes next
        ; display 'matched tmp1(tmp2)' bappend 10
        jump nope
    next:
        call m68k.is_one_token, tmp1
        jyup next2
        ; display 'tmp1 is one token' bappend 10
        jump nope
    next2:
        call m68k.is_one_token, tmp2
        jyup next3
        ; display 'tmp2 is one token' bappend 10
        jump nope
    next3:
        check tmp1 eqtype 0 & tmp2 relativeto m68k.address_reg
        jno nope
        compute xxcalm.ret, 1
        ; display 10 bappend "INDIRECT_DISPLACEMENT" bappend 10 bappend 10
        ; TODO: What would the different be if I used `publish` here?
        compute m68k.ret_imm, tmp1
        arrange m68k.ret_reg, tmp2
        exit
    nope:
        compute xxcalm.ret, 0
end calminstruction

;; PARSE_PC_DISPLACEMENT ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Supposed to be callable.
; Side-effects:
;     m68k.ret_imm
;     xxcalm.ret - 0 if false
;                  1 if true
; TODO: This is super-similar to parse_indirect_displacement. Examine if can
;       reduce code duplication or optimize performance.
calminstruction m68k.parse_pc_displacement operand*
        local tmp1
        local tmp2

        match tmp1(tmp2), operand
        jyes next
        ; display 'matched tmp1(tmp2)' bappend 10
        jump nope
    next:
        call m68k.is_one_token, tmp1
        jyup next2
        ; display 'tmp1 is one token' bappend 10
        jump nope
    next2:
        call m68k.is_one_token, tmp2
        jyup next3
        ; display 'tmp2 is one token' bappend 10
        jump nope
    next3:
        check tmp1 eqtype 0 & tmp2 eq pc
        jno nope
        compute xxcalm.ret, 1
        ; display 10 bappend PC DISPLACEMENT" bappend 10 bappend 10
        ; TODO: What would the different be if I used `publish` here?
        arrange m68k.ret_imm, tmp1
        exit
    nope:
        compute xxcalm.ret, 0
end calminstruction

;; PARSE_PC_INDEX ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; TODO: Maybe this is better so store return data in a namespace named by the
;       function?
define m68k.parse_pc_index_result
namespace m68k.parse_pc_index_result
    define is_pc_index ; 1 if operand is pc with index addressing mode, else 0
    ; m
    ;     0 if the register is a data register
    ;     1 if the register is an address register
    define m

    ; xn is the number of the register
    ; 000b - 111b i.e. 0 to 7
    define xn

    ; s
    ;     0 for word
    ;     1 for long
    define s

    ; Note: What is saved in d is actually not the displacement relative to the
    ; program counter but is the computed value of what the user put in to the
    ; operand (at the d location). The displacement relative to pc can't be
    ; computed here since we at this point don't know at which location in
    ; memory the `extension word` corresponding to this operand will be located.
    ; Just to clafify:
    ;     On Motorola 68000 opcodes the encoded value is not relative to the
    ;     address that the instruction is located at but it is encoded as the
    ;     relative displacement in relation to where the `extension word` is
    ;     located. This is what makes pc relative addressing a bit more
    ;     complicated to encode.
    define d
end namespace

; TODO: Update and correct comment.
; Supposed to be called.
calminstruction m68k.parse_pc_index operand*
        local tmp
        local tmp1 ; TODO: remove?
        local tmp2 ; TODO: remove?
        local opstr

        ; display 'parse_pc_index' bappend 10
        arrange opstr, operand
        stringify opstr
        ; display 'operand: ' bappend opstr bappend 10

        local d
        local _pc
        local xn
        local s

        ; Init default values
        compute m68k.parse_pc_index_result.is_pc_index, 0
        compute m68k.parse_pc_index_result.m,           0
        compute m68k.parse_pc_index_result.xn,          0
        compute m68k.parse_pc_index_result.s,           0
        compute m68k.parse_pc_index_result.d,           0

        match d(_pc=,xn.s), operand
        jno nope
        ; display 'matched d(pc,xn.s)' bappend 10

        ; TODO: Actually it could be several tokens such as in `$123` (seems #$123 is not valid format)
        ; That's computable anyway i.e. d should be computable into a number.
    ; validate_d_is_one_token:
        compute d, d
        ; match tmp1 tmp2, d
        ; jyes nope
        ; arrange tmp, d
        ; stringify tmp
        ; display 'd `' bappend tmp bappend '` is one token' bappend 10

    ; validate_pc_is_one_token:
    ; TODO: I could probably remove this check
        match tmp1 tmp2, _pc
        jyes nope
        ; display 'pc is one token' bappend 10

    ; validate_xn_is_one_token:
    ; TODO: I could probably remove this check
        match tmp1 tmp2, xn
        jyes nope
        ; display 'xn is one token' bappend 10

    ; validate_s_is_one_token:
    ; TODO: I could probably remove this check
        match tmp1 tmp2, s
        jyes nope
        ; display 's is one token' bappend 10
        stringify s
        ; display "s: " bappend s bappend 10

        check d eqtype 0 & _pc eq pc & (xn relativeto m68k.data_reg | xn relativeto m68k.address_reg) & (s = 'w' | s = 'l')
        jno nope
        ; compute xxcalm.ret, 1
        ; ; display 10 bappend PC DISPLACEMENT" bappend 10 bappend 10
        ; ; TODO: What would the different be if I used `publish` here?
        ; arrange m68k.ret_imm, tmp1

        check xn relativeto m68k.address_reg
        jno skip ; TODO: better label name
        compute m68k.parse_pc_index_result.m, 1
        jump skip2 ; TODO: better label name
    skip:
        compute m, 0
    skip2:

    ; set_size_bit
        check s = 'l'
        jno skip3 ; TODO: better label name
        compute m68k.parse_pc_index_result.s, 1
    skip3:

        ; return result
        compute m68k.parse_pc_index_result.is_pc_index, 1
        compute m68k.parse_pc_index_result.xn,          0 scaleof xn
        compute m68k.parse_pc_index_result.d,           d

        ; display opstr bappend ' matched d(pc,xn.s)' bappend 10
        exit
    nope:
        ; display opstr bappend ' did NOT match d(pc,xn.s)' bappend 10
end calminstruction

;; PARSE_MEM_INDEX ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; TODO: Maybe this is better so store return data in a namespace named by the
;       function?
define m68k.parse_mem_index_result
namespace m68k.parse_mem_index_result
    define is_mem_index ; 1 if operand is pc with index addressing mode, else 0
    ; m
    ;     0 if the register is a data register
    ;     1 if the register is an address register
    define m

    ; xn is the number of the register
    ; 000b - 111b i.e. 0 to 7
    define xn

    ; s
    ;     0 for word
    ;     1 for long
    define s

    ; Note: What is saved in d is actually not the displacement relative to the
    ; program counter but is the computed value of what the user put in to the
    ; operand (at the d location). The displacement relative to pc can't be
    ; computed here since we at this point don't know at which location in
    ; memory the `extension word` corresponding to this operand will be located.
    ; Just to clafify:
    ;     On Motorola 68000 opcodes the encoded value is not relative to the
    ;     address that the instruction is located at but it is encoded as the
    ;     relative displacement in relation to where the `extension word` is
    ;     located. This is what makes pc relative addressing a bit more
    ;     complicated to encode.
    define d
end namespace

; TODO: Update and corret comment.
; Supposed to be callable.
calminstruction m68k.parse_mem_index operand*
        local tmp
        local tmp1 ; TODO: remove?
        local tmp2 ; TODO: remove?
        local opstr

        ; display 'parse_mem_index' bappend 10
        arrange opstr, operand
        stringify opstr
        ; display 'operand: ' bappend opstr bappend 10

        local d
        local an
        local xn
        local s

        ; Init default values
        compute m68k.parse_mem_index_result.is_pc_index, 0
        compute m68k.parse_mem_index_result.m,           0
        compute m68k.parse_mem_index_result.an,          0
        compute m68k.parse_mem_index_result.xn,          0
        compute m68k.parse_mem_index_result.s,           0
        compute m68k.parse_mem_index_result.d,           0

        match d(an=,xn.s), operand
        jno nope
        ; display 'matched d(an,xn.s)' bappend 10

        ; TODO: Actually it could be several tokens such as in `$123` (seems #$123 is not valid format)
        ; That's computable anyway i.e. d should be computable into a number.
    ; validate_d_is_one_token:
        compute d, d
        ; match tmp1 tmp2, d
        ; jyes nope
        ; arrange tmp, d
        ; stringify tmp
        ; display 'd `' bappend tmp bappend '` is one token' bappend 10

    ; validate_pc_is_one_token:
    ; TODO: I could probably remove this check
        match tmp1 tmp2, an
        jyes nope
        ; display 'an is one token' bappend 10

    ; validate_xn_is_one_token:
    ; TODO: I could probably remove this check
        match tmp1 tmp2, xn
        jyes nope
        ; display 'xn is one token' bappend 10

    ; validate_s_is_one_token:
    ; TODO: I could probably remove this check
        match tmp1 tmp2, s
        jyes nope
        ; display 's is one token' bappend 10
        stringify s
        ; display "s: " bappend s bappend 10

        check d eqtype 0 & an relativeto m68k.address_reg & \
              (xn relativeto m68k.data_reg | xn relativeto m68k.address_reg) & \
              (s = 'w' | s = 'l')
        jno nope
        ; compute xxcalm.ret, 1
        ; ; display 10 bappend PC DISPLACEMENT" bappend 10 bappend 10
        ; ; TODO: What would the different be if I used `publish` here?
        ; arrange m68k.ret_imm, tmp1

        check xn relativeto m68k.address_reg
        jno skip ; TODO: better label name
        compute m68k.parse_mem_index_result.m, 1
        jump skip2 ; TODO: better label name
    skip:
        compute m, 0
    skip2:

    ; set_size_bit
        check s = 'l'
        jno skip3 ; TODO: better label name
        compute m68k.parse_mem_index_result.s, 1
    skip3:

        ; return result
        compute m68k.parse_mem_index_result.is_mem_index, 1
        compute m68k.parse_mem_index_result.an,           0 scaleof an
        compute m68k.parse_mem_index_result.xn,           0 scaleof xn
        compute m68k.parse_mem_index_result.d,            d

        ; display opstr bappend ' matched d(an,xn.s)' bappend 10
        exit
    nope:
        ; display opstr bappend ' did NOT match d(an,xn.s)' bappend 10
end calminstruction
