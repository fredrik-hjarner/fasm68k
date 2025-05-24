;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Motorola 68000 dyadic instructions                                         ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; MOVEP ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

define movep?

; Syntax:
;     movep dx,(d,ay)
;     movep (d,ay),dx
; Sample syntax:
;     movep d3,(control,a0)
;     movep (input,a6),d5
iterate <size,  size_bit>, \
        w,      0b, \
        l,      1000000b

    calminstruction movep.size? operands&
            xcall m68k.parse_and_validate_instruction, \
                <movep>, operands, <size>, <size>

        ; check_direction:
            match =dn, @op2.type_token

            jno d_to_d_an
        ; d_an_to_d
            emit 1, 1b or @op2.ea_reg_bits shl 1
            emit 1, size_bit or 1000b or @op1.ea_reg_bits

            ; extension words
            emit_be @op1.ext_bytes, @op1.ext_bytes_bits
            exit
        d_to_d_an:
            emit 1, 1b or @op1.ea_reg_bits shl 1
            emit 1, 10000000b or size_bit or 1000b or @op2.ea_reg_bits

            ; extension words
            emit_be @op2.ext_bytes,  @op2.ext_bytes_bits
    end calminstruction

end iterate ; <size, size_bit>

;; CMPM ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

define cmpm?

; Syntax:
;     cmpm.[bwl] (ay)+,(ax)+
; Sample syntax:
;     cmpm.b (a3)+,(a4)+
iterate <size,  instr_bits>, \
        b,      00001000b, \
        w,      01001000b, \
        l,      10001000b

    calminstruction cmpm.size? operands&
        xcall m68k.parse_and_validate_instruction, \
            <cmpm>, operands, <size>, <size>
        emit 1, 10110001b or @op2.ea_reg_bits shl 1
        emit 1, instr_bits or @op1.ea_reg_bits
    end calminstruction

end iterate ; <size, instr_bits>

;; EXG ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

define exg?

; Syntax:
;     exg.l reg,reg
; Sample syntax:
;     exg d3,d4
;     exg d2,a0
;     exg a7,d5
; Note that the encoding of the 3 M bits are not explained in:
;     http://goldencrystal.free.fr/M68kOpcodes-v2.3.pdf
calminstruction exg.l? operands&
        xcall m68k.parse_and_validate_instruction, <exg>, operands, <l>, <l>

    ; check_dn_an:
        match =dn, @op1.type_token
        jno check_an_an
        match =an, @op2.type_token
        jno check_an_an
        emit 1, 11000001b or @op1.ea_reg_bits shl 1
        emit 1, 10001000b or @op2.ea_reg_bits
        exit
    check_an_an:
        match =an, @op1.type_token
        jno check_an_dn
        match =an, @op2.type_token
        jno check_an_dn
        emit 1, 11000001b or @op1.ea_reg_bits shl 1
        emit 1, 01001000b or @op2.ea_reg_bits
        exit
    check_an_dn:
        ; seems `exg.l a7,d5` is encoded as `exg.l d5,a7`
        match =an, @op1.type_token
        jno dn_to_dn
        match =dn, @op2.type_token
        jno dn_to_dn
        emit 1, 11000001b or @op2.ea_reg_bits shl 1
        emit 1, 10001000b or @op1.ea_reg_bits
        exit
    dn_to_dn:
        emit 1, 11000001b or @op1.ea_reg_bits shl 1
        emit 1, 01000000b or @op2.ea_reg_bits
end calminstruction

;; CHK ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

define chk?

; Syntax:
;     chk.w <ea>,dn
calminstruction chk.w? operands&
    xcall m68k.parse_and_validate_instruction, <chk>, operands, <w>, <w>

    emit 1, 01000001b or @op2.ea_reg_bits shl 1
    emit 1, 10000000b or @op1.ea_mode_bits shl 3 or @op1.ea_reg_bits

    ; <ea> extension words
    call emit_ext_words, @op1.ext_bytes, @op1.ext_bytes_bits, @op1.type_token
end calminstruction

;; LINK ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

define link?

