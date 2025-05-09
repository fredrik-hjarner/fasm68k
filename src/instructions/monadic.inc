;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Motorola 68000 monadic instructions                                        ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; UNLK ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Syntax:
;     unlk an
; Attributes:
;     Unsized
calminstruction unlk? an*
    assert_word_aligned
    call m68k.parse_operand@op1, an
    emit_be 2, 0100111001011000b + @op1.ea_reg_bits
end calminstruction

;; STOP ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Syntax:
;     stop #<data>
; Sample syntax:
;     stop #$2700
;     stop #setup ; TODO: Observe this example. I must make that work!!!
; Attributes:
;     Unsized
calminstruction stop? imm*
    assert_word_aligned
    call m68k.parse_operand@op1, imm

    emit_be 2, 0100111001110010b

    ; imm
    emit_be 2, @op1.imm
end calminstruction

;; NCBD, PEA, TAS ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Syntax:
;     nbcd.b <ea>
;     pea.l  <ea>
;     tas.b  <ea>
; TODO:
;     !!!
;     THESE INSTRUCTIONS WERE PRETTY NICELY IMPLEMENTED
;     CHECK TO SEE IF ANY OTHER INSTRUCTIONS COULD BE BAKED INTO THIS PATTER
;     AND ADDED INTO THE BODY OF THIS ITERATE CONSTRUCTION.
iterate <instr, instr_word>, \
        nbcd.b, 0100100000000000b, \
        pea.l,  0100100001000000b, \
        tas.b,  0100101011000000b

        calminstruction instr? operands&
            assert_word_aligned

            call m68k.split_operands, operands
            call m68k.parse_operand@op1, m68k.split_operands_result.op1

            emit_be 2, instr_word + @op1.ea_mode_bits shl 3 + @op1.ea_reg_bits

            ; <ea> extension words
            call emit_ext_words, @op1.ext_bytes, @op1.ext_bytes_bits
        end calminstruction

end iterate ; <instr, instr_word>

;; SCC ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Syntax:
;     scc.b <ea>
; Aliases:
;     hs = cc
;     lo = cs
iterate <cc,  cc_bits>, \
        t,      0000b, \
        f,      0001b, \
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

        calminstruction s#cc.b? operands&
                assert_word_aligned

                call m68k.split_operands, operands
                call m68k.parse_operand@op1, m68k.split_operands_result.op1

                emit_be 1, 01010000b + cc_bits
                emit_be 1, 11000000b + @op1.ea_mode_bits shl 3 + @op1.ea_reg_bits

                ; <ea> extension words
                call emit_ext_words, @op1.ext_bytes, @op1.ext_bytes_bits
        end calminstruction

end iterate ; <cc, cc_bits>

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Syntax:
;     negx <ea>
;     clr  <ea>
;     neg  <ea>
;     not  <ea>
;     tst  <ea>
; Addressing modes:
;     Dn  An  (An)  (An)+  ‑(An)  (d,An)  (d,An,Xi) 
;      ✓       ✓     ✓       ✓      ✓         ✓ 
;     ABS.W  ABS.L  (d,PC)  (d,PC,Xn)  imm
;       ✓     ✓                 
; TODO: Double-check addressing modes for all instructions.
;     tst also supports (d,PC)  (d,PC,Xn) modes
; TODO: Restrict to valid addressing modes for the instructions.
iterate <instr,  first_byte>, \
        negx,    01000000b, \
        clr,     01000010b, \
        neg,     01000100b, \
        not,     01000110b, \
        tst,     01001010b
    iterate <size,  size_bits>, \
            b,      00b, \
            w,      01b, \
            l,      10b
    
        calminstruction instr.size? operands&
                assert_word_aligned

                call m68k.split_operands, operands
                call m68k.parse_operand@op1, m68k.split_operands_result.op1

                emit_be 1, first_byte
                emit_be 1, size_bits shl 6 + @op1.ea_mode_bits shl 3 + @op1.ea_reg_bits

                ; <ea> extension words
                call emit_ext_words, @op1.ext_bytes, @op1.ext_bytes_bits
            end calminstruction

    end iterate ; <size, size_bits>
end iterate ; <instr, first_byte>

