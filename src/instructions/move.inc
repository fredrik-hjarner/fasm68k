;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; MOVE INSTRUCTION                                                           ;;
;; TODO: Could probably be refactored a bit.                                  ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Supposed to be called.
calminstruction move_macro? op1*, op2*, size
        call m68k.parse_operand@op1, op1, size
        call m68k.parse_operand@op2, op2, size

        ; TODO: This checks could be more complete.
        check @op1.type = 'sr'
        jyes sr_to_ea
        check @op2.type = 'ccr'
        jyes ea_to_ccr
        check @op2.type = 'sr'
        jyes ea_to_sr
        check @op1.type = 'usp'
        jyes usp_to_an
        check @op2.type = 'usp'
        jyes an_to_usp
        jump ea_to_ea

    sr_to_ea:
        emit 1, 0100_0000_b
        emit 1, 1100_0000_b + @op2.ea_mode_bits shl 3 + @op2.ea_reg_bits 
        ; op1 extension words
        call emit_ext_words, @op2.ext_bytes, @op2.ext_bytes_bits
        jump done
    ea_to_ccr:
        emit 1, 0100_0100_b
        emit 1, 1100_0000_b + @op1.ea_mode_bits shl 3 + @op1.ea_reg_bits 
        ; op1 extension words
        call emit_ext_words, @op1.ext_bytes, @op1.ext_bytes_bits
        jump done
    ea_to_sr:
        emit 1, 01000110b
        emit 1, 11000000b + @op1.ea_mode_bits shl 3 + @op1.ea_reg_bits 
        ; op1 extension words
        call emit_ext_words, @op1.ext_bytes, @op1.ext_bytes_bits
        jump done
    usp_to_an:
        emit 2, 0100_1110__0110_1000_b + @op2.ea_reg_bits
        jump done
    an_to_usp:
        emit 2, 0100_1110__0110_0000_b + @op1.ea_reg_bits
        jump done
    ea_to_ea:
        call move_ea_to_ea, size
        jump done
    done:
end calminstruction

; TODO: move.[bwl] prolly should use `macro calminstruction?.` extensions that
; can be in the .[bwl] variants reused
; Syntax:
;     move.w     sr,   <ea>
;     move.w     <ea>, ccr
;     move.w     <ea>, sr
;     move.l     usp,  an
;     move.l     an,   usp
;     move.[bwl] <ea1>, <ea2>
iterate size,  b,w,l
    calminstruction move.size? operands&
        local _size

        ; TODO: I am not sure why I have to do this to get the `call` to work...
        arrange _size, =size

        call m68k.split_operands, operands
        call move_macro, \
            m68k.split_operands_result.op1, \
            m68k.split_operands_result.op2, \
            _size
    end calminstruction
end iterate

calminstruction move? operands&
    call m68k.split_operands, operands
    call move_macro, \
        m68k.split_operands_result.op1, \
        m68k.split_operands_result.op2
end calminstruction

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
        ; emit 1st and 2nd byte in one go
        emit 2, size_bits shl 12 + @op2.ea_reg_bits shl 9 + @op2.ea_mode_bits shl 6 + @op1.ea_mode_bits shl 3 + @op1.ea_reg_bits

        ; op1 extension words
        call emit_ext_words, @op1.ext_bytes, @op1.ext_bytes_bits

        ; op2 extension words
        call emit_ext_words, @op2.ext_bytes, @op2.ext_bytes_bits
end calminstruction