;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Motorola 68000 variadic instructions.                                      ;;
;;                                                                            ;;
;; What I mean with "variadic" are instruction that can take either 1 or 2    ;;
;; operands so they aren't quite monadic or dyadic but rather both at the     ;;
;; same time in a way.                                                        ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Seems all of these only allow the immediate operande to be 1-8
; though it seems that 8 will be encoded as zero.
iterate <instr,  instr_bits>, \
        as,             00b, \
        ls,             01b, \
        rox,            10b, \
        ro,             11b
    iterate <dir,  dir_bit>, \
            r,            0b, \
            l,            1b
        iterate <size,  size_bits>, \
                b,             00b, \
                w,             01b, \
                l,             10b

            ; Description:
            ;     Arithmetic Shift Left.
            ;     See the different variants for more documentation.
            ; Arguments (monadic):
            ;     <ea>:
            ;         shift this location left by 1 bit
            ; Arguments (dyadic):
            ;     rotation:
            ;         - either a data register
            ;         - or an immediate value 000 - 111
            ;     dn: The data register that gets shifted: d0 - d7
            calminstruction instr#dir#.#size? operands&
                        xcall m68k.parse_and_validate_instruction, <instr#dir>,\
                                                                  operands, \
                                                                  <size>, \
                                                                  <size>

                        check m68k.split_operands_result.num_operands = 1
                        jyes one_operand
                ; two_operands:
                        match =dn, @op1.type_token
                        jyes data_reg
                    ; immediate:
                        assert_min @op1.imm, 1
                        assert_max @op1.imm, 8

                        local tmp
                        ; 8 is encoded as 0, I think mod with 8 takes care of that.
                        compute tmp, @op1.imm mod 8
                        emit 1, 11100000b or (tmp shl 1) or dir_bit
                        emit 1, size_bits shl 6 or instr_bits shl 3 or \
                                @op2.ea_reg_bits
                        exit
                    data_reg:
                        emit 1, 11100000b or @op1.ea_reg_bits shl 1 or dir_bit
                        emit 1, size_bits shl 6 or 1 shl 5 or instr_bits \
                                shl 3 + @op2.ea_reg_bits
                        exit
                one_operand:
                        ; TODO: I think this one can only be .w
                        ; Seems manual says if monadic then it shift a word.
                        ; Double-check this. As it is I generate instructions
                        ; for all sizes right now.
                        emit 1, 11100000b or instr_bits shl 1 or dir_bit
                        emit 1, 11000000b or @op1.ea_mode_bits shl 3 or \
                                @op1.ea_reg_bits

                        ; <ea> extension words
                        emit_be @op1.ext_bytes, @op1.ext_bytes_bits
            end calminstruction

        end iterate ; <size, size_bits>
    end iterate ; <dir, dir_bit>
end iterate ; <instr, instr_bits>