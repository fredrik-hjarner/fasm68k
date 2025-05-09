;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; CREATE TILES                                                               ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    set_write_vram vram_tiles_addr

    ; Tile $0 ; Fully transparent
    move.l #$00000000, vdp_data.l ; row 1
    move.l #$00000000, vdp_data.l ; row 2
    move.l #$00000000, vdp_data.l ; row 3
    move.l #$00000000, vdp_data.l ; row 4
    move.l #$00000000, vdp_data.l ; row 5
    move.l #$00000000, vdp_data.l ; row 6
    move.l #$00000000, vdp_data.l ; row 7
    move.l #$00000000, vdp_data.l ; row 8

    ; Tile $1 ; Full square color 1
    move.l #$11111111, vdp_data.l ; row 1
    move.l #$11111111, vdp_data.l ; row 2
    move.l #$11111111, vdp_data.l ; row 3
    move.l #$11111111, vdp_data.l ; row 4
    move.l #$11111111, vdp_data.l ; row 5
    move.l #$11111111, vdp_data.l ; row 6
    move.l #$11111111, vdp_data.l ; row 7
    move.l #$11111111, vdp_data.l ; row 8

    ; Tile $2
    move.l #$22222222, vdp_data.l ; row 1
    move.l #$22222222, vdp_data.l ; row 2
    move.l #$22222222, vdp_data.l ; row 3
    move.l #$22222222, vdp_data.l ; row 4
    move.l #$22222222, vdp_data.l ; row 5
    move.l #$22222222, vdp_data.l ; row 6
    move.l #$22222222, vdp_data.l ; row 7
    move.l #$22222222, vdp_data.l ; row 8

    ; Tile $3
    move.l #$33333333, vdp_data.l ; row 1
    move.l #$33333333, vdp_data.l ; row 2
    move.l #$33333333, vdp_data.l ; row 3
    move.l #$33333333, vdp_data.l ; row 4
    move.l #$33333333, vdp_data.l ; row 5
    move.l #$33333333, vdp_data.l ; row 6
    move.l #$33333333, vdp_data.l ; row 7
    move.l #$33333333, vdp_data.l ; row 8

    ; Tile $4
    move.l #$44444444, vdp_data.l ; row 1
    move.l #$44444444, vdp_data.l ; row 2
    move.l #$44444444, vdp_data.l ; row 3
    move.l #$44444444, vdp_data.l ; row 4
    move.l #$44444444, vdp_data.l ; row 5
    move.l #$44444444, vdp_data.l ; row 6
    move.l #$44444444, vdp_data.l ; row 7
    move.l #$44444444, vdp_data.l ; row 8

    ; Tile $5
    move.l #$55555555, vdp_data.l ; row 1
    move.l #$55555555, vdp_data.l ; row 2
    move.l #$55555555, vdp_data.l ; row 3
    move.l #$55555555, vdp_data.l ; row 4
    move.l #$55555555, vdp_data.l ; row 5
    move.l #$55555555, vdp_data.l ; row 6
    move.l #$55555555, vdp_data.l ; row 7
    move.l #$55555555, vdp_data.l ; row 8

    ; Tile $6
    move.l #$66666666, vdp_data.l ; row 1
    move.l #$66666666, vdp_data.l ; row 2
    move.l #$66666666, vdp_data.l ; row 3
    move.l #$66666666, vdp_data.l ; row 4
    move.l #$66666666, vdp_data.l ; row 5
    move.l #$66666666, vdp_data.l ; row 6
    move.l #$66666666, vdp_data.l ; row 7
    move.l #$66666666, vdp_data.l ; row 8

    ; Tile $7
    move.l #$77777777, vdp_data.l ; row 1
    move.l #$77777777, vdp_data.l ; row 2
    move.l #$77777777, vdp_data.l ; row 3
    move.l #$77777777, vdp_data.l ; row 4
    move.l #$77777777, vdp_data.l ; row 5
    move.l #$77777777, vdp_data.l ; row 6
    move.l #$77777777, vdp_data.l ; row 7
    move.l #$77777777, vdp_data.l ; row 8