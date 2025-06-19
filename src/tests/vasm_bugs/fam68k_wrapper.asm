; The purpose of this file is just to set fasm68k settings.

include "listing.inc"

; TODO: I should really use that this format I have in some TODO, set?
m68k.settings.optimize_or_to_ori = 0
m68k.settings.optimize_and_to_andi = 0
m68k.settings.optimize_sub_to_subi = 0
m68k.settings.optimize_add_to_addi = 0
m68k.settings.optimize_cmp_to_cmpi = 0

include 'valid_instructions.asm'