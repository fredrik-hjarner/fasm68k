
equ_0 equ 0
equ_1 equ 1
; equ_imm_0 equ #0 ; You're not allowed to do this in vasm and clownassembler.
; equ_imm_1 equ #1 ; You're not allowed to do this in vasm and clownassembler.
equ_equ_1 equ equ_1
equ_1_plus_equ_1 equ equ_1+equ_1
; equ_a1 equ a1 ; You're not allowed to do this in vasm and clownassembler.

label_start:


; edge cases and so on

OBJ_SCENE_BASE = $1000

OBJ_SCENE_PLANT_ALT = OBJ_SCENE_BASE + $38

MEM_ACTION_TARGET_OBJID = $FFFF002E

    cmp.w #OBJ_SCENE_PLANT_ALT, (MEM_ACTION_TARGET_OBJID)

    ; or -> ori
    or.w #1, d1
    or.w #1, ($1)

; labels
label_end:

; equs and defines