; Syntax:
;   bcc.b <label>
;   bcc.w <label>
;
; TODO: What exactly does label and literal mean in this context?
; Aliases:
;     hs = cc
;     lo = cs
iterate <cc,  cc_bits>, \
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

        ; TODO: Check if fits in a byte. Maybe do that in parse_operand?
        ; Also, check if displacement is a valid displacement.
        ; 0 is not allowed for .b I think.
        ; TODO: How will this be able to work with both label and literals???
        calminstruction? b#cc.b? label*
            assert_word_aligned

            local pc
            local label_val

            ; call m68k.parse_operand@op1, label

            compute pc, $ + 2
            compute label_val, label

            emit_be 1, 01100000b + cc_bits

            ; Assume label is $10 and address is $20
            ; $10 - $20 = $10
            emit_be 1, label_val - pc
        end calminstruction

        ; TODO: Check if fits in a word. Maybe do that in parse_operand?
        ;' Warn if fits in a byte.
        ; TODO: How will this be able to work with both label and literals???
        calminstruction? b#cc.w? label*
            assert_word_aligned

            local pc
            local label_val

            ; call m68k.parse_operand@op1, label

            compute pc, $ + 2
            compute label_val, label

            emit_be 1, 01100000b + cc_bits
            emit_be 1, 0 ; second byte being zero
            emit_be 2, label_val - pc
        end calminstruction

        ; alias for .b
        ; TODO: Move to aliases.inc file!!!
        macro b#cc.s? line&
            b#cc.b line
        end macro

        ; TODO: Move to aliases.inc file!!!
        macro b#cc? line&
            b#cc.w line
        end macro

end iterate ; <cc, cc_bits>

; Syntax:
;   bra.w <label> | <literal>
;   bra.b <label> | <literal>
;   bsr.w <label> | <literal>
;   bsr.b <label> | <literal>
;
; TODO: What exactly does label and literal mean in this context?
iterate <instr,  first_byte>, \
        bra,     01100000b, \
        bsr,     01100001b

        ; TODO: Check if fits in a byte. Maybe do that in parse_operand?
        ; Also, check if displacement is a valid displacement.
        ; 0 is not allowed for .b I think.
        ; TODO: How will this be able to work with both label and literals???
        calminstruction? instr.b? label*
                assert_word_aligned

                local pc
                local label_val

                ; call m68k.parse_operand@op1, label

                compute pc, $ + 2
                compute label_val, label

                emit_be 1, first_byte

                ; Assume label is $10 and address is $20
                ; $10 - $20 = $10
                emit_be 1, label_val - pc
        end calminstruction

        ; TODO: Check if fits in a word. Maybe do that in parse_operand?
        ;' Warn if fits in a byte.
        ; TODO: How will this be able to work with both label and literals???
        calminstruction? instr.w? label*
            assert_word_aligned

            local pc
            local label_val

            ; call m68k.parse_operand@op1, label

            compute pc, $ + 2
            compute label_val, label

            emit_be 1, first_byte
            emit_be 1, 0 ; second byte being zero
            emit_be 2, label_val - pc
        end calminstruction

end iterate ; <instr, first_byte>

;; EXL ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Syntax:
;     ext.[wl] dn
iterate <size,  size_bit>, \
        w,      0, \
        l,      1

        calminstruction ext.size? dn*
            assert_word_aligned
            call m68k.parse_operand@op1, dn
            assert_data_reg dn
            emit_be 2, 0100_1000___1000_0000_b + size_bit shl 6 + @op1.ea_reg_bits
        end calminstruction
            
end iterate ; <size, size_bit>

;; JMP, JSR ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Syntax:
;     jmp <ea>
;     jsr <ea>
; Addressing modes:
;     Dn  An  (An)  (An)+  ‑(An)  (d,An)  (d,An,Xi) 
;              ✓                    ✓         ✓ 
;     ABS.W  ABS.L  (d,PC)  (d,PC,Xn)  imm
;       ✓     ✓       ✓        ✓
; TODO: Restrict to valid addressing modes for jmp/jsr.
iterate <instr,  second_byte>, \
        jmp,     11000000b, \
        jsr,     10000000b

        calminstruction instr? operands&
            assert_word_aligned

            call m68k.split_operands, operands
            call m68k.parse_operand@op1, m68k.split_operands_result.op1

            emit_be 1, 01001110b
            emit_be 1, second_byte + @op1.ea_mode_bits shl 3 + @op1.ea_reg_bits
            
            ; <ea> extension words
            call emit_ext_words, @op1.ext_bytes, @op1.ext_bytes_bits
        end calminstruction

end iterate ; <instr, second_byte>

; Syntax: swap dn
;
; Exchange the upper and lower 16-bit words of a data register.
; arguments:
;     dn: data register (d0 - d7)
calminstruction swap.w? dn*
    assert_word_aligned

    call m68k.parse_operand@op1, dn

    assert_data_reg dn

    emit_be 2, 0100_1000__0100_0000b + @op1.ea_reg_bits
end calminstruction

; Syntax: trap #<vector>
;
; Trigger any of the 16 "trap" interrupts.
; arguments:
;     vector: 0000 - 1111
calminstruction trap? vector*
        assert_word_aligned

        call m68k.parse_operand@op1, vector

        check @op1.type eq 'imm'
        jyes skip_error
        ; TODO: I should prolly have a better way to display error messages
        ; Some more general error handling stuff.
        display @op1.type bappend 13 bappend 10
        display @op1.type
        err 'trap only accepts immediate values'
    skip_error:

        assert_min vector, 0
        assert_max vector, 15

        emit_be 2, 0100_1110__0100_0000b + vector
end calminstruction