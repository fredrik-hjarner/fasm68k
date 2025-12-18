;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; EMIT_EXT_WORDS - Output Extension Words with PC-Relative Handling          ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Extension words provide additional data for complex addressing modes such  ;;
;; as displacements, absolute addresses, immediate values, and indexed modes. ;;
;;                                                                            ;;
;; This function handles three cases:                                         ;;
;;   1. Normal case: Emit extension words as-is                               ;;
;;   2. PC-relative with index d(PC,Xn): Calculate displacement from current $;;
;;   3. PC-relative with displacement d(PC): Calculate displacement from $    ;;
;;                                                                            ;;
;; PC-relative addressing requires special handling because:                  ;;
;;   - The displacement is relative to the extension word's address (not the  ;;
;;     instruction word's address)                                            ;;
;;   - We can't calculate the displacement until we know the final address    ;;
;;   - The 68000 calculates: effective_address = (current PC) + displacement  ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Emit extension words, handling PC-relative address calculation
; Parameters:
;   ext_bytes - Number of bytes to emit (2 or 4)
;   ext_bytes_bits - Data to emit (may contain multiple components for PC-relative)
;   type_token - Operand type token (pc_idx, pc_displace, or other)
calminstruction emit_ext_words? ext_bytes*, ext_bytes_bits*, type_token*
        match =pc_idx, type_token
        jyes pc_idx
        match =pc_displace, type_token
        jyes pc_displace
    ; Normal case: emit extension words without modification
        emit_be ext_bytes, ext_bytes_bits
        exit
    pc_idx:
        ; PC-relative with index: d(PC,Xn)
        ; Build brief extension word: [M Xn S 0 displacement]
        ; - '0 scaleof ext_bytes_bits' contains the M/Xn/S bits (index register info)
        ; - '1 scaleof ext_bytes_bits' contains the user-specified displacement 'd'
        ; - Actual displacement = d - $ (where $ is at the extension word)
        ; - Displacement is 8-bit signed, so mask with $FF
        ; TODO: Add range check - error if displacement doesn't fit in signed byte
        emit_be ext_bytes, (0 scaleof ext_bytes_bits) or \
                           ((1 scaleof ext_bytes_bits - $) and $FF)
        exit
    pc_displace:
        ; PC-relative with displacement only: d(PC)
        ; Emit 16-bit displacement word
        ; - '1 scaleof ext_bytes_bits' contains the user-specified displacement 'd'
        ; - Actual displacement = d - $ (where $ is at the extension word)
        ; TODO: Add range check - error if displacement doesn't fit in signed word
        emit_be ext_bytes, 1 scaleof ext_bytes_bits - $
end calminstruction