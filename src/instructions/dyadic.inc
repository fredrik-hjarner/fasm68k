;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Motorola 68000 dyadic instructions                                         ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; MOVEP ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Syntax:
;     movep dx,(d,ay)
;     movep (d,ay),dx
; Sample syntax:
;     movep d3,(control,a0)
;     movep (input,a6),d5
iterate <size,  size_bit>, \
        w,      0b, \
        l,      1b

    calminstruction movep.size? operands&
            assert_word_aligned

            local direction
            local reg_bits1
            local reg_bits2
            local ext_bytes
            local ext_bytes_bits

            call m68k.split_operands, operands
            call m68k.parse_operand@op1, m68k.split_operands_result.op1
            call m68k.parse_operand@op2, m68k.split_operands_result.op2

        ;; START - TESTING NEW VALIDATION ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

            ; TODO: So this is my first attempt at validating. WHat I want now
            ;       is to merge
            ;           split_operands, parse_operand(a) and validate
            ;       into a single function.
            xcall validate, <movep>, <size>, @op1.type_token, @op2.type_token

        ;; END  - TESTING NEW VALIDATION ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

            ; Initial default values
            compute direction, 1 ; Default is dn to (d,an)
            compute reg_bits1, @op1.ea_reg_bits ; Default is dn to (d,an)
            compute reg_bits2, @op2.ea_reg_bits ; Default is dn to (d,an)
            compute ext_bytes, @op2.ext_bytes   ; Default is dn to (d,an)
            compute ext_bytes_bits, @op2.ext_bytes_bits ;Default is dn to (d,an)

        ; check_direction:
            check @op2.type = 'dn'
            jno emit_bytes
            compute direction, 0
            compute reg_bits1, @op2.ea_reg_bits
            compute reg_bits2, @op1.ea_reg_bits
            compute ext_bytes, @op1.ext_bytes
            compute ext_bytes_bits, @op1.ext_bytes_bits
        emit_bytes:
            emit_be 1, 00000001b + reg_bits1 shl 1
            emit_be 1, direction shl 7 + size_bit shl 6 + 001b shl 3 + reg_bits2

            ; extension words
            call emit_ext_words, ext_bytes, ext_bytes_bits
    end calminstruction

end iterate ; <size, size_bit>

;; CMPM ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Syntax:
;     cmpm.[bwl] (ay)+,(ax)+
; Sample syntax:
;     cmpm.b (a3)+,(a4)+
iterate <size,  size_bits>, \
        b,      00b, \
        w,      01b, \
        l,      10b

    calminstruction cmpm.size? operands&
        assert_word_aligned

        call m68k.split_operands, operands
        call m68k.parse_operand@op1, m68k.split_operands_result.op1
        call m68k.parse_operand@op2, m68k.split_operands_result.op2

        emit_be 1, 10110001b + @op2.ea_reg_bits shl 1
        emit_be 1, size_bits shl 6 + 001b shl 3 + @op1.ea_reg_bits
    end calminstruction

end iterate ; <size, size_bits>

