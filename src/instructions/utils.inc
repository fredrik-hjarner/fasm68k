; TODO: Should this file be in a different folder?

; TODO: Explain why this exists and what the purpose is.
; I need to convert positive and negative numbers to binary, to do that
; I use `store` and `load` since the store command does such a conversion.
; I am not sure if there is another easier way to make such a conversion.
virtual at 0
    one_byte::
    rb 1
end virtual

; TODO: Comment what this does and why it is needed.
; Supposed to be called
; See where this is used in `parse_operand`.
; This function is needed when extension words are emitted,
; because of "pc relative addressing modes" which causes some headache.
; TODO:
;     I think `0(pc)` and `0(pc, xn.s)` will break :'( test it out!
calminstruction emit_ext_words? ext_bytes*, ext_bytes_bits*
        local tmp

         ; TODO: Better name. Is pc where head of instruction is.
        local element_1_scale
        ; TODO: Better name. If this is the first ext word then it is 2.
        ;       If it is the 2nd ext word then it depends upon how many bytes
        ;       the ext words of the first operand has.
        ;       i.e. element_1_scale + bytes_into_instruction is the address of
        ;       where exactly this word is (will be emitted).

        ; TODO: Explain better.
        compute element_1_scale, 1 scaleof ext_bytes_bits
        ; If pc is part of it then 1 scaleof will not be 0, it could be positive
        ; and negative though. wll I dunno... Suure it can be negative if it
        ; wraps around 
        check element_1_scale <> 0
        jno default_case

        ; Here it's either of these two addressing modes:
        ;     - program counter with displacement
        ;     - program counter with index
        ; So I need to check which one of them it is.
        check 1 elementof ext_bytes_bits eq pc_displacement
        jyes pc_displacement
    ; pc_index:
        compute element_1_scale, element_1_scale - $
        ; use `store` and `load` for data massaging. needed so that negative
        ; values are constrained within1 byte.
        store one_byte:0, 1, element_1_scale
        load element_1_scale, one_byte:0, 1
        emit ext_bytes, (0 scaleof ext_bytes_bits) or element_1_scale
        jump done
    pc_displacement:
        emit ext_bytes, element_1_scale - $
        jump done
    default_case:
        emit ext_bytes, ext_bytes_bits
    done:
end calminstruction