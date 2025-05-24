; Syntax:
;     ori.[bwl]  #<data>,<ea>
;     andi.[bwl] #<data>,<ea>
;     subi.[bwl] #<data>,<ea>
;     addi.[bwl] #<data>,<ea>
;     eori.[bwl] #<data>,<ea>
;     cmpi.[bwl] #<data>,<ea>
; Syntax (some of them have crr/sr variants):
;     ori.b  #<data>,ccr
;     ori.w  #<data>,sr
;     andi.b #<data>,ccr
;     andi.w #<data>,sr
;     eori.b #<data>,ccr
;     eori.w #<data>,sr
; TODO: Should validate that imm.l, imm.w and imm.b are within bounds.
; TODO: Explain ccr_variant and sr_variant and that 0 mean instr has no such.
iterate <instr,  instr_word,         ccr_variant,        sr_variant>, \
        ori,     0000000000000000b,  0000000000111100b,  0000000001111100b, \
        andi,    0000001000000000b,  0000001000111100b,  0000001001111100b, \
        subi,    0000010000000000b,  0,                  0, \
        addi,    0000011000000000b,  0,                  0, \
        eori,    0000101000000000b,  0000101000111100b,  0000101001111100b, \
        cmpi,    0000110000000000b,  0,                  0

    define instr?

    ; TODO: Can I remove the imm_bytes now and use the stuff from
    ; parse_operand instread?
    iterate <size,  dot_size,  size_str, size_bits,  imm_bytes, max_imm_size>, \
            _,      ,          '',       0,          0,         $FFFF, \
            b,      .b,        'b',      00000000b,  2,         $FF, \
            w,      .w,        'w',      01000000b,  2,         $FFFF, \
            l,      .l,        'l',      10000000b,  4,         $FFFFFFFF

            calminstruction instr#dot_size? operands&
                xcall ori_and_etc_impl, operands, <instr>, <instr_word>, \
                                        <ccr_variant>, <sr_variant>, <size>, \
                                        <size_bits>, <imm_bytes>, <max_imm_size>
            end calminstruction

    end iterate ; <size, dot_size, size_str, size_bits, imm_bytes>
end iterate ; <instr, instr_word>

; Splitting up instructions like this with macros (above) and one implementation
; body seems to yield better performance.
calminstruction ori_and_etc_impl? operands*, instr*, instr_word*, \
                                  ccr_variant*, sr_variant*, size*, \
                                  size_bits*, imm_bytes*, max_imm_size*

            call m68k.parse_and_validate_instruction, instr, operands, size
    ;; CHECK CCR ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            match =ccr, @op2.type_token
            jno check_sr
        ; ccr:
            emit_be 2, ccr_variant
            emit_be 2, @op1.imm and max_imm_size
            exit
    ;; CKECK SR ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    check_sr:
            match =sr, @op2.type_token
            jno normal_case
        ; sr:
            emit_be 2, sr_variant
            emit_be 2, @op1.imm
            exit
    normal_case:
            ; TODO: Assert that imm is within bounds.
            ; assert_min imm, 1
            ; assert_max imm, 8

            emit_be 2, instr_word or size_bits or \
                    @op2.ea_mode_bits shl 3 + @op2.ea_reg_bits
            
            ; immediate bytes
            emit_be imm_bytes, @op1.imm and max_imm_size

            ; extension words
            emit_be @op2.ext_bytes, @op2.ext_bytes_bits
end calminstruction