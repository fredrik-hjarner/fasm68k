;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; PARSE_OPERAND                                                              ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; TODO: Comment this. It's not completely a hack but it is not obvious what this
; is really. I was needed to set the `ext_bytes` to the correct value when the
; operande is an immediate.
define m68k.instr_size_to_imm_size
namespace m68k.instr_size_to_imm_size
    define b? 2
    define w? 2
    define l? 4
    define _? 2 ; TODO: This is not well-thought out. Rethink size related stuff
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

        ; TODO: I really ought to make it is a bit nicer for the user get to
        ;       info about the operands, so go through this code again and see
        ;       if variables needs to be added or change names.

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
        ; TODO: So I noted that I need the type (above) in the form of a token
        ;       also, so I just slapped `type_token` here. Honestly, I should
        ;       probably replace the current `type` that is a string with this
        ;       `type_token` instead. Seems it is quite common that tokens are
        ;       better to store and work with than strings.
        ; `type_token` has other values, for now see the
        ;       `instruction_validation_structure.inc` file.
        define type_token

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

        ;
        include "parsing/parse_complex_operand.inc"

        ; The `instr_size` argument is needed to set `ext_bytes` to the correct
        ;     value for immediate values (when the official syntax specifies
        ;     <ea>).
        ; TODO: I will probably need another size argument that I can use to
        ;       check whether odd addresses should be allowed in `absolute
        ;       adddressing`.
        calminstruction m68k.parse_operand#op operand*, instr_size
                    local tmp
                    local tmp2
                    local opstr
                    local maybe_number
                    local maybe_abs

                    ; stringify operand so I can print it to debug.
                    ; arrange opstr, operand
                    ; stringify opstr
                    ; display opstr bappend 9

                    ; default values
                    compute type, 'unknown'    ; TODO: Better default value?
                    arrange type_token, =_     ; TODO: Better default value?
                    ; compute ea_mode_bits, 123d ; TODO: Better default value?
                    ; compute ea_reg_bits,  123d ; TODO: Better default value?
                    compute ext_bytes, 0       ; TODO: Better default value?
                    compute ext_bytes_bits, 0  ; TODO: Better default value?
                    ; compute imm, 0             ; TODO: Better default value?

            ;; check if empty ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                    ; If split operands only finds one argument then the other
                    ; argumnt will be empty, which is perfectly valid since some
                    ; instructions only have one operand.
                    match ,operand
                    jyes done
            ;; imm ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                    ; parse_immediate need the operand to be "untransformed"
                    ; so that the `#` is not transformed away.
                    parse_immediate operand
                    ; This is needed for example if the user has made
                    ; an alias for `sr` with `define status_register sr`
                    full_transform operand
            ;; (an) ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                    parse_indirect_an operand
            ; -(an) ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                    parse_indirect_pre_decr operand
            ; (an)+ ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                    parse_indirect_post_incr operand
            ;; abs.w ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            check_if_abs_w:
                    match maybe_abs.=w, operand
                    jyes has_w_suffix
                    match maybe_abs.=W, operand
                    jno check_if_abs_l
                has_w_suffix:
                    massage_expression maybe_abs
                    check maybe_abs relativeto 0
                    jno check_if_abs_l
                    ; TODO:  also assert that the address is word-aligned
                    ; call m68k.warn_if_abs_address_is_odd, maybe_abs, instr_size
                    compute type, 'abs.w'
                    arrange type_token, =abs_w
                    compute ea_mode_bits, 111b
                    compute ea_reg_bits, 000b
                    compute ext_bytes, 2
                    ; Warn if maybe_abs is too large then truncate.
                    ; TODO: actually, maybe I need to check if too negative too?
                    check maybe_abs > (1 shl 16 - 1)
                    jno skip_constrain_abs_w
                ; too_large:
                    diag_absolute_too_big 'abs.w too large to fit in word.'
                    compute maybe_abs, maybe_abs and $FFFF
                skip_constrain_abs_w:
                    compute ext_bytes_bits, maybe_abs
                    jump done
            ;; abs.l ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            check_if_abs_l:
                    match maybe_abs.=l, operand
                    jyes has_l_suffix
                    match maybe_abs.=L, operand
                    jno check_one_token_operands
                has_l_suffix:
                    massage_expression maybe_abs
                    check maybe_abs relativeto 0
                    jno check_one_token_operands
                    ; TODO: also assert that the address is word-aligned
                    ; call m68k.warn_if_abs_address_is_odd, maybe_abs, instr_size
                    compute type, 'abs.l'
                    arrange type_token, =abs_l
                    compute ea_mode_bits, 111b
                    compute ea_reg_bits, 001b
                    compute ext_bytes, 4
                    ; Warn if maybe_abs is too large then truncate.
                    ; TODO: actually, maybe I need to check if too negative too?
                    check maybe_abs > (1 shl 32 - 1)
                    jno skip_constrain_abs_l
                ; too_large:
                    diag_absolute_too_big 'abs.l too large to fit in longword.'
                    compute maybe_abs, maybe_abs and $FFFFFFFF
                skip_constrain_abs_l:
                    compute ext_bytes_bits, maybe_abs
                    jump done
            check_one_token_operands:
                    local tmp1, tmp2
                    match tmp1 tmp2, operand
                    jyes check_complex_operand
            ; is_one_token:
            ; dn:
                    check operand relativeto m68k.data_reg
                    jno an
                    compute type, 'dn'
                    arrange type_token, =dn
                    compute ea_mode_bits, 000b
                    compute ea_reg_bits, 0 scaleof operand
                    exit
            an:
                    check operand relativeto m68k.address_reg
                    jno sr
                    compute type, 'an'
                    arrange type_token, =an
                    compute ea_mode_bits, 001b
                    compute ea_reg_bits, 0 scaleof operand
                    exit
            sr:
                    check operand relativeto sr
                    jno ccr
                    compute type, 'sr'
                    arrange type_token, =sr
                    exit
            ccr:
                    check operand relativeto ccr
                    jno usp
                    compute type, 'ccr'
                    arrange type_token, =ccr
                    exit
            usp:
                    check operand relativeto usp
                    jno check_complex_operand
                    compute type, 'usp'
                    arrange type_token, =usp
                    exit
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
            check_complex_operand:
                    call m68k.parse_complex_operand#op, operand
                    check parse_complex_operand_ret = 1
                    jyes done
            ;; Check for "abs" again
            ; I think this case will cover labels because I don't think labels
            ;     usually have a size suffix... might need to double check this.
            check_abs_without_size_suffix:
                    massage_expression operand
                    ; TODO: Possibly refactor this. Reason I check for absolute
                    ;       addressing at two places is because the 1st place
                    ;       checks for `($1).w `($1).l` while and here I check
                    ;       for `$1`.
                    check operand relativeto 0
                    jno unknown
                    ; Warn if maybe_abs is too large then truncate.
                    ; TODO: actually, maybe I need to check if too negative too?
                    check operand > (1 shl 32 - 1)
                    jno skip_constrain_abs
                ; too_large:
                    diag_absolute_too_big 'abs.l too large to fit in longword.'
                    compute operand, operand and $FFFFFFFF
                skip_constrain_abs:
                    ; TODO: also assert that the address is word-aligned
                    ; call m68k.warn_if_abs_address_is_odd, operand, instr_size
                    compute type, 'abs.l'
                    arrange type_token, =abs_l
                    compute ea_mode_bits, 111b
                    compute ea_reg_bits, 001b
                    compute ext_bytes, 4
                    compute ext_bytes_bits, operand
                    jump done
            ;; Temporary stuff ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            unknown:
                    nice_err 10 bappend 'Failed to parse operand' bappend 10
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
                ; display 'type: ' bappend type bappend 10
        end calminstruction

    end namespace
end iterate

;; IMMEDIATE ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; TODO: Immediate can have either 1 or 2 extension words!
macro calminstruction?.parse_immediate? operand*
        new @is_not_string
        new @skip_immediate_addressing_error
        new @skip_invalid_size_err
        new @empty_instr_size
        new @next

        ; Note: `transform` would remove the leading `#` so operand must be
        ;       "untransformed".
        match =# maybe_number, operand
        @ jno @next
    ; hash_prefix:
        ; fasmg uses shl instead of <<
        ; TODO: There may be more of these cases that can be fixed!
        massage_expression maybe_number

        check maybe_number eqtype 0
        @ jyes @skip_immediate_addressing_error
        ; test as string instead as fallback
        check maybe_number eqtype ''
        @ jno @is_not_string
    ; is_string:
        local str_len
        ; reverse the string otherwise it will be emitted in
        ; reverse order.
        compute str_len, lengthof maybe_number
        compute maybe_number, maybe_number bswap str_len
        ; compute maybe_number, +maybe_number
        @ jump @skip_immediate_addressing_error
    @ @is_not_string:
        nice_err 'immediate_addressing_error' ; TODO: better err message.
    @ @skip_immediate_addressing_error:
        compute type, 'imm'
        arrange type_token, =imm
        compute ea_mode_bits, 111b
        compute ea_reg_bits, 100b
        compute imm, maybe_number
        compute ext_bytes, 2 ; TODO: Assumes 2 but could also be 4!!
        compute ext_bytes_bits, imm

        ; If instr_size is empty (optional argument) then ext_bytes
        ; will have it's default value 0 (or 2 when imm), which is
        ; think might be good. The way fasmg works is  that
        ; `emit_be 0, n` throws an error when n is not 0, so in order
        ; words trying to output "immediate extension words" will
        ; only succeed if instr_size is not empty, I think that will
        ; work with how 68000 instructions tend to work...
        match , instr_size
        @ jyes @empty_instr_size
        arrange tmp, instr_size
        transform tmp, m68k.instr_size_to_imm_size
        ; stringify tmp
        ; display tmp bappend 10 bappend 10 bappend 10
        @ jyes @skip_invalid_size_err
        nice_err 'Invalid size'
    @ @skip_invalid_size_err:
        ; So yea, how ext_bytes is set for immediate values is a bit
        ; complicated...
        compute ext_bytes, tmp
    @ @empty_instr_size:
        exit
    @ @next:
end macro

;; INDIRECT ADDRESSING ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; TODO: Try to make this into a "callable" insteadm maybe...
macro calminstruction?.parse_indirect_an? operand*
        new @next
        match (an), operand
        @ jno @next
        call m68k.is_one_token, an
        @ jnope @next
        check an relativeto m68k.address_reg
        @ jno @next
        compute type, '(an)'
        arrange type_token, =indir_an
        compute ea_mode_bits, 010b
        compute ea_reg_bits, 0 scaleof an
        exit
    @ @next:
end macro

;; INDIRECT ADDRESSING WITH PRE-DECREMENT ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

macro calminstruction?.parse_indirect_pre_decr? operand*
        new @next
        match -(an), operand
        @ jno @next
        ; check an relativeto m68k.address_reg
        ; @ jno @next
        compute type, '-(an)'
        arrange type_token, =an_pre_decr
        compute ea_mode_bits, 100b
        ; compute ea_reg_bits, 0 scaleof an
        compute ea_reg_bits, 0 scaleof an
        exit
    @ @next:
end macro

;; INDIRECT ADDRESSING WITH POST-INCREMENT ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

macro calminstruction?.parse_indirect_post_incr? operand*
        new @next
        match (an)+, operand
        @ jno @next
        ; check an relativeto m68k.address_reg
        ; @ jno @next
        compute type, '(an)+'
        arrange type_token, =an_post_incr
        compute ea_mode_bits, 011b
        ; compute ea_reg_bits, 0 scaleof an
        compute ea_reg_bits, 0 scaleof an
        exit
    @ @next:
