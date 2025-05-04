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

            ; Supposed to be called.
            calminstruction instr#dir#size#_dyadic_data_reg? dn1*, dn2*
                assert_data_reg dn1
                assert_data_reg dn2

                emit 1, 11100000b + (0 scaleof dn1) shl 1 + dir_bit
                emit 1, size_bits shl 6 + 1 shl 5 + instr_bits shl 3 + \
                        (0 scaleof dn2)
            end calminstruction

            ; Supposed to be called.
            calminstruction instr#dir#size#_dyadic_imm? imm*, dn*
                    local tmp

                    assert_min imm, 1
                    assert_max imm, 8
                    assert_data_reg dn

                    ; 8 is encoded as 0, I think mod with 8 takes care of that.
                    compute tmp, imm mod 8
                    emit 1, 11100000b + (tmp shl 1) + dir_bit
                    emit 1, size_bits shl 6 + instr_bits shl 3 + (0 scaleof dn)
            end calminstruction

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
                        local op1, op2

                        call m68k.split_operands, operands
                        arr_tra op1, =m68k.=split_operands_result.=op1
                        arr_tra op2, =m68k.=split_operands_result.=op2
                        check m68k.split_operands_result.num_operands = 1
                        jyes one_operand
                ; two_operands:
                        check op1 relativeto m68k.data_reg
                        jyes data_reg
                    ; immediate:
                        call instr#dir#size#_dyadic_imm, op1, op2
                        exit
                    data_reg:
                        call instr#dir#size#_dyadic_data_reg, op1, op2
                        exit
                one_operand:
                        ; TODO: I think this one can only be .w
                        ; Seems manual says if monadic then it shift a word.
                        ; Double-check this. As it is I generate instructions
                        ; for all sizes right now.
                        emit 1, 11100000b + instr_bits shl 1 + dir_bit
                        emit 1, 11000000b + @op1.ea_mode_bits shl 3 + \
                                @op1.ea_reg_bits

                        ; <ea> extension words
                        call emit_ext_words, @op1.ext_bytes, @op1.ext_bytes_bits
            end calminstruction

        end iterate ; <size, size_bits>
    end iterate ; <dir, dir_bit>
end iterate ; <instr, instr_bits>