;; EXG ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Syntax:
;     exg.l reg,reg
; Sample syntax:
;     exg d3,d4
;     exg d2,a0
;     exg a7,d5
; Note that the encoding of the 3 M bits are not explained in:
;     http://goldencrystal.free.fr/M68kOpcodes-v2.3.pdf
calminstruction exg.l? operands&
            assert_word_aligned

            local type_bits1
            local type_bits2
            local reg1_bits
            local reg2_bits

            call m68k.split_operands, operands
            call m68k.parse_operand@op1, m68k.split_operands_result.op1
            call m68k.parse_operand@op2, m68k.split_operands_result.op2

            ; Init default values
            compute type_bits1, 01b ; default to dn,dn
            compute type_bits2, 0b  ; default to dn,dn
            compute reg1_bits,  @op1.ea_reg_bits ; default to dn,dn
            compute reg2_bits,  @op2.ea_reg_bits ; default to dn,dn

    ; check_dn_an:
            check @op1.type = 'dn' & @op2.type = 'an'
            jno check_an_an
            compute type_bits1, 10b
            compute type_bits2, 1b
            jump emit_bytes
    check_an_an:
            check @op1.type = 'an' & @op2.type = 'an'
            jno check_an_dn
            ; compute type_bits1, 01b
            compute type_bits2, 1b
            jump emit_bytes
    check_an_dn:
            ; seems `exg.l a7,d5` is encoded as `exg.l d5,a7`
            check @op1.type = 'an' & @op2.type = 'dn'
            jno emit_bytes
            compute type_bits1, 10b
            compute type_bits2, 1b
        ; exchange reg1 and reg2
            compute reg1_bits,  @op2.ea_reg_bits
            compute reg2_bits,  @op1.ea_reg_bits
    emit_bytes:
            emit_be 1, 11000001b + reg1_bits shl 1
            emit_be 1, type_bits1 shl 6 + type_bits2 shl 3 + reg2_bits
end calminstruction

;; CHK ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Syntax:
;     chk.w <ea>,dn
calminstruction chk.w? operands&
    assert_word_aligned

    call m68k.split_operands, operands
    call m68k.parse_operand@op1, m68k.split_operands_result.op1
    call m68k.parse_operand@op2, m68k.split_operands_result.op2

    emit_be 1, 01000001b + @op2.ea_reg_bits shl 1
    emit_be 1, 10000000b + @op1.ea_mode_bits shl 3 + @op1.ea_reg_bits

    ; <ea> extension words
    call emit_ext_words, @op1.ext_bytes, @op1.ext_bytes_bits
end calminstruction

;; LINK ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Syntax:
;     link.w an,#<displacement>
; Sample syntax:
;     link a6,#-12
calminstruction link.w? operands&
    assert_word_aligned

    call m68k.split_operands, operands
    call m68k.parse_operand@op1, m68k.split_operands_result.op1
    call m68k.parse_operand@op2, m68k.split_operands_result.op2

    emit_be 2, 0100111001010000b + @op1.ea_reg_bits

    ; extension words
    call emit_ext_words, @op2.ext_bytes, @op2.ext_bytes_bits
end calminstruction

;; SUBX, ADDX ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Syntax:
;     subx.[bwl] dy,dx
;     subx.[bwl] -(ay),-(ax)
;     addx.[bwl] dy,dx
;     addx.[bwl] -(ay),-(ax)
iterate <instr,  first_byte>, \
        subx,    10010001b, \
        addx,    11010001b
    iterate <size,  size_bits>, \
        b,      00b, \
        w,      01b, \
        l,      10b

        calminstruction instr.size? operands&
            assert_word_aligned

            local m_bit

            ; Init default values
            compute m_bit, 0 ; dn to dn

            call m68k.split_operands, operands
            call m68k.parse_operand@op1, m68k.split_operands_result.op1
            call m68k.parse_operand@op2, m68k.split_operands_result.op2

            ; TODO: This check is just to make it work. I need
            ; to make a more serious check for valid addressing modes.
            check @op1.type = '-(an)'
            jno emit_bytes
        ; Is -(an) to -(an)
            compute m_bit, 1
        emit_bytes:
            emit_be 1, first_byte + @op2.ea_reg_bits shl 1
            emit_be 1, size_bits shl 6 + m_bit shl 3 + @op1.ea_reg_bits
        end calminstruction
    end iterate ; <size, size_bits>

end iterate ; <instr, first_byte>