end macro

;; SPLIT_OPERANDS ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; TODO: Comment. Look at comment on the commented out function above.
; TODO: Remove this, it will no longer be needed!
; TODO: Well... I still need to think about a way for the user to be able
;       to make use of the parsing stuff so they can use it in their own code.
define m68k.split_operands_result
namespace m68k.split_operands_result
    define op1
    define op2
end namespace

; Supposed to be called.
; TODO: Maybe it's better to add @op1.tokens and @op2.tokens to hold the
;       tokens of the operands? Yes That will also aid in making error messages
;       I think!
; TODO: This legacy `split_operands` is only used by `movem`, I'd like to
;       remove this eventually.
calminstruction m68k.split_operands? line&
        local op1, op2
        match op1 =, op2, line, ()
        jyes two_operands
    ; one_operand:
        arrange m68k.split_operands_result.op1, line
        arrange m68k.split_operands_result.op2,
        exit
    two_operands:
        arrange m68k.split_operands_result.op1, op1
        arrange m68k.split_operands_result.op2, op2
end calminstruction
; TODO: This is a refactoring of the function above to include more stuff.
; Remove the function above and replace with this one.
; TODO: Might be a bit unclear what `imm_size` is though it's related to how
;       maybe bytes an immediate will take up in an extention word I think...
calminstruction m68k.parse_and_validate_instruction? instr*, \
                                                     operands*, \
                                                     size_suffix, \
                                                     imm_size
        assert_word_aligned

        local op1, op2
        match op1 =, op2, operands, ()
        jyes two_operands
    ; one_operand:
        call m68k.parse_operand@op1, operands, imm_size
        arrange @op2.type_token, =_
        jump validate
    two_operands:
        call m68k.parse_operand@op1, op1, imm_size
        call m68k.parse_operand@op2, op2, imm_size
    validate:
        xcall validate, instr, size_suffix, @op1.type_token, @op2.type_token
end calminstruction

; supposed to be called
; TODO: Figure out how I am going to make this work.
;       The problem is that odd address are not allowed "unless" .b is used
;       for some or all instructions.
; calminstruction m68k.warn_if_abs_address_is_odd? address*, size_suffix*
;         match =b, size_suffix
;         local s_str
;         arrange s_str,  size_suffix
;         stringify s_str
;         display "s_str: " bappend s_str bappend 10
;         jyes valid_address
;         check address mod 2 = 1
;         jno valid_address
;         warn 'Address is odd but is required to be word-aligned.'
;     valid_address:
; end calminstruction