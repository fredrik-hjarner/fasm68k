;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Motorola 68000 Niladic Instructions (No Operands)                          ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; These instructions take no operands and are encoded as a single 16-bit     ;;
;; instruction word with no extension words.                                  ;;
;;                                                                            ;;
;; Implemented instructions:                                                  ;;
;;   ILLEGAL - Illegal instruction trap                                       ;;
;;   NOP     - No operation                                                   ;;
;;   RESET   - Reset external devices                                         ;;
;;   RTE     - Return from exception                                          ;;
;;   RTR     - Return and restore condition codes                             ;;
;;   RTS     - Return from subroutine                                         ;;
;;   TRAPV   - Trap on overflow                                               ;;
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
        assert_word_aligned           ; Ensure instruction is on even address
        emit_be 2, instr_word         ; Emit the 16-bit instruction word
    end calminstruction

end iterate