define size_to_size_bit? size_to_size_bit
size_to_size_bit.w? := 0
size_to_size_bit.l? := 1

; stores return value for `parse_complex_operand`
; 1 if the operand was identified, otherwise 0.
define parse_complex_operand_ret?

calminstruction m68k.parse_complex_operand#op? operand*
                    local d
                    local in_paren
                    local pc_or_an
                    local xn
                    local size
                    local m
                    local an

                    match d?(in_paren), operand
                    jno return_false
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;; IDENTIDY OPERAND TYPE                                          ;;
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                    match , d
                    jno has_d_prefix
    ; operand has no d prefix
                    match (d=,in_paren), operand
                    jno return_false
                    check d relativeto m68k.address_reg
                    jno has_d_prefix ; re-use the same code.
                    ; `(an, xn)` where `d` is omitted is handled as a special
                    ; case. it's currently reusing other code but maybe it
                    ; should be a separate case (TODO).
                    match (in_paren), operand
                    compute d, 0
                    jump operand_is_not_d_pc
    has_d_prefix:
                    ; See docs/compatability.md for explanation
                    massage_expression d
                    compute d, d
                    match =pc, in_paren
                    jyes d_pc
        operand_is_not_d_pc:
                    match pc_or_an=,xn, in_paren
                    jno d_an
            ; operand has index:
                    match xn.size, xn
                    jyes explicit_size
                ; xn has no explicit size
                    compute size, 0 ; 0 means word. use word as default.
                    jump check_dn_or_an
                explicit_size:
                    arrange size, size_to_size_bit.size
                    compute size, size
                check_dn_or_an:
                    compute m, 0 ; init default. 0 means xn is data register
                    check xn relativeto m68k.data_reg
                    jyes check_pc_or_an
                ; xn is an address register
                    compute m, 1 ; 1 means address register.
                check_pc_or_an:
                    match =pc, pc_or_an
                    jyes d_pc_xn
                    jump d_an_xn
    no_d_prefix:
                    ; TODO: Implement
                    ; compute parse_complex_operand_ret, 1
                    jump return_false
                    exit
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;; CALCULATE OPERAND PROPERTIES                                   ;;
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    d_pc:
                    compute type, '(d,pc)'
                    arrange type_token, =pc_displace
                    compute ea_mode_bits, 111b
                    compute ea_reg_bits, 010b
                    compute ext_bytes, 2
                    ; See docs/pc_relative_addressing.md for explanation
                    compute ext_bytes_bits, pc_relative_decorator * d
                    compute parse_complex_operand_ret, 1
                    exit
    d_an:
                    compute type, '(d,an)'
                    arrange type_token, =an_displace
                    compute ea_mode_bits, 101b
                    compute ea_reg_bits, 0 scaleof in_paren
                    compute ext_bytes, 2
                    compute ext_bytes_bits, d
                    compute parse_complex_operand_ret, 1
                    exit
    d_pc_xn:
                    compute type, '(d,pc,xn)'
                    arrange type_token, =pc_idx
                    compute ea_mode_bits, 111b
                    compute ea_reg_bits, 011b
                    compute ext_bytes, 2
                    ; See docs/pc_relative_addressing.md for explanation
                    compute ext_bytes_bits, \
                        m shl 15 + (0 scaleof xn) shl 12 + \
                        \ ; TODO: Err if `d` is too big when emitting.
                        size shl 11 + d * pc_relative_decorator
                    compute parse_complex_operand_ret, 1
                    exit
    d_an_xn:
                    compute type, '(d,an,xn)'
                    arrange type_token, =an_idx
                    compute ea_mode_bits, 110b
                    compute ea_reg_bits, 0 scaleof pc_or_an
                    compute ext_bytes, 2
                    ; TODO: The displacement could only be max one byte
                    ;       and I should validate that.
                    compute ext_bytes_bits, \
                        m shl 15 or (0 scaleof xn) shl 12 or \
                        \ ; d is just allowed to fill 1 byte
                        \ ; TODO: Err if `d` does not fit a byte.
                        size shl 11 or (d and $FF)
                    compute parse_complex_operand_ret, 1
                    exit
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    return_false:
                    compute parse_complex_operand_ret, 0
end calminstruction