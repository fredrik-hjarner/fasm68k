;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; PARSE_OPERAND                                                              ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; TODO: Comment this. It's not completely a hack but it is not obvious what this
; is really. I was needed to set the `ext_bytes` to the correct value when the
; operande is an immediate.
define m68k.instr_size_to_imm_size
namespace m68k.instr_size_to_imm_size
    define b 2
    define w 2
    define l 4
end namespace

; Define variable/namespace where parse_operand will store its results,
; for example @op1.type
; Use parse_operand by suffixing it will either @op1 or @op2 like this:
;     parse_operand@op1 some_operand_to_parse
define @op1 @op1
define @op2 @op2

iterate op, @op1,@op2
    namespace op
        ;; Define values in the @op1 and @op2 namespaces. ;;;;;;;;;;;;;;;;;;;;;;

        ; TODO: I really ought to make it is a bit nicer for the user get info
        ;       about the operands, so go through this code again and see if
        ;       variables needs to be added or change names.

        ; TODO: use these instead:
        ;     Dn  An  (An)  (An)+  ‑(An)  (d,An)  (d,An,Xi)  ABS.W  ABS.L  (d,PC)  (d,PC,Xn)  imm
        ; type:
        ;     'unknown'         (default. may indicate error)
        ;     'dn'              (direct data register addressing)
        ;     'an'              (direct address register addressing)
        ;     '(an)'            (indirect address register addressing)
        ;     '-(an)'
        ;     '(an)+'
        ;     'abs.w'           (absolute word addressing)
        ;     'abs.l'           (absolute long addressing)
        ;     'imm'             (immediate addressing)
        ;     'pc'
        ;     'sr'
        ;     'ccr'
        ;     'usp'
        ;     'label'           (label. this might be stange, dunno)
        define type

        ; TODO: Comment.
        ; 3 bits. 000b to 111b.
        ; type:
        ;     'unknown'         (default. may indicate error)
        ;     000b              dn
        ;     001b              an
        ;     010b              (an)
        ;     011b              (an)+
        ;     100b              -(an)
        ;     101b              (d,an)
        ;     110b              (d,an,Xn)
        ;     111b              (d,pc)
        ;     111b              (d,pc,Xn)
        ;     111b              abs.w
        ;     111b              abs.l
        ;     111b              imm
        define ea_mode_bits

        ; The number of the register.
        ; 3 bits. 000b to 111b.
        define ea_reg_bits

        ; The number of extension words,
        ; but I changed it to bytes because then I don't have to multiply
        ; by 2 when I output the extension words.
        define ext_bytes

        ; Either 16 or 32 bits i.e. 1 or 2 extension words,
        ; but I changed it to bytes because then I don't have to multiply
        ; by 2 when I output the extension words.
        define ext_bytes_bits

        ; The value of the immediate operand.
        define imm ; TODO: Think about this.

        ; abs_size:
        ;     'unknown'         (default. may indicate error)
        ;     'w'               (absolute word addressing)
        ;     'l'               (absolute long addressing)
        ; define abs_size ; TODO I propbably don't need this?

        ; TODO: Probably change name to `parse_effective_address`,
        ; but I am not sure that's a good idea or not because maybe this
        ; could be used for dn, an etc too.
        ;
        ; The `instr_size` argument is needed to set `ext_bytes` to the correct
        ; value for immediate values (when the official syntax specifies <ea>).
        calminstruction m68k.parse_operand#op operand*, instr_size
                    local tmp
                    local opstr
                    local maybe_number
                    local maybe_abs

                    ; stringify operand so I can print it to debug.
                    arrange opstr, operand
                    stringify opstr
                    ; display opstr bappend 9

                    ; default values
                    compute type, 'unknown'    ; TODO: Better default value?
                    compute ea_mode_bits, 123d ; TODO: Better default value?
                    compute ea_reg_bits,  123d ; TODO: Better default value?
                    compute ext_bytes, 0       ; TODO: Better default value?
                    compute ext_bytes_bits, 0  ; TODO: Better default value?
                    compute imm, 0             ; TODO: Better default value?

            ;; (an) ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            ; check_if_indirect_an:
                    match (an), operand
                    jno check_if_minus_an
                    check an relativeto m68k.address_reg
                    jno check_if_minus_an
                    compute type, '(an)'
                    compute ea_mode_bits, 010b
                    compute ea_reg_bits, 0 scaleof an
                    jump done
            ; -(an) ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            check_if_minus_an:
                    match -(an), operand
                    jno check_if_plus_an
                    check an relativeto m68k.address_reg
                    jno check_if_plus_an
                    compute type, '-(an)'
                    compute ea_mode_bits, 100b
                    compute ea_reg_bits, 0 scaleof an
                    jump done
            ; (an)+ ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            check_if_plus_an:
                    match (an)+, operand
                    jno check_if_immediate
                    check an relativeto m68k.address_reg
                    jno check_if_immediate
                    compute type, '(an)+'
                    compute ea_mode_bits, 011b
                    compute ea_reg_bits, 0 scaleof an
                    jump done
            ;; imm ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            ; TODO: Immediate can have either 1 or 2 extension words!
            check_if_immediate:
                    match =# maybe_number, operand, ()
                    jno check_if_abs_w
                ; hash_prefix:
                    ; fasmg uses shl instead of <<
                    ; TODO: There may be more of these cases that can be fixed!
                    replace_legacy_operators maybe_number

                    check maybe_number eqtype 0
                    jyes skip_immediate_addressing_error
                    ; test as string instead as fallback
                    check maybe_number eqtype ''
                    jno is_not_string
                ; is_string:
                    local str_len
                    ; reverse the string otherwise it will be emitted in
                    ; reverse order.
                    compute str_len, lengthof maybe_number
                    compute maybe_number, maybe_number bswap str_len
                    compute maybe_number, +maybe_number
                    jump skip_immediate_addressing_error
                is_not_string:
                    err 'immediate_addressing_error' ; TODO: better err message.
                skip_immediate_addressing_error:
                    compute type, 'imm'
                    compute ea_mode_bits, 111b
                    compute ea_reg_bits, 100b
                    compute imm, maybe_number
                    compute ext_bytes, 2 ; TODO: Assumes 2 but could also be 4!!
                    compute ext_bytes_bits, imm

                    ; If instr_size is empty (optional argument) then ext_bytes
                    ; will have it's default value 0 (or 2 when imm), which is
                    ; think might be good. The way fasmg works is  that
                    ; `emit 0, n` throws an error when n is not 0, so in order
                    ; words trying to output "immediate extension words" will
                    ; only succeed if instr_size is not empty, I think that will
                    ; work with how 68000 instructions tend to work...
                    match , instr_size
                    jyes empty_instr_size
                    arrange tmp, instr_size
                    transform tmp, m68k.instr_size_to_imm_size
                    ; stringify tmp
                    ; display tmp bappend 10 bappend 10 bappend 10
                    jyes skip_invalid_size_err
                    err 'Invalid size'
                skip_invalid_size_err:
                    compute tmp, tmp
                    ; So yea, how ext_bytes is set for immediate values is a bit
                    ; complicated...
                    compute ext_bytes, tmp

                empty_instr_size:

                    jump done
            ;; abs.w ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            check_if_abs_w:
                    match maybe_abs.=w, operand, ()
                    jno check_if_abs_l
                    check maybe_abs relativeto 0
                    jno check_if_abs_l
                    compute type, 'abs.w'
                    compute ea_mode_bits, 111b
                    compute ea_reg_bits, 000b
                    compute ext_bytes, 2
                    ; Warn if maybe_abs is too large then truncate.
                    ; TODO: actually, maybe I need to check if too negative too?
                    check maybe_abs > (1 shl 16 - 1)
                    jno skip_constrain_abs_w
                ; too_large:
                    display 'Warning: abs.w too large to fit in word.' bappend 10
                    compute maybe_abs, 1 shl 16 - 1
                skip_constrain_abs_w:
                    compute ext_bytes_bits, maybe_abs
                    jump done
            ;; abs.l ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            check_if_abs_l:
                    match maybe_abs.=l, operand, ()
                    jno check_if_dn
                    check maybe_abs relativeto 0
                    jno check_if_dn
                    compute type, 'abs.l'
                    compute ea_mode_bits, 111b
                    compute ea_reg_bits, 001b
                    compute ext_bytes, 4
                    ; Warn if maybe_abs is too large then truncate.
                    ; TODO: actually, maybe I need to check if too negative too?
                    check maybe_abs > (1 shl 32 - 1)
                    jno skip_constrain_abs_l
                ; too_large:
                    display 'Warning: abs.l too large to fit in longword.' bappend 10
                    compute maybe_abs, 1 shl 32 - 1
                skip_constrain_abs_l:
                    compute ext_bytes_bits, maybe_abs
                    jump done
            ;; Check if `dn` (direct data register addressing) ;;;;;;;;;;;;;;;;;
            check_if_dn:
                    call m68k.is_one_token, operand
                    jnope check_if_an
                    check operand relativeto m68k.data_reg
                    jno check_if_an
                    compute type, 'dn'
                    compute ea_mode_bits, 000b
                    compute ea_reg_bits, operand - m68k.data_reg
                    ; compute ext_bytes, 0
                    ; compute ext_bytes_bits, 0
                    jump done
            ;; Check if `an` (direct address register addressing) ;;;;;;;;;;;;;;
            check_if_an:
                    call m68k.is_one_token, operand
                    jnope sr
                    check operand relativeto m68k.address_reg
                    jno sr
                    compute type, 'an'
                    compute ea_mode_bits, 001b
                    compute ea_reg_bits, operand - m68k.address_reg
                    ; compute ext_bytes, 0
                    ; compute ext_bytes_bits, 0
                    jump done
            ;; label ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            ; TODO: Can labels be both .w and and .l?
            ; TODO: Do I need this or is abs.w and abs.l enough??
            ; label_w:
            ;         match (tmp).=w, operand
            ;         jno done
            ;         ; I have added an is_label property to each label.
            ;         arrange tmp, tmp.=is_label
            ;         check defined tmp
            ;         jno done
            ;         compute type, 'label'
            ;         jump done
            ;; sr ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            sr:
                    call m68k.is_one_token, operand
                    jnope ccr
                    ; TODO: Is it dumb to use relativeto here? equal better?
                    check operand relativeto sr
                    jno ccr
                    compute type, 'sr'
                    jump done
            ;; ccr ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            ccr:
                    call m68k.is_one_token, operand
                    jnope usp
                    ; TODO: Is it dumb to use relativeto here? equal better?
                    check operand relativeto ccr
                    jno usp
                    compute type, 'ccr'
                    jump done
            ;; usp ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            usp:
                    call m68k.is_one_token, operand
                    jnope check_indirect_displacement
                    ; TODO: Is it dumb to use relativeto here? equal better?
                    check operand relativeto usp
                    jno check_indirect_displacement
                    compute type, 'usp'
                    jump done
            ;; (d,an) a.k.a. d(an) - indirect address with displacement ;;;;;;;;
            check_indirect_displacement:
                    call m68k.parse_indirect_displacement, operand
                    jnope check_pc_displacement
                    compute type, '(d,an)'
                    compute ea_mode_bits, 101b
                    compute ea_reg_bits, 0 scaleof m68k.ret_reg
                    compute ext_bytes, 2
                    compute ext_bytes_bits, m68k.ret_imm
                    jump done
            ;; (d,pc) a.k.a. d(pc) - program counter with displacement ;;;;;;;;;
            check_pc_displacement:
                    call m68k.parse_pc_displacement, operand
                    jnope check_pc_index
                    compute type, '(d,pc)'
                    compute ea_mode_bits, 111b
                    compute ea_reg_bits, 010b
                    compute ext_bytes, 2
                    ; This stuff is because the d(pc) is relative to the
                    ; operands own extension words is, and the previous operand
                    ; could have added extension words so that why that has to
                    ; be subtracted.
                    ; some instructions swap the order of the
                    ; arguments so it's complicated.
                    ; I add the element `pc` to it so that it's value can be
                    ; "evaluated/computed" later (in emit_ext_words). Since
                    ; emit_ext_words will probabaly be executed when the code
                    ; "knows" how many extension words into the instruction we
                    ; are this will work.
                    ; TODO: I could prolly do this in a better/nice way
                    ; such as store old $ in a variable somewhere maybe.
                    ; compute ext_bytes_bits, $*pc + m68k.ret_imm
                    ; TODO: There's a bug lurking here where imm/displacement
                    ;       is to big, but if it's too big or not can not be
                    ;       known here in the code, there has to be a check
                    ;       later when the extension words are emitted.
                    ; TODO: I should remove  m68k.ret_imm and return data
                    ;       in the same way `parse_pc_index` does.
                    compute ext_bytes_bits, pc_displacement * m68k.ret_imm
                    jump done
            ;; (d,pc,xn.[wl]) a.k.a. d(pc,xn.[wl]) - program conter with index ;
            check_pc_index:
                    call m68k.parse_pc_index, operand
                    check m68k.parse_pc_index_result.is_pc_index = 1
                    jno check_memory_index
                    compute type, '(d,pc,xn)'
                    compute ea_mode_bits, 111b
                    compute ea_reg_bits, 011b
                    compute ext_bytes, 2
                    ; This stuff is because the d(pc) is relative to the
                    ; operands own extension words is, and the previous operand
                    ; could have added extension words so that why that has to
                    ; be subtracted.
                    ; some instructions swap the order of the
                    ; arguments so it's complicated.
                    ; How I solved it is by storing both the current $
                    ; and also add a `pc` element to `ext_bytes_bits`.
                    ; `$*pc` is a "decoration" that is evaulated later
                    ; see `emit_ext_words` function.
                    ; TODO: I could prolly do this in a better/nice way
                    ; such as store old $ in a variable somewhere maybe.
                    ; TODO: m68k.ret_imm? that might be a bad name...
                    ; TODO: There's a bug lurking here where imm/displacement
                    ;       is to big, but if it's too big or not can not be
                    ;       known here in the code, there has to be a check
                    ;       later when the extension words are emitted.
                    ; TODO: Maybe I could do this computation in
                    ;       `parse_pc_index` and so on with the rest of the
                    ;       functions.
                    compute ext_bytes_bits, \
                        m68k.parse_pc_index_result.m shl 15 + \
                        m68k.parse_pc_index_result.xn shl 12 + \
                        m68k.parse_pc_index_result.s shl 11 + \
                        m68k.parse_pc_index_result.d * pc_index
                    jump done
            ;; (d,an,xn.[wl]) a.k.a. d(an,xn.[wl]) - Address Register Indirect with Index ;
            check_memory_index:
                    call m68k.parse_mem_index, operand
                    check m68k.parse_mem_index_result.is_mem_index = 1
                    jno unknown
                    compute type, '(d,an,xn)'
                    compute ea_mode_bits, 110b
                    compute ea_reg_bits, m68k.parse_mem_index_result.an
                    compute ext_bytes, 2
                    ; TODO: The displacement could only be max one byte
                    ;       and I should validate that.
                    compute ext_bytes_bits, \
                        m68k.parse_mem_index_result.m shl 15 + \
                        m68k.parse_mem_index_result.xn shl 12 + \
                        m68k.parse_mem_index_result.s shl 11 + \
                        m68k.parse_mem_index_result.d
                    jump done
            ;; Temporary stuff ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            unknown:
                    err 'Failed to parse operand'
                    ; compute type, 'unknown'
                    ; display 'unknown' bappend 10
                    exit
            ;; Post-processing kind of ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            ; done: ; commented out to skip logging
                    ;; header ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

                    display 'op' bappend 9
                    display 'type' bappend 9
                    display 'mode' bappend 9
                    display 'reg' bappend 9
                    display '#ext' bappend 10

                    ;; data ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

                    display opstr bappend 9

                    ; log type
                    display type bappend 9

                    ; log ea_mode_bits
                    arrange tmp, ea_mode_bits
                    stringify tmp
                    display tmp bappend 9

                    ; log ea_reg_bits
                    arrange tmp, ea_reg_bits
                    stringify tmp
                    display tmp bappend 9

                    ; log ext_bytes
                    arrange tmp, ext_bytes
                    stringify tmp
                    display tmp bappend 9

                    ; log ext_bytes_bits
                    ; arrange can't handle negative numbers!
                    ; TODO: I should make a helper to support negative numbers.
                    ; TODO: I could really clean this up.
                    ; TODO: I commented out logging ext_bytes_bits since my
                    ;       pc relative fix with pc element has broken the
                    ;       logging.
                ;     check ext_bytes_bits < 0
                ;     jyes skip_log_ext_bytes_bits
                ; ; log_ext_bytes_bits:
                ;     arrange tmp, ext_bytes_bits
                ;     stringify tmp
                ;     display 'ext_bytes_bits: ' bappend tmp bappend 9
                ;     jump done_ext_bytes_bits
                ; skip_log_ext_bytes_bits:
                    ; display 'ext_bytes_bits: ' bappend 'neg' bappend 9
                done_ext_bytes_bits:

                    ; log imm
                    ; arrange can't handle negative numbers!
                    ; TODO: I should make a helper to support negative numbers.
                    check imm < 0
                    jyes skip_log_imm
                ; log_imm:
                    arrange tmp, imm
                    stringify tmp
                    display 'imm: ' bappend tmp bappend 10
                    exit
                skip_log_imm:
                    display 10

                    exit
            done:
        end calminstruction

    end namespace
end iterate

;; SPLIT_OPERANDS ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; TODO: Comment. Look at comment on the commented out function above.
define m68k.split_operands_result
namespace m68k.split_operands_result
    define num_operands
    define op1
    define op2
end namespace

; Supposed to be called.
; TODO: Maybe it's better to add @op1.tokens and @op2.tokens to hold the
;       tokens of the operands?
calminstruction m68k.split_operands? line&
        local op1, op2
        match op1 =, op2, line, ()
        jyes two_operands
    ; one_operand:
        call m68k.parse_operand@op1, line
        compute m68k.split_operands_result.num_operands, 1
        arrange m68k.split_operands_result.op1, line
        exit
    two_operands:
        compute m68k.split_operands_result.num_operands, 2
        arrange m68k.split_operands_result.op1, op1
        arrange m68k.split_operands_result.op2, op2
end calminstruction