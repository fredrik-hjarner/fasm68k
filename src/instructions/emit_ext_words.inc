; TODO: Should this file be in a different folder?

; TODO: Comment what this does and why it is needed.
; Supposed to be called
; See where this is used in `parse_operand`.
; This function is needed when extension words are emitted,
; because of "pc relative addressing modes".
calminstruction emit_ext_words? ext_bytes*, ext_bytes_bits*, type_token*
        match =pc_idx, type_token
        jyes pc_idx
        match =pc_displace, type_token
        jyes pc_displace
    ; normal case. emit as normal:
        emit_be ext_bytes, ext_bytes_bits
        exit
    pc_idx:
        ; `0 scaleof ext_bytes_bits` hold the "M Xn S" part of the 
        ; `Brief Extension Word`, so we're just constructing the
        ; `Brief Extension Word` here by or:ing in the displacement.
        ; `1 scaleof ext_bytes_bits` holds the `d` part of `d(pc,xn)`.
         ; TODO: Error if too big to fit byte.
        emit_be ext_bytes, (0 scaleof ext_bytes_bits) or \
                           ((1 scaleof ext_bytes_bits - $) and $FF)
        exit
    pc_displace:
        ; TODO: Error if too big to fit word.
        ; `1 scaleof ext_bytes_bits` holds the `d` part of `d(pc)`.
        emit_be ext_bytes, 1 scaleof ext_bytes_bits - $
end calminstruction