; Syntax:
;     link.w an,#<displacement>
; Sample syntax:
;     link a6,#-12
calminstruction link.w? operands&
    xcall m68k.parse_and_validate_instruction, <link>, operands, <w>, <w>

    emit_be 2, 0100111001010000b or @op1.ea_reg_bits

    ; extension words
    emit_be @op2.ext_bytes, @op2.ext_bytes_bits
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

    define instr?

    iterate <size,  size_bits>, \
        b,      00000000b, \
        w,      01000000b, \
        l,      10000000b

        calminstruction instr.size? operands&
            xcall m68k.parse_and_validate_instruction, \
                <instr>, operands, <size>, <size>

            local m_bit

            ; Init default values
            compute m_bit, 0 ; dn to dn

            match =an_pre_decr, @op1.type_token
            jno emit_bytes
        ; Is -(an) to -(an)
            compute m_bit, 1000b
        emit_bytes:
            emit 1, first_byte or @op2.ea_reg_bits shl 1
            emit 1, size_bits or m_bit or @op1.ea_reg_bits
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

        define instr?

        calminstruction instr.b? operands&
                xcall m68k.parse_and_validate_instruction, \
                    <instr>, operands, <b>, <b>

                local m_bit

                ; Init default values
                compute m_bit, 0 ; dn to dn

                match =an_pre_decr, @op1.type_token
                jno emit_bytes
            ; Is -(an) to -(an)
                compute m_bit, 1000b
            emit_bytes:
                emit 1, first_byte or @op2.ea_reg_bits shl 1
                emit 1, m_bit or @op1.ea_reg_bits
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

    define instr?

    iterate <size,  size_bit>, \
            w,      0b, \
            l,      1b

            calminstruction instr.size? operands&
                xcall m68k.parse_and_validate_instruction, \
                    <instr>, operands, <size>, <size>

                emit 1, first_byte or @op2.ea_reg_bits shl 1 or size_bit
                emit 1, 11000000b or @op1.ea_mode_bits shl 3 or @op1.ea_reg_bits

                ; <ea> extension words
                call emit_ext_words, @op1.ext_bytes, @op1.ext_bytes_bits, @op1.type_token
            end calminstruction

    end iterate ; <size,size_bit>
end iterate ; <instr, first_byte>

;; EOR, CMP ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

iterate <size,  size_bits>, \
        b,      00000000b, \
        w,      01000000b, \
        l,      10000000b

        define eor?

        ; Syntax:
        ;     EOR.[bwl] Dn,<ea>
        calminstruction eor.size? operands&
                xcall m68k.parse_and_validate_instruction, \
                    <eor>, operands, <size>, <size>

            ; Auto-fix if op1 is imm
                match =imm, @op1.type_token
                jno skip_error
                warn '`eor` does not allow the first operand to' \
                    bappend ' be an immediate. Will use `eori` instead.'
                call eori.size, operands
                exit
            skip_error:
                emit 1, 10110001b or @op1.ea_reg_bits shl 1
                emit 1, size_bits or @op2.ea_mode_bits shl 3 or @op2.ea_reg_bits

                ; <ea> extension words
                emit_be @op2.ext_bytes, @op2.ext_bytes_bits
        end calminstruction

        define cmp?

        ; Syntax:
        ;     CMP.[bwl] <ea>,Dn
        calminstruction cmp.size? operands&
                xcall m68k.parse_and_validate_instruction, \
                    <cmp>, operands, <size>, <size>

            ; Auto-fix if op2 is an
                match =an, @op2.type_token
                jno skip_an
                warn '`cmp` does not allow the second operand to be' \
                    bappend ' an address register. Will use `cmpa` instead.'
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
                warn '`cmp` does not allow the first operand to' \
                    bappend ' be an immediate. Will use `cmpi` instead.'
                call cmpi.size, operands
                exit
            skip_imm:
                emit 1, 10110000b or @op2.ea_reg_bits shl 1
                emit 1, size_bits or @op1.ea_mode_bits shl 3 or @op1.ea_reg_bits

                ; <ea> extension words
                call emit_ext_words, @op1.ext_bytes, @op1.ext_bytes_bits, @op1.type_token
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

        define instr?

        calminstruction instr.w? operands&
            xcall m68k.parse_and_validate_instruction, \
                <instr>, operands, <w>, <w>

            emit 1, first_byte or @op2.ea_reg_bits shl 1
            emit 1, 11000000b or @op1.ea_mode_bits shl 3 or @op1.ea_reg_bits

            ; <ea> extension words
            call emit_ext_words, @op1.ext_bytes, @op1.ext_bytes_bits, @op1.type_token
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
        btst,    00000000b, \
        bchg,    01000000b, \
        bclr,    10000000b, \
        bset,    11000000b

    define instr?

    ; TODO: I think the size_in_bytes is strange.
    ;       What even does .b and .l mean for these specific instructions?
    ;       I really need to figure this out, is it that the addressing mode
    ;       bits are changed, that seems reasonable? I require explicit .[bwl]
    ;       but maybe another assembler when .[bwl] is not input on <ea> it will
    ;       take the size from the instruction suffix.. yea that must be it.
    iterate <size, dot_size, size_in_bytes>, \
             _,    ,         2,  \
             b,    .b,       2,  \
             l,    .l,       2

        calminstruction instr#dot_size? operands&
                ; TODO: I don't quite understand why I have to pass <b> here?
                xcall m68k.parse_and_validate_instruction, \
                    <instr>, operands, <size>, <b>

                match =dn, @op1.type_token
                jno op1_is_imm
            ; op1_is_dn
                emit 1, @op1.ea_reg_bits shl 1 or 1
                emit 1, instr_bits or @op2.ea_mode_bits shl 3 or  @op2.ea_reg_bits

                ; <ea> extension words
                call emit_ext_words, @op2.ext_bytes, @op2.ext_bytes_bits, @op2.type_token
                exit
            op1_is_imm:
                emit 1, 1000b
                emit 1, instr_bits or @op2.ea_mode_bits shl 3 or  @op2.ea_reg_bits

                ; bit index
                emit_be size_in_bytes, @op1.imm

                ; <ea> extension words
                call emit_ext_words, @op2.ext_bytes, @op2.ext_bytes_bits, @op2.type_token
                exit
        end calminstruction

    end iterate ; <size, size_in_bytes>
