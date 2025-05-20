;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; MOVE INSTRUCTION                                                           ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

define move?

; Syntax:
;     move.w     sr,   <ea>
;     move.w     <ea>, ccr
;     move.w     <ea>, sr
;     move.l     usp,  an
;     move.l     an,   usp
;     move.[bwl] <ea1>, <ea2>
iterate <size, dot_size>, \
        _,     , \
        b,     .b, \
        w,     .w, \
        l,     .l

    calminstruction move#dot_size? operands&
            xcall m68k.parse_and_validate_instruction, <move>, \
                                                    operands, \
                                                    <size>, \
                                                    <size>
            match =sr, @op1.type_token
            jyes sr_to_ea
            match =ccr, @op2.type_token
            jyes ea_to_ccr
            match =sr, @op2.type_token
            jyes ea_to_sr
            match =usp, @op1.type_token
            jyes usp_to_an
            match =usp, @op2.type_token
            jyes an_to_usp

        ; ea_to_ea:
            call move_ea_to_ea_#size
            exit
        sr_to_ea:
            emit 1, 0100_0000_b
            emit 1, 1100_0000_b or @op2.ea_mode_bits shl 3 or @op2.ea_reg_bits 
            ; op1 extension words
            emit_be @op2.ext_bytes, @op2.ext_bytes_bits
            exit
        ea_to_ccr:
            emit 1, 0100_0100_b
            emit 1, 1100_0000_b or @op1.ea_mode_bits shl 3 or @op1.ea_reg_bits 
            ; op1 extension words
            call emit_ext_words, @op1.ext_bytes, @op1.ext_bytes_bits
            exit
        ea_to_sr:
            emit 1, 01000110b
            emit 1, 11000000b or @op1.ea_mode_bits shl 3 or @op1.ea_reg_bits 
            ; op1 extension words
            call emit_ext_words, @op1.ext_bytes, @op1.ext_bytes_bits
            exit
        usp_to_an:
            emit_be 2, 0100_1110__0110_1000_b or @op2.ea_reg_bits
            exit
        an_to_usp:
            emit_be 2, 0100_1110__0110_0000_b or @op1.ea_reg_bits
    end calminstruction

end iterate ; <size, dot_size>

iterate <size,  size_bits>, \
        _,      11000000000000b, \
        b,      01000000000000b, \
        w,      11000000000000b, \
        l,      10000000000000b

    ; Supposed to be call:ed.
    ; Assume that ea1 and ea2 has already been parsed with `parse_operand` and are
    ; available on @op1 and @op2.
    calminstruction move_ea_to_ea_#size
            ; emit_be 1st and 2nd byte in one go
            emit_be 2, size_bits or @op2.ea_reg_bits shl 9 or @op2.ea_mode_bits shl 6 or @op1.ea_mode_bits shl 3 or @op1.ea_reg_bits

            ; I need a special case here. If 'imm' and size b then need to limit
            ; it to max 255.
            initsym size, size ; This is to get match to accept `size`
            match =b, size
            jno skip_imm_b_fix
            match =imm, @op1.type_token
            jno skip_imm_b_fix
            ; fix
            compute @op1.ext_bytes_bits, @op1.ext_bytes_bits and $FF
        skip_imm_b_fix:

            ; op1 extension words
            call emit_ext_words, @op1.ext_bytes, @op1.ext_bytes_bits

            ; op2 extension words
            emit_be @op2.ext_bytes, @op2.ext_bytes_bits
    end calminstruction

end iterate ; <size, size_bits>