;; SBCD, ABCD ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Syntax:
;     sbcd.b dy,dx
;     sbcd.b -(ay),-(ax)
;     abcd.b dy,dx
;     abcd.b -(ay),-(ax)
iterate <instr,  first_byte>, \
        sbcd,    10000001b, \
        abcd,    11000001b

        calminstruction instr.b? operands&
                assert_word_aligned

                local m_bit

                ; Init default values
                compute m_bit, 0 ; dn to dn

                call m68k.split_operands, operands
                call m68k.parse_operand@op1, m68k.split_operands_result.op1
                call m68k.parse_operand@op2, m68k.split_operands_result.op2

                ; TODO: This check is just to make it work. I need
                ; to make a more serious check for valid addressing modes.
                check @op1.type = '-(an)'
                jno emit_bytes
            ; Is -(an) to -(an)
                compute m_bit, 1
            emit_bytes:
                emit_be 1, first_byte + @op2.ea_reg_bits shl 1
                emit_be 1, m_bit shl 3 + @op1.ea_reg_bits
        end calminstruction

end iterate ; <instr, first_byte>

;; SUBA, CMPA, ADDA ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Syntax:
;     SUBA.[wl] <ea>,An
;     CMPA.[wl] <ea>,An
;     ADDA.[wl] <ea>,An
iterate <instr,  first_byte>, \
        suba,    10010000b, \
        cmpa,    10110000b, \
        adda,    11010000b
    iterate <size,  size_bit>, \
            w,      0b, \
            l,      1b

            calminstruction instr.size operands&
                assert_word_aligned

                ; TODO: I am not sure why I have to do this to get the call to work.
                arrange _size, =size

                call m68k.split_operands, operands
                call m68k.parse_operand@op1, m68k.split_operands_result.op1, _size
                call m68k.parse_operand@op2, m68k.split_operands_result.op2, _size

                emit_be 1, first_byte + @op2.ea_reg_bits shl 1 + size_bit
                emit_be 1, 11000000b + @op1.ea_mode_bits shl 3 + @op1.ea_reg_bits

                ; <ea> extension words
                call emit_ext_words, @op1.ext_bytes, @op1.ext_bytes_bits
            end calminstruction

    end iterate ; <size,size_bit>
end iterate ; <instr, first_byte>

;; EOR, CMP ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

iterate <size,  size_bits>, \
        b,      00b, \
        w,      01b, \
        l,      10b

        ; Syntax:
        ;     EOR.[bwl] Dn,<ea>
        calminstruction eor.size? operands&
                assert_word_aligned

                call m68k.split_operands, operands
                call m68k.parse_operand@op1, m68k.split_operands_result.op1
                call m68k.parse_operand@op2, m68k.split_operands_result.op2

            ; Show error message if imm
                check @op1.type = 'imm'
                jno skip_error
                display '`eor` does not allow the first operand to' \
                    bappend ' be an immediate. Will use `eori` instead.' \
                    bappend 13 bappend 10
                
                ; local cmd
                ; arrange cmd, =eor=i.=size operands
                ; stringify cmd
                ; eval cmd
                call eori.size, operands
                exit
            skip_error:
                emit_be 1, 10110001b + @op1.ea_reg_bits shl 1
                emit_be 1, size_bits shl 6 + @op2.ea_mode_bits shl 3 + @op2.ea_reg_bits

                ; <ea> extension words
                call emit_ext_words, @op2.ext_bytes, @op2.ext_bytes_bits
        end calminstruction

        ; Syntax:
        ;     CMP.[bwl] <ea>,Dn
        calminstruction cmp.size? operands&
                assert_word_aligned

                local _size

                ; TODO: I am not sure why I have to do this to get the call to work.
                ; TODO: Can I use backtick instead pehaps?
                arrange _size, =size

                call m68k.split_operands, operands
                call m68k.parse_operand@op1, m68k.split_operands_result.op1, _size
                call m68k.parse_operand@op2, m68k.split_operands_result.op2, _size

            ; Show error message if imm ; TODO: Move comment. better comments.
                check @op2.type = 'an'
                jno skip_an
                display '`cmp` does not allow the second operand to be' \
                    bappend ' an address register. Will use `cmpa` instead.' \
                    bappend 13 bappend 10
                ; local cmd
                ; arrange cmd, =cmp=a.=size operands
                ; stringify cmd
                ; eval cmd
                call cmpa.size, operands
                exit
            skip_an:

                local is_compat_vasm_cmp_bug1 ; TODO: Remove
                bool is_compat_vasm_cmp_bug1, \
                    m68k.settings.compat_vasm_cmp_bug1 = 1 & \
                    (`size = 'b' | `size = 'l')

                check @op1.type = 'imm' & \
                    ~is_compat_vasm_cmp_bug1

                jno skip_imm
                display '`cmp` does not allow the first operand to' \
                    bappend ' be an immediate. Will use `cmpi` instead.' \
                    bappend 13 bappend 10
                
                ; local cmd
                ; arrange cmd, =cmp=i.=size operands
                ; stringify cmd
                ; eval cmd
                call cmpi.size, operands
                exit
            skip_imm:
                emit_be 1, 10110000b + @op2.ea_reg_bits shl 1
                emit_be 1, size_bits shl 6 + @op1.ea_mode_bits shl 3 + @op1.ea_reg_bits

                ; <ea> extension words
                call emit_ext_words, @op1.ext_bytes, @op1.ext_bytes_bits
        end calminstruction