end iterate ; <instr, instr_bits>

;; MOVEM ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

define movem?

iterate <size,  size_bits>, \
        w,      10000000b, \
        l,      11000000b

        ; Syntax:
        ;     movem.[wl] <ea>,<register list>
        ;     movem.[wl] <register list>,<ea>
        calminstruction movem.size? operands&
                    assert_word_aligned

                    local bit_mask

                    call m68k.split_operands, operands
                    call m68k.parse_reg_list@reg_list1, m68k.split_operands_result.op1
                    call m68k.parse_reg_list@reg_list2, m68k.split_operands_result.op2

            ; Figure out direction
                    check @reg_list1.is_reg_list = 1
                    jyes reglist_to_ea
            ; ea_to_reglist:
                    call m68k.parse_operand@op1, m68k.split_operands_result.op1
                    compute bit_mask, @reg_list2.mask_word
                    ; check if reverse mask should be used
                    match =an_pre_decr, @op1.type_token
                    jno skip_reverse1
                ; reverse:
                    reverse_bit_in_word  bit_mask
                skip_reverse1:
                    emit 1, 01001100b
                    emit 1, size_bits or @op1.ea_mode_bits shl 3 or @op1.ea_reg_bits

                    ; register list bit mask
                    emit_be 2, bit_mask

                    ; <ea> extension words
                    call emit_ext_words, @op1.ext_bytes, @op1.ext_bytes_bits, @op1.type_token
                    exit
            reglist_to_ea:
                    call m68k.parse_operand@op2, m68k.split_operands_result.op2
                    compute bit_mask, @reg_list1.mask_word
                    ; check if reverse mask should be used
                    match =an_pre_decr, @op2.type_token
                    jno skip_reverse2
                ; reverse:
                    reverse_bit_in_word  bit_mask
                skip_reverse2:
                    emit 1, 01001000b
                    emit 1, size_bits or @op2.ea_mode_bits shl 3 or @op2.ea_reg_bits

                    ; register list bit mask
                    emit_be 2, bit_mask

                    ; <ea> extension words
                    call emit_ext_words, @op2.ext_bytes, @op2.ext_bytes_bits, @op2.type_token
        end calminstruction

end iterate ; <size, size_bits>

;; OR, SUB, AND, ADD ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; define or? ;This crashes because it collides with `or` and `and` keywords.
define sub?
; define and? ; This crashes because it collides with `or` and `and` keywords.
define add?

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
            b,      0, \
            w,      01000000b, \
            l,      10000000b

            calminstruction instr.size? operands&
                    xcall m68k.parse_and_validate_instruction, \
                        <instr>, operands, <size>, <size>

                ; Auto-fix add/sub to adda/suba if second operand is an
                    check @op2.type = 'an' & (`instr = 'add' | `instr = 'sub')
                    jno skip_auto_fix_an
                ; auto_fix_an:
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
                    warn wrong \
                        bappend ' does not allow the first operand to' \
                        bappend ' be an immediate. Will use ' \
                        bappend correct \
                        bappend ' instead.'

                    call instr#i.size, operands
                    exit
                skip_error:

                    match =dn, @op2.type_token
                    jno dn_to_ea
                ; ea_to_dn:
                    emit 1, first_byte or @op2.ea_reg_bits shl 1
                    emit 1, size_bits or @op1.ea_mode_bits shl 3 or @op1.ea_reg_bits

                    ; extension words
                    call emit_ext_words, @op1.ext_bytes, @op1.ext_bytes_bits, @op1.type_token

                    exit
                dn_to_ea:
                    ; first byte                                  dir
                    emit 1, first_byte or @op1.ea_reg_bits shl 1 or 1

                    ; second byte
                    emit 1, size_bits or @op2.ea_mode_bits shl 3 or  @op2.ea_reg_bits

                    ; extension words
                    emit_be @op2.ext_bytes, @op2.ext_bytes_bits
            end calminstruction

    end iterate ; <size, size_bits>
