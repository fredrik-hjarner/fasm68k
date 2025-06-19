; The purpose of this file is just to set fasm68k settings.

; include "listing.inc"

; TODO: I should really use that this format I have in some TODO, set?
m68k.settings.optimize_cmp_to_cmpi = 2 ; TODO: Test if 1 and 2 works.
m68k.settings.optimize_or_to_ori = 2
m68k.settings.optimize_and_to_andi = 2
m68k.settings.optimize_sub_to_subi = 2
m68k.settings.optimize_add_to_addi = 2
; TODO: Setting optimize_cmp_to_cmpi again will wrreck stuff!!! Fix.
; m68k.settings.optimize_cmp_to_cmpi = 2
include 'valid_instructions.asm'