end iterate ; <size, size_bits>

;; DIVU, DIVS, MULU, MULS ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Syntax:
;     divs <ea>,dn
;     divu <ea>,dn
;     muls <ea>,dn
;     mulu <ea>,dn
iterate <instr,  first_byte>, \
        divu,    10000000b, \
        divs,    10000001b, \
        mulu,    11000000b, \
        muls,    11000001b

        calminstruction instr.w? operands&
            assert_word_aligned

            call m68k.split_operands, operands
            call m68k.parse_operand@op1, m68k.split_operands_result.op1
            call m68k.parse_operand@op2, m68k.split_operands_result.op2

            emit_be 1, first_byte + @op2.ea_reg_bits shl 1
            emit_be 1, 11000000b + @op1.ea_mode_bits shl 3 + @op1.ea_reg_bits

            ; <ea> extension words
            call emit_ext_words, @op1.ext_bytes, @op1.ext_bytes_bits
        end calminstruction

end iterate ; <instr, first_byte>

;; BTST BCHG BCLR BSET ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Syntax:
;     btst.[bl] dn,<ea>
;     btst.[bl] #<data>,<ea>
; Syntax:
;     bchg.[bl] dn,<ea>
;     bchg.[bl] #<data>,<ea>
; Syntax:
;     bclr.[bl] dn,<ea>
;     bclr.[bl] #<data>,<ea>
; Syntax:
;     bset.[bl] dn,<ea>
;     bset.[bl] #<data>,<ea>
; TODO: When looking at: http://goldencrystal.free.fr/M68kOpcodes-v2.3.pdf
;       I don't see how size .b/.l is encoded...??
iterate <instr,  instr_bits>, \
        btst,    00b, \
        bchg,    01b, \
        bclr,    10b, \
        bset,    11b
    ; TODO: I think the size_in_bytes is strange.
    ;       What even does .b and .l mean for these specific instructions?
    ;       I really need to figure this out, is it that the addressing mode
    ;       bits are changed, that seems reasonable? I require explicit .[bwl]
    ;       but maybe another assembler when .[bwl] is not input on <ea> it will
    ;       take the size from the instruction suffix.. yea that must be it.
    iterate <size, size_in_bytes>, \
             b,    2, \
             l,    2

        calminstruction instr.size? operands&
                assert_word_aligned

                local op1_bits
                local op1_type_bit
                local bit_index
                local bit_index_size

                ; Init default values
                compute op1_bits, 0 ; This is the value when op1 is imm
                compute op1_type_bit, 1000b ; This is the value when op1 is imm
                compute bit_index, 0
                compute bit_index_size, size_in_bytes ; This is the value when op1 is imm

                call m68k.split_operands, operands
                call m68k.parse_operand@op1, m68k.split_operands_result.op1
                call m68k.parse_operand@op2, m68k.split_operands_result.op2

                ; TODO:
                ;   If type was a token instead of a value, the I suppose I
                ;   could use transform too, i.e. transform the type to 1 or 0.
                check @op1.type = 'dn'
                jno op1_is_imm ; TODO: I mean I have not validated that though...
            ; op1_is_dn
                compute op1_bits, @op1.ea_reg_bits shl 1
                compute op1_type_bit, 1
                compute bit_index_size, 0
                jump emit_bytes
            op1_is_imm:
                compute bit_index, @op1.imm
            emit_bytes:

                emit_be 1, op1_bits + op1_type_bit
                emit_be 1, instr_bits shl 6 + @op2.ea_mode_bits shl 3 +  @op2.ea_reg_bits

                ; bit index
                emit_be bit_index_size, bit_index

                ; <ea> extension words
                call emit_ext_words, @op2.ext_bytes, @op2.ext_bytes_bits
        end calminstruction

    end iterate ; <size, size_in_bytes>
