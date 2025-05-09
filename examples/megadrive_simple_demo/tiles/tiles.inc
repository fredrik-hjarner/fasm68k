;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; CREATE TILES                                                               ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

set_write_vram vram_tiles_addr

; Tile $0 ; Fully transparent
repeat 8
    move.l #$00000000, vdp_data.l
end repeat

; Tile $1 ; Full square color 1
repeat 8
    move.l #$11111111, vdp_data.l
end repeat

; Tile $2
repeat 8
    move.l #$22222222, vdp_data.l
end repeat

; Tile $3
repeat 8
    move.l #$33333333, vdp_data.l
end repeat

; Tile $4
repeat 8
    move.l #$44444444, vdp_data.l
end repeat

; Tile $5
repeat 8
    move.l #$55555555, vdp_data.l
end repeat

; Tile $6
repeat 8
    move.l #$66666666, vdp_data.l
end repeat

; Tile $7
repeat 8
    move.l #$77777777, vdp_data.l
end repeat