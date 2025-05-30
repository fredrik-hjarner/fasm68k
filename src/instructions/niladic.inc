;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Motorola 68000 niladic instructions                                        ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

iterate <instr, instr_word>, \
    illegal,    0100_1010__1111_1100_b, \
    nop,        0100_1110__0111_0001_b, \
    reset,      0100_1110__0111_0000_b, \
    rte,        0100_1110__0111_0011_b, \
    rtr,        0100_1110__0111_0111_b, \
    rts,        0100_1110__0111_0101_b, \
    trapv,      0100_1110__0111_0110_b

    calminstruction instr?
        assert_word_aligned
        emit_be 2, instr_word
    end calminstruction

end iterate