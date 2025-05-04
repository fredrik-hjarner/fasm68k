define m68k m68k

element m68k.data_reg
d0? := m68k.data_reg + 000b
d1? := m68k.data_reg + 001b
d2? := m68k.data_reg + 010b
d3? := m68k.data_reg + 011b
d4? := m68k.data_reg + 100b
d5? := m68k.data_reg + 101b
d6? := m68k.data_reg + 110b
d7? := m68k.data_reg + 111b

element m68k.address_reg
a0? := m68k.address_reg + 000b
a1? := m68k.address_reg + 001b
a2? := m68k.address_reg + 010b
a3? := m68k.address_reg + 011b
a4? := m68k.address_reg + 100b
a5? := m68k.address_reg + 101b
a6? := m68k.address_reg + 110b
a7? := m68k.address_reg + 111b
sp? := m68k.address_reg + 111b

; TODO: Do I even need these? I don't use them in any calculations?
; TODO: Comment
element pc
; TODO: Comment
element sr
; TODO: Comment
element ccr
; TODO: Comment
element usp

; TODO: pc_displacement and pc_index are not really registers, so maybe move
;       them?
; The `pc_displacement` is added to values when the d(pc) addressing mode is
; used.
element pc_displacement
; The `pc_index` is added to values when the d(pc,xn) addressing mode is used.
element pc_index