end iterate ; <instr, first_byte>

;; DBcc ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Syntax:
;   dbcc.w Dn,<label>
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

        define db#cc?

        iterate <size, dot_size>, \
                _,    ,  \
                w,    .w
            ; TODO: Check if displacement fits a in word.
            ; Maybe do that in parse_operand?
            ; Also, check if displacement is a valid displacement.
            ; 0 is not allowed for .b I think.
            calminstruction? db#cc#dot_size? operands&
                xcall m68k.parse_and_validate_instruction, \
                    <db#cc>, operands, <size>, <w>

                emit 1, 01010000b or cc_bits
                emit 1, 11001000b or @op1.ea_reg_bits

                ; immediate word
                ; this looks strange but works.
                ;     ext_bytes_bits will contain the value the label (op2).
                emit_be 2, @op2.ext_bytes_bits - $
            end calminstruction

    end iterate ; <size, dot_size>
end iterate ; <cc, cc_bits>

;; MOVEA ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

define movea?

; Syntax:
;     movea.[wl] <ea>,an
iterate <size,  size_bits>, \
        w,      110000b, \
        l,      100000b

        calminstruction movea.size? operands&
            xcall m68k.parse_and_validate_instruction, \
                <movea>, operands, <size>, <size>

            emit 1, size_bits or @op2.ea_reg_bits shl 1
            emit 1, 01000000b or @op1.ea_mode_bits shl 3 or @op1.ea_reg_bits
                        
            ; extension words
            ; TODO: So, seems the number of extension words depend upon .w,.l
            ;       IN THE SPECIFIC CASE OF IMMEDITE OPERANDS this complicated
            ;       the implementation of parse_operands a bit.
            call emit_ext_words, @op1.ext_bytes, @op1.ext_bytes_bits, @op1.type_token
        end calminstruction

end iterate ; <size, size_bits>

;; LEA ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

define lea?

; TODO: Comment
calminstruction lea.l? operands&
    xcall m68k.parse_and_validate_instruction, <lea>, operands, <l>, <l>

    emit 1, 01000001b or @op2.ea_reg_bits shl 1
    emit 1, 11000000b or @op1.ea_mode_bits shl 3 or @op1.ea_reg_bits
                
    ; extension words
    call emit_ext_words, @op1.ext_bytes, @op1.ext_bytes_bits, @op1.type_token
end calminstruction

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Syntax:
;     addq #<data>,<ea>
;     subq #<data>,<ea>
; Valid imm range: 1-8 (8 is encoded as 000b i.e. 0).
iterate <instr,  first_byte>, \
        addq,    01010000b, \
        subq,    01010001b

    define instr?

    iterate <size,  size_bits>, \
            b,      0, \
            w,      01000000b, \
            l,      10000000b

            calminstruction instr.size? operands&
                xcall m68k.parse_and_validate_instruction, \
                    <instr>, operands, <size>, <size>

                assert_min @op1.imm, 1
                assert_max @op1.imm, 8

                local tmp
                ; 8 is encoded as 000b
                compute tmp, @op1.imm mod 8
                emit 1, first_byte or tmp shl 1
                emit 1, size_bits or @op2.ea_mode_bits shl 3 or @op2.ea_reg_bits
                
                ; extension words
                emit_be @op2.ext_bytes, @op2.ext_bytes_bits
            end calminstruction

    end iterate ; <size, size_bits>
end iterate ; <instr, first_byte>

;; MOVEQ ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

define moveq?

; Description:
;     Move the literal to a data register. The literal data is an
;     eight-bit signed value (-128 to +127). The literal is sign-extended
;     to 32 bits to cover the whole of the data register.
; Arguments:
;     data: 0000_0000 - 1111_1111
;     dn: d0 - d7
; TODO: Give error if data is out of range.
calminstruction moveq.l? operands&
    xcall m68k.parse_and_validate_instruction, <moveq>, operands, <l>, <l>

    ; TODO: Hm I think this is tricky because what the user can be different.
    ;       They can enter bits like `1111_1111b` which is valid however
    ;       converted into a positive number that will be +255. 255 (as a
    ;       signed number) is in a way out of range. The signed range is
    ;       -128 to 127. So how do I constrain the value here?
    ;       It's almost as if I need to know if they uses binary, hex or
    ;       decimal...
    assert_min @op1.imm, -128 ; I think this is invalid under all circumstances.
    assert_max @op1.imm, 255  ; Valid for unsigned but invalid for signed...

    emit 1, 01110000b or @op2.ea_reg_bits shl 1
    emit 1, @op1.imm
end calminstruction