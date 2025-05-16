;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; MOVE INSTRUCTION                                                           ;;
;; TODO: Could probably be refactored a bit.                                  ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

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
            ; TODO: This checks could be more complete.
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
            jump ea_to_ea

        sr_to_ea:
            emit 1, 0100_0000_b
            emit 1, 1100_0000_b or @op2.ea_mode_bits shl 3 or @op2.ea_reg_bits 
            ; op1 extension words
            emit_be @op2.ext_bytes, @op2.ext_bytes_bits
            jump done
        ea_to_ccr:
            emit 1, 0100_0100_b
            emit 1, 1100_0000_b or @op1.ea_mode_bits shl 3 or @op1.ea_reg_bits 
            ; op1 extension words
            call emit_ext_words, @op1.ext_bytes, @op1.ext_bytes_bits
            jump done
        ea_to_sr:
            emit 1, 01000110b
            emit 1, 11000000b or @op1.ea_mode_bits shl 3 or @op1.ea_reg_bits 
            ; op1 extension words
            call emit_ext_words, @op1.ext_bytes, @op1.ext_bytes_bits
            jump done
        usp_to_an:
            emit_be 2, 0100_1110__0110_1000_b or @op2.ea_reg_bits
            jump done
        an_to_usp:
            emit_be 2, 0100_1110__0110_0000_b or @op1.ea_reg_bits
            jump done
        ea_to_ea:
            xcall move_ea_to_ea, <size>
            jump done
        done:
    end calminstruction

end iterate ; <size, dot_size>

; TODO: Comment
; For move_ea_to_ea specifically!
define m68k.move_size_bits
define m68k.move_size_bits.b 01b
define m68k.move_size_bits.w 11b
define m68k.move_size_bits.l 10b

; Supposed to be call:ed.
; Assume that ea1 and ea2 has already been parsed with `parse_operand` and are
; available on @op1 and @op2.
calminstruction move_ea_to_ea size:w
        local size_bits

        arrange size_bits, size
        transform size_bits, m68k.move_size_bits
        jyes skip_size_error
        err "size error" ; TODO: Better error message
    skip_size_error:
        ; emit_be 1st and 2nd byte in one go
        emit_be 2, size_bits shl 12 or @op2.ea_reg_bits shl 9 or @op2.ea_mode_bits shl 6 or @op1.ea_mode_bits shl 3 or @op1.ea_reg_bits

        ; op1 extension words
        call emit_ext_words, @op1.ext_bytes, @op1.ext_bytes_bits

        ; op2 extension words
        emit_be @op2.ext_bytes, @op2.ext_bytes_bits
end calminstruction