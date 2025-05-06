; Syntax:
;     ori.[bwl]  #<data>,<ea>
;     andi.[bwl] #<data>,<ea>
;     subi.[bwl] #<data>,<ea>
;     addi.[bwl] #<data>,<ea>
;     eori.[bwl] #<data>,<ea>
;     cmpi.[bwl] #<data>,<ea>
; Addressing modes:
;     Dn  An  (An)  (An)+  ‑(An)  (d,An)  (d,An,Xi) 
;      ✓       ✓     ✓       ✓      ✓         ✓ 
;     ABS.W  ABS.L  (d,PC)  (d,PC,Xn)  imm
;       ✓     ✓           
; Syntax (some of them have crr/sr variants):
;     ori.b  #<data>,ccr
;     ori.w  #<data>,sr
;     andi.b #<data>,ccr
;     andi.w #<data>,sr
;     eori.b #<data>,ccr
;     eori.w #<data>,sr
; TODO: Double check addressing modes for each instruction.
; TODO: Should validate that imm.l, imm.w and imm.b are within bounds.
; TODO: Explain ccr_variant and sr_variant and that 0 mean instr has no such.
iterate <instr,  instr_word,         ccr_variant,        sr_variant>, \
        ori,     0000000000000000b,  0000000000111100b,  0000000001111100b, \
        andi,    0000001000000000b,  0000001000111100b,  0000001001111100b, \
        subi,    0000010000000000b,  0,                  0, \
        addi,    0000011000000000b,  0,                  0, \
        eori,    0000101000000000b,  0000101000111100b,  0000101001111100b, \
        cmpi,    0000110000000000b,  0,                  0
    ; TODO: Can I remove the imm_bytes now and use the stuff from
    ; parse_operand instread?
    iterate <size,  size_str, size_bits,  imm_bytes>, \
            <>,      '',       0,          0, \
            .b,      'b',      00b,        2, \
            .w,      'w',      01b,        2, \
            .l,      'l',      10b,        4

            calminstruction instr#size? operands&
                        local tmp

                        call m68k.split_operands, operands
                        call m68k.parse_operand@op1, m68k.split_operands_result.op1
                        call m68k.parse_operand@op2, m68k.split_operands_result.op2

                ;; CHECK CCR ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                        ; TODO: Add .type_token for convenience? Prolly not...
                        check ccr_variant <> 0 & @op2.type = 'ccr' & \
                              (size_str = 'b' | size_str = '')
                        jno check_sr
                    ; ccr:
                        emit_be 2, ccr_variant

                        ; imm
                        emit_be 2, @op1.imm
                        exit
                ;; CKECK SR ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                check_sr:
                        check sr_variant <> 0 & @op2.type = 'sr' & \
                              (size_str = 'w' | size_str = '')
                        jno normal_case
                    ; sr:
                        emit_be 2, sr_variant

                        ; imm
                        emit_be 2, @op1.imm
                        exit
                normal_case:
                        ; TODO: Assert that imm is within bounds.
                        ; assert_min imm, 1
                        ; assert_max imm, 8

                        emit_be 2, instr_word + size_bits shl 6 + \
                                @op2.ea_mode_bits shl 3 + @op2.ea_reg_bits
                        
                        ; immediate bytes
                        emit_be imm_bytes, @op1.imm

                        ; extension words
                        call emit_ext_words, @op2.ext_bytes, @op2.ext_bytes_bits
            end calminstruction

    end iterate ; <size, size_bits>
end iterate ; <instr, instr_word>