end iterate ; <instr, instr_bits>

;; MOVEM ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

iterate <size,  size_bits>, \
        w,      0b, \
        l,      1b

        ; Syntax:
        ;     movem.[wl] <ea>,<register list>
        ;     movem.[wl] <register list>,<ea>
        calminstruction movem.size? operands&
                    assert_word_aligned

                    local direction
                    local bit_mask
                    local ea_mode_bits
                    local ea_reg_bits
                    local ext_bytes
                    local ext_bytes_bits

            ; Init default values
                    ; 0 means <register list> to <ea>
                    ; 1 means <ea>,<register list>
                    ; compute direction, 0
                    ; compute bit_mask, 0

                    call m68k.split_operands, operands
                    call m68k.parse_reg_list@reg_list1, m68k.split_operands_result.op1
                    call m68k.parse_reg_list@reg_list2, m68k.split_operands_result.op2

            ; Figure out direction
                    check @reg_list1.is_reg_list = 1
                    jyes reglist_to_ea
            ; ea_to_reglist:
                    call m68k.parse_operand@op1, m68k.split_operands_result.op1
                    compute direction, 1
                    ; TODO: Instead of doing all these twice for the 2 cases
                    ;       can I not `arrange ea, @op1 or something??
                    compute ea_mode_bits, @op1.ea_mode_bits
                    compute ea_reg_bits, @op1.ea_reg_bits
                    compute ext_bytes, @op1.ext_bytes
                    compute ext_bytes_bits, @op1.ext_bytes_bits
                    compute bit_mask, @reg_list2.mask_word
                    ; check if reverse mask should be used
                    check @op1.type = '-(an)'
                    jno skip_reverse1
                ; reverse:
                    compute bit_mask, @reg_list2.mask_word_reverse
                skip_reverse1: ; TODO: just jump to emit_bytes instead?
                    jump emit_bytes
            reglist_to_ea:
                    call m68k.parse_operand@op2, m68k.split_operands_result.op2
                    compute direction, 0
                    compute ea_mode_bits, @op2.ea_mode_bits
                    compute ea_reg_bits, @op2.ea_reg_bits
                    compute ext_bytes, @op2.ext_bytes
                    compute ext_bytes_bits, @op2.ext_bytes_bits
                    compute bit_mask, @reg_list1.mask_word
                    ; check if reverse mask should be used
                    check @op2.type = '-(an)'
                    jno skip_reverse2
                ; reverse:
                    compute bit_mask, @reg_list1.mask_word_reverse
                skip_reverse2: ; TODO: just jump to emit_bytes instead?
            emit_bytes:
                    emit_be 1, 01001000b + direction shl 2
                    emit_be 1, 10000000b + size_bits shl 6 + ea_mode_bits shl 3 + ea_reg_bits

                    ; register list bit mask
                    emit_be 2, bit_mask

                    ; <ea> extension words
                    call emit_ext_words, ext_bytes, ext_bytes_bits
        end calminstruction

end iterate ; <size, size_bits>

;; OR, SUB, AND, ADD ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Syntax:
;     or.[bwl]  <ea>,dn
;     or.[bwl]  dn,<ea>
;     sub.[bwl] <ea>,dn
;     sub.[bwl] dn,<ea>
;     and.[bwl] <ea>,dn
;     and.[bwl] dn,<ea>
;     add.[bwl] <ea>,dn
;     add.[bwl] dn,<ea>
iterate <instr,  first_byte>, \
        or,      10000000b, \
        sub,     10010000b, \
        and,     11000000b, \
        add,     11010000b
    iterate <size,  size_bits>, \
            b,      00b, \
            w,      01b, \
            l,      10b

            calminstruction instr.size? operands&
                    assert_word_aligned

                    local _size

                    ; TODO: I am not sure why I have to do this to get the call to work.
                    ; TODO: Can I use backtick instead pehaps?
                    arrange _size, =size

                    call m68k.split_operands, operands
                    call m68k.parse_operand@op1, m68k.split_operands_result.op1, _size
                    call m68k.parse_operand@op2, m68k.split_operands_result.op2, _size

                ; Auto-fix add/sub to adda/suba if second operand is an
                    check @op2.type = 'an' & (`instr = 'add' | `instr = 'sub')
                    jno skip_auto_fix_an
                ; auto_fix_an:
                    ; local cmd
                    ; arrange cmd, =instr=a.=size operands
                    ; stringify cmd
                    ; eval cmd
                    call instr#a.size, operands
                    exit
                skip_auto_fix_an:

                ; Show error message if imm
                    local is_compat_vasm_add_bug1
                    bool is_compat_vasm_add_bug1, \
                        m68k.settings.compat_vasm_add_bug1 = 1 & \
                        `instr = 'add' & \
                        `size = 'l' & \
                        @op2.type = 'dn'

                    local is_compat_vasm_add_bug2
                    bool is_compat_vasm_add_bug2, \
                        m68k.settings.compat_vasm_add_bug2 = 1 & \
                        `instr = 'add' & \
                        `size = 'w' & \
                        @op2.type = 'dn'

                    local is_compat_vasm_add_bug3
                    bool is_compat_vasm_add_bug3, \
                        m68k.settings.compat_vasm_add_bug3 = 1 & \
                        `instr = 'add' & \
                        `size = 'w' & \
                        @op2.type = 'dn'

                    local is_compat_vasm_and_bug1
                    bool is_compat_vasm_and_bug1, \
                        m68k.settings.compat_vasm_add_bug1 = 1 & \
                        `instr = 'and' & \
                        @op2.type = 'dn'

                    local is_compat_vasm_sub_bug1
                    bool is_compat_vasm_sub_bug1, \
                        m68k.settings.compat_vasm_sub_bug1 = 1 & \
                        `instr = 'sub' & \
                        `size = 'w' & \
                        (@op1.imm >= 10b)

                    local is_compat_vasm_sub_bug2
                    bool is_compat_vasm_sub_bug2, \
                        m68k.settings.compat_vasm_sub_bug2 = 1 & \
                        `instr = 'sub' & \
                        `size = 'w' & \
                        (@op2.ea_reg_bits = 011b | @op2.ea_reg_bits = 110b | @op2.ea_reg_bits = 111b) & \
                        (@op1.imm = 1)

                    local is_compat_vasm_or_bug1
                    bool is_compat_vasm_or_bug1, \
                        m68k.settings.compat_vasm_or_bug1 = 1 & \
                        `instr = 'or'

                    check @op1.type = 'imm' & \
                        ~is_compat_vasm_add_bug1 & \
                        ~is_compat_vasm_add_bug2 & \
                        ~is_compat_vasm_add_bug3 & \
                        ~is_compat_vasm_and_bug1 & \
                        ~is_compat_vasm_sub_bug1 & \
                        ~is_compat_vasm_sub_bug2 & \
                        ~is_compat_vasm_or_bug1

                    jno skip_error
                    local wrong, correct
                    arr_str wrong, `=instr`
                    arr_str correct, `=instr=i`
                    display wrong \
                        bappend ' does not allow the first operand to' \
                        bappend ' be an immediate. Will use ' \
                        bappend correct \
                        bappend ' instead.' bappend 13 bappend 10

                    ; local cmd
                    ; arrange cmd, =instr=i.=size operands
                    ; stringify cmd
                    ; eval cmd
                    call instr#i.size, operands
                    exit
                skip_error:

                    ; TODO: This is a sloppy check, do a more complete check in the
                    ; future.
                    ; TODO: Is there anything such as ternary in fasmg? 
                    ; @op1.type = 'dn' ? 1 : 0
                    check @op2.type = 'dn'
                    jno dn_to_ea
                ; ea_to_dn:
                    emit_be 1, first_byte + @op2.ea_reg_bits shl 1
                    emit_be 1, size_bits shl 6 + @op1.ea_mode_bits shl 3 +  @op1.ea_reg_bits

                    ; extension words
                    call emit_ext_words, @op1.ext_bytes, @op1.ext_bytes_bits

                    exit
                dn_to_ea:
                    ; first byte                                  dir
                    emit_be 1, first_byte + @op1.ea_reg_bits shl 1 + 1

                    ; second byte
                    emit_be 1, size_bits shl 6 + @op2.ea_mode_bits shl 3 +  @op2.ea_reg_bits

                    ; extension words
                    call emit_ext_words, @op2.ext_bytes, @op2.ext_bytes_bits
            end calminstruction

    end iterate ; <size, size_bits>
end iterate ; <instr, first_byte>

;; DBcc ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Syntax:
;   dbcc.w Dn,<label>
;
; TODO: What exactly does label and literal mean in this context?
; TODO: Add the different aliases for the conditions.
; Aliases:
;     ra = f
;     hs = cc
;     lo = cs
iterate <cc,  cc_bits>, \
        t,      0000b, \
        f,      0001b, \
        \ ; Alias for f
        ra,     0001b, \
        hi,     0010b, \
        ls,     0011b, \
        cc,     0100b, \
        \ ; Alias for cc
        hs,     0100b, \
        cs,     0101b, \
        \ ; Alias for cs
        lo,     0101b, \
        ne,     0110b, \
        eq,     0111b, \
        vc,     1000b, \
        vs,     1001b, \
        pl,     1010b, \
        mi,     1011b, \
        ge,     1100b, \
        lt,     1101b, \
        gt,     1110b, \
        le,     1111b

        ; TODO: Check if displacement fits a in word.
        ; Maybe do that in parse_operand?
        ; Also, check if displacement is a valid displacement.
        ; 0 is not allowed for .b I think.
        calminstruction? db#cc.w? operands&
            assert_word_aligned

            local pc

            call m68k.split_operands, operands
            call m68k.parse_operand@op1, m68k.split_operands_result.op1
            call m68k.parse_operand@op2, m68k.split_operands_result.op2

            emit_be 1, 01010000b + cc_bits
            emit_be 1, 11001000b + @op1.ea_reg_bits

            ; immediate word
            ; this looks strange but works.
            ;     ext_bytes_bits will contain the value the label (op2).
            emit_be 2, @op2.ext_bytes_bits - $
        end calminstruction

end iterate ; <cc, cc_bits>

; Syntax:
;     movea.[wl] <ea>,an
iterate <size,  size_bits>, \
        w,      11b, \
        l,      10b

        calminstruction movea.size? operands&
            assert_word_aligned

            ; display 10 bappend 'movea:' bappend 10

            local tmp
            arrange tmp, =size

            call m68k.split_operands, operands
            call m68k.parse_operand@op1, m68k.split_operands_result.op1, tmp
            call m68k.parse_operand@op2, m68k.split_operands_result.op2

            emit_be 1, size_bits shl 4 + @op2.ea_reg_bits shl 1
            emit_be 1, 01000000b + @op1.ea_mode_bits shl 3 + @op1.ea_reg_bits
                        
            ; extension words
            ; TODO: So, seems the number of extension words depend upon .w,.l
            ;       IN THE SPECIFIC CASE OF IMMEDITE OPERANDS this complicated
            ;       the implementation of parse_operands a bit.
            call emit_ext_words, @op1.ext_bytes, @op1.ext_bytes_bits
        end calminstruction

end iterate ; <size, size_bits>

; TODO: Comment
calminstruction lea.l? operands&
    assert_word_aligned

    call m68k.split_operands, operands
    call m68k.parse_operand@op1, m68k.split_operands_result.op1
    call m68k.parse_operand@op2, m68k.split_operands_result.op2

    emit_be 1, 01000001b + @op2.ea_reg_bits shl 1
    emit_be 1, 11000000b + @op1.ea_mode_bits shl 3 + @op1.ea_reg_bits
                
    ; extension words
    call emit_ext_words, @op1.ext_bytes, @op1.ext_bytes_bits
end calminstruction

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Syntax:
;     addq #<data>,<ea>
;     subq #<data>,<ea>
; Addressing modes:
;     Dn  An  (An)  (An)+  ‑(An)  (d,An)  (d,An,Xi) 
;      ✓   ✓   ✓     ✓       ✓      ✓         ✓ 
;     ABS.W  ABS.L  (d,PC)  (d,PC,Xn)  imm
;       ✓     ✓                 
; TODO: Restrict to valid addressing modes for the instructions.
; Valid imm range: 1-8 (8 is encoded as 000b i.e. 0).
iterate <instr,  first_byte>, \
        addq,    01010000b, \
        subq,    01010001b
    iterate <size,  size_bits>, \
            b,      00b, \
            w,      01b, \
            l,      10b

            calminstruction instr.size? operands&
                assert_word_aligned

                local tmp

                call m68k.split_operands, operands
                call m68k.parse_operand@op1, m68k.split_operands_result.op1
                call m68k.parse_operand@op2, m68k.split_operands_result.op2

                assert_min @op1.imm, 1
                assert_max @op1.imm, 8

                ; 8 is encoded as 000b
                compute tmp, @op1.imm mod 8
                emit_be 1, first_byte + tmp shl 1
                emit_be 1, size_bits shl 6 + @op2.ea_mode_bits shl 3 + @op2.ea_reg_bits
                
                ; extension words
                call emit_ext_words, @op2.ext_bytes, @op2.ext_bytes_bits
            end calminstruction

    end iterate ; <size, size_bits>
end iterate ; <instr, first_byte>

; Description:
;     Move the literal to a data register. The literal data is an
;     eight-bit signed value (-128 to +127). The literal is sign-extended
;     to 32 bits to cover the whole of the data register.
; Arguments:
;     data: 0000_0000 - 1111_1111
;     dn: d0 - d7
; TODO: Give error if data is out of range.
; TODO: Validate that dn is a data register.
; TODO: Figure out how to work with signed numbers so it works with
;       whatever formats you can use in normal m68k assemblers
;       I assume 1111_1111b and -1d are should both be allowed?!
calminstruction moveq.l? operands&
    assert_word_aligned

    call m68k.split_operands, operands
    call m68k.parse_operand@op1, m68k.split_operands_result.op1
    call m68k.parse_operand@op2, m68k.split_operands_result.op2

    emit_be 1, 01110000b + @op2.ea_reg_bits shl 1
    emit_be 1, @op1.imm
end calminstruction