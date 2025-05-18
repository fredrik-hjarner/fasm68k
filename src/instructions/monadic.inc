;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Motorola 68000 monadic instructions                                        ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; UNLK ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Syntax:
;     unlk an
; Attributes:
;     Unsized
calminstruction unlk? operands&
    xcall m68k.parse_and_validate_instruction, <unlk>, operands, <_>
    emit_be 2, 0100111001011000b or @op1.ea_reg_bits
end calminstruction

;; STOP ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Syntax:
;     stop #<data>
; Sample syntax:
;     stop #$2700
;     stop #setup ; TODO: Observe this example. I must make that work!!!
; Attributes:
;     Unsized
calminstruction stop? operands&
    xcall m68k.parse_and_validate_instruction, <stop>, operands, <_>
    emit_be 2, 0100111001110010b
    emit_be 2, @op1.imm
end calminstruction

;; NCBD, PEA, TAS ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

define nbcd?
define pea?
define tas?

; Syntax:
;     nbcd.b <ea>
;     pea.l  <ea>
;     tas.b  <ea>
iterate <instr, size, dot_size, instr_word>, \
        nbcd,   _,    ,         0100100000000000b, \
        nbcd,   b,    .b,       0100100000000000b, \
        pea,    _,    ,         0100100001000000b, \
        pea,    l,    .l,       0100100001000000b, \
        tas,    _,    ,         0100101011000000b, \
        tas,    b,    .b,       0100101011000000b

        calminstruction instr#dot_size? operands&
            xcall m68k.parse_and_validate_instruction, <instr>, operands, <size>

            emit_be 2, instr_word or @op1.ea_mode_bits shl 3 or @op1.ea_reg_bits

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

        define s#cc?

        calminstruction s#cc.b? operands&
                xcall m68k.parse_and_validate_instruction, <s#cc>, operands, <b>

                emit 1, 01010000b or cc_bits
                emit 1, 11000000b or @op1.ea_mode_bits shl 3 or @op1.ea_reg_bits

                ; <ea> extension words
                emit_be @op1.ext_bytes, @op1.ext_bytes_bits
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

    define instr?

    iterate <size,  size_bits>, \
            b,      00b, \
            w,      01b, \
            l,      10b
    
        calminstruction instr.size? operands&
            xcall m68k.parse_and_validate_instruction, <instr>, operands, <size>

            emit 1, first_byte
            emit 1, size_bits shl 6 or @op1.ea_mode_bits shl 3 or @op1.ea_reg_bits

            ; <ea> extension words
            emit_be @op1.ext_bytes, @op1.ext_bytes_bits
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

        define b#cc?

        ; TODO: Check if fits in a byte. Maybe do that in parse_operand?
        ; Also, check if displacement is a valid displacement.
        ; 0 is not allowed for .b I think.
        ; TODO: How will this be able to work with both label and literals???
        calminstruction? b#cc.b? operands&
            xcall m68k.parse_and_validate_instruction, <b#cc>, operands, <b>

            local pc
            compute pc, $ + 2

            emit 1, 01100000b or cc_bits

            ; may look strange but it works.
            ; @op1.ext_bytes_bits will contain the value the label (op1).
            emit 1, @op1.ext_bytes_bits - pc
        end calminstruction

        ; TODO: Check if fits in a word. Maybe do that in parse_operand?
        ;' Warn if fits in a byte.
        ; TODO: How will this be able to work with both label and literals???
        calminstruction? b#cc.w? operands&
            xcall m68k.parse_and_validate_instruction, <b#cc>, operands, <w>

            emit 1, 01100000b or cc_bits
            emit 1, 0 ; second byte being zero
            emit_be 2, @op1.ext_bytes_bits - $
        end calminstruction

        ; alias for .b
        macro b#cc.s? line&
            b#cc.b line
        end macro

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

        define instr?

        ; TODO: Check if fits in a byte. Maybe do that in parse_operand?
        ; Also, check if displacement is a valid displacement.
        ; 0 is not allowed for .b I think.
        ; TODO: How will this be able to work with both label and literals???
        calminstruction? instr.b? operands&
                xcall m68k.parse_and_validate_instruction, <instr>, operands, <b>

                local pc
                compute pc, $ + 2

                emit 1, first_byte
                emit 1, @op1.ext_bytes_bits - pc
        end calminstruction

        ; TODO: Check if fits in a word. Maybe do that in parse_operand?
        ;' Warn if fits in a byte.
        ; TODO: How will this be able to work with both label and literals???
        calminstruction? instr.w? operands&
            xcall m68k.parse_and_validate_instruction, <instr>, operands, <b>

            emit 1, first_byte
            emit 1, 0 ; second byte being zero
            emit_be 2, @op1.ext_bytes_bits - $
        end calminstruction

end iterate ; <instr, first_byte>

;; EXL ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

define ext?

; Syntax:
;     ext.[wl] dn
iterate <size,  size_bit>, \
        w,      0, \
        l,      1

        calminstruction ext.size? operands&
            xcall m68k.parse_and_validate_instruction, <ext>, operands, <size>

            emit_be 2, 0100_1000___1000_0000_b or size_bit shl 6 or @op1.ea_reg_bits
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
            xcall m68k.parse_and_validate_instruction, <instr>, operands, <_>

            emit 1, 01001110b
            emit 1, second_byte or @op1.ea_mode_bits shl 3 or @op1.ea_reg_bits
            
            ; <ea> extension words
            call emit_ext_words, @op1.ext_bytes, @op1.ext_bytes_bits
        end calminstruction

end iterate ; <instr, second_byte>

;; SWAP ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

define swap?

; Syntax: swap dn
;
; Exchange the upper and lower 16-bit words of a data register.
; arguments:
;     dn: data register (d0 - d7)
iterate <size, dot_size>, \
         _,    ,  \
         w,    .w

    calminstruction swap#dot_size? operands&
        xcall m68k.parse_and_validate_instruction, <swap>, operands, <w>

        emit_be 2, 0100_1000__0100_0000b or @op1.ea_reg_bits
    end calminstruction

end iterate ; <size, dot_size>

; Syntax: trap #<vector>
;
; Trigger any of the 16 "trap" interrupts.
; arguments:
;     vector: 0000 - 1111
calminstruction trap? operands&
        xcall m68k.parse_and_validate_instruction, <trap>, operands, <_>

        assert_min @op1.imm, 0
        assert_max @op1.imm, 15

        emit_be 2, 0100_1110__0100_0000b or @op1.imm
end calminstruction