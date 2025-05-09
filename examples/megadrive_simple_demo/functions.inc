; Intended to be the place where memory variables are initialized.
init_ram_variables:
    rts

; arguments:
;     d1: color index (0-7)
; returns:
;     nothing
set_bg_color:
    ; Set VDP register 7 to the color index in d1
    move.w  #(1<<15 | (7<<8)), d2    ; Create the command word for register 7
    or.w    d1, d2                   ; OR in the color index from d1
    move.w  d2, vdp_ctrl.l             ; Write to VDP control register
    rts

; TODO: Comment
update_color:
        ; if not a then skip
        tst.b (gamepad1_a).l
        beq.b .skip
        addq.w #1, color_index.l
        cmpi.w #(16<<2), color_index.l
        blo.b .increment
        move.w #0, color_index.l
    .increment:
        move.w color_index.l, d1
        ; right shift d1 to get the color index
        lsr.w #2, d1
        ; TODO: clownassembler interprets `jsr label` as `jsr label.l`
        jsr set_bg_color.l ; TODO: Could be set_bg_color.w prolly.
    .skip:
        rts

; TODO: Comment
update_vscroll:
        ; TODO: clownassembler interprets `jsr label` as `jsr label.l`
        tst.b gamepad1_down.l
        beq.b .skip_down
        addi.w #-1, vscroll_amount.l
        bra.b .increment
    .skip_down:
        ; TODO: clownassembler interprets `jsr label` as `jsr label.l`
        tst.b gamepad1_up.l
        beq.b .skip_up
        addi.w #1, vscroll_amount.l
    .increment:
        move.w vscroll_amount.l, d1
        ; right shift d1 to slower speed or something.
        ; Wait what's this now...
        ;     logical shift right... oh, that's why it's slow.
        ; So we have the `vscroll_amount` but the actual amount of scrolling
        ; is that divided by 4.
        lsr.w #1, d1
    ; now also h.scroll plane A and plane B
        ; set_write_vram vram_hscroll_addr
        ; move.w d1, vdp_data.l ; plane a
        ; move.w d1, vdp_data.l ; plane b
    ; now also v.scroll plane A and plane B
        set_write_vsram $0
        move.w d1, vdp_data.l ; plane a
        neg.w d1
        move.w d1, vdp_data.l ; plane b
    .skip_up:
        rts

; TODO: Comment
update_hscroll:
        ; TODO: clownassembler interprets `jsr label` as `jsr label.l`
        tst.b gamepad1_left.l
        beq.b .skip_left
        addi.w #-1, hscroll_amount.l
        bra.b .increment2
    .skip_left:
        ; TODO: clownassembler interprets `jsr label` as `jsr label.l`
        tst.b gamepad1_right.l
        beq.b .skip_right
        addi.w #1, hscroll_amount.l
    .increment2:
        move.w hscroll_amount.l, d1
        ; right shift d1 to slower speed or something.
        ; Wait what's this now...
        ;     logical shift right... oh, that's why it's slow.
        ; So we have the `hscroll_amount` but the actual amount of scrolling
        ; is that divided by 4.
        lsr.w #1, d1
    ; now also h.scroll plane A and plane B
        set_write_vram vram_hscroll_addr
        move.w d1, vdp_data.l ; plane a
        neg.w d1
        move.w d1, vdp_data.l ; plane b
    ; now also v.scroll plane A and plane B
        ; set_write_vsram $0
        ; move.w d1, vdp_data.l ; plane a
        ; neg.w d1
        ; move.w d1, vdp_data.l ; plane b
    .skip_right:
        rts

; TODO: Comment
; A plane tile is one word.
; arguments:
;     d0.l: Tile index  : 11 bits
;     d1.b: Palette     : 0-3
;     d2.b: Vertical    : 1 = flipped, 0 = normal
;     d3.b: Horizontal  : 1 = flipped, 0 = normal
;     d4.b: Priority    : 1 = high, 0 = low
; returns:
;     nothing
; https://segaretro.org/Sega_Mega_Drive/Planes
; TODO: Also use the other arguments.
set_plane_tile:
    move.w d0, vdp_data.l
    rts

; https://plutiedev.com/controllers
gamepads_get_input:
    ; a0 = IoData1 for player 1
    ;    = IoData2 for player 2

    move.b #$40, gamepad1_ctrl.l

    ; TODO: Wouldn't movea work here as well??
    ; Why or why not??
    lea.l  gamepad1_data.l, a0
    
    ; set bit 6 (TH) to 1 to get first group of buttons
    move.b  #$40, (a0)  ; Do 1st step
    nop                 ; D-pad, B and C
    nop
    move.b  (a0), d0
    not.b d0 ; invert so pressed = 1 instead of 0
    ; d0 will now contain
    ; Bit5 	Bit4 	Bit3 	Bit2 	Bit1 	Bit0
    ; C 	B 	    Right 	Left 	Down 	Up

    ; Up
    move.b d0, d1
    andi.b #1, d1
    move.b d1, gamepad1_up.l

    ; Down
    lsr.b #1, d0
    move.b d0, d1
    andi.b #1, d1
    move.b d1, gamepad1_down.l

    ; Left
    lsr.b #1, d0
    move.b d0, d1
    andi.b #1, d1
    move.b d1, gamepad1_left.l

    ; Right
    lsr.b #1, d0
    move.b d0, d1
    andi.b #1, d1
    move.b d1, gamepad1_right.l

    ; B
    lsr.b #1, d0
    move.b d0, d1
    andi.b #1, d1
    move.b d1, gamepad1_b.l

    ; C
    lsr.b #1, d0
    move.b d0, d1
    andi.b #1, d1
    move.b d1, gamepad1_c.l
    
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;; 2nd set of buttons                                                 ;;
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    move.b  #$00, (a0)
    nop
    nop
    move.b  (a0), d0
    not.b d0 ; invert so pressed = 1 instead of 0
    ; d0 will now contain
    ; Bit5   Bit4
    ; Start  A

    ; A
    lsr.b #4, d0
    move.b d0, d1
    andi.b #1, d1
    move.b d1, gamepad1_a.l

    ; Start
    lsr.b #1, d0
    move.b d0, d1
    andi.b #1, d1
    move.b d1, gamepad1_start.l
    rts