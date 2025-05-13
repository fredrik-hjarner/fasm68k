
equ_0 equ 0
equ_1 equ 1
; equ_imm_0 equ #0 ; You're not allowed to do this in vasm and clownassembler.
; equ_imm_1 equ #1 ; You're not allowed to do this in vasm and clownassembler.
equ_equ_1 equ equ_1
equ_1_plus_equ_1 equ equ_1+equ_1
; equ_a1 equ a1 ; You're not allowed to do this in vasm and clownassembler.

label_start:

	dc.b 'or.b #0,d1'
	or.b	#0,d1
	dc.b 'or.b #0,d2'
	or.b	#0,d2
	dc.b 'or.b #0,d3'
	or.b	#0,d3
	dc.b 'or.b #0,d4'
	or.b	#0,d4
	dc.b 'or.b #0,d5'
	or.b	#0,d5
	dc.b 'or.b #$FF,d1'
	or.b	#$FF,d1
	dc.b 'or.b #$FF,d2'
	or.b	#$FF,d2
	dc.b 'or.b #$FF,d3'
	or.b	#$FF,d3
	dc.b 'or.b #$FF,d4'
	or.b	#$FF,d4
	dc.b 'or.b #$FF,d5'
	or.b	#$FF,d5
	dc.b 'or.b #"X",d1'
	or.b	#"X",d1
	dc.b 'or.b #"X",d2'
	or.b	#"X",d2
	dc.b 'or.b #"X",d3'
	or.b	#"X",d3
	dc.b 'or.b #"X",d4'
	or.b	#"X",d4
	dc.b 'or.b #"X",d5'
	or.b	#"X",d5
	dc.b 'or.w #0,d1'
	or.w	#0,d1
	dc.b 'or.w #0,d2'
	or.w	#0,d2
	dc.b 'or.w #0,d3'
	or.w	#0,d3
	dc.b 'or.w #0,d4'
	or.w	#0,d4
	dc.b 'or.w #0,d5'
	or.w	#0,d5
	dc.b 'or.w #4,d1'
	or.w	#4,d1
	dc.b 'or.w #4,d2'
	or.w	#4,d2
	dc.b 'or.w #4,d3'
	or.w	#4,d3
	dc.b 'or.w #4,d4'
	or.w	#4,d4
	dc.b 'or.w #4,d5'
	or.w	#4,d5
	dc.b 'or.w #$FF,d1'
	or.w	#$FF,d1
	dc.b 'or.w #$FF,d2'
	or.w	#$FF,d2
	dc.b 'or.w #$FF,d3'
	or.w	#$FF,d3
	dc.b 'or.w #$FF,d4'
	or.w	#$FF,d4
	dc.b 'or.w #$FF,d5'
	or.w	#$FF,d5
	dc.b 'or.w  #"XY",d1'
	or.w	#"XY",d1
	dc.b 'or.w  #"XY",d2'
	or.w	#"XY",d2
	dc.b 'or.w  #"XY",d3'
	or.w	#"XY",d3
	dc.b 'or.w  #"XY",d4'
	or.w	#"XY",d4
	dc.b 'or.w  #"XY",d5'
	or.w	#"XY",d5
	dc.b 'or.w #$2700,d1'
	or.w	#$2700,d1
	dc.b 'or.w #$2700,d2'
	or.w	#$2700,d2
	dc.b 'or.w #$2700,d3'
	or.w	#$2700,d3
	dc.b 'or.w #$2700,d4'
	or.w	#$2700,d4
	dc.b 'or.w #$2700,d5'
	or.w	#$2700,d5
	dc.b 'or.w #$7FFF,d1'
	or.w	#$7FFF,d1
	dc.b 'or.w #$7FFF,d2'
	or.w	#$7FFF,d2
	dc.b 'or.w #$7FFF,d3'
	or.w	#$7FFF,d3
	dc.b 'or.w #$7FFF,d4'
	or.w	#$7FFF,d4
	dc.b 'or.w #$7FFF,d5'
	or.w	#$7FFF,d5
	dc.b 'or.w #$FFFF,d1'
	or.w	#$FFFF,d1
	dc.b 'or.w #$FFFF,d2'
	or.w	#$FFFF,d2
	dc.b 'or.w #$FFFF,d3'
	or.w	#$FFFF,d3
	dc.b 'or.w #$FFFF,d4'
	or.w	#$FFFF,d4
	dc.b 'or.w #$FFFF,d5'
	or.w	#$FFFF,d5
	dc.b 'or.l #0,d1'
	or.l	#0,d1
	dc.b 'or.l #0,d2'
	or.l	#0,d2
	dc.b 'or.l #0,d3'
	or.l	#0,d3
	dc.b 'or.l #0,d4'
	or.l	#0,d4
	dc.b 'or.l #0,d5'
	or.l	#0,d5
	dc.b 'or.l #4,d1'
	or.l	#4,d1
	dc.b 'or.l #4,d2'
	or.l	#4,d2
	dc.b 'or.l #4,d3'
	or.l	#4,d3
	dc.b 'or.l #4,d4'
	or.l	#4,d4
	dc.b 'or.l #4,d5'
	or.l	#4,d5
	dc.b 'or.l #$FF,d1'
	or.l	#$FF,d1
	dc.b 'or.l #$FF,d2'
	or.l	#$FF,d2
	dc.b 'or.l #$FF,d3'
	or.l	#$FF,d3
	dc.b 'or.l #$FF,d4'
	or.l	#$FF,d4
	dc.b 'or.l #$FF,d5'
	or.l	#$FF,d5
	dc.b 'or.l #$7FFF,d1'
	or.l	#$7FFF,d1
	dc.b 'or.l #$7FFF,d2'
	or.l	#$7FFF,d2
	dc.b 'or.l #$7FFF,d3'
	or.l	#$7FFF,d3
	dc.b 'or.l #$7FFF,d4'
	or.l	#$7FFF,d4
	dc.b 'or.l #$7FFF,d5'
	or.l	#$7FFF,d5
	dc.b 'or.l #$FFFF,d1'
	or.l	#$FFFF,d1
	dc.b 'or.l #$FFFF,d2'
	or.l	#$FFFF,d2
	dc.b 'or.l #$FFFF,d3'
	or.l	#$FFFF,d3
	dc.b 'or.l #$FFFF,d4'
	or.l	#$FFFF,d4
	dc.b 'or.l #$FFFF,d5'
	or.l	#$FFFF,d5
	dc.b 'or.l #$FFFFFFFF,d1'
	or.l	#$FFFFFFFF,d1
	dc.b 'or.l #$FFFFFFFF,d2'
	or.l	#$FFFFFFFF,d2
	dc.b 'or.l #$FFFFFFFF,d3'
	or.l	#$FFFFFFFF,d3
	dc.b 'or.l #$FFFFFFFF,d4'
	or.l	#$FFFFFFFF,d4
	dc.b 'or.l #$FFFFFFFF,d5'
	or.l	#$FFFFFFFF,d5
	dc.b 'or.l  #"WXYZ",d1'
	or.l	#"WXYZ",d1
	dc.b 'or.l  #"WXYZ",d2'
	or.l	#"WXYZ",d2
	dc.b 'or.l  #"WXYZ",d3'
	or.l	#"WXYZ",d3
	dc.b 'or.l  #"WXYZ",d4'
	or.l	#"WXYZ",d4
	dc.b 'or.l  #"WXYZ",d5'
	or.l	#"WXYZ",d5
	dc.b 'or.l #1+1,d1'
	or.l	#1+1,d1
	dc.b 'or.l #1+1,d2'
	or.l	#1+1,d2
	dc.b 'or.l #1+1,d3'
	or.l	#1+1,d3
	dc.b 'or.l #1+1,d4'
	or.l	#1+1,d4
	dc.b 'or.l #1+1,d5'
	or.l	#1+1,d5
	dc.b 'or.l #(3+4),d1'
	or.l	#(3+4),d1
	dc.b 'or.l #(3+4),d2'
	or.l	#(3+4),d2
	dc.b 'or.l #(3+4),d3'
	or.l	#(3+4),d3
	dc.b 'or.l #(3+4),d4'
	or.l	#(3+4),d4
	dc.b 'or.l #(3+4),d5'
	or.l	#(3+4),d5
	dc.b 'or.l  #-1,d1'
	or.l	#-1,d1
	dc.b 'or.l  #-1,d2'
	or.l	#-1,d2
	dc.b 'or.l  #-1,d3'
	or.l	#-1,d3
	dc.b 'or.l  #-1,d4'
	or.l	#-1,d4
	dc.b 'or.l  #-1,d5'
	or.l	#-1,d5
	dc.b 'or.l  #-2,d1'
	or.l	#-2,d1
	dc.b 'or.l  #-2,d2'
	or.l	#-2,d2
	dc.b 'or.l  #-2,d3'
	or.l	#-2,d3
	dc.b 'or.l  #-2,d4'
	or.l	#-2,d4
	dc.b 'or.l  #-2,d5'
	or.l	#-2,d5

	dc.b 'and.b  #0,d1'
	and.b	#0,d1
	dc.b 'and.b  #0,d2'
	and.b	#0,d2
	dc.b 'and.b  #0,d3'
	and.b	#0,d3
	dc.b 'and.b  #0,d4'
	and.b	#0,d4
	dc.b 'and.b  #0,d5'
	and.b	#0,d5
	dc.b 'and.b  #$FF,d1'
	and.b	#$FF,d1
	dc.b 'and.b  #$FF,d2'
	and.b	#$FF,d2
	dc.b 'and.b  #$FF,d3'
	and.b	#$FF,d3
	dc.b 'and.b  #$FF,d4'
	and.b	#$FF,d4
	dc.b 'and.b  #$FF,d5'
	and.b	#$FF,d5
	dc.b 'and.b  #"X",d1'
	and.b	#"X",d1
	dc.b 'and.b  #"X",d2'
	and.b	#"X",d2
	dc.b 'and.b  #"X",d3'
	and.b	#"X",d3
	dc.b 'and.b  #"X",d4'
	and.b	#"X",d4
	dc.b 'and.b  #"X",d5'
	and.b	#"X",d5
	dc.b 'and.w  #0,d1'
	and.w	#0,d1
	dc.b 'and.w  #0,d2'
	and.w	#0,d2
	dc.b 'and.w  #0,d3'
	and.w	#0,d3
	dc.b 'and.w  #0,d4'
	and.w	#0,d4
	dc.b 'and.w  #0,d5'
	and.w	#0,d5
	dc.b 'and.w  #4,d1'
	and.w	#4,d1
	dc.b 'and.w  #4,d2'
	and.w	#4,d2
	dc.b 'and.w  #4,d3'
	and.w	#4,d3
	dc.b 'and.w  #4,d4'
	and.w	#4,d4
	dc.b 'and.w  #4,d5'
	and.w	#4,d5
	dc.b 'and.w  #$FF,d1'
	and.w	#$FF,d1
	dc.b 'and.w  #$FF,d2'
	and.w	#$FF,d2
	dc.b 'and.w  #$FF,d3'
	and.w	#$FF,d3
	dc.b 'and.w  #$FF,d4'
	and.w	#$FF,d4
	dc.b 'and.w  #$FF,d5'
	and.w	#$FF,d5
	dc.b 'and.w #"XY",d1'
	and.w	#"XY",d1
	dc.b 'and.w #"XY",d2'
	and.w	#"XY",d2
	dc.b 'and.w #"XY",d3'
	and.w	#"XY",d3
	dc.b 'and.w #"XY",d4'
	and.w	#"XY",d4
	dc.b 'and.w #"XY",d5'
	and.w	#"XY",d5
	dc.b 'and.w  #$2700,d1'
	and.w	#$2700,d1
	dc.b 'and.w  #$2700,d2'
	and.w	#$2700,d2
	dc.b 'and.w  #$2700,d3'
	and.w	#$2700,d3
	dc.b 'and.w  #$2700,d4'
	and.w	#$2700,d4
	dc.b 'and.w  #$2700,d5'
	and.w	#$2700,d5
	dc.b 'and.w  #$7FFF,d1'
	and.w	#$7FFF,d1
	dc.b 'and.w  #$7FFF,d2'
	and.w	#$7FFF,d2
	dc.b 'and.w  #$7FFF,d3'
	and.w	#$7FFF,d3
	dc.b 'and.w  #$7FFF,d4'
	and.w	#$7FFF,d4
	dc.b 'and.w  #$7FFF,d5'
	and.w	#$7FFF,d5
	dc.b 'and.w  #$FFFF,d1'
	and.w	#$FFFF,d1
	dc.b 'and.w  #$FFFF,d2'
	and.w	#$FFFF,d2
	dc.b 'and.w  #$FFFF,d3'
	and.w	#$FFFF,d3
	dc.b 'and.w  #$FFFF,d4'
	and.w	#$FFFF,d4
	dc.b 'and.w  #$FFFF,d5'
	and.w	#$FFFF,d5
	dc.b 'and.l  #0,d1'
	and.l	#0,d1
	dc.b 'and.l  #0,d2'
	and.l	#0,d2
	dc.b 'and.l  #0,d3'
	and.l	#0,d3
	dc.b 'and.l  #0,d4'
	and.l	#0,d4
	dc.b 'and.l  #0,d5'
	and.l	#0,d5
	dc.b 'and.l  #4,d1'
	and.l	#4,d1
	dc.b 'and.l  #4,d2'
	and.l	#4,d2
	dc.b 'and.l  #4,d3'
	and.l	#4,d3
	dc.b 'and.l  #4,d4'
	and.l	#4,d4
	dc.b 'and.l  #4,d5'
	and.l	#4,d5
	dc.b 'and.l  #$FF,d1'
	and.l	#$FF,d1
	dc.b 'and.l  #$FF,d2'
	and.l	#$FF,d2
	dc.b 'and.l  #$FF,d3'
	and.l	#$FF,d3
	dc.b 'and.l  #$FF,d4'
	and.l	#$FF,d4
	dc.b 'and.l  #$FF,d5'
	and.l	#$FF,d5
	dc.b 'and.l  #$7FFF,d1'
	and.l	#$7FFF,d1
	dc.b 'and.l  #$7FFF,d2'
	and.l	#$7FFF,d2
	dc.b 'and.l  #$7FFF,d3'
	and.l	#$7FFF,d3
	dc.b 'and.l  #$7FFF,d4'
	and.l	#$7FFF,d4
	dc.b 'and.l  #$7FFF,d5'
	and.l	#$7FFF,d5
	dc.b 'and.l  #$FFFF,d1'
	and.l	#$FFFF,d1
	dc.b 'and.l  #$FFFF,d2'
	and.l	#$FFFF,d2
	dc.b 'and.l  #$FFFF,d3'
	and.l	#$FFFF,d3
	dc.b 'and.l  #$FFFF,d4'
	and.l	#$FFFF,d4
	dc.b 'and.l  #$FFFF,d5'
	and.l	#$FFFF,d5
	dc.b 'and.l  #$FFFFFFFF,d1'
	and.l	#$FFFFFFFF,d1
	dc.b 'and.l  #$FFFFFFFF,d2'
	and.l	#$FFFFFFFF,d2
	dc.b 'and.l  #$FFFFFFFF,d3'
	and.l	#$FFFFFFFF,d3
	dc.b 'and.l  #$FFFFFFFF,d4'
	and.l	#$FFFFFFFF,d4
	dc.b 'and.l  #$FFFFFFFF,d5'
	and.l	#$FFFFFFFF,d5
	dc.b 'and.l #"WXYZ",d1'
	and.l	#"WXYZ",d1
	dc.b 'and.l #"WXYZ",d2'
	and.l	#"WXYZ",d2
	dc.b 'and.l #"WXYZ",d3'
	and.l	#"WXYZ",d3
	dc.b 'and.l #"WXYZ",d4'
	and.l	#"WXYZ",d4
	dc.b 'and.l #"WXYZ",d5'
	and.l	#"WXYZ",d5
	dc.b 'and.l  #1+1,d1'
	and.l	#1+1,d1
	dc.b 'and.l  #1+1,d2'
	and.l	#1+1,d2
	dc.b 'and.l  #1+1,d3'
	and.l	#1+1,d3
	dc.b 'and.l  #1+1,d4'
	and.l	#1+1,d4
	dc.b 'and.l  #1+1,d5'
	and.l	#1+1,d5
	dc.b 'and.l  #(3+4),d1'
	and.l	#(3+4),d1
	dc.b 'and.l  #(3+4),d2'
	and.l	#(3+4),d2
	dc.b 'and.l  #(3+4),d3'
	and.l	#(3+4),d3
	dc.b 'and.l  #(3+4),d4'
	and.l	#(3+4),d4
	dc.b 'and.l  #(3+4),d5'
	and.l	#(3+4),d5
	dc.b 'and.l #-1,d1'
	and.l	#-1,d1
	dc.b 'and.l #-1,d2'
	and.l	#-1,d2
	dc.b 'and.l #-1,d3'
	and.l	#-1,d3
	dc.b 'and.l #-1,d4'
	and.l	#-1,d4
	dc.b 'and.l #-1,d5'
	and.l	#-1,d5
	dc.b 'and.l #-2,d1'
	and.l	#-2,d1
	dc.b 'and.l #-2,d2'
	and.l	#-2,d2
	dc.b 'and.l #-2,d3'
	and.l	#-2,d3
	dc.b 'and.l #-2,d4'
	and.l	#-2,d4
	dc.b 'and.l #-2,d5'
	and.l	#-2,d5

	dc.b 'sub.b  #0,d1'
	sub.b	#0,d1
	dc.b 'sub.b  #0,d2'
	sub.b	#0,d2
	dc.b 'sub.b  #0,d3'
	sub.b	#0,d3
	dc.b 'sub.b  #0,d4'
	sub.b	#0,d4
	dc.b 'sub.b  #0,d5'
	sub.b	#0,d5
	dc.b 'sub.b  #$FF,d1'
	sub.b	#$FF,d1
	dc.b 'sub.b  #$FF,d2'
	sub.b	#$FF,d2
	dc.b 'sub.b  #$FF,d3'
	sub.b	#$FF,d3
	dc.b 'sub.b  #$FF,d4'
	sub.b	#$FF,d4
	dc.b 'sub.b  #$FF,d5'
	sub.b	#$FF,d5
	dc.b 'sub.b  #"X",d1'
	sub.b	#"X",d1
	dc.b 'sub.b  #"X",d2'
	sub.b	#"X",d2
	dc.b 'sub.b  #"X",d3'
	sub.b	#"X",d3
	dc.b 'sub.b  #"X",d4'
	sub.b	#"X",d4
	dc.b 'sub.b  #"X",d5'
	sub.b	#"X",d5
	dc.b 'sub.w  #0,d1'
	sub.w	#0,d1
	dc.b 'sub.w  #0,d2'
	sub.w	#0,d2
	dc.b 'sub.w  #0,d3'
	sub.w	#0,d3
	dc.b 'sub.w  #0,d4'
	sub.w	#0,d4
	dc.b 'sub.w  #0,d5'
	sub.w	#0,d5
	dc.b 'sub.w  #4,d1'
	sub.w	#4,d1
	dc.b 'sub.w  #4,d2'
	sub.w	#4,d2
	dc.b 'sub.w  #4,d3'
	sub.w	#4,d3
	dc.b 'sub.w  #4,d4'
	sub.w	#4,d4
	dc.b 'sub.w  #4,d5'
	sub.w	#4,d5
	dc.b 'sub.w  #$FF,d1'
	sub.w	#$FF,d1
	dc.b 'sub.w  #$FF,d2'
	sub.w	#$FF,d2
	dc.b 'sub.w  #$FF,d3'
	sub.w	#$FF,d3
	dc.b 'sub.w  #$FF,d4'
	sub.w	#$FF,d4
	dc.b 'sub.w  #$FF,d5'
	sub.w	#$FF,d5
	dc.b 'sub.w #"XY",d1'
	sub.w	#"XY",d1
	dc.b 'sub.w #"XY",d2'
	sub.w	#"XY",d2
	dc.b 'sub.w #"XY",d3'
	sub.w	#"XY",d3
	dc.b 'sub.w #"XY",d4'
	sub.w	#"XY",d4
	dc.b 'sub.w #"XY",d5'
	sub.w	#"XY",d5
	dc.b 'sub.w  #$2700,d1'
	sub.w	#$2700,d1
	dc.b 'sub.w  #$2700,d2'
	sub.w	#$2700,d2
	dc.b 'sub.w  #$2700,d3'
	sub.w	#$2700,d3
	dc.b 'sub.w  #$2700,d4'
	sub.w	#$2700,d4
	dc.b 'sub.w  #$2700,d5'
	sub.w	#$2700,d5
	dc.b 'sub.w  #$7FFF,d1'
	sub.w	#$7FFF,d1
	dc.b 'sub.w  #$7FFF,d2'
	sub.w	#$7FFF,d2
	dc.b 'sub.w  #$7FFF,d3'
	sub.w	#$7FFF,d3
	dc.b 'sub.w  #$7FFF,d4'
	sub.w	#$7FFF,d4
	dc.b 'sub.w  #$7FFF,d5'
	sub.w	#$7FFF,d5
	dc.b 'sub.w  #$FFFF,d1'
	sub.w	#$FFFF,d1
	dc.b 'sub.w  #$FFFF,d2'
	sub.w	#$FFFF,d2
	dc.b 'sub.w  #$FFFF,d3'
	sub.w	#$FFFF,d3
	dc.b 'sub.w  #$FFFF,d4'
	sub.w	#$FFFF,d4
	dc.b 'sub.w  #$FFFF,d5'
	sub.w	#$FFFF,d5
	dc.b 'sub.l  #0,d1'
	sub.l	#0,d1
	dc.b 'sub.l  #0,d2'
	sub.l	#0,d2
	dc.b 'sub.l  #0,d3'
	sub.l	#0,d3
	dc.b 'sub.l  #0,d4'
	sub.l	#0,d4
	dc.b 'sub.l  #0,d5'
	sub.l	#0,d5
	dc.b 'sub.l  #4,d1'
	sub.l	#4,d1
	dc.b 'sub.l  #4,d2'
	sub.l	#4,d2
	dc.b 'sub.l  #4,d3'
	sub.l	#4,d3
	dc.b 'sub.l  #4,d4'
	sub.l	#4,d4
	dc.b 'sub.l  #4,d5'
	sub.l	#4,d5
	dc.b 'sub.l  #$FF,d1'
	sub.l	#$FF,d1
	dc.b 'sub.l  #$FF,d2'
	sub.l	#$FF,d2
	dc.b 'sub.l  #$FF,d3'
	sub.l	#$FF,d3
	dc.b 'sub.l  #$FF,d4'
	sub.l	#$FF,d4
	dc.b 'sub.l  #$FF,d5'
	sub.l	#$FF,d5
	dc.b 'sub.l  #$7FFF,d1'
	sub.l	#$7FFF,d1
	dc.b 'sub.l  #$7FFF,d2'
	sub.l	#$7FFF,d2
	dc.b 'sub.l  #$7FFF,d3'
	sub.l	#$7FFF,d3
	dc.b 'sub.l  #$7FFF,d4'
	sub.l	#$7FFF,d4
	dc.b 'sub.l  #$7FFF,d5'
	sub.l	#$7FFF,d5
	dc.b 'sub.l  #$FFFF,d1'
	sub.l	#$FFFF,d1
	dc.b 'sub.l  #$FFFF,d2'
	sub.l	#$FFFF,d2
	dc.b 'sub.l  #$FFFF,d3'
	sub.l	#$FFFF,d3
	dc.b 'sub.l  #$FFFF,d4'
	sub.l	#$FFFF,d4
	dc.b 'sub.l  #$FFFF,d5'
	sub.l	#$FFFF,d5
	dc.b 'sub.l  #$FFFFFFFF,d1'
	sub.l	#$FFFFFFFF,d1
	dc.b 'sub.l  #$FFFFFFFF,d2'
	sub.l	#$FFFFFFFF,d2
	dc.b 'sub.l  #$FFFFFFFF,d3'
	sub.l	#$FFFFFFFF,d3
	dc.b 'sub.l  #$FFFFFFFF,d4'
	sub.l	#$FFFFFFFF,d4
	dc.b 'sub.l  #$FFFFFFFF,d5'
	sub.l	#$FFFFFFFF,d5
	dc.b 'sub.l #"WXYZ",d1'
	sub.l	#"WXYZ",d1
	dc.b 'sub.l #"WXYZ",d2'
	sub.l	#"WXYZ",d2
	dc.b 'sub.l #"WXYZ",d3'
	sub.l	#"WXYZ",d3
	dc.b 'sub.l #"WXYZ",d4'
	sub.l	#"WXYZ",d4
	dc.b 'sub.l #"WXYZ",d5'
	sub.l	#"WXYZ",d5
	dc.b 'sub.l  #1+1,d1'
	sub.l	#1+1,d1
	dc.b 'sub.l  #1+1,d2'
	sub.l	#1+1,d2
	dc.b 'sub.l  #1+1,d3'
	sub.l	#1+1,d3
	dc.b 'sub.l  #1+1,d4'
	sub.l	#1+1,d4
	dc.b 'sub.l  #1+1,d5'
	sub.l	#1+1,d5
	dc.b 'sub.l  #(3+4),d1'
	sub.l	#(3+4),d1
	dc.b 'sub.l  #(3+4),d2'
	sub.l	#(3+4),d2
	dc.b 'sub.l  #(3+4),d3'
	sub.l	#(3+4),d3
	dc.b 'sub.l  #(3+4),d4'
	sub.l	#(3+4),d4
	dc.b 'sub.l  #(3+4),d5'
	sub.l	#(3+4),d5
	dc.b 'sub.l #-1,d1'
	sub.l	#-1,d1
	dc.b 'sub.l #-1,d2'
	sub.l	#-1,d2
	dc.b 'sub.l #-1,d3'
	sub.l	#-1,d3
	dc.b 'sub.l #-1,d4'
	sub.l	#-1,d4
	dc.b 'sub.l #-1,d5'
	sub.l	#-1,d5
	dc.b 'sub.l #-2,d1'
	sub.l	#-2,d1
	dc.b 'sub.l #-2,d2'
	sub.l	#-2,d2
	dc.b 'sub.l #-2,d3'
	sub.l	#-2,d3
	dc.b 'sub.l #-2,d4'
	sub.l	#-2,d4
	dc.b 'sub.l #-2,d5'
	sub.l	#-2,d5
	dc.b 'sub.w  #0,a1'
	sub.w	#0,a1
	dc.b 'sub.w  #0,a2'
	sub.w	#0,a2
	dc.b 'sub.w  #0,a3'
	sub.w	#0,a3
	dc.b 'sub.w  #0,a4'
	sub.w	#0,a4
	dc.b 'sub.w  #0,a5'
	sub.w	#0,a5
	dc.b 'sub.w  #0,a6'
	sub.w	#0,a6
	dc.b 'sub.w  #0,a7'
	sub.w	#0,a7
	dc.b 'sub.w  #0,sp'
	sub.w	#0,sp
	dc.b 'sub.w  #4,a1'
	sub.w	#4,a1
	dc.b 'sub.w  #4,a2'
	sub.w	#4,a2
	dc.b 'sub.w  #4,a3'
	sub.w	#4,a3
	dc.b 'sub.w  #4,a4'
	sub.w	#4,a4
	dc.b 'sub.w  #4,a5'
	sub.w	#4,a5
	dc.b 'sub.w  #4,a6'
	sub.w	#4,a6
	dc.b 'sub.w  #4,a7'
	sub.w	#4,a7
	dc.b 'sub.w  #4,sp'
	sub.w	#4,sp
	dc.b 'sub.w  #$FF,a1'
	sub.w	#$FF,a1
	dc.b 'sub.w  #$FF,a2'
	sub.w	#$FF,a2
	dc.b 'sub.w  #$FF,a3'
	sub.w	#$FF,a3
	dc.b 'sub.w  #$FF,a4'
	sub.w	#$FF,a4
	dc.b 'sub.w  #$FF,a5'
	sub.w	#$FF,a5
	dc.b 'sub.w  #$FF,a6'
	sub.w	#$FF,a6
	dc.b 'sub.w  #$FF,a7'
	sub.w	#$FF,a7
	dc.b 'sub.w  #$FF,sp'
	sub.w	#$FF,sp
	dc.b 'sub.w #"XY",a1'
	sub.w	#"XY",a1
	dc.b 'sub.w #"XY",a2'
	sub.w	#"XY",a2
	dc.b 'sub.w #"XY",a3'
	sub.w	#"XY",a3
	dc.b 'sub.w #"XY",a4'
	sub.w	#"XY",a4
	dc.b 'sub.w #"XY",a5'
	sub.w	#"XY",a5
	dc.b 'sub.w #"XY",a6'
	sub.w	#"XY",a6
	dc.b 'sub.w #"XY",a7'
	sub.w	#"XY",a7
	dc.b 'sub.w #"XY",sp'
	sub.w	#"XY",sp
	dc.b 'sub.w  #$2700,a1'
	sub.w	#$2700,a1
	dc.b 'sub.w  #$2700,a2'
	sub.w	#$2700,a2
	dc.b 'sub.w  #$2700,a3'
	sub.w	#$2700,a3
	dc.b 'sub.w  #$2700,a4'
	sub.w	#$2700,a4
	dc.b 'sub.w  #$2700,a5'
	sub.w	#$2700,a5
	dc.b 'sub.w  #$2700,a6'
	sub.w	#$2700,a6
	dc.b 'sub.w  #$2700,a7'
	sub.w	#$2700,a7
	dc.b 'sub.w  #$2700,sp'
	sub.w	#$2700,sp
	dc.b 'sub.w  #$7FFF,a1'
	sub.w	#$7FFF,a1
	dc.b 'sub.w  #$7FFF,a2'
	sub.w	#$7FFF,a2
	dc.b 'sub.w  #$7FFF,a3'
	sub.w	#$7FFF,a3
	dc.b 'sub.w  #$7FFF,a4'
	sub.w	#$7FFF,a4
	dc.b 'sub.w  #$7FFF,a5'
	sub.w	#$7FFF,a5
	dc.b 'sub.w  #$7FFF,a6'
	sub.w	#$7FFF,a6
	dc.b 'sub.w  #$7FFF,a7'
	sub.w	#$7FFF,a7
	dc.b 'sub.w  #$7FFF,sp'
	sub.w	#$7FFF,sp
	dc.b 'sub.w  #$FFFF,a1'
	sub.w	#$FFFF,a1
	dc.b 'sub.w  #$FFFF,a2'
	sub.w	#$FFFF,a2
	dc.b 'sub.w  #$FFFF,a3'
	sub.w	#$FFFF,a3
	dc.b 'sub.w  #$FFFF,a4'
	sub.w	#$FFFF,a4
	dc.b 'sub.w  #$FFFF,a5'
	sub.w	#$FFFF,a5
	dc.b 'sub.w  #$FFFF,a6'
	sub.w	#$FFFF,a6
	dc.b 'sub.w  #$FFFF,a7'
	sub.w	#$FFFF,a7
	dc.b 'sub.w  #$FFFF,sp'
	sub.w	#$FFFF,sp
	dc.b 'sub.l  #0,a1'
	sub.l	#0,a1
	dc.b 'sub.l  #0,a2'
	sub.l	#0,a2
	dc.b 'sub.l  #0,a3'
	sub.l	#0,a3
	dc.b 'sub.l  #0,a4'
	sub.l	#0,a4
	dc.b 'sub.l  #0,a5'
	sub.l	#0,a5
	dc.b 'sub.l  #0,a6'
	sub.l	#0,a6
	dc.b 'sub.l  #0,a7'
	sub.l	#0,a7
	dc.b 'sub.l  #0,sp'
	sub.l	#0,sp
	dc.b 'sub.l  #4,a1'
	sub.l	#4,a1
	dc.b 'sub.l  #4,a2'
	sub.l	#4,a2
	dc.b 'sub.l  #4,a3'
	sub.l	#4,a3
	dc.b 'sub.l  #4,a4'
	sub.l	#4,a4
	dc.b 'sub.l  #4,a5'
	sub.l	#4,a5
	dc.b 'sub.l  #4,a6'
	sub.l	#4,a6
	dc.b 'sub.l  #4,a7'
	sub.l	#4,a7
	dc.b 'sub.l  #4,sp'
	sub.l	#4,sp
	dc.b 'sub.l  #$FF,a1'
	sub.l	#$FF,a1
	dc.b 'sub.l  #$FF,a2'
	sub.l	#$FF,a2
	dc.b 'sub.l  #$FF,a3'
	sub.l	#$FF,a3
	dc.b 'sub.l  #$FF,a4'
	sub.l	#$FF,a4
	dc.b 'sub.l  #$FF,a5'
	sub.l	#$FF,a5
	dc.b 'sub.l  #$FF,a6'
	sub.l	#$FF,a6
	dc.b 'sub.l  #$FF,a7'
	sub.l	#$FF,a7
	dc.b 'sub.l  #$FF,sp'
	sub.l	#$FF,sp
	dc.b 'sub.l  #$7FFF,a1'
	sub.l	#$7FFF,a1
	dc.b 'sub.l  #$7FFF,a2'
	sub.l	#$7FFF,a2
	dc.b 'sub.l  #$7FFF,a3'
	sub.l	#$7FFF,a3
	dc.b 'sub.l  #$7FFF,a4'
	sub.l	#$7FFF,a4
	dc.b 'sub.l  #$7FFF,a5'
	sub.l	#$7FFF,a5
	dc.b 'sub.l  #$7FFF,a6'
	sub.l	#$7FFF,a6
	dc.b 'sub.l  #$7FFF,a7'
	sub.l	#$7FFF,a7
	dc.b 'sub.l  #$7FFF,sp'
	sub.l	#$7FFF,sp
	dc.b 'sub.l  #$FFFF,a1'
	sub.l	#$FFFF,a1
	dc.b 'sub.l  #$FFFF,a2'
	sub.l	#$FFFF,a2
	dc.b 'sub.l  #$FFFF,a3'
	sub.l	#$FFFF,a3
	dc.b 'sub.l  #$FFFF,a4'
	sub.l	#$FFFF,a4
	dc.b 'sub.l  #$FFFF,a5'
	sub.l	#$FFFF,a5
	dc.b 'sub.l  #$FFFF,a6'
	sub.l	#$FFFF,a6
	dc.b 'sub.l  #$FFFF,a7'
	sub.l	#$FFFF,a7
	dc.b 'sub.l  #$FFFF,sp'
	sub.l	#$FFFF,sp
	dc.b 'sub.l  #$FFFFFFFF,a1'
	sub.l	#$FFFFFFFF,a1
	dc.b 'sub.l  #$FFFFFFFF,a2'
	sub.l	#$FFFFFFFF,a2
	dc.b 'sub.l  #$FFFFFFFF,a3'
	sub.l	#$FFFFFFFF,a3
	dc.b 'sub.l  #$FFFFFFFF,a4'
	sub.l	#$FFFFFFFF,a4
	dc.b 'sub.l  #$FFFFFFFF,a5'
	sub.l	#$FFFFFFFF,a5
	dc.b 'sub.l  #$FFFFFFFF,a6'
	sub.l	#$FFFFFFFF,a6
	dc.b 'sub.l  #$FFFFFFFF,a7'
	sub.l	#$FFFFFFFF,a7
	dc.b 'sub.l  #$FFFFFFFF,sp'
	sub.l	#$FFFFFFFF,sp
	dc.b 'sub.l #"WXYZ",a1'
	sub.l	#"WXYZ",a1
	dc.b 'sub.l #"WXYZ",a2'
	sub.l	#"WXYZ",a2
	dc.b 'sub.l #"WXYZ",a3'
	sub.l	#"WXYZ",a3
	dc.b 'sub.l #"WXYZ",a4'
	sub.l	#"WXYZ",a4
	dc.b 'sub.l #"WXYZ",a5'
	sub.l	#"WXYZ",a5
	dc.b 'sub.l #"WXYZ",a6'
	sub.l	#"WXYZ",a6
	dc.b 'sub.l #"WXYZ",a7'
	sub.l	#"WXYZ",a7
	dc.b 'sub.l #"WXYZ",sp'
	sub.l	#"WXYZ",sp
	dc.b 'sub.l  #1+1,a1'
	sub.l	#1+1,a1
	dc.b 'sub.l  #1+1,a2'
	sub.l	#1+1,a2
	dc.b 'sub.l  #1+1,a3'
	sub.l	#1+1,a3
	dc.b 'sub.l  #1+1,a4'
	sub.l	#1+1,a4
	dc.b 'sub.l  #1+1,a5'
	sub.l	#1+1,a5
	dc.b 'sub.l  #1+1,a6'
	sub.l	#1+1,a6
	dc.b 'sub.l  #1+1,a7'
	sub.l	#1+1,a7
	dc.b 'sub.l  #1+1,sp'
	sub.l	#1+1,sp
	dc.b 'sub.l  #(3+4),a1'
	sub.l	#(3+4),a1
	dc.b 'sub.l  #(3+4),a2'
	sub.l	#(3+4),a2
	dc.b 'sub.l  #(3+4),a3'
	sub.l	#(3+4),a3
	dc.b 'sub.l  #(3+4),a4'
	sub.l	#(3+4),a4
	dc.b 'sub.l  #(3+4),a5'
	sub.l	#(3+4),a5
	dc.b 'sub.l  #(3+4),a6'
	sub.l	#(3+4),a6
	dc.b 'sub.l  #(3+4),a7'
	sub.l	#(3+4),a7
	dc.b 'sub.l  #(3+4),sp'
	sub.l	#(3+4),sp
	dc.b 'sub.l #-1,a1'
	sub.l	#-1,a1
	dc.b 'sub.l #-1,a2'
	sub.l	#-1,a2
	dc.b 'sub.l #-1,a3'
	sub.l	#-1,a3
	dc.b 'sub.l #-1,a4'
	sub.l	#-1,a4
	dc.b 'sub.l #-1,a5'
	sub.l	#-1,a5
	dc.b 'sub.l #-1,a6'
	sub.l	#-1,a6
	dc.b 'sub.l #-1,a7'
	sub.l	#-1,a7
	dc.b 'sub.l #-1,sp'
	sub.l	#-1,sp
	dc.b 'sub.l #-2,a1'
	sub.l	#-2,a1
	dc.b 'sub.l #-2,a2'
	sub.l	#-2,a2
	dc.b 'sub.l #-2,a3'
	sub.l	#-2,a3
	dc.b 'sub.l #-2,a4'
	sub.l	#-2,a4
	dc.b 'sub.l #-2,a5'
	sub.l	#-2,a5
	dc.b 'sub.l #-2,a6'
	sub.l	#-2,a6
	dc.b 'sub.l #-2,a7'
	sub.l	#-2,a7
	dc.b 'sub.l #-2,sp'
	sub.l	#-2,sp

	dc.b 'add.b  #0,d1'
	add.b	#0,d1
	dc.b 'add.b  #0,d2'
	add.b	#0,d2
	dc.b 'add.b  #0,d3'
	add.b	#0,d3
	dc.b 'add.b  #0,d4'
	add.b	#0,d4
	dc.b 'add.b  #0,d5'
	add.b	#0,d5
	dc.b 'add.b  #$FF,d1'
	add.b	#$FF,d1
	dc.b 'add.b  #$FF,d2'
	add.b	#$FF,d2
	dc.b 'add.b  #$FF,d3'
	add.b	#$FF,d3
	dc.b 'add.b  #$FF,d4'
	add.b	#$FF,d4
	dc.b 'add.b  #$FF,d5'
	add.b	#$FF,d5
	dc.b 'add.b  #"X",d1'
	add.b	#"X",d1
	dc.b 'add.b  #"X",d2'
	add.b	#"X",d2
	dc.b 'add.b  #"X",d3'
	add.b	#"X",d3
	dc.b 'add.b  #"X",d4'
	add.b	#"X",d4
	dc.b 'add.b  #"X",d5'
	add.b	#"X",d5
	dc.b 'add.w  #0,d1'
	add.w	#0,d1
	dc.b 'add.w  #0,d2'
	add.w	#0,d2
	dc.b 'add.w  #0,d3'
	add.w	#0,d3
	dc.b 'add.w  #0,d4'
	add.w	#0,d4
	dc.b 'add.w  #0,d5'
	add.w	#0,d5
	dc.b 'add.w  #4,d1'
	add.w	#4,d1
	dc.b 'add.w  #4,d2'
	add.w	#4,d2
	dc.b 'add.w  #4,d3'
	add.w	#4,d3
	dc.b 'add.w  #4,d4'
	add.w	#4,d4
	dc.b 'add.w  #4,d5'
	add.w	#4,d5
	dc.b 'add.w  #$FF,d1'
	add.w	#$FF,d1
	dc.b 'add.w  #$FF,d2'
	add.w	#$FF,d2
	dc.b 'add.w  #$FF,d3'
	add.w	#$FF,d3
	dc.b 'add.w  #$FF,d4'
	add.w	#$FF,d4
	dc.b 'add.w  #$FF,d5'
	add.w	#$FF,d5
	dc.b 'add.w #"XY",d1'
	add.w	#"XY",d1
	dc.b 'add.w #"XY",d2'
	add.w	#"XY",d2
	dc.b 'add.w #"XY",d3'
	add.w	#"XY",d3
	dc.b 'add.w #"XY",d4'
	add.w	#"XY",d4
	dc.b 'add.w #"XY",d5'
	add.w	#"XY",d5
	dc.b 'add.w  #$2700,d1'
	add.w	#$2700,d1
	dc.b 'add.w  #$2700,d2'
	add.w	#$2700,d2
	dc.b 'add.w  #$2700,d3'
	add.w	#$2700,d3
	dc.b 'add.w  #$2700,d4'
	add.w	#$2700,d4
	dc.b 'add.w  #$2700,d5'
	add.w	#$2700,d5
	dc.b 'add.w  #$7FFF,d1'
	add.w	#$7FFF,d1
	dc.b 'add.w  #$7FFF,d2'
	add.w	#$7FFF,d2
	dc.b 'add.w  #$7FFF,d3'
	add.w	#$7FFF,d3
	dc.b 'add.w  #$7FFF,d4'
	add.w	#$7FFF,d4
	dc.b 'add.w  #$7FFF,d5'
	add.w	#$7FFF,d5
	dc.b 'add.w  #$FFFF,d1'
	add.w	#$FFFF,d1
	dc.b 'add.w  #$FFFF,d2'
	add.w	#$FFFF,d2
	dc.b 'add.w  #$FFFF,d3'
	add.w	#$FFFF,d3
	dc.b 'add.w  #$FFFF,d4'
	add.w	#$FFFF,d4
	dc.b 'add.w  #$FFFF,d5'
	add.w	#$FFFF,d5
	dc.b 'add.l  #0,d1'
	add.l	#0,d1
	dc.b 'add.l  #0,d2'
	add.l	#0,d2
	dc.b 'add.l  #0,d3'
	add.l	#0,d3
	dc.b 'add.l  #0,d4'
	add.l	#0,d4
	dc.b 'add.l  #0,d5'
	add.l	#0,d5
	dc.b 'add.l  #4,d1'
	add.l	#4,d1
	dc.b 'add.l  #4,d2'
	add.l	#4,d2
	dc.b 'add.l  #4,d3'
	add.l	#4,d3
	dc.b 'add.l  #4,d4'
	add.l	#4,d4
	dc.b 'add.l  #4,d5'
	add.l	#4,d5
	dc.b 'add.l  #$FF,d1'
	add.l	#$FF,d1
	dc.b 'add.l  #$FF,d2'
	add.l	#$FF,d2
	dc.b 'add.l  #$FF,d3'
	add.l	#$FF,d3
	dc.b 'add.l  #$FF,d4'
	add.l	#$FF,d4
	dc.b 'add.l  #$FF,d5'
	add.l	#$FF,d5
	dc.b 'add.l  #$7FFF,d1'
	add.l	#$7FFF,d1
	dc.b 'add.l  #$7FFF,d2'
	add.l	#$7FFF,d2
	dc.b 'add.l  #$7FFF,d3'
	add.l	#$7FFF,d3
	dc.b 'add.l  #$7FFF,d4'
	add.l	#$7FFF,d4
	dc.b 'add.l  #$7FFF,d5'
	add.l	#$7FFF,d5
	dc.b 'add.l  #$FFFF,d1'
	add.l	#$FFFF,d1
	dc.b 'add.l  #$FFFF,d2'
	add.l	#$FFFF,d2
	dc.b 'add.l  #$FFFF,d3'
	add.l	#$FFFF,d3
	dc.b 'add.l  #$FFFF,d4'
	add.l	#$FFFF,d4
	dc.b 'add.l  #$FFFF,d5'
	add.l	#$FFFF,d5
	dc.b 'add.l  #$FFFFFFFF,d1'
	add.l	#$FFFFFFFF,d1
	dc.b 'add.l  #$FFFFFFFF,d2'
	add.l	#$FFFFFFFF,d2
	dc.b 'add.l  #$FFFFFFFF,d3'
	add.l	#$FFFFFFFF,d3
	dc.b 'add.l  #$FFFFFFFF,d4'
	add.l	#$FFFFFFFF,d4
	dc.b 'add.l  #$FFFFFFFF,d5'
	add.l	#$FFFFFFFF,d5
	dc.b 'add.l #"WXYZ",d1'
	add.l	#"WXYZ",d1
	dc.b 'add.l #"WXYZ",d2'
	add.l	#"WXYZ",d2
	dc.b 'add.l #"WXYZ",d3'
	add.l	#"WXYZ",d3
	dc.b 'add.l #"WXYZ",d4'
	add.l	#"WXYZ",d4
	dc.b 'add.l #"WXYZ",d5'
	add.l	#"WXYZ",d5
	dc.b 'add.l  #1+1,d1'
	add.l	#1+1,d1
	dc.b 'add.l  #1+1,d2'
	add.l	#1+1,d2
	dc.b 'add.l  #1+1,d3'
	add.l	#1+1,d3
	dc.b 'add.l  #1+1,d4'
	add.l	#1+1,d4
	dc.b 'add.l  #1+1,d5'
	add.l	#1+1,d5
	dc.b 'add.l  #(3+4),d1'
	add.l	#(3+4),d1
	dc.b 'add.l  #(3+4),d2'
	add.l	#(3+4),d2
	dc.b 'add.l  #(3+4),d3'
	add.l	#(3+4),d3
	dc.b 'add.l  #(3+4),d4'
	add.l	#(3+4),d4
	dc.b 'add.l  #(3+4),d5'
	add.l	#(3+4),d5
	dc.b 'add.l #-1,d1'
	add.l	#-1,d1
	dc.b 'add.l #-1,d2'
	add.l	#-1,d2
	dc.b 'add.l #-1,d3'
	add.l	#-1,d3
	dc.b 'add.l #-1,d4'
	add.l	#-1,d4
	dc.b 'add.l #-1,d5'
	add.l	#-1,d5
	dc.b 'add.l #-2,d1'
	add.l	#-2,d1
	dc.b 'add.l #-2,d2'
	add.l	#-2,d2
	dc.b 'add.l #-2,d3'
	add.l	#-2,d3
	dc.b 'add.l #-2,d4'
	add.l	#-2,d4
	dc.b 'add.l #-2,d5'
	add.l	#-2,d5
	dc.b 'add.w  #0,a1'
	add.w	#0,a1
	dc.b 'add.w  #0,a2'
	add.w	#0,a2
	dc.b 'add.w  #0,a3'
	add.w	#0,a3
	dc.b 'add.w  #0,a4'
	add.w	#0,a4
	dc.b 'add.w  #0,a5'
	add.w	#0,a5
	dc.b 'add.w  #0,a6'
	add.w	#0,a6
	dc.b 'add.w  #0,a7'
	add.w	#0,a7
	dc.b 'add.w  #0,sp'
	add.w	#0,sp
	dc.b 'add.w  #4,a1'
	add.w	#4,a1
	dc.b 'add.w  #4,a2'
	add.w	#4,a2
	dc.b 'add.w  #4,a3'
	add.w	#4,a3
	dc.b 'add.w  #4,a4'
	add.w	#4,a4
	dc.b 'add.w  #4,a5'
	add.w	#4,a5
	dc.b 'add.w  #4,a6'
	add.w	#4,a6
	dc.b 'add.w  #4,a7'
	add.w	#4,a7
	dc.b 'add.w  #4,sp'
	add.w	#4,sp
	dc.b 'add.w  #$FF,a1'
	add.w	#$FF,a1
	dc.b 'add.w  #$FF,a2'
	add.w	#$FF,a2
	dc.b 'add.w  #$FF,a3'
	add.w	#$FF,a3
	dc.b 'add.w  #$FF,a4'
	add.w	#$FF,a4
	dc.b 'add.w  #$FF,a5'
	add.w	#$FF,a5
	dc.b 'add.w  #$FF,a6'
	add.w	#$FF,a6
	dc.b 'add.w  #$FF,a7'
	add.w	#$FF,a7
	dc.b 'add.w  #$FF,sp'
	add.w	#$FF,sp
	dc.b 'add.w #"XY",a1'
	add.w	#"XY",a1
	dc.b 'add.w #"XY",a2'
	add.w	#"XY",a2
	dc.b 'add.w #"XY",a3'
	add.w	#"XY",a3
	dc.b 'add.w #"XY",a4'
	add.w	#"XY",a4
	dc.b 'add.w #"XY",a5'
	add.w	#"XY",a5
	dc.b 'add.w #"XY",a6'
	add.w	#"XY",a6
	dc.b 'add.w #"XY",a7'
	add.w	#"XY",a7
	dc.b 'add.w #"XY",sp'
	add.w	#"XY",sp
	dc.b 'add.w  #$2700,a1'
	add.w	#$2700,a1
	dc.b 'add.w  #$2700,a2'
	add.w	#$2700,a2
	dc.b 'add.w  #$2700,a3'
	add.w	#$2700,a3
	dc.b 'add.w  #$2700,a4'
	add.w	#$2700,a4
	dc.b 'add.w  #$2700,a5'
	add.w	#$2700,a5
	dc.b 'add.w  #$2700,a6'
	add.w	#$2700,a6
	dc.b 'add.w  #$2700,a7'
	add.w	#$2700,a7
	dc.b 'add.w  #$2700,sp'
	add.w	#$2700,sp
	dc.b 'add.w  #$7FFF,a1'
	add.w	#$7FFF,a1
	dc.b 'add.w  #$7FFF,a2'
	add.w	#$7FFF,a2
	dc.b 'add.w  #$7FFF,a3'
	add.w	#$7FFF,a3
	dc.b 'add.w  #$7FFF,a4'
	add.w	#$7FFF,a4
	dc.b 'add.w  #$7FFF,a5'
	add.w	#$7FFF,a5
	dc.b 'add.w  #$7FFF,a6'
	add.w	#$7FFF,a6
	dc.b 'add.w  #$7FFF,a7'
	add.w	#$7FFF,a7
	dc.b 'add.w  #$7FFF,sp'
	add.w	#$7FFF,sp
	dc.b 'add.w  #$FFFF,a1'
	add.w	#$FFFF,a1
	dc.b 'add.w  #$FFFF,a2'
	add.w	#$FFFF,a2
	dc.b 'add.w  #$FFFF,a3'
	add.w	#$FFFF,a3
	dc.b 'add.w  #$FFFF,a4'
	add.w	#$FFFF,a4
	dc.b 'add.w  #$FFFF,a5'
	add.w	#$FFFF,a5
	dc.b 'add.w  #$FFFF,a6'
	add.w	#$FFFF,a6
	dc.b 'add.w  #$FFFF,a7'
	add.w	#$FFFF,a7
	dc.b 'add.w  #$FFFF,sp'
	add.w	#$FFFF,sp
	dc.b 'add.l  #0,a1'
	add.l	#0,a1
	dc.b 'add.l  #0,a2'
	add.l	#0,a2
	dc.b 'add.l  #0,a3'
	add.l	#0,a3
	dc.b 'add.l  #0,a4'
	add.l	#0,a4
	dc.b 'add.l  #0,a5'
	add.l	#0,a5
	dc.b 'add.l  #0,a6'
	add.l	#0,a6
	dc.b 'add.l  #0,a7'
	add.l	#0,a7
	dc.b 'add.l  #0,sp'
	add.l	#0,sp
	dc.b 'add.l  #4,a1'
	add.l	#4,a1
	dc.b 'add.l  #4,a2'
	add.l	#4,a2
	dc.b 'add.l  #4,a3'
	add.l	#4,a3
	dc.b 'add.l  #4,a4'
	add.l	#4,a4
	dc.b 'add.l  #4,a5'
	add.l	#4,a5
	dc.b 'add.l  #4,a6'
	add.l	#4,a6
	dc.b 'add.l  #4,a7'
	add.l	#4,a7
	dc.b 'add.l  #4,sp'
	add.l	#4,sp
	dc.b 'add.l  #$FF,a1'
	add.l	#$FF,a1
	dc.b 'add.l  #$FF,a2'
	add.l	#$FF,a2
	dc.b 'add.l  #$FF,a3'
	add.l	#$FF,a3
	dc.b 'add.l  #$FF,a4'
	add.l	#$FF,a4
	dc.b 'add.l  #$FF,a5'
	add.l	#$FF,a5
	dc.b 'add.l  #$FF,a6'
	add.l	#$FF,a6
	dc.b 'add.l  #$FF,a7'
	add.l	#$FF,a7
	dc.b 'add.l  #$FF,sp'
	add.l	#$FF,sp
	dc.b 'add.l  #$7FFF,a1'
	add.l	#$7FFF,a1
	dc.b 'add.l  #$7FFF,a2'
	add.l	#$7FFF,a2
	dc.b 'add.l  #$7FFF,a3'
	add.l	#$7FFF,a3
	dc.b 'add.l  #$7FFF,a4'
	add.l	#$7FFF,a4
	dc.b 'add.l  #$7FFF,a5'
	add.l	#$7FFF,a5
	dc.b 'add.l  #$7FFF,a6'
	add.l	#$7FFF,a6
	dc.b 'add.l  #$7FFF,a7'
	add.l	#$7FFF,a7
	dc.b 'add.l  #$7FFF,sp'
	add.l	#$7FFF,sp
	dc.b 'add.l  #$FFFF,a1'
	add.l	#$FFFF,a1
	dc.b 'add.l  #$FFFF,a2'
	add.l	#$FFFF,a2
	dc.b 'add.l  #$FFFF,a3'
	add.l	#$FFFF,a3
	dc.b 'add.l  #$FFFF,a4'
	add.l	#$FFFF,a4
	dc.b 'add.l  #$FFFF,a5'
	add.l	#$FFFF,a5
	dc.b 'add.l  #$FFFF,a6'
	add.l	#$FFFF,a6
	dc.b 'add.l  #$FFFF,a7'
	add.l	#$FFFF,a7
	dc.b 'add.l  #$FFFF,sp'
	add.l	#$FFFF,sp
	dc.b 'add.l  #$FFFFFFFF,a1'
	add.l	#$FFFFFFFF,a1
	dc.b 'add.l  #$FFFFFFFF,a2'
	add.l	#$FFFFFFFF,a2
	dc.b 'add.l  #$FFFFFFFF,a3'
	add.l	#$FFFFFFFF,a3
	dc.b 'add.l  #$FFFFFFFF,a4'
	add.l	#$FFFFFFFF,a4
	dc.b 'add.l  #$FFFFFFFF,a5'
	add.l	#$FFFFFFFF,a5
	dc.b 'add.l  #$FFFFFFFF,a6'
	add.l	#$FFFFFFFF,a6
	dc.b 'add.l  #$FFFFFFFF,a7'
	add.l	#$FFFFFFFF,a7
	dc.b 'add.l  #$FFFFFFFF,sp'
	add.l	#$FFFFFFFF,sp
	dc.b 'add.l #"WXYZ",a1'
	add.l	#"WXYZ",a1
	dc.b 'add.l #"WXYZ",a2'
	add.l	#"WXYZ",a2
	dc.b 'add.l #"WXYZ",a3'
	add.l	#"WXYZ",a3
	dc.b 'add.l #"WXYZ",a4'
	add.l	#"WXYZ",a4
	dc.b 'add.l #"WXYZ",a5'
	add.l	#"WXYZ",a5
	dc.b 'add.l #"WXYZ",a6'
	add.l	#"WXYZ",a6
	dc.b 'add.l #"WXYZ",a7'
	add.l	#"WXYZ",a7
	dc.b 'add.l #"WXYZ",sp'
	add.l	#"WXYZ",sp
	dc.b 'add.l  #1+1,a1'
	add.l	#1+1,a1
	dc.b 'add.l  #1+1,a2'
	add.l	#1+1,a2
	dc.b 'add.l  #1+1,a3'
	add.l	#1+1,a3
	dc.b 'add.l  #1+1,a4'
	add.l	#1+1,a4
	dc.b 'add.l  #1+1,a5'
	add.l	#1+1,a5
	dc.b 'add.l  #1+1,a6'
	add.l	#1+1,a6
	dc.b 'add.l  #1+1,a7'
	add.l	#1+1,a7
	dc.b 'add.l  #1+1,sp'
	add.l	#1+1,sp
	dc.b 'add.l  #(3+4),a1'
	add.l	#(3+4),a1
	dc.b 'add.l  #(3+4),a2'
	add.l	#(3+4),a2
	dc.b 'add.l  #(3+4),a3'
	add.l	#(3+4),a3
	dc.b 'add.l  #(3+4),a4'
	add.l	#(3+4),a4
	dc.b 'add.l  #(3+4),a5'
	add.l	#(3+4),a5
	dc.b 'add.l  #(3+4),a6'
	add.l	#(3+4),a6
	dc.b 'add.l  #(3+4),a7'
	add.l	#(3+4),a7
	dc.b 'add.l  #(3+4),sp'
	add.l	#(3+4),sp
	dc.b 'add.l #-1,a1'
	add.l	#-1,a1
	dc.b 'add.l #-1,a2'
	add.l	#-1,a2
	dc.b 'add.l #-1,a3'
	add.l	#-1,a3
	dc.b 'add.l #-1,a4'
	add.l	#-1,a4
	dc.b 'add.l #-1,a5'
	add.l	#-1,a5
	dc.b 'add.l #-1,a6'
	add.l	#-1,a6
	dc.b 'add.l #-1,a7'
	add.l	#-1,a7
	dc.b 'add.l #-1,sp'
	add.l	#-1,sp
	dc.b 'add.l #-2,a1'
	add.l	#-2,a1
	dc.b 'add.l #-2,a2'
	add.l	#-2,a2
	dc.b 'add.l #-2,a3'
	add.l	#-2,a3
	dc.b 'add.l #-2,a4'
	add.l	#-2,a4
	dc.b 'add.l #-2,a5'
	add.l	#-2,a5
	dc.b 'add.l #-2,a6'
	add.l	#-2,a6
	dc.b 'add.l #-2,a7'
	add.l	#-2,a7
	dc.b 'add.l #-2,sp'
	add.l	#-2,sp

	dc.b 'eor.b  #0,(a1)'
	eor.b	#0,(a1)
	dc.b 'eor.b  #0,(a2)'
	eor.b	#0,(a2)
	dc.b 'eor.b  #0,(a3)'
	eor.b	#0,(a3)
	dc.b 'eor.b  #0,(a4)'
	eor.b	#0,(a4)
	dc.b 'eor.b  #0,(a5)'
	eor.b	#0,(a5)
	dc.b 'eor.b  #0,(a6)'
	eor.b	#0,(a6)
	dc.b 'eor.b  #0,(a7)'
	eor.b	#0,(a7)
	dc.b 'eor.b  #0,(sp)'
	eor.b	#0,(sp)
	dc.b 'eor.b  #$FF,(a1)'
	eor.b	#$FF,(a1)
	dc.b 'eor.b  #$FF,(a2)'
	eor.b	#$FF,(a2)
	dc.b 'eor.b  #$FF,(a3)'
	eor.b	#$FF,(a3)
	dc.b 'eor.b  #$FF,(a4)'
	eor.b	#$FF,(a4)
	dc.b 'eor.b  #$FF,(a5)'
	eor.b	#$FF,(a5)
	dc.b 'eor.b  #$FF,(a6)'
	eor.b	#$FF,(a6)
	dc.b 'eor.b  #$FF,(a7)'
	eor.b	#$FF,(a7)
	dc.b 'eor.b  #$FF,(sp)'
	eor.b	#$FF,(sp)
	dc.b 'eor.b  #"X",(a1)'
	eor.b	#"X",(a1)
	dc.b 'eor.b  #"X",(a2)'
	eor.b	#"X",(a2)
	dc.b 'eor.b  #"X",(a3)'
	eor.b	#"X",(a3)
	dc.b 'eor.b  #"X",(a4)'
	eor.b	#"X",(a4)
	dc.b 'eor.b  #"X",(a5)'
	eor.b	#"X",(a5)
	dc.b 'eor.b  #"X",(a6)'
	eor.b	#"X",(a6)
	dc.b 'eor.b  #"X",(a7)'
	eor.b	#"X",(a7)
	dc.b 'eor.b  #"X",(sp)'
	eor.b	#"X",(sp)
	dc.b 'eor.b #0,(a1)+'
	eor.b	#0,(a1)+
	dc.b 'eor.b #0,(a2)+'
	eor.b	#0,(a2)+
	dc.b 'eor.b #0,(a3)+'
	eor.b	#0,(a3)+
	dc.b 'eor.b #0,(a4)+'
	eor.b	#0,(a4)+
	dc.b 'eor.b #0,(a5)+'
	eor.b	#0,(a5)+
	dc.b 'eor.b #0,(a6)+'
	eor.b	#0,(a6)+
	dc.b 'eor.b #0,(a7)+'
	eor.b	#0,(a7)+
	dc.b 'eor.b #0,(sp)+'
	eor.b	#0,(sp)+
	dc.b 'eor.b #$FF,(a1)+'
	eor.b	#$FF,(a1)+
	dc.b 'eor.b #$FF,(a2)+'
	eor.b	#$FF,(a2)+
	dc.b 'eor.b #$FF,(a3)+'
	eor.b	#$FF,(a3)+
	dc.b 'eor.b #$FF,(a4)+'
	eor.b	#$FF,(a4)+
	dc.b 'eor.b #$FF,(a5)+'
	eor.b	#$FF,(a5)+
	dc.b 'eor.b #$FF,(a6)+'
	eor.b	#$FF,(a6)+
	dc.b 'eor.b #$FF,(a7)+'
	eor.b	#$FF,(a7)+
	dc.b 'eor.b #$FF,(sp)+'
	eor.b	#$FF,(sp)+
	dc.b 'eor.b #"X",(a1)+'
	eor.b	#"X",(a1)+
	dc.b 'eor.b #"X",(a2)+'
	eor.b	#"X",(a2)+
	dc.b 'eor.b #"X",(a3)+'
	eor.b	#"X",(a3)+
	dc.b 'eor.b #"X",(a4)+'
	eor.b	#"X",(a4)+
	dc.b 'eor.b #"X",(a5)+'
	eor.b	#"X",(a5)+
	dc.b 'eor.b #"X",(a6)+'
	eor.b	#"X",(a6)+
	dc.b 'eor.b #"X",(a7)+'
	eor.b	#"X",(a7)+
	dc.b 'eor.b #"X",(sp)+'
	eor.b	#"X",(sp)+
	dc.b 'eor.b #0,-(a1)'
	eor.b	#0,-(a1)
	dc.b 'eor.b #0,-(a2)'
	eor.b	#0,-(a2)
	dc.b 'eor.b #0,-(a3)'
	eor.b	#0,-(a3)
	dc.b 'eor.b #0,-(a4)'
	eor.b	#0,-(a4)
	dc.b 'eor.b #0,-(a5)'
	eor.b	#0,-(a5)
	dc.b 'eor.b #0,-(a6)'
	eor.b	#0,-(a6)
	dc.b 'eor.b #0,-(a7)'
	eor.b	#0,-(a7)
	dc.b 'eor.b #0,-(sp)'
	eor.b	#0,-(sp)
	dc.b 'eor.b #$FF,-(a1)'
	eor.b	#$FF,-(a1)
	dc.b 'eor.b #$FF,-(a2)'
	eor.b	#$FF,-(a2)
	dc.b 'eor.b #$FF,-(a3)'
	eor.b	#$FF,-(a3)
	dc.b 'eor.b #$FF,-(a4)'
	eor.b	#$FF,-(a4)
	dc.b 'eor.b #$FF,-(a5)'
	eor.b	#$FF,-(a5)
	dc.b 'eor.b #$FF,-(a6)'
	eor.b	#$FF,-(a6)
	dc.b 'eor.b #$FF,-(a7)'
	eor.b	#$FF,-(a7)
	dc.b 'eor.b #$FF,-(sp)'
	eor.b	#$FF,-(sp)
	dc.b 'eor.b #"X",-(a1)'
	eor.b	#"X",-(a1)
	dc.b 'eor.b #"X",-(a2)'
	eor.b	#"X",-(a2)
	dc.b 'eor.b #"X",-(a3)'
	eor.b	#"X",-(a3)
	dc.b 'eor.b #"X",-(a4)'
	eor.b	#"X",-(a4)
	dc.b 'eor.b #"X",-(a5)'
	eor.b	#"X",-(a5)
	dc.b 'eor.b #"X",-(a6)'
	eor.b	#"X",-(a6)
	dc.b 'eor.b #"X",-(a7)'
	eor.b	#"X",-(a7)
	dc.b 'eor.b #"X",-(sp)'
	eor.b	#"X",-(sp)
	dc.b 'eor.b #0,($FFFFFFFF).l'
	eor.b	#0,($FFFFFFFF).l
	dc.b 'eor.b #0,label_start.l'
	eor.b	#0,label_start.l
	dc.b 'eor.b #0,$FFFFFFFF'
	eor.b	#0,$FFFFFFFF
	dc.b 'eor.b  #0,$1'
	eor.b	#0,$1
	dc.b 'eor.b #$FF,($FFFFFFFF).l'
	eor.b	#$FF,($FFFFFFFF).l
	dc.b 'eor.b #$FF,label_start.l'
	eor.b	#$FF,label_start.l
	dc.b 'eor.b #$FF,$FFFFFFFF'
	eor.b	#$FF,$FFFFFFFF
	dc.b 'eor.b  #$FF,$1'
	eor.b	#$FF,$1
	dc.b 'eor.b #"X",($FFFFFFFF).l'
	eor.b	#"X",($FFFFFFFF).l
	dc.b 'eor.b #"X",label_start.l'
	eor.b	#"X",label_start.l
	dc.b 'eor.b #"X",$FFFFFFFF'
	eor.b	#"X",$FFFFFFFF
	dc.b 'eor.b  #"X",$1'
	eor.b	#"X",$1
	dc.b 'eor.b #0,($FFFFFFFF).w'
	eor.b	#0,($FFFFFFFF).w
	dc.b 'eor.b  #0,$1'
	eor.b	#0,$1
	dc.b 'eor.b #$FF,($FFFFFFFF).w'
	eor.b	#$FF,($FFFFFFFF).w
	dc.b 'eor.b  #$FF,$1'
	eor.b	#$FF,$1
	dc.b 'eor.b #"X",($FFFFFFFF).w'
	eor.b	#"X",($FFFFFFFF).w
	dc.b 'eor.b  #"X",$1'
	eor.b	#"X",$1
	dc.b 'eor.b #0,$7FFF(a2)'
	eor.b	#0,$7FFF(a2)
	dc.b 'eor.b #0,$7FFF(a5)'
	eor.b	#0,$7FFF(a5)
	dc.b 'eor.b  #0,-2(sp)'
	eor.b	#0,-2(sp)
	dc.b 'eor.b #$FF,$7FFF(a2)'
	eor.b	#$FF,$7FFF(a2)
	dc.b 'eor.b #$FF,$7FFF(a5)'
	eor.b	#$FF,$7FFF(a5)
	dc.b 'eor.b  #$FF,-2(sp)'
	eor.b	#$FF,-2(sp)
	dc.b 'eor.b #"X",$7FFF(a2)'
	eor.b	#"X",$7FFF(a2)
	dc.b 'eor.b #"X",$7FFF(a5)'
	eor.b	#"X",$7FFF(a5)
	dc.b 'eor.b  #"X",-2(sp)'
	eor.b	#"X",-2(sp)
	dc.b 'eor.b  #0,$7F(a2,d5.w)'
	eor.b	#0,$7F(a2,d5.w)
	dc.b 'eor.b  #0,$7F(a5,d2.w)'
	eor.b	#0,$7F(a5,d2.w)
	dc.b 'eor.b  #0,$0F(a5,d2.l)'
	eor.b	#0,$0F(a5,d2.l)
	dc.b 'eor.b #0,$1+1(a5,d2.l)'
	eor.b	#0,$1+1(a5,d2.l)
	dc.b 'eor.b #0,-2(a5,d2.l)'
	eor.b	#0,-2(a5,d2.l)
	dc.b 'eor.b #0,(a0,d1.w)'
	eor.b	#0,(a0,d1.w)
	dc.b 'eor.b #0,(a1,d6)'
	eor.b	#0,(a1,d6)
	dc.b 'eor.b  #$FF,$7F(a2,d5.w)'
	eor.b	#$FF,$7F(a2,d5.w)
	dc.b 'eor.b  #$FF,$7F(a5,d2.w)'
	eor.b	#$FF,$7F(a5,d2.w)
	dc.b 'eor.b  #$FF,$0F(a5,d2.l)'
	eor.b	#$FF,$0F(a5,d2.l)
	dc.b 'eor.b #$FF,$1+1(a5,d2.l)'
	eor.b	#$FF,$1+1(a5,d2.l)
	dc.b 'eor.b #$FF,-2(a5,d2.l)'
	eor.b	#$FF,-2(a5,d2.l)
	dc.b 'eor.b #$FF,(a0,d1.w)'
	eor.b	#$FF,(a0,d1.w)
	dc.b 'eor.b #$FF,(a1,d6)'
	eor.b	#$FF,(a1,d6)
	dc.b 'eor.b  #"X",$7F(a2,d5.w)'
	eor.b	#"X",$7F(a2,d5.w)
	dc.b 'eor.b  #"X",$7F(a5,d2.w)'
	eor.b	#"X",$7F(a5,d2.w)
	dc.b 'eor.b  #"X",$0F(a5,d2.l)'
	eor.b	#"X",$0F(a5,d2.l)
	dc.b 'eor.b #"X",$1+1(a5,d2.l)'
	eor.b	#"X",$1+1(a5,d2.l)
	dc.b 'eor.b #"X",-2(a5,d2.l)'
	eor.b	#"X",-2(a5,d2.l)
	dc.b 'eor.b #"X",(a0,d1.w)'
	eor.b	#"X",(a0,d1.w)
	dc.b 'eor.b #"X",(a1,d6)'
	eor.b	#"X",(a1,d6)
	dc.b 'eor.b  #0,d1'
	eor.b	#0,d1
	dc.b 'eor.b  #0,d2'
	eor.b	#0,d2
	dc.b 'eor.b  #0,d3'
	eor.b	#0,d3
	dc.b 'eor.b  #0,d4'
	eor.b	#0,d4
	dc.b 'eor.b  #0,d5'
	eor.b	#0,d5
	dc.b 'eor.b  #$FF,d1'
	eor.b	#$FF,d1
	dc.b 'eor.b  #$FF,d2'
	eor.b	#$FF,d2
	dc.b 'eor.b  #$FF,d3'
	eor.b	#$FF,d3
	dc.b 'eor.b  #$FF,d4'
	eor.b	#$FF,d4
	dc.b 'eor.b  #$FF,d5'
	eor.b	#$FF,d5
	dc.b 'eor.b  #"X",d1'
	eor.b	#"X",d1
	dc.b 'eor.b  #"X",d2'
	eor.b	#"X",d2
	dc.b 'eor.b  #"X",d3'
	eor.b	#"X",d3
	dc.b 'eor.b  #"X",d4'
	eor.b	#"X",d4
	dc.b 'eor.b  #"X",d5'
	eor.b	#"X",d5
	dc.b 'eor.w  #0,(a1)'
	eor.w	#0,(a1)
	dc.b 'eor.w  #0,(a2)'
	eor.w	#0,(a2)
	dc.b 'eor.w  #0,(a3)'
	eor.w	#0,(a3)
	dc.b 'eor.w  #0,(a4)'
	eor.w	#0,(a4)
	dc.b 'eor.w  #0,(a5)'
	eor.w	#0,(a5)
	dc.b 'eor.w  #0,(a6)'
	eor.w	#0,(a6)
	dc.b 'eor.w  #0,(a7)'
	eor.w	#0,(a7)
	dc.b 'eor.w  #0,(sp)'
	eor.w	#0,(sp)
	dc.b 'eor.w  #4,(a1)'
	eor.w	#4,(a1)
	dc.b 'eor.w  #4,(a2)'
	eor.w	#4,(a2)
	dc.b 'eor.w  #4,(a3)'
	eor.w	#4,(a3)
	dc.b 'eor.w  #4,(a4)'
	eor.w	#4,(a4)
	dc.b 'eor.w  #4,(a5)'
	eor.w	#4,(a5)
	dc.b 'eor.w  #4,(a6)'
	eor.w	#4,(a6)
	dc.b 'eor.w  #4,(a7)'
	eor.w	#4,(a7)
	dc.b 'eor.w  #4,(sp)'
	eor.w	#4,(sp)
	dc.b 'eor.w  #$FF,(a1)'
	eor.w	#$FF,(a1)
	dc.b 'eor.w  #$FF,(a2)'
	eor.w	#$FF,(a2)
	dc.b 'eor.w  #$FF,(a3)'
	eor.w	#$FF,(a3)
	dc.b 'eor.w  #$FF,(a4)'
	eor.w	#$FF,(a4)
	dc.b 'eor.w  #$FF,(a5)'
	eor.w	#$FF,(a5)
	dc.b 'eor.w  #$FF,(a6)'
	eor.w	#$FF,(a6)
	dc.b 'eor.w  #$FF,(a7)'
	eor.w	#$FF,(a7)
	dc.b 'eor.w  #$FF,(sp)'
	eor.w	#$FF,(sp)
	dc.b 'eor.w #"XY",(a1)'
	eor.w	#"XY",(a1)
	dc.b 'eor.w #"XY",(a2)'
	eor.w	#"XY",(a2)
	dc.b 'eor.w #"XY",(a3)'
	eor.w	#"XY",(a3)
	dc.b 'eor.w #"XY",(a4)'
	eor.w	#"XY",(a4)
	dc.b 'eor.w #"XY",(a5)'
	eor.w	#"XY",(a5)
	dc.b 'eor.w #"XY",(a6)'
	eor.w	#"XY",(a6)
	dc.b 'eor.w #"XY",(a7)'
	eor.w	#"XY",(a7)
	dc.b 'eor.w #"XY",(sp)'
	eor.w	#"XY",(sp)
	dc.b 'eor.w  #$2700,(a1)'
	eor.w	#$2700,(a1)
	dc.b 'eor.w  #$2700,(a2)'
	eor.w	#$2700,(a2)
	dc.b 'eor.w  #$2700,(a3)'
	eor.w	#$2700,(a3)
	dc.b 'eor.w  #$2700,(a4)'
	eor.w	#$2700,(a4)
	dc.b 'eor.w  #$2700,(a5)'
	eor.w	#$2700,(a5)
	dc.b 'eor.w  #$2700,(a6)'
	eor.w	#$2700,(a6)
	dc.b 'eor.w  #$2700,(a7)'
	eor.w	#$2700,(a7)
	dc.b 'eor.w  #$2700,(sp)'
	eor.w	#$2700,(sp)
	dc.b 'eor.w  #$7FFF,(a1)'
	eor.w	#$7FFF,(a1)
	dc.b 'eor.w  #$7FFF,(a2)'
	eor.w	#$7FFF,(a2)
	dc.b 'eor.w  #$7FFF,(a3)'
	eor.w	#$7FFF,(a3)
	dc.b 'eor.w  #$7FFF,(a4)'
	eor.w	#$7FFF,(a4)
	dc.b 'eor.w  #$7FFF,(a5)'
	eor.w	#$7FFF,(a5)
	dc.b 'eor.w  #$7FFF,(a6)'
	eor.w	#$7FFF,(a6)
	dc.b 'eor.w  #$7FFF,(a7)'
	eor.w	#$7FFF,(a7)
	dc.b 'eor.w  #$7FFF,(sp)'
	eor.w	#$7FFF,(sp)
	dc.b 'eor.w  #$FFFF,(a1)'
	eor.w	#$FFFF,(a1)
	dc.b 'eor.w  #$FFFF,(a2)'
	eor.w	#$FFFF,(a2)
	dc.b 'eor.w  #$FFFF,(a3)'
	eor.w	#$FFFF,(a3)
	dc.b 'eor.w  #$FFFF,(a4)'
	eor.w	#$FFFF,(a4)
	dc.b 'eor.w  #$FFFF,(a5)'
	eor.w	#$FFFF,(a5)
	dc.b 'eor.w  #$FFFF,(a6)'
	eor.w	#$FFFF,(a6)
	dc.b 'eor.w  #$FFFF,(a7)'
	eor.w	#$FFFF,(a7)
	dc.b 'eor.w  #$FFFF,(sp)'
	eor.w	#$FFFF,(sp)
	dc.b 'eor.w #0,(a1)+'
	eor.w	#0,(a1)+
	dc.b 'eor.w #0,(a2)+'
	eor.w	#0,(a2)+
	dc.b 'eor.w #0,(a3)+'
	eor.w	#0,(a3)+
	dc.b 'eor.w #0,(a4)+'
	eor.w	#0,(a4)+
	dc.b 'eor.w #0,(a5)+'
	eor.w	#0,(a5)+
	dc.b 'eor.w #0,(a6)+'
	eor.w	#0,(a6)+
	dc.b 'eor.w #0,(a7)+'
	eor.w	#0,(a7)+
	dc.b 'eor.w #0,(sp)+'
	eor.w	#0,(sp)+
	dc.b 'eor.w #4,(a1)+'
	eor.w	#4,(a1)+
	dc.b 'eor.w #4,(a2)+'
	eor.w	#4,(a2)+
	dc.b 'eor.w #4,(a3)+'
	eor.w	#4,(a3)+
	dc.b 'eor.w #4,(a4)+'
	eor.w	#4,(a4)+
	dc.b 'eor.w #4,(a5)+'
	eor.w	#4,(a5)+
	dc.b 'eor.w #4,(a6)+'
	eor.w	#4,(a6)+
	dc.b 'eor.w #4,(a7)+'
	eor.w	#4,(a7)+
	dc.b 'eor.w #4,(sp)+'
	eor.w	#4,(sp)+
	dc.b 'eor.w #$FF,(a1)+'
	eor.w	#$FF,(a1)+
	dc.b 'eor.w #$FF,(a2)+'
	eor.w	#$FF,(a2)+
	dc.b 'eor.w #$FF,(a3)+'
	eor.w	#$FF,(a3)+
	dc.b 'eor.w #$FF,(a4)+'
	eor.w	#$FF,(a4)+
	dc.b 'eor.w #$FF,(a5)+'
	eor.w	#$FF,(a5)+
	dc.b 'eor.w #$FF,(a6)+'
	eor.w	#$FF,(a6)+
	dc.b 'eor.w #$FF,(a7)+'
	eor.w	#$FF,(a7)+
	dc.b 'eor.w #$FF,(sp)+'
	eor.w	#$FF,(sp)+
	dc.b 'eor.w  #"XY",(a1)+'
	eor.w	#"XY",(a1)+
	dc.b 'eor.w  #"XY",(a2)+'
	eor.w	#"XY",(a2)+
	dc.b 'eor.w  #"XY",(a3)+'
	eor.w	#"XY",(a3)+
	dc.b 'eor.w  #"XY",(a4)+'
	eor.w	#"XY",(a4)+
	dc.b 'eor.w  #"XY",(a5)+'
	eor.w	#"XY",(a5)+
	dc.b 'eor.w  #"XY",(a6)+'
	eor.w	#"XY",(a6)+
	dc.b 'eor.w  #"XY",(a7)+'
	eor.w	#"XY",(a7)+
	dc.b 'eor.w  #"XY",(sp)+'
	eor.w	#"XY",(sp)+
	dc.b 'eor.w #$2700,(a1)+'
	eor.w	#$2700,(a1)+
	dc.b 'eor.w #$2700,(a2)+'
	eor.w	#$2700,(a2)+
	dc.b 'eor.w #$2700,(a3)+'
	eor.w	#$2700,(a3)+
	dc.b 'eor.w #$2700,(a4)+'
	eor.w	#$2700,(a4)+
	dc.b 'eor.w #$2700,(a5)+'
	eor.w	#$2700,(a5)+
	dc.b 'eor.w #$2700,(a6)+'
	eor.w	#$2700,(a6)+
	dc.b 'eor.w #$2700,(a7)+'
	eor.w	#$2700,(a7)+
	dc.b 'eor.w #$2700,(sp)+'
	eor.w	#$2700,(sp)+
	dc.b 'eor.w #$7FFF,(a1)+'
	eor.w	#$7FFF,(a1)+
	dc.b 'eor.w #$7FFF,(a2)+'
	eor.w	#$7FFF,(a2)+
	dc.b 'eor.w #$7FFF,(a3)+'
	eor.w	#$7FFF,(a3)+
	dc.b 'eor.w #$7FFF,(a4)+'
	eor.w	#$7FFF,(a4)+
	dc.b 'eor.w #$7FFF,(a5)+'
	eor.w	#$7FFF,(a5)+
	dc.b 'eor.w #$7FFF,(a6)+'
	eor.w	#$7FFF,(a6)+
	dc.b 'eor.w #$7FFF,(a7)+'
	eor.w	#$7FFF,(a7)+
	dc.b 'eor.w #$7FFF,(sp)+'
	eor.w	#$7FFF,(sp)+
	dc.b 'eor.w #$FFFF,(a1)+'
	eor.w	#$FFFF,(a1)+
	dc.b 'eor.w #$FFFF,(a2)+'
	eor.w	#$FFFF,(a2)+
	dc.b 'eor.w #$FFFF,(a3)+'
	eor.w	#$FFFF,(a3)+
	dc.b 'eor.w #$FFFF,(a4)+'
	eor.w	#$FFFF,(a4)+
	dc.b 'eor.w #$FFFF,(a5)+'
	eor.w	#$FFFF,(a5)+
	dc.b 'eor.w #$FFFF,(a6)+'
	eor.w	#$FFFF,(a6)+
	dc.b 'eor.w #$FFFF,(a7)+'
	eor.w	#$FFFF,(a7)+
	dc.b 'eor.w #$FFFF,(sp)+'
	eor.w	#$FFFF,(sp)+
	dc.b 'eor.w #0,-(a1)'
	eor.w	#0,-(a1)
	dc.b 'eor.w #0,-(a2)'
	eor.w	#0,-(a2)
	dc.b 'eor.w #0,-(a3)'
	eor.w	#0,-(a3)
	dc.b 'eor.w #0,-(a4)'
	eor.w	#0,-(a4)
	dc.b 'eor.w #0,-(a5)'
	eor.w	#0,-(a5)
	dc.b 'eor.w #0,-(a6)'
	eor.w	#0,-(a6)
	dc.b 'eor.w #0,-(a7)'
	eor.w	#0,-(a7)
	dc.b 'eor.w #0,-(sp)'
	eor.w	#0,-(sp)
	dc.b 'eor.w #4,-(a1)'
	eor.w	#4,-(a1)
	dc.b 'eor.w #4,-(a2)'
	eor.w	#4,-(a2)
	dc.b 'eor.w #4,-(a3)'
	eor.w	#4,-(a3)
	dc.b 'eor.w #4,-(a4)'
	eor.w	#4,-(a4)
	dc.b 'eor.w #4,-(a5)'
	eor.w	#4,-(a5)
	dc.b 'eor.w #4,-(a6)'
	eor.w	#4,-(a6)
	dc.b 'eor.w #4,-(a7)'
	eor.w	#4,-(a7)
	dc.b 'eor.w #4,-(sp)'
	eor.w	#4,-(sp)
	dc.b 'eor.w #$FF,-(a1)'
	eor.w	#$FF,-(a1)
	dc.b 'eor.w #$FF,-(a2)'
	eor.w	#$FF,-(a2)
	dc.b 'eor.w #$FF,-(a3)'
	eor.w	#$FF,-(a3)
	dc.b 'eor.w #$FF,-(a4)'
	eor.w	#$FF,-(a4)
	dc.b 'eor.w #$FF,-(a5)'
	eor.w	#$FF,-(a5)
	dc.b 'eor.w #$FF,-(a6)'
	eor.w	#$FF,-(a6)
	dc.b 'eor.w #$FF,-(a7)'
	eor.w	#$FF,-(a7)
	dc.b 'eor.w #$FF,-(sp)'
	eor.w	#$FF,-(sp)
	dc.b 'eor.w  #"XY",-(a1)'
	eor.w	#"XY",-(a1)
	dc.b 'eor.w  #"XY",-(a2)'
	eor.w	#"XY",-(a2)
	dc.b 'eor.w  #"XY",-(a3)'
	eor.w	#"XY",-(a3)
	dc.b 'eor.w  #"XY",-(a4)'
	eor.w	#"XY",-(a4)
	dc.b 'eor.w  #"XY",-(a5)'
	eor.w	#"XY",-(a5)
	dc.b 'eor.w  #"XY",-(a6)'
	eor.w	#"XY",-(a6)
	dc.b 'eor.w  #"XY",-(a7)'
	eor.w	#"XY",-(a7)
	dc.b 'eor.w  #"XY",-(sp)'
	eor.w	#"XY",-(sp)
	dc.b 'eor.w #$2700,-(a1)'
	eor.w	#$2700,-(a1)
	dc.b 'eor.w #$2700,-(a2)'
	eor.w	#$2700,-(a2)
	dc.b 'eor.w #$2700,-(a3)'
	eor.w	#$2700,-(a3)
	dc.b 'eor.w #$2700,-(a4)'
	eor.w	#$2700,-(a4)
	dc.b 'eor.w #$2700,-(a5)'
	eor.w	#$2700,-(a5)
	dc.b 'eor.w #$2700,-(a6)'
	eor.w	#$2700,-(a6)
	dc.b 'eor.w #$2700,-(a7)'
	eor.w	#$2700,-(a7)
	dc.b 'eor.w #$2700,-(sp)'
	eor.w	#$2700,-(sp)
	dc.b 'eor.w #$7FFF,-(a1)'
	eor.w	#$7FFF,-(a1)
	dc.b 'eor.w #$7FFF,-(a2)'
	eor.w	#$7FFF,-(a2)
	dc.b 'eor.w #$7FFF,-(a3)'
	eor.w	#$7FFF,-(a3)
	dc.b 'eor.w #$7FFF,-(a4)'
	eor.w	#$7FFF,-(a4)
	dc.b 'eor.w #$7FFF,-(a5)'
	eor.w	#$7FFF,-(a5)
	dc.b 'eor.w #$7FFF,-(a6)'
	eor.w	#$7FFF,-(a6)
	dc.b 'eor.w #$7FFF,-(a7)'
	eor.w	#$7FFF,-(a7)
	dc.b 'eor.w #$7FFF,-(sp)'
	eor.w	#$7FFF,-(sp)
	dc.b 'eor.w #$FFFF,-(a1)'
	eor.w	#$FFFF,-(a1)
	dc.b 'eor.w #$FFFF,-(a2)'
	eor.w	#$FFFF,-(a2)
	dc.b 'eor.w #$FFFF,-(a3)'
	eor.w	#$FFFF,-(a3)
	dc.b 'eor.w #$FFFF,-(a4)'
	eor.w	#$FFFF,-(a4)
	dc.b 'eor.w #$FFFF,-(a5)'
	eor.w	#$FFFF,-(a5)
	dc.b 'eor.w #$FFFF,-(a6)'
	eor.w	#$FFFF,-(a6)
	dc.b 'eor.w #$FFFF,-(a7)'
	eor.w	#$FFFF,-(a7)
	dc.b 'eor.w #$FFFF,-(sp)'
	eor.w	#$FFFF,-(sp)
	dc.b 'eor.w #0,($FFFFFFFF).l'
	eor.w	#0,($FFFFFFFF).l
	dc.b 'eor.w #0,label_start.l'
	eor.w	#0,label_start.l
	dc.b 'eor.w #0,$FFFFFFFF'
	eor.w	#0,$FFFFFFFF
	dc.b 'eor.w  #0,$1'
	eor.w	#0,$1
	dc.b 'eor.w #4,($FFFFFFFF).l'
	eor.w	#4,($FFFFFFFF).l
	dc.b 'eor.w #4,label_start.l'
	eor.w	#4,label_start.l
	dc.b 'eor.w #4,$FFFFFFFF'
	eor.w	#4,$FFFFFFFF
	dc.b 'eor.w  #4,$1'
	eor.w	#4,$1
	dc.b 'eor.w #$FF,($FFFFFFFF).l'
	eor.w	#$FF,($FFFFFFFF).l
	dc.b 'eor.w #$FF,label_start.l'
	eor.w	#$FF,label_start.l
	dc.b 'eor.w #$FF,$FFFFFFFF'
	eor.w	#$FF,$FFFFFFFF
	dc.b 'eor.w  #$FF,$1'
	eor.w	#$FF,$1
	dc.b 'eor.w  #"XY",($FFFFFFFF).l'
	eor.w	#"XY",($FFFFFFFF).l
	dc.b 'eor.w  #"XY",label_start.l'
	eor.w	#"XY",label_start.l
	dc.b 'eor.w  #"XY",$FFFFFFFF'
	eor.w	#"XY",$FFFFFFFF
	dc.b 'eor.w #"XY",$1'
	eor.w	#"XY",$1
	dc.b 'eor.w #$2700,($FFFFFFFF).l'
	eor.w	#$2700,($FFFFFFFF).l
	dc.b 'eor.w #$2700,label_start.l'
	eor.w	#$2700,label_start.l
	dc.b 'eor.w #$2700,$FFFFFFFF'
	eor.w	#$2700,$FFFFFFFF
	dc.b 'eor.w  #$2700,$1'
	eor.w	#$2700,$1
	dc.b 'eor.w #$7FFF,($FFFFFFFF).l'
	eor.w	#$7FFF,($FFFFFFFF).l
	dc.b 'eor.w #$7FFF,label_start.l'
	eor.w	#$7FFF,label_start.l
	dc.b 'eor.w #$7FFF,$FFFFFFFF'
	eor.w	#$7FFF,$FFFFFFFF
	dc.b 'eor.w  #$7FFF,$1'
	eor.w	#$7FFF,$1
	dc.b 'eor.w #$FFFF,($FFFFFFFF).l'
	eor.w	#$FFFF,($FFFFFFFF).l
	dc.b 'eor.w #$FFFF,label_start.l'
	eor.w	#$FFFF,label_start.l
	dc.b 'eor.w #$FFFF,$FFFFFFFF'
	eor.w	#$FFFF,$FFFFFFFF
	dc.b 'eor.w  #$FFFF,$1'
	eor.w	#$FFFF,$1
	dc.b 'eor.w #0,($FFFFFFFF).w'
	eor.w	#0,($FFFFFFFF).w
	dc.b 'eor.w  #0,$1'
	eor.w	#0,$1
	dc.b 'eor.w #4,($FFFFFFFF).w'
	eor.w	#4,($FFFFFFFF).w
	dc.b 'eor.w  #4,$1'
	eor.w	#4,$1
	dc.b 'eor.w #$FF,($FFFFFFFF).w'
	eor.w	#$FF,($FFFFFFFF).w
	dc.b 'eor.w  #$FF,$1'
	eor.w	#$FF,$1
	dc.b 'eor.w  #"XY",($FFFFFFFF).w'
	eor.w	#"XY",($FFFFFFFF).w
	dc.b 'eor.w #"XY",$1'
	eor.w	#"XY",$1
	dc.b 'eor.w #$2700,($FFFFFFFF).w'
	eor.w	#$2700,($FFFFFFFF).w
	dc.b 'eor.w  #$2700,$1'
	eor.w	#$2700,$1
	dc.b 'eor.w #$7FFF,($FFFFFFFF).w'
	eor.w	#$7FFF,($FFFFFFFF).w
	dc.b 'eor.w  #$7FFF,$1'
	eor.w	#$7FFF,$1
	dc.b 'eor.w #$FFFF,($FFFFFFFF).w'
	eor.w	#$FFFF,($FFFFFFFF).w
	dc.b 'eor.w  #$FFFF,$1'
	eor.w	#$FFFF,$1
	dc.b 'eor.w #0,$7FFF(a2)'
	eor.w	#0,$7FFF(a2)
	dc.b 'eor.w #0,$7FFF(a5)'
	eor.w	#0,$7FFF(a5)
	dc.b 'eor.w  #0,-2(sp)'
	eor.w	#0,-2(sp)
	dc.b 'eor.w #4,$7FFF(a2)'
	eor.w	#4,$7FFF(a2)
	dc.b 'eor.w #4,$7FFF(a5)'
	eor.w	#4,$7FFF(a5)
	dc.b 'eor.w  #4,-2(sp)'
	eor.w	#4,-2(sp)
	dc.b 'eor.w #$FF,$7FFF(a2)'
	eor.w	#$FF,$7FFF(a2)
	dc.b 'eor.w #$FF,$7FFF(a5)'
	eor.w	#$FF,$7FFF(a5)
	dc.b 'eor.w  #$FF,-2(sp)'
	eor.w	#$FF,-2(sp)
	dc.b 'eor.w  #"XY",$7FFF(a2)'
	eor.w	#"XY",$7FFF(a2)
	dc.b 'eor.w  #"XY",$7FFF(a5)'
	eor.w	#"XY",$7FFF(a5)
	dc.b 'eor.w #"XY",-2(sp)'
	eor.w	#"XY",-2(sp)
	dc.b 'eor.w #$2700,$7FFF(a2)'
	eor.w	#$2700,$7FFF(a2)
	dc.b 'eor.w #$2700,$7FFF(a5)'
	eor.w	#$2700,$7FFF(a5)
	dc.b 'eor.w  #$2700,-2(sp)'
	eor.w	#$2700,-2(sp)
	dc.b 'eor.w #$7FFF,$7FFF(a2)'
	eor.w	#$7FFF,$7FFF(a2)
	dc.b 'eor.w #$7FFF,$7FFF(a5)'
	eor.w	#$7FFF,$7FFF(a5)
	dc.b 'eor.w  #$7FFF,-2(sp)'
	eor.w	#$7FFF,-2(sp)
	dc.b 'eor.w #$FFFF,$7FFF(a2)'
	eor.w	#$FFFF,$7FFF(a2)
	dc.b 'eor.w #$FFFF,$7FFF(a5)'
	eor.w	#$FFFF,$7FFF(a5)
	dc.b 'eor.w  #$FFFF,-2(sp)'
	eor.w	#$FFFF,-2(sp)
	dc.b 'eor.w  #0,$7F(a2,d5.w)'
	eor.w	#0,$7F(a2,d5.w)
	dc.b 'eor.w  #0,$7F(a5,d2.w)'
	eor.w	#0,$7F(a5,d2.w)
	dc.b 'eor.w  #0,$0F(a5,d2.l)'
	eor.w	#0,$0F(a5,d2.l)
	dc.b 'eor.w #0,$1+1(a5,d2.l)'
	eor.w	#0,$1+1(a5,d2.l)
	dc.b 'eor.w #0,-2(a5,d2.l)'
	eor.w	#0,-2(a5,d2.l)
	dc.b 'eor.w #0,(a0,d1.w)'
	eor.w	#0,(a0,d1.w)
	dc.b 'eor.w #0,(a1,d6)'
	eor.w	#0,(a1,d6)
	dc.b 'eor.w  #4,$7F(a2,d5.w)'
	eor.w	#4,$7F(a2,d5.w)
	dc.b 'eor.w  #4,$7F(a5,d2.w)'
	eor.w	#4,$7F(a5,d2.w)
	dc.b 'eor.w  #4,$0F(a5,d2.l)'
	eor.w	#4,$0F(a5,d2.l)
	dc.b 'eor.w #4,$1+1(a5,d2.l)'
	eor.w	#4,$1+1(a5,d2.l)
	dc.b 'eor.w #4,-2(a5,d2.l)'
	eor.w	#4,-2(a5,d2.l)
	dc.b 'eor.w #4,(a0,d1.w)'
	eor.w	#4,(a0,d1.w)
	dc.b 'eor.w #4,(a1,d6)'
	eor.w	#4,(a1,d6)
	dc.b 'eor.w  #$FF,$7F(a2,d5.w)'
	eor.w	#$FF,$7F(a2,d5.w)
	dc.b 'eor.w  #$FF,$7F(a5,d2.w)'
	eor.w	#$FF,$7F(a5,d2.w)
	dc.b 'eor.w  #$FF,$0F(a5,d2.l)'
	eor.w	#$FF,$0F(a5,d2.l)
	dc.b 'eor.w #$FF,$1+1(a5,d2.l)'
	eor.w	#$FF,$1+1(a5,d2.l)
	dc.b 'eor.w #$FF,-2(a5,d2.l)'
	eor.w	#$FF,-2(a5,d2.l)
	dc.b 'eor.w #$FF,(a0,d1.w)'
	eor.w	#$FF,(a0,d1.w)
	dc.b 'eor.w #$FF,(a1,d6)'
	eor.w	#$FF,(a1,d6)
	dc.b 'eor.w #"XY",$7F(a2,d5.w)'
	eor.w	#"XY",$7F(a2,d5.w)
	dc.b 'eor.w #"XY",$7F(a5,d2.w)'
	eor.w	#"XY",$7F(a5,d2.w)
	dc.b 'eor.w #"XY",$0F(a5,d2.l)'
	eor.w	#"XY",$0F(a5,d2.l)
	dc.b 'eor.w  #"XY",$1+1(a5,d2.l)'
	eor.w	#"XY",$1+1(a5,d2.l)
	dc.b 'eor.w  #"XY",-2(a5,d2.l)'
	eor.w	#"XY",-2(a5,d2.l)
	dc.b 'eor.w  #"XY",(a0,d1.w)'
	eor.w	#"XY",(a0,d1.w)
	dc.b 'eor.w  #"XY",(a1,d6)'
	eor.w	#"XY",(a1,d6)
	dc.b 'eor.w  #$2700,$7F(a2,d5.w)'
	eor.w	#$2700,$7F(a2,d5.w)
	dc.b 'eor.w  #$2700,$7F(a5,d2.w)'
	eor.w	#$2700,$7F(a5,d2.w)
	dc.b 'eor.w  #$2700,$0F(a5,d2.l)'
	eor.w	#$2700,$0F(a5,d2.l)
	dc.b 'eor.w #$2700,$1+1(a5,d2.l)'
	eor.w	#$2700,$1+1(a5,d2.l)
	dc.b 'eor.w #$2700,-2(a5,d2.l)'
	eor.w	#$2700,-2(a5,d2.l)
	dc.b 'eor.w #$2700,(a0,d1.w)'
	eor.w	#$2700,(a0,d1.w)
	dc.b 'eor.w #$2700,(a1,d6)'
	eor.w	#$2700,(a1,d6)
	dc.b 'eor.w  #$7FFF,$7F(a2,d5.w)'
	eor.w	#$7FFF,$7F(a2,d5.w)
	dc.b 'eor.w  #$7FFF,$7F(a5,d2.w)'
	eor.w	#$7FFF,$7F(a5,d2.w)
	dc.b 'eor.w  #$7FFF,$0F(a5,d2.l)'
	eor.w	#$7FFF,$0F(a5,d2.l)
	dc.b 'eor.w #$7FFF,$1+1(a5,d2.l)'
	eor.w	#$7FFF,$1+1(a5,d2.l)
	dc.b 'eor.w #$7FFF,-2(a5,d2.l)'
	eor.w	#$7FFF,-2(a5,d2.l)
	dc.b 'eor.w #$7FFF,(a0,d1.w)'
	eor.w	#$7FFF,(a0,d1.w)
	dc.b 'eor.w #$7FFF,(a1,d6)'
	eor.w	#$7FFF,(a1,d6)
	dc.b 'eor.w  #$FFFF,$7F(a2,d5.w)'
	eor.w	#$FFFF,$7F(a2,d5.w)
	dc.b 'eor.w  #$FFFF,$7F(a5,d2.w)'
	eor.w	#$FFFF,$7F(a5,d2.w)
	dc.b 'eor.w  #$FFFF,$0F(a5,d2.l)'
	eor.w	#$FFFF,$0F(a5,d2.l)
	dc.b 'eor.w #$FFFF,$1+1(a5,d2.l)'
	eor.w	#$FFFF,$1+1(a5,d2.l)
	dc.b 'eor.w #$FFFF,-2(a5,d2.l)'
	eor.w	#$FFFF,-2(a5,d2.l)
	dc.b 'eor.w #$FFFF,(a0,d1.w)'
	eor.w	#$FFFF,(a0,d1.w)
	dc.b 'eor.w #$FFFF,(a1,d6)'
	eor.w	#$FFFF,(a1,d6)
	dc.b 'eor.w  #0,d1'
	eor.w	#0,d1
	dc.b 'eor.w  #0,d2'
	eor.w	#0,d2
	dc.b 'eor.w  #0,d3'
	eor.w	#0,d3
	dc.b 'eor.w  #0,d4'
	eor.w	#0,d4
	dc.b 'eor.w  #0,d5'
	eor.w	#0,d5
	dc.b 'eor.w  #4,d1'
	eor.w	#4,d1
	dc.b 'eor.w  #4,d2'
	eor.w	#4,d2
	dc.b 'eor.w  #4,d3'
	eor.w	#4,d3
	dc.b 'eor.w  #4,d4'
	eor.w	#4,d4
	dc.b 'eor.w  #4,d5'
	eor.w	#4,d5
	dc.b 'eor.w  #$FF,d1'
	eor.w	#$FF,d1
	dc.b 'eor.w  #$FF,d2'
	eor.w	#$FF,d2
	dc.b 'eor.w  #$FF,d3'
	eor.w	#$FF,d3
	dc.b 'eor.w  #$FF,d4'
	eor.w	#$FF,d4
	dc.b 'eor.w  #$FF,d5'
	eor.w	#$FF,d5
	dc.b 'eor.w #"XY",d1'
	eor.w	#"XY",d1
	dc.b 'eor.w #"XY",d2'
	eor.w	#"XY",d2
	dc.b 'eor.w #"XY",d3'
	eor.w	#"XY",d3
	dc.b 'eor.w #"XY",d4'
	eor.w	#"XY",d4
	dc.b 'eor.w #"XY",d5'
	eor.w	#"XY",d5
	dc.b 'eor.w  #$2700,d1'
	eor.w	#$2700,d1
	dc.b 'eor.w  #$2700,d2'
	eor.w	#$2700,d2
	dc.b 'eor.w  #$2700,d3'
	eor.w	#$2700,d3
	dc.b 'eor.w  #$2700,d4'
	eor.w	#$2700,d4
	dc.b 'eor.w  #$2700,d5'
	eor.w	#$2700,d5
	dc.b 'eor.w  #$7FFF,d1'
	eor.w	#$7FFF,d1
	dc.b 'eor.w  #$7FFF,d2'
	eor.w	#$7FFF,d2
	dc.b 'eor.w  #$7FFF,d3'
	eor.w	#$7FFF,d3
	dc.b 'eor.w  #$7FFF,d4'
	eor.w	#$7FFF,d4
	dc.b 'eor.w  #$7FFF,d5'
	eor.w	#$7FFF,d5
	dc.b 'eor.w  #$FFFF,d1'
	eor.w	#$FFFF,d1
	dc.b 'eor.w  #$FFFF,d2'
	eor.w	#$FFFF,d2
	dc.b 'eor.w  #$FFFF,d3'
	eor.w	#$FFFF,d3
	dc.b 'eor.w  #$FFFF,d4'
	eor.w	#$FFFF,d4
	dc.b 'eor.w  #$FFFF,d5'
	eor.w	#$FFFF,d5
	dc.b 'eor.l  #0,(a1)'
	eor.l	#0,(a1)
	dc.b 'eor.l  #0,(a2)'
	eor.l	#0,(a2)
	dc.b 'eor.l  #0,(a3)'
	eor.l	#0,(a3)
	dc.b 'eor.l  #0,(a4)'
	eor.l	#0,(a4)
	dc.b 'eor.l  #0,(a5)'
	eor.l	#0,(a5)
	dc.b 'eor.l  #0,(a6)'
	eor.l	#0,(a6)
	dc.b 'eor.l  #0,(a7)'
	eor.l	#0,(a7)
	dc.b 'eor.l  #0,(sp)'
	eor.l	#0,(sp)
	dc.b 'eor.l  #4,(a1)'
	eor.l	#4,(a1)
	dc.b 'eor.l  #4,(a2)'
	eor.l	#4,(a2)
	dc.b 'eor.l  #4,(a3)'
	eor.l	#4,(a3)
	dc.b 'eor.l  #4,(a4)'
	eor.l	#4,(a4)
	dc.b 'eor.l  #4,(a5)'
	eor.l	#4,(a5)
	dc.b 'eor.l  #4,(a6)'
	eor.l	#4,(a6)
	dc.b 'eor.l  #4,(a7)'
	eor.l	#4,(a7)
	dc.b 'eor.l  #4,(sp)'
	eor.l	#4,(sp)
	dc.b 'eor.l  #$FF,(a1)'
	eor.l	#$FF,(a1)
	dc.b 'eor.l  #$FF,(a2)'
	eor.l	#$FF,(a2)
	dc.b 'eor.l  #$FF,(a3)'
	eor.l	#$FF,(a3)
	dc.b 'eor.l  #$FF,(a4)'
	eor.l	#$FF,(a4)
	dc.b 'eor.l  #$FF,(a5)'
	eor.l	#$FF,(a5)
	dc.b 'eor.l  #$FF,(a6)'
	eor.l	#$FF,(a6)
	dc.b 'eor.l  #$FF,(a7)'
	eor.l	#$FF,(a7)
	dc.b 'eor.l  #$FF,(sp)'
	eor.l	#$FF,(sp)
	dc.b 'eor.l  #$7FFF,(a1)'
	eor.l	#$7FFF,(a1)
	dc.b 'eor.l  #$7FFF,(a2)'
	eor.l	#$7FFF,(a2)
	dc.b 'eor.l  #$7FFF,(a3)'
	eor.l	#$7FFF,(a3)
	dc.b 'eor.l  #$7FFF,(a4)'
	eor.l	#$7FFF,(a4)
	dc.b 'eor.l  #$7FFF,(a5)'
	eor.l	#$7FFF,(a5)
	dc.b 'eor.l  #$7FFF,(a6)'
	eor.l	#$7FFF,(a6)
	dc.b 'eor.l  #$7FFF,(a7)'
	eor.l	#$7FFF,(a7)
	dc.b 'eor.l  #$7FFF,(sp)'
	eor.l	#$7FFF,(sp)
	dc.b 'eor.l  #$FFFF,(a1)'
	eor.l	#$FFFF,(a1)
	dc.b 'eor.l  #$FFFF,(a2)'
	eor.l	#$FFFF,(a2)
	dc.b 'eor.l  #$FFFF,(a3)'
	eor.l	#$FFFF,(a3)
	dc.b 'eor.l  #$FFFF,(a4)'
	eor.l	#$FFFF,(a4)
	dc.b 'eor.l  #$FFFF,(a5)'
	eor.l	#$FFFF,(a5)
	dc.b 'eor.l  #$FFFF,(a6)'
	eor.l	#$FFFF,(a6)
	dc.b 'eor.l  #$FFFF,(a7)'
	eor.l	#$FFFF,(a7)
	dc.b 'eor.l  #$FFFF,(sp)'
	eor.l	#$FFFF,(sp)
	dc.b 'eor.l  #$FFFFFFFF,(a1)'
	eor.l	#$FFFFFFFF,(a1)
	dc.b 'eor.l  #$FFFFFFFF,(a2)'
	eor.l	#$FFFFFFFF,(a2)
	dc.b 'eor.l  #$FFFFFFFF,(a3)'
	eor.l	#$FFFFFFFF,(a3)
	dc.b 'eor.l  #$FFFFFFFF,(a4)'
	eor.l	#$FFFFFFFF,(a4)
	dc.b 'eor.l  #$FFFFFFFF,(a5)'
	eor.l	#$FFFFFFFF,(a5)
	dc.b 'eor.l  #$FFFFFFFF,(a6)'
	eor.l	#$FFFFFFFF,(a6)
	dc.b 'eor.l  #$FFFFFFFF,(a7)'
	eor.l	#$FFFFFFFF,(a7)
	dc.b 'eor.l  #$FFFFFFFF,(sp)'
	eor.l	#$FFFFFFFF,(sp)
	dc.b 'eor.l #"WXYZ",(a1)'
	eor.l	#"WXYZ",(a1)
	dc.b 'eor.l #"WXYZ",(a2)'
	eor.l	#"WXYZ",(a2)
	dc.b 'eor.l #"WXYZ",(a3)'
	eor.l	#"WXYZ",(a3)
	dc.b 'eor.l #"WXYZ",(a4)'
	eor.l	#"WXYZ",(a4)
	dc.b 'eor.l #"WXYZ",(a5)'
	eor.l	#"WXYZ",(a5)
	dc.b 'eor.l #"WXYZ",(a6)'
	eor.l	#"WXYZ",(a6)
	dc.b 'eor.l #"WXYZ",(a7)'
	eor.l	#"WXYZ",(a7)
	dc.b 'eor.l #"WXYZ",(sp)'
	eor.l	#"WXYZ",(sp)
	dc.b 'eor.l  #1+1,(a1)'
	eor.l	#1+1,(a1)
	dc.b 'eor.l  #1+1,(a2)'
	eor.l	#1+1,(a2)
	dc.b 'eor.l  #1+1,(a3)'
	eor.l	#1+1,(a3)
	dc.b 'eor.l  #1+1,(a4)'
	eor.l	#1+1,(a4)
	dc.b 'eor.l  #1+1,(a5)'
	eor.l	#1+1,(a5)
	dc.b 'eor.l  #1+1,(a6)'
	eor.l	#1+1,(a6)
	dc.b 'eor.l  #1+1,(a7)'
	eor.l	#1+1,(a7)
	dc.b 'eor.l  #1+1,(sp)'
	eor.l	#1+1,(sp)
	dc.b 'eor.l  #(3+4),(a1)'
	eor.l	#(3+4),(a1)
	dc.b 'eor.l  #(3+4),(a2)'
	eor.l	#(3+4),(a2)
	dc.b 'eor.l  #(3+4),(a3)'
	eor.l	#(3+4),(a3)
	dc.b 'eor.l  #(3+4),(a4)'
	eor.l	#(3+4),(a4)
	dc.b 'eor.l  #(3+4),(a5)'
	eor.l	#(3+4),(a5)
	dc.b 'eor.l  #(3+4),(a6)'
	eor.l	#(3+4),(a6)
	dc.b 'eor.l  #(3+4),(a7)'
	eor.l	#(3+4),(a7)
	dc.b 'eor.l  #(3+4),(sp)'
	eor.l	#(3+4),(sp)
	dc.b 'eor.l #-1,(a1)'
	eor.l	#-1,(a1)
	dc.b 'eor.l #-1,(a2)'
	eor.l	#-1,(a2)
	dc.b 'eor.l #-1,(a3)'
	eor.l	#-1,(a3)
	dc.b 'eor.l #-1,(a4)'
	eor.l	#-1,(a4)
	dc.b 'eor.l #-1,(a5)'
	eor.l	#-1,(a5)
	dc.b 'eor.l #-1,(a6)'
	eor.l	#-1,(a6)
	dc.b 'eor.l #-1,(a7)'
	eor.l	#-1,(a7)
	dc.b 'eor.l #-1,(sp)'
	eor.l	#-1,(sp)
	dc.b 'eor.l #-2,(a1)'
	eor.l	#-2,(a1)
	dc.b 'eor.l #-2,(a2)'
	eor.l	#-2,(a2)
	dc.b 'eor.l #-2,(a3)'
	eor.l	#-2,(a3)
	dc.b 'eor.l #-2,(a4)'
	eor.l	#-2,(a4)
	dc.b 'eor.l #-2,(a5)'
	eor.l	#-2,(a5)
	dc.b 'eor.l #-2,(a6)'
	eor.l	#-2,(a6)
	dc.b 'eor.l #-2,(a7)'
	eor.l	#-2,(a7)
	dc.b 'eor.l #-2,(sp)'
	eor.l	#-2,(sp)
	dc.b 'eor.l #0,(a1)+'
	eor.l	#0,(a1)+
	dc.b 'eor.l #0,(a2)+'
	eor.l	#0,(a2)+
	dc.b 'eor.l #0,(a3)+'
	eor.l	#0,(a3)+
	dc.b 'eor.l #0,(a4)+'
	eor.l	#0,(a4)+
	dc.b 'eor.l #0,(a5)+'
	eor.l	#0,(a5)+
	dc.b 'eor.l #0,(a6)+'
	eor.l	#0,(a6)+
	dc.b 'eor.l #0,(a7)+'
	eor.l	#0,(a7)+
	dc.b 'eor.l #0,(sp)+'
	eor.l	#0,(sp)+
	dc.b 'eor.l #4,(a1)+'
	eor.l	#4,(a1)+
	dc.b 'eor.l #4,(a2)+'
	eor.l	#4,(a2)+
	dc.b 'eor.l #4,(a3)+'
	eor.l	#4,(a3)+
	dc.b 'eor.l #4,(a4)+'
	eor.l	#4,(a4)+
	dc.b 'eor.l #4,(a5)+'
	eor.l	#4,(a5)+
	dc.b 'eor.l #4,(a6)+'
	eor.l	#4,(a6)+
	dc.b 'eor.l #4,(a7)+'
	eor.l	#4,(a7)+
	dc.b 'eor.l #4,(sp)+'
	eor.l	#4,(sp)+
	dc.b 'eor.l #$FF,(a1)+'
	eor.l	#$FF,(a1)+
	dc.b 'eor.l #$FF,(a2)+'
	eor.l	#$FF,(a2)+
	dc.b 'eor.l #$FF,(a3)+'
	eor.l	#$FF,(a3)+
	dc.b 'eor.l #$FF,(a4)+'
	eor.l	#$FF,(a4)+
	dc.b 'eor.l #$FF,(a5)+'
	eor.l	#$FF,(a5)+
	dc.b 'eor.l #$FF,(a6)+'
	eor.l	#$FF,(a6)+
	dc.b 'eor.l #$FF,(a7)+'
	eor.l	#$FF,(a7)+
	dc.b 'eor.l #$FF,(sp)+'
	eor.l	#$FF,(sp)+
	dc.b 'eor.l #$7FFF,(a1)+'
	eor.l	#$7FFF,(a1)+
	dc.b 'eor.l #$7FFF,(a2)+'
	eor.l	#$7FFF,(a2)+
	dc.b 'eor.l #$7FFF,(a3)+'
	eor.l	#$7FFF,(a3)+
	dc.b 'eor.l #$7FFF,(a4)+'
	eor.l	#$7FFF,(a4)+
	dc.b 'eor.l #$7FFF,(a5)+'
	eor.l	#$7FFF,(a5)+
	dc.b 'eor.l #$7FFF,(a6)+'
	eor.l	#$7FFF,(a6)+
	dc.b 'eor.l #$7FFF,(a7)+'
	eor.l	#$7FFF,(a7)+
	dc.b 'eor.l #$7FFF,(sp)+'
	eor.l	#$7FFF,(sp)+
	dc.b 'eor.l #$FFFF,(a1)+'
	eor.l	#$FFFF,(a1)+
	dc.b 'eor.l #$FFFF,(a2)+'
	eor.l	#$FFFF,(a2)+
	dc.b 'eor.l #$FFFF,(a3)+'
	eor.l	#$FFFF,(a3)+
	dc.b 'eor.l #$FFFF,(a4)+'
	eor.l	#$FFFF,(a4)+
	dc.b 'eor.l #$FFFF,(a5)+'
	eor.l	#$FFFF,(a5)+
	dc.b 'eor.l #$FFFF,(a6)+'
	eor.l	#$FFFF,(a6)+
	dc.b 'eor.l #$FFFF,(a7)+'
	eor.l	#$FFFF,(a7)+
	dc.b 'eor.l #$FFFF,(sp)+'
	eor.l	#$FFFF,(sp)+
	dc.b 'eor.l #$FFFFFFFF,(a1)+'
	eor.l	#$FFFFFFFF,(a1)+
	dc.b 'eor.l #$FFFFFFFF,(a2)+'
	eor.l	#$FFFFFFFF,(a2)+
	dc.b 'eor.l #$FFFFFFFF,(a3)+'
	eor.l	#$FFFFFFFF,(a3)+
	dc.b 'eor.l #$FFFFFFFF,(a4)+'
	eor.l	#$FFFFFFFF,(a4)+
	dc.b 'eor.l #$FFFFFFFF,(a5)+'
	eor.l	#$FFFFFFFF,(a5)+
	dc.b 'eor.l #$FFFFFFFF,(a6)+'
	eor.l	#$FFFFFFFF,(a6)+
	dc.b 'eor.l #$FFFFFFFF,(a7)+'
	eor.l	#$FFFFFFFF,(a7)+
	dc.b 'eor.l #$FFFFFFFF,(sp)+'
	eor.l	#$FFFFFFFF,(sp)+
	dc.b 'eor.l  #"WXYZ",(a1)+'
	eor.l	#"WXYZ",(a1)+
	dc.b 'eor.l  #"WXYZ",(a2)+'
	eor.l	#"WXYZ",(a2)+
	dc.b 'eor.l  #"WXYZ",(a3)+'
	eor.l	#"WXYZ",(a3)+
	dc.b 'eor.l  #"WXYZ",(a4)+'
	eor.l	#"WXYZ",(a4)+
	dc.b 'eor.l  #"WXYZ",(a5)+'
	eor.l	#"WXYZ",(a5)+
	dc.b 'eor.l  #"WXYZ",(a6)+'
	eor.l	#"WXYZ",(a6)+
	dc.b 'eor.l  #"WXYZ",(a7)+'
	eor.l	#"WXYZ",(a7)+
	dc.b 'eor.l  #"WXYZ",(sp)+'
	eor.l	#"WXYZ",(sp)+
	dc.b 'eor.l #1+1,(a1)+'
	eor.l	#1+1,(a1)+
	dc.b 'eor.l #1+1,(a2)+'
	eor.l	#1+1,(a2)+
	dc.b 'eor.l #1+1,(a3)+'
	eor.l	#1+1,(a3)+
	dc.b 'eor.l #1+1,(a4)+'
	eor.l	#1+1,(a4)+
	dc.b 'eor.l #1+1,(a5)+'
	eor.l	#1+1,(a5)+
	dc.b 'eor.l #1+1,(a6)+'
	eor.l	#1+1,(a6)+
	dc.b 'eor.l #1+1,(a7)+'
	eor.l	#1+1,(a7)+
	dc.b 'eor.l #1+1,(sp)+'
	eor.l	#1+1,(sp)+
	dc.b 'eor.l #(3+4),(a1)+'
	eor.l	#(3+4),(a1)+
	dc.b 'eor.l #(3+4),(a2)+'
	eor.l	#(3+4),(a2)+
	dc.b 'eor.l #(3+4),(a3)+'
	eor.l	#(3+4),(a3)+
	dc.b 'eor.l #(3+4),(a4)+'
	eor.l	#(3+4),(a4)+
	dc.b 'eor.l #(3+4),(a5)+'
	eor.l	#(3+4),(a5)+
	dc.b 'eor.l #(3+4),(a6)+'
	eor.l	#(3+4),(a6)+
	dc.b 'eor.l #(3+4),(a7)+'
	eor.l	#(3+4),(a7)+
	dc.b 'eor.l #(3+4),(sp)+'
	eor.l	#(3+4),(sp)+
	dc.b 'eor.l  #-1,(a1)+'
	eor.l	#-1,(a1)+
	dc.b 'eor.l  #-1,(a2)+'
	eor.l	#-1,(a2)+
	dc.b 'eor.l  #-1,(a3)+'
	eor.l	#-1,(a3)+
	dc.b 'eor.l  #-1,(a4)+'
	eor.l	#-1,(a4)+
	dc.b 'eor.l  #-1,(a5)+'
	eor.l	#-1,(a5)+
	dc.b 'eor.l  #-1,(a6)+'
	eor.l	#-1,(a6)+
	dc.b 'eor.l  #-1,(a7)+'
	eor.l	#-1,(a7)+
	dc.b 'eor.l  #-1,(sp)+'
	eor.l	#-1,(sp)+
	dc.b 'eor.l  #-2,(a1)+'
	eor.l	#-2,(a1)+
	dc.b 'eor.l  #-2,(a2)+'
	eor.l	#-2,(a2)+
	dc.b 'eor.l  #-2,(a3)+'
	eor.l	#-2,(a3)+
	dc.b 'eor.l  #-2,(a4)+'
	eor.l	#-2,(a4)+
	dc.b 'eor.l  #-2,(a5)+'
	eor.l	#-2,(a5)+
	dc.b 'eor.l  #-2,(a6)+'
	eor.l	#-2,(a6)+
	dc.b 'eor.l  #-2,(a7)+'
	eor.l	#-2,(a7)+
	dc.b 'eor.l  #-2,(sp)+'
	eor.l	#-2,(sp)+
	dc.b 'eor.l #0,-(a1)'
	eor.l	#0,-(a1)
	dc.b 'eor.l #0,-(a2)'
	eor.l	#0,-(a2)
	dc.b 'eor.l #0,-(a3)'
	eor.l	#0,-(a3)
	dc.b 'eor.l #0,-(a4)'
	eor.l	#0,-(a4)
	dc.b 'eor.l #0,-(a5)'
	eor.l	#0,-(a5)
	dc.b 'eor.l #0,-(a6)'
	eor.l	#0,-(a6)
	dc.b 'eor.l #0,-(a7)'
	eor.l	#0,-(a7)
	dc.b 'eor.l #0,-(sp)'
	eor.l	#0,-(sp)
	dc.b 'eor.l #4,-(a1)'
	eor.l	#4,-(a1)
	dc.b 'eor.l #4,-(a2)'
	eor.l	#4,-(a2)
	dc.b 'eor.l #4,-(a3)'
	eor.l	#4,-(a3)
	dc.b 'eor.l #4,-(a4)'
	eor.l	#4,-(a4)
	dc.b 'eor.l #4,-(a5)'
	eor.l	#4,-(a5)
	dc.b 'eor.l #4,-(a6)'
	eor.l	#4,-(a6)
	dc.b 'eor.l #4,-(a7)'
	eor.l	#4,-(a7)
	dc.b 'eor.l #4,-(sp)'
	eor.l	#4,-(sp)
	dc.b 'eor.l #$FF,-(a1)'
	eor.l	#$FF,-(a1)
	dc.b 'eor.l #$FF,-(a2)'
	eor.l	#$FF,-(a2)
	dc.b 'eor.l #$FF,-(a3)'
	eor.l	#$FF,-(a3)
	dc.b 'eor.l #$FF,-(a4)'
	eor.l	#$FF,-(a4)
	dc.b 'eor.l #$FF,-(a5)'
	eor.l	#$FF,-(a5)
	dc.b 'eor.l #$FF,-(a6)'
	eor.l	#$FF,-(a6)
	dc.b 'eor.l #$FF,-(a7)'
	eor.l	#$FF,-(a7)
	dc.b 'eor.l #$FF,-(sp)'
	eor.l	#$FF,-(sp)
	dc.b 'eor.l #$7FFF,-(a1)'
	eor.l	#$7FFF,-(a1)
	dc.b 'eor.l #$7FFF,-(a2)'
	eor.l	#$7FFF,-(a2)
	dc.b 'eor.l #$7FFF,-(a3)'
	eor.l	#$7FFF,-(a3)
	dc.b 'eor.l #$7FFF,-(a4)'
	eor.l	#$7FFF,-(a4)
	dc.b 'eor.l #$7FFF,-(a5)'
	eor.l	#$7FFF,-(a5)
	dc.b 'eor.l #$7FFF,-(a6)'
	eor.l	#$7FFF,-(a6)
	dc.b 'eor.l #$7FFF,-(a7)'
	eor.l	#$7FFF,-(a7)
	dc.b 'eor.l #$7FFF,-(sp)'
	eor.l	#$7FFF,-(sp)
	dc.b 'eor.l #$FFFF,-(a1)'
	eor.l	#$FFFF,-(a1)
	dc.b 'eor.l #$FFFF,-(a2)'
	eor.l	#$FFFF,-(a2)
	dc.b 'eor.l #$FFFF,-(a3)'
	eor.l	#$FFFF,-(a3)
	dc.b 'eor.l #$FFFF,-(a4)'
	eor.l	#$FFFF,-(a4)
	dc.b 'eor.l #$FFFF,-(a5)'
	eor.l	#$FFFF,-(a5)
	dc.b 'eor.l #$FFFF,-(a6)'
	eor.l	#$FFFF,-(a6)
	dc.b 'eor.l #$FFFF,-(a7)'
	eor.l	#$FFFF,-(a7)
	dc.b 'eor.l #$FFFF,-(sp)'
	eor.l	#$FFFF,-(sp)
	dc.b 'eor.l #$FFFFFFFF,-(a1)'
	eor.l	#$FFFFFFFF,-(a1)
	dc.b 'eor.l #$FFFFFFFF,-(a2)'
	eor.l	#$FFFFFFFF,-(a2)
	dc.b 'eor.l #$FFFFFFFF,-(a3)'
	eor.l	#$FFFFFFFF,-(a3)
	dc.b 'eor.l #$FFFFFFFF,-(a4)'
	eor.l	#$FFFFFFFF,-(a4)
	dc.b 'eor.l #$FFFFFFFF,-(a5)'
	eor.l	#$FFFFFFFF,-(a5)
	dc.b 'eor.l #$FFFFFFFF,-(a6)'
	eor.l	#$FFFFFFFF,-(a6)
	dc.b 'eor.l #$FFFFFFFF,-(a7)'
	eor.l	#$FFFFFFFF,-(a7)
	dc.b 'eor.l #$FFFFFFFF,-(sp)'
	eor.l	#$FFFFFFFF,-(sp)
	dc.b 'eor.l  #"WXYZ",-(a1)'
	eor.l	#"WXYZ",-(a1)
	dc.b 'eor.l  #"WXYZ",-(a2)'
	eor.l	#"WXYZ",-(a2)
	dc.b 'eor.l  #"WXYZ",-(a3)'
	eor.l	#"WXYZ",-(a3)
	dc.b 'eor.l  #"WXYZ",-(a4)'
	eor.l	#"WXYZ",-(a4)
	dc.b 'eor.l  #"WXYZ",-(a5)'
	eor.l	#"WXYZ",-(a5)
	dc.b 'eor.l  #"WXYZ",-(a6)'
	eor.l	#"WXYZ",-(a6)
	dc.b 'eor.l  #"WXYZ",-(a7)'
	eor.l	#"WXYZ",-(a7)
	dc.b 'eor.l  #"WXYZ",-(sp)'
	eor.l	#"WXYZ",-(sp)
	dc.b 'eor.l #1+1,-(a1)'
	eor.l	#1+1,-(a1)
	dc.b 'eor.l #1+1,-(a2)'
	eor.l	#1+1,-(a2)
	dc.b 'eor.l #1+1,-(a3)'
	eor.l	#1+1,-(a3)
	dc.b 'eor.l #1+1,-(a4)'
	eor.l	#1+1,-(a4)
	dc.b 'eor.l #1+1,-(a5)'
	eor.l	#1+1,-(a5)
	dc.b 'eor.l #1+1,-(a6)'
	eor.l	#1+1,-(a6)
	dc.b 'eor.l #1+1,-(a7)'
	eor.l	#1+1,-(a7)
	dc.b 'eor.l #1+1,-(sp)'
	eor.l	#1+1,-(sp)
	dc.b 'eor.l #(3+4),-(a1)'
	eor.l	#(3+4),-(a1)
	dc.b 'eor.l #(3+4),-(a2)'
	eor.l	#(3+4),-(a2)
	dc.b 'eor.l #(3+4),-(a3)'
	eor.l	#(3+4),-(a3)
	dc.b 'eor.l #(3+4),-(a4)'
	eor.l	#(3+4),-(a4)
	dc.b 'eor.l #(3+4),-(a5)'
	eor.l	#(3+4),-(a5)
	dc.b 'eor.l #(3+4),-(a6)'
	eor.l	#(3+4),-(a6)
	dc.b 'eor.l #(3+4),-(a7)'
	eor.l	#(3+4),-(a7)
	dc.b 'eor.l #(3+4),-(sp)'
	eor.l	#(3+4),-(sp)
	dc.b 'eor.l  #-1,-(a1)'
	eor.l	#-1,-(a1)
	dc.b 'eor.l  #-1,-(a2)'
	eor.l	#-1,-(a2)
	dc.b 'eor.l  #-1,-(a3)'
	eor.l	#-1,-(a3)
	dc.b 'eor.l  #-1,-(a4)'
	eor.l	#-1,-(a4)
	dc.b 'eor.l  #-1,-(a5)'
	eor.l	#-1,-(a5)
	dc.b 'eor.l  #-1,-(a6)'
	eor.l	#-1,-(a6)
	dc.b 'eor.l  #-1,-(a7)'
	eor.l	#-1,-(a7)
	dc.b 'eor.l  #-1,-(sp)'
	eor.l	#-1,-(sp)
	dc.b 'eor.l  #-2,-(a1)'
	eor.l	#-2,-(a1)
	dc.b 'eor.l  #-2,-(a2)'
	eor.l	#-2,-(a2)
	dc.b 'eor.l  #-2,-(a3)'
	eor.l	#-2,-(a3)
	dc.b 'eor.l  #-2,-(a4)'
	eor.l	#-2,-(a4)
	dc.b 'eor.l  #-2,-(a5)'
	eor.l	#-2,-(a5)
	dc.b 'eor.l  #-2,-(a6)'
	eor.l	#-2,-(a6)
	dc.b 'eor.l  #-2,-(a7)'
	eor.l	#-2,-(a7)
	dc.b 'eor.l  #-2,-(sp)'
	eor.l	#-2,-(sp)
	dc.b 'eor.l #0,($FFFFFFFF).l'
	eor.l	#0,($FFFFFFFF).l
	dc.b 'eor.l #0,label_start.l'
	eor.l	#0,label_start.l
	dc.b 'eor.l #0,$FFFFFFFF'
	eor.l	#0,$FFFFFFFF
	dc.b 'eor.l  #0,$1'
	eor.l	#0,$1
	dc.b 'eor.l #4,($FFFFFFFF).l'
	eor.l	#4,($FFFFFFFF).l
	dc.b 'eor.l #4,label_start.l'
	eor.l	#4,label_start.l
	dc.b 'eor.l #4,$FFFFFFFF'
	eor.l	#4,$FFFFFFFF
	dc.b 'eor.l  #4,$1'
	eor.l	#4,$1
	dc.b 'eor.l #$FF,($FFFFFFFF).l'
	eor.l	#$FF,($FFFFFFFF).l
	dc.b 'eor.l #$FF,label_start.l'
	eor.l	#$FF,label_start.l
	dc.b 'eor.l #$FF,$FFFFFFFF'
	eor.l	#$FF,$FFFFFFFF
	dc.b 'eor.l  #$FF,$1'
	eor.l	#$FF,$1
	dc.b 'eor.l #$7FFF,($FFFFFFFF).l'
	eor.l	#$7FFF,($FFFFFFFF).l
	dc.b 'eor.l #$7FFF,label_start.l'
	eor.l	#$7FFF,label_start.l
	dc.b 'eor.l #$7FFF,$FFFFFFFF'
	eor.l	#$7FFF,$FFFFFFFF
	dc.b 'eor.l  #$7FFF,$1'
	eor.l	#$7FFF,$1
	dc.b 'eor.l #$FFFF,($FFFFFFFF).l'
	eor.l	#$FFFF,($FFFFFFFF).l
	dc.b 'eor.l #$FFFF,label_start.l'
	eor.l	#$FFFF,label_start.l
	dc.b 'eor.l #$FFFF,$FFFFFFFF'
	eor.l	#$FFFF,$FFFFFFFF
	dc.b 'eor.l  #$FFFF,$1'
	eor.l	#$FFFF,$1
	dc.b 'eor.l #$FFFFFFFF,($FFFFFFFF).l'
	eor.l	#$FFFFFFFF,($FFFFFFFF).l
	dc.b 'eor.l #$FFFFFFFF,label_start.l'
	eor.l	#$FFFFFFFF,label_start.l
	dc.b 'eor.l #$FFFFFFFF,$FFFFFFFF'
	eor.l	#$FFFFFFFF,$FFFFFFFF
	dc.b 'eor.l  #$FFFFFFFF,$1'
	eor.l	#$FFFFFFFF,$1
	dc.b 'eor.l  #"WXYZ",($FFFFFFFF).l'
	eor.l	#"WXYZ",($FFFFFFFF).l
	dc.b 'eor.l  #"WXYZ",label_start.l'
	eor.l	#"WXYZ",label_start.l
	dc.b 'eor.l  #"WXYZ",$FFFFFFFF'
	eor.l	#"WXYZ",$FFFFFFFF
	dc.b 'eor.l #"WXYZ",$1'
	eor.l	#"WXYZ",$1
	dc.b 'eor.l #1+1,($FFFFFFFF).l'
	eor.l	#1+1,($FFFFFFFF).l
	dc.b 'eor.l #1+1,label_start.l'
	eor.l	#1+1,label_start.l
	dc.b 'eor.l #1+1,$FFFFFFFF'
	eor.l	#1+1,$FFFFFFFF
	dc.b 'eor.l  #1+1,$1'
	eor.l	#1+1,$1
	dc.b 'eor.l #(3+4),($FFFFFFFF).l'
	eor.l	#(3+4),($FFFFFFFF).l
	dc.b 'eor.l #(3+4),label_start.l'
	eor.l	#(3+4),label_start.l
	dc.b 'eor.l #(3+4),$FFFFFFFF'
	eor.l	#(3+4),$FFFFFFFF
	dc.b 'eor.l  #(3+4),$1'
	eor.l	#(3+4),$1
	dc.b 'eor.l  #-1,($FFFFFFFF).l'
	eor.l	#-1,($FFFFFFFF).l
	dc.b 'eor.l  #-1,label_start.l'
	eor.l	#-1,label_start.l
	dc.b 'eor.l  #-1,$FFFFFFFF'
	eor.l	#-1,$FFFFFFFF
	dc.b 'eor.l #-1,$1'
	eor.l	#-1,$1
	dc.b 'eor.l  #-2,($FFFFFFFF).l'
	eor.l	#-2,($FFFFFFFF).l
	dc.b 'eor.l  #-2,label_start.l'
	eor.l	#-2,label_start.l
	dc.b 'eor.l  #-2,$FFFFFFFF'
	eor.l	#-2,$FFFFFFFF
	dc.b 'eor.l #-2,$1'
	eor.l	#-2,$1
	dc.b 'eor.l #0,($FFFFFFFF).w'
	eor.l	#0,($FFFFFFFF).w
	dc.b 'eor.l  #0,$1'
	eor.l	#0,$1
	dc.b 'eor.l #4,($FFFFFFFF).w'
	eor.l	#4,($FFFFFFFF).w
	dc.b 'eor.l  #4,$1'
	eor.l	#4,$1
	dc.b 'eor.l #$FF,($FFFFFFFF).w'
	eor.l	#$FF,($FFFFFFFF).w
	dc.b 'eor.l  #$FF,$1'
	eor.l	#$FF,$1
	dc.b 'eor.l #$7FFF,($FFFFFFFF).w'
	eor.l	#$7FFF,($FFFFFFFF).w
	dc.b 'eor.l  #$7FFF,$1'
	eor.l	#$7FFF,$1
	dc.b 'eor.l #$FFFF,($FFFFFFFF).w'
	eor.l	#$FFFF,($FFFFFFFF).w
	dc.b 'eor.l  #$FFFF,$1'
	eor.l	#$FFFF,$1
	dc.b 'eor.l #$FFFFFFFF,($FFFFFFFF).w'
	eor.l	#$FFFFFFFF,($FFFFFFFF).w
	dc.b 'eor.l  #$FFFFFFFF,$1'
	eor.l	#$FFFFFFFF,$1
	dc.b 'eor.l  #"WXYZ",($FFFFFFFF).w'
	eor.l	#"WXYZ",($FFFFFFFF).w
	dc.b 'eor.l #"WXYZ",$1'
	eor.l	#"WXYZ",$1
	dc.b 'eor.l #1+1,($FFFFFFFF).w'
	eor.l	#1+1,($FFFFFFFF).w
	dc.b 'eor.l  #1+1,$1'
	eor.l	#1+1,$1
	dc.b 'eor.l #(3+4),($FFFFFFFF).w'
	eor.l	#(3+4),($FFFFFFFF).w
	dc.b 'eor.l  #(3+4),$1'
	eor.l	#(3+4),$1
	dc.b 'eor.l  #-1,($FFFFFFFF).w'
	eor.l	#-1,($FFFFFFFF).w
	dc.b 'eor.l #-1,$1'
	eor.l	#-1,$1
	dc.b 'eor.l  #-2,($FFFFFFFF).w'
	eor.l	#-2,($FFFFFFFF).w
	dc.b 'eor.l #-2,$1'
	eor.l	#-2,$1
	dc.b 'eor.l #0,$7FFF(a2)'
	eor.l	#0,$7FFF(a2)
	dc.b 'eor.l #0,$7FFF(a5)'
	eor.l	#0,$7FFF(a5)
	dc.b 'eor.l  #0,-2(sp)'
	eor.l	#0,-2(sp)
	dc.b 'eor.l #4,$7FFF(a2)'
	eor.l	#4,$7FFF(a2)
	dc.b 'eor.l #4,$7FFF(a5)'
	eor.l	#4,$7FFF(a5)
	dc.b 'eor.l  #4,-2(sp)'
	eor.l	#4,-2(sp)
	dc.b 'eor.l #$FF,$7FFF(a2)'
	eor.l	#$FF,$7FFF(a2)
	dc.b 'eor.l #$FF,$7FFF(a5)'
	eor.l	#$FF,$7FFF(a5)
	dc.b 'eor.l  #$FF,-2(sp)'
	eor.l	#$FF,-2(sp)
	dc.b 'eor.l #$7FFF,$7FFF(a2)'
	eor.l	#$7FFF,$7FFF(a2)
	dc.b 'eor.l #$7FFF,$7FFF(a5)'
	eor.l	#$7FFF,$7FFF(a5)
	dc.b 'eor.l  #$7FFF,-2(sp)'
	eor.l	#$7FFF,-2(sp)
	dc.b 'eor.l #$FFFF,$7FFF(a2)'
	eor.l	#$FFFF,$7FFF(a2)
	dc.b 'eor.l #$FFFF,$7FFF(a5)'
	eor.l	#$FFFF,$7FFF(a5)
	dc.b 'eor.l  #$FFFF,-2(sp)'
	eor.l	#$FFFF,-2(sp)
	dc.b 'eor.l #$FFFFFFFF,$7FFF(a2)'
	eor.l	#$FFFFFFFF,$7FFF(a2)
	dc.b 'eor.l #$FFFFFFFF,$7FFF(a5)'
	eor.l	#$FFFFFFFF,$7FFF(a5)
	dc.b 'eor.l  #$FFFFFFFF,-2(sp)'
	eor.l	#$FFFFFFFF,-2(sp)
	dc.b 'eor.l  #"WXYZ",$7FFF(a2)'
	eor.l	#"WXYZ",$7FFF(a2)
	dc.b 'eor.l  #"WXYZ",$7FFF(a5)'
	eor.l	#"WXYZ",$7FFF(a5)
	dc.b 'eor.l #"WXYZ",-2(sp)'
	eor.l	#"WXYZ",-2(sp)
	dc.b 'eor.l #1+1,$7FFF(a2)'
	eor.l	#1+1,$7FFF(a2)
	dc.b 'eor.l #1+1,$7FFF(a5)'
	eor.l	#1+1,$7FFF(a5)
	dc.b 'eor.l  #1+1,-2(sp)'
	eor.l	#1+1,-2(sp)
	dc.b 'eor.l #(3+4),$7FFF(a2)'
	eor.l	#(3+4),$7FFF(a2)
	dc.b 'eor.l #(3+4),$7FFF(a5)'
	eor.l	#(3+4),$7FFF(a5)
	dc.b 'eor.l  #(3+4),-2(sp)'
	eor.l	#(3+4),-2(sp)
	dc.b 'eor.l  #-1,$7FFF(a2)'
	eor.l	#-1,$7FFF(a2)
	dc.b 'eor.l  #-1,$7FFF(a5)'
	eor.l	#-1,$7FFF(a5)
	dc.b 'eor.l #-1,-2(sp)'
	eor.l	#-1,-2(sp)
	dc.b 'eor.l  #-2,$7FFF(a2)'
	eor.l	#-2,$7FFF(a2)
	dc.b 'eor.l  #-2,$7FFF(a5)'
	eor.l	#-2,$7FFF(a5)
	dc.b 'eor.l #-2,-2(sp)'
	eor.l	#-2,-2(sp)
	dc.b 'eor.l  #0,$7F(a2,d5.w)'
	eor.l	#0,$7F(a2,d5.w)
	dc.b 'eor.l  #0,$7F(a5,d2.w)'
	eor.l	#0,$7F(a5,d2.w)
	dc.b 'eor.l  #0,$0F(a5,d2.l)'
	eor.l	#0,$0F(a5,d2.l)
	dc.b 'eor.l #0,$1+1(a5,d2.l)'
	eor.l	#0,$1+1(a5,d2.l)
	dc.b 'eor.l #0,-2(a5,d2.l)'
	eor.l	#0,-2(a5,d2.l)
	dc.b 'eor.l #0,(a0,d1.w)'
	eor.l	#0,(a0,d1.w)
	dc.b 'eor.l #0,(a1,d6)'
	eor.l	#0,(a1,d6)
	dc.b 'eor.l  #4,$7F(a2,d5.w)'
	eor.l	#4,$7F(a2,d5.w)
	dc.b 'eor.l  #4,$7F(a5,d2.w)'
	eor.l	#4,$7F(a5,d2.w)
	dc.b 'eor.l  #4,$0F(a5,d2.l)'
	eor.l	#4,$0F(a5,d2.l)
	dc.b 'eor.l #4,$1+1(a5,d2.l)'
	eor.l	#4,$1+1(a5,d2.l)
	dc.b 'eor.l #4,-2(a5,d2.l)'
	eor.l	#4,-2(a5,d2.l)
	dc.b 'eor.l #4,(a0,d1.w)'
	eor.l	#4,(a0,d1.w)
	dc.b 'eor.l #4,(a1,d6)'
	eor.l	#4,(a1,d6)
	dc.b 'eor.l  #$FF,$7F(a2,d5.w)'
	eor.l	#$FF,$7F(a2,d5.w)
	dc.b 'eor.l  #$FF,$7F(a5,d2.w)'
	eor.l	#$FF,$7F(a5,d2.w)
	dc.b 'eor.l  #$FF,$0F(a5,d2.l)'
	eor.l	#$FF,$0F(a5,d2.l)
	dc.b 'eor.l #$FF,$1+1(a5,d2.l)'
	eor.l	#$FF,$1+1(a5,d2.l)
	dc.b 'eor.l #$FF,-2(a5,d2.l)'
	eor.l	#$FF,-2(a5,d2.l)
	dc.b 'eor.l #$FF,(a0,d1.w)'
	eor.l	#$FF,(a0,d1.w)
	dc.b 'eor.l #$FF,(a1,d6)'
	eor.l	#$FF,(a1,d6)
	dc.b 'eor.l  #$7FFF,$7F(a2,d5.w)'
	eor.l	#$7FFF,$7F(a2,d5.w)
	dc.b 'eor.l  #$7FFF,$7F(a5,d2.w)'
	eor.l	#$7FFF,$7F(a5,d2.w)
	dc.b 'eor.l  #$7FFF,$0F(a5,d2.l)'
	eor.l	#$7FFF,$0F(a5,d2.l)
	dc.b 'eor.l #$7FFF,$1+1(a5,d2.l)'
	eor.l	#$7FFF,$1+1(a5,d2.l)
	dc.b 'eor.l #$7FFF,-2(a5,d2.l)'
	eor.l	#$7FFF,-2(a5,d2.l)
	dc.b 'eor.l #$7FFF,(a0,d1.w)'
	eor.l	#$7FFF,(a0,d1.w)
	dc.b 'eor.l #$7FFF,(a1,d6)'
	eor.l	#$7FFF,(a1,d6)
	dc.b 'eor.l  #$FFFF,$7F(a2,d5.w)'
	eor.l	#$FFFF,$7F(a2,d5.w)
	dc.b 'eor.l  #$FFFF,$7F(a5,d2.w)'
	eor.l	#$FFFF,$7F(a5,d2.w)
	dc.b 'eor.l  #$FFFF,$0F(a5,d2.l)'
	eor.l	#$FFFF,$0F(a5,d2.l)
	dc.b 'eor.l #$FFFF,$1+1(a5,d2.l)'
	eor.l	#$FFFF,$1+1(a5,d2.l)
	dc.b 'eor.l #$FFFF,-2(a5,d2.l)'
	eor.l	#$FFFF,-2(a5,d2.l)
	dc.b 'eor.l #$FFFF,(a0,d1.w)'
	eor.l	#$FFFF,(a0,d1.w)
	dc.b 'eor.l #$FFFF,(a1,d6)'
	eor.l	#$FFFF,(a1,d6)
	dc.b 'eor.l  #$FFFFFFFF,$7F(a2,d5.w)'
	eor.l	#$FFFFFFFF,$7F(a2,d5.w)
	dc.b 'eor.l  #$FFFFFFFF,$7F(a5,d2.w)'
	eor.l	#$FFFFFFFF,$7F(a5,d2.w)
	dc.b 'eor.l  #$FFFFFFFF,$0F(a5,d2.l)'
	eor.l	#$FFFFFFFF,$0F(a5,d2.l)
	dc.b 'eor.l #$FFFFFFFF,$1+1(a5,d2.l)'
	eor.l	#$FFFFFFFF,$1+1(a5,d2.l)
	dc.b 'eor.l #$FFFFFFFF,-2(a5,d2.l)'
	eor.l	#$FFFFFFFF,-2(a5,d2.l)
	dc.b 'eor.l #$FFFFFFFF,(a0,d1.w)'
	eor.l	#$FFFFFFFF,(a0,d1.w)
	dc.b 'eor.l #$FFFFFFFF,(a1,d6)'
	eor.l	#$FFFFFFFF,(a1,d6)
	dc.b 'eor.l #"WXYZ",$7F(a2,d5.w)'
	eor.l	#"WXYZ",$7F(a2,d5.w)
	dc.b 'eor.l #"WXYZ",$7F(a5,d2.w)'
	eor.l	#"WXYZ",$7F(a5,d2.w)
	dc.b 'eor.l #"WXYZ",$0F(a5,d2.l)'
	eor.l	#"WXYZ",$0F(a5,d2.l)
	dc.b 'eor.l  #"WXYZ",$1+1(a5,d2.l)'
	eor.l	#"WXYZ",$1+1(a5,d2.l)
	dc.b 'eor.l  #"WXYZ",-2(a5,d2.l)'
	eor.l	#"WXYZ",-2(a5,d2.l)
	dc.b 'eor.l  #"WXYZ",(a0,d1.w)'
	eor.l	#"WXYZ",(a0,d1.w)
	dc.b 'eor.l  #"WXYZ",(a1,d6)'
	eor.l	#"WXYZ",(a1,d6)
	dc.b 'eor.l  #1+1,$7F(a2,d5.w)'
	eor.l	#1+1,$7F(a2,d5.w)
	dc.b 'eor.l  #1+1,$7F(a5,d2.w)'
	eor.l	#1+1,$7F(a5,d2.w)
	dc.b 'eor.l  #1+1,$0F(a5,d2.l)'
	eor.l	#1+1,$0F(a5,d2.l)
	dc.b 'eor.l #1+1,$1+1(a5,d2.l)'
	eor.l	#1+1,$1+1(a5,d2.l)
	dc.b 'eor.l #1+1,-2(a5,d2.l)'
	eor.l	#1+1,-2(a5,d2.l)
	dc.b 'eor.l #1+1,(a0,d1.w)'
	eor.l	#1+1,(a0,d1.w)
	dc.b 'eor.l #1+1,(a1,d6)'
	eor.l	#1+1,(a1,d6)
	dc.b 'eor.l  #(3+4),$7F(a2,d5.w)'
	eor.l	#(3+4),$7F(a2,d5.w)
	dc.b 'eor.l  #(3+4),$7F(a5,d2.w)'
	eor.l	#(3+4),$7F(a5,d2.w)
	dc.b 'eor.l  #(3+4),$0F(a5,d2.l)'
	eor.l	#(3+4),$0F(a5,d2.l)
	dc.b 'eor.l #(3+4),$1+1(a5,d2.l)'
	eor.l	#(3+4),$1+1(a5,d2.l)
	dc.b 'eor.l #(3+4),-2(a5,d2.l)'
	eor.l	#(3+4),-2(a5,d2.l)
	dc.b 'eor.l #(3+4),(a0,d1.w)'
	eor.l	#(3+4),(a0,d1.w)
	dc.b 'eor.l #(3+4),(a1,d6)'
	eor.l	#(3+4),(a1,d6)
	dc.b 'eor.l #-1,$7F(a2,d5.w)'
	eor.l	#-1,$7F(a2,d5.w)
	dc.b 'eor.l #-1,$7F(a5,d2.w)'
	eor.l	#-1,$7F(a5,d2.w)
	dc.b 'eor.l #-1,$0F(a5,d2.l)'
	eor.l	#-1,$0F(a5,d2.l)
	dc.b 'eor.l  #-1,$1+1(a5,d2.l)'
	eor.l	#-1,$1+1(a5,d2.l)
	dc.b 'eor.l  #-1,-2(a5,d2.l)'
	eor.l	#-1,-2(a5,d2.l)
	dc.b 'eor.l  #-1,(a0,d1.w)'
	eor.l	#-1,(a0,d1.w)
	dc.b 'eor.l  #-1,(a1,d6)'
	eor.l	#-1,(a1,d6)
	dc.b 'eor.l #-2,$7F(a2,d5.w)'
	eor.l	#-2,$7F(a2,d5.w)
	dc.b 'eor.l #-2,$7F(a5,d2.w)'
	eor.l	#-2,$7F(a5,d2.w)
	dc.b 'eor.l #-2,$0F(a5,d2.l)'
	eor.l	#-2,$0F(a5,d2.l)
	dc.b 'eor.l  #-2,$1+1(a5,d2.l)'
	eor.l	#-2,$1+1(a5,d2.l)
	dc.b 'eor.l  #-2,-2(a5,d2.l)'
	eor.l	#-2,-2(a5,d2.l)
	dc.b 'eor.l  #-2,(a0,d1.w)'
	eor.l	#-2,(a0,d1.w)
	dc.b 'eor.l  #-2,(a1,d6)'
	eor.l	#-2,(a1,d6)
	dc.b 'eor.l  #0,d1'
	eor.l	#0,d1
	dc.b 'eor.l  #0,d2'
	eor.l	#0,d2
	dc.b 'eor.l  #0,d3'
	eor.l	#0,d3
	dc.b 'eor.l  #0,d4'
	eor.l	#0,d4
	dc.b 'eor.l  #0,d5'
	eor.l	#0,d5
	dc.b 'eor.l  #4,d1'
	eor.l	#4,d1
	dc.b 'eor.l  #4,d2'
	eor.l	#4,d2
	dc.b 'eor.l  #4,d3'
	eor.l	#4,d3
	dc.b 'eor.l  #4,d4'
	eor.l	#4,d4
	dc.b 'eor.l  #4,d5'
	eor.l	#4,d5
	dc.b 'eor.l  #$FF,d1'
	eor.l	#$FF,d1
	dc.b 'eor.l  #$FF,d2'
	eor.l	#$FF,d2
	dc.b 'eor.l  #$FF,d3'
	eor.l	#$FF,d3
	dc.b 'eor.l  #$FF,d4'
	eor.l	#$FF,d4
	dc.b 'eor.l  #$FF,d5'
	eor.l	#$FF,d5
	dc.b 'eor.l  #$7FFF,d1'
	eor.l	#$7FFF,d1
	dc.b 'eor.l  #$7FFF,d2'
	eor.l	#$7FFF,d2
	dc.b 'eor.l  #$7FFF,d3'
	eor.l	#$7FFF,d3
	dc.b 'eor.l  #$7FFF,d4'
	eor.l	#$7FFF,d4
	dc.b 'eor.l  #$7FFF,d5'
	eor.l	#$7FFF,d5
	dc.b 'eor.l  #$FFFF,d1'
	eor.l	#$FFFF,d1
	dc.b 'eor.l  #$FFFF,d2'
	eor.l	#$FFFF,d2
	dc.b 'eor.l  #$FFFF,d3'
	eor.l	#$FFFF,d3
	dc.b 'eor.l  #$FFFF,d4'
	eor.l	#$FFFF,d4
	dc.b 'eor.l  #$FFFF,d5'
	eor.l	#$FFFF,d5
	dc.b 'eor.l  #$FFFFFFFF,d1'
	eor.l	#$FFFFFFFF,d1
	dc.b 'eor.l  #$FFFFFFFF,d2'
	eor.l	#$FFFFFFFF,d2
	dc.b 'eor.l  #$FFFFFFFF,d3'
	eor.l	#$FFFFFFFF,d3
	dc.b 'eor.l  #$FFFFFFFF,d4'
	eor.l	#$FFFFFFFF,d4
	dc.b 'eor.l  #$FFFFFFFF,d5'
	eor.l	#$FFFFFFFF,d5
	dc.b 'eor.l #"WXYZ",d1'
	eor.l	#"WXYZ",d1
	dc.b 'eor.l #"WXYZ",d2'
	eor.l	#"WXYZ",d2
	dc.b 'eor.l #"WXYZ",d3'
	eor.l	#"WXYZ",d3
	dc.b 'eor.l #"WXYZ",d4'
	eor.l	#"WXYZ",d4
	dc.b 'eor.l #"WXYZ",d5'
	eor.l	#"WXYZ",d5
	dc.b 'eor.l  #1+1,d1'
	eor.l	#1+1,d1
	dc.b 'eor.l  #1+1,d2'
	eor.l	#1+1,d2
	dc.b 'eor.l  #1+1,d3'
	eor.l	#1+1,d3
	dc.b 'eor.l  #1+1,d4'
	eor.l	#1+1,d4
	dc.b 'eor.l  #1+1,d5'
	eor.l	#1+1,d5
	dc.b 'eor.l  #(3+4),d1'
	eor.l	#(3+4),d1
	dc.b 'eor.l  #(3+4),d2'
	eor.l	#(3+4),d2
	dc.b 'eor.l  #(3+4),d3'
	eor.l	#(3+4),d3
	dc.b 'eor.l  #(3+4),d4'
	eor.l	#(3+4),d4
	dc.b 'eor.l  #(3+4),d5'
	eor.l	#(3+4),d5
	dc.b 'eor.l #-1,d1'
	eor.l	#-1,d1
	dc.b 'eor.l #-1,d2'
	eor.l	#-1,d2
	dc.b 'eor.l #-1,d3'
	eor.l	#-1,d3
	dc.b 'eor.l #-1,d4'
	eor.l	#-1,d4
	dc.b 'eor.l #-1,d5'
	eor.l	#-1,d5
	dc.b 'eor.l #-2,d1'
	eor.l	#-2,d1
	dc.b 'eor.l #-2,d2'
	eor.l	#-2,d2
	dc.b 'eor.l #-2,d3'
	eor.l	#-2,d3
	dc.b 'eor.l #-2,d4'
	eor.l	#-2,d4
	dc.b 'eor.l #-2,d5'
	eor.l	#-2,d5

	dc.b 'cmp.b  #0,d1'
	cmp.b	#0,d1
	dc.b 'cmp.b  #0,d2'
	cmp.b	#0,d2
	dc.b 'cmp.b  #0,d3'
	cmp.b	#0,d3
	dc.b 'cmp.b  #0,d4'
	cmp.b	#0,d4
	dc.b 'cmp.b  #0,d5'
	cmp.b	#0,d5
	dc.b 'cmp.b  #$FF,d1'
	cmp.b	#$FF,d1
	dc.b 'cmp.b  #$FF,d2'
	cmp.b	#$FF,d2
	dc.b 'cmp.b  #$FF,d3'
	cmp.b	#$FF,d3
	dc.b 'cmp.b  #$FF,d4'
	cmp.b	#$FF,d4
	dc.b 'cmp.b  #$FF,d5'
	cmp.b	#$FF,d5
	dc.b 'cmp.b  #"X",d1'
	cmp.b	#"X",d1
	dc.b 'cmp.b  #"X",d2'
	cmp.b	#"X",d2
	dc.b 'cmp.b  #"X",d3'
	cmp.b	#"X",d3
	dc.b 'cmp.b  #"X",d4'
	cmp.b	#"X",d4
	dc.b 'cmp.b  #"X",d5'
	cmp.b	#"X",d5
	dc.b 'cmp.w  #0,d1'
	cmp.w	#0,d1
	dc.b 'cmp.w  #0,d2'
	cmp.w	#0,d2
	dc.b 'cmp.w  #0,d3'
	cmp.w	#0,d3
	dc.b 'cmp.w  #0,d4'
	cmp.w	#0,d4
	dc.b 'cmp.w  #0,d5'
	cmp.w	#0,d5
	dc.b 'cmp.w  #4,d1'
	cmp.w	#4,d1
	dc.b 'cmp.w  #4,d2'
	cmp.w	#4,d2
	dc.b 'cmp.w  #4,d3'
	cmp.w	#4,d3
	dc.b 'cmp.w  #4,d4'
	cmp.w	#4,d4
	dc.b 'cmp.w  #4,d5'
	cmp.w	#4,d5
	dc.b 'cmp.w  #$FF,d1'
	cmp.w	#$FF,d1
	dc.b 'cmp.w  #$FF,d2'
	cmp.w	#$FF,d2
	dc.b 'cmp.w  #$FF,d3'
	cmp.w	#$FF,d3
	dc.b 'cmp.w  #$FF,d4'
	cmp.w	#$FF,d4
	dc.b 'cmp.w  #$FF,d5'
	cmp.w	#$FF,d5
	dc.b 'cmp.w #"XY",d1'
	cmp.w	#"XY",d1
	dc.b 'cmp.w #"XY",d2'
	cmp.w	#"XY",d2
	dc.b 'cmp.w #"XY",d3'
	cmp.w	#"XY",d3
	dc.b 'cmp.w #"XY",d4'
	cmp.w	#"XY",d4
	dc.b 'cmp.w #"XY",d5'
	cmp.w	#"XY",d5
	dc.b 'cmp.w  #$2700,d1'
	cmp.w	#$2700,d1
	dc.b 'cmp.w  #$2700,d2'
	cmp.w	#$2700,d2
	dc.b 'cmp.w  #$2700,d3'
	cmp.w	#$2700,d3
	dc.b 'cmp.w  #$2700,d4'
	cmp.w	#$2700,d4
	dc.b 'cmp.w  #$2700,d5'
	cmp.w	#$2700,d5
	dc.b 'cmp.w  #$7FFF,d1'
	cmp.w	#$7FFF,d1
	dc.b 'cmp.w  #$7FFF,d2'
	cmp.w	#$7FFF,d2
	dc.b 'cmp.w  #$7FFF,d3'
	cmp.w	#$7FFF,d3
	dc.b 'cmp.w  #$7FFF,d4'
	cmp.w	#$7FFF,d4
	dc.b 'cmp.w  #$7FFF,d5'
	cmp.w	#$7FFF,d5
	dc.b 'cmp.w  #$FFFF,d1'
	cmp.w	#$FFFF,d1
	dc.b 'cmp.w  #$FFFF,d2'
	cmp.w	#$FFFF,d2
	dc.b 'cmp.w  #$FFFF,d3'
	cmp.w	#$FFFF,d3
	dc.b 'cmp.w  #$FFFF,d4'
	cmp.w	#$FFFF,d4
	dc.b 'cmp.w  #$FFFF,d5'
	cmp.w	#$FFFF,d5
	dc.b 'cmp.l  #0,d1'
	cmp.l	#0,d1
	dc.b 'cmp.l  #0,d2'
	cmp.l	#0,d2
	dc.b 'cmp.l  #0,d3'
	cmp.l	#0,d3
	dc.b 'cmp.l  #0,d4'
	cmp.l	#0,d4
	dc.b 'cmp.l  #0,d5'
	cmp.l	#0,d5
	dc.b 'cmp.l  #4,d1'
	cmp.l	#4,d1
	dc.b 'cmp.l  #4,d2'
	cmp.l	#4,d2
	dc.b 'cmp.l  #4,d3'
	cmp.l	#4,d3
	dc.b 'cmp.l  #4,d4'
	cmp.l	#4,d4
	dc.b 'cmp.l  #4,d5'
	cmp.l	#4,d5
	dc.b 'cmp.l  #$FF,d1'
	cmp.l	#$FF,d1
	dc.b 'cmp.l  #$FF,d2'
	cmp.l	#$FF,d2
	dc.b 'cmp.l  #$FF,d3'
	cmp.l	#$FF,d3
	dc.b 'cmp.l  #$FF,d4'
	cmp.l	#$FF,d4
	dc.b 'cmp.l  #$FF,d5'
	cmp.l	#$FF,d5
	dc.b 'cmp.l  #$7FFF,d1'
	cmp.l	#$7FFF,d1
	dc.b 'cmp.l  #$7FFF,d2'
	cmp.l	#$7FFF,d2
	dc.b 'cmp.l  #$7FFF,d3'
	cmp.l	#$7FFF,d3
	dc.b 'cmp.l  #$7FFF,d4'
	cmp.l	#$7FFF,d4
	dc.b 'cmp.l  #$7FFF,d5'
	cmp.l	#$7FFF,d5
	dc.b 'cmp.l  #$FFFF,d1'
	cmp.l	#$FFFF,d1
	dc.b 'cmp.l  #$FFFF,d2'
	cmp.l	#$FFFF,d2
	dc.b 'cmp.l  #$FFFF,d3'
	cmp.l	#$FFFF,d3
	dc.b 'cmp.l  #$FFFF,d4'
	cmp.l	#$FFFF,d4
	dc.b 'cmp.l  #$FFFF,d5'
	cmp.l	#$FFFF,d5
	dc.b 'cmp.l  #$FFFFFFFF,d1'
	cmp.l	#$FFFFFFFF,d1
	dc.b 'cmp.l  #$FFFFFFFF,d2'
	cmp.l	#$FFFFFFFF,d2
	dc.b 'cmp.l  #$FFFFFFFF,d3'
	cmp.l	#$FFFFFFFF,d3
	dc.b 'cmp.l  #$FFFFFFFF,d4'
	cmp.l	#$FFFFFFFF,d4
	dc.b 'cmp.l  #$FFFFFFFF,d5'
	cmp.l	#$FFFFFFFF,d5
	dc.b 'cmp.l #"WXYZ",d1'
	cmp.l	#"WXYZ",d1
	dc.b 'cmp.l #"WXYZ",d2'
	cmp.l	#"WXYZ",d2
	dc.b 'cmp.l #"WXYZ",d3'
	cmp.l	#"WXYZ",d3
	dc.b 'cmp.l #"WXYZ",d4'
	cmp.l	#"WXYZ",d4
	dc.b 'cmp.l #"WXYZ",d5'
	cmp.l	#"WXYZ",d5
	dc.b 'cmp.l  #1+1,d1'
	cmp.l	#1+1,d1
	dc.b 'cmp.l  #1+1,d2'
	cmp.l	#1+1,d2
	dc.b 'cmp.l  #1+1,d3'
	cmp.l	#1+1,d3
	dc.b 'cmp.l  #1+1,d4'
	cmp.l	#1+1,d4
	dc.b 'cmp.l  #1+1,d5'
	cmp.l	#1+1,d5
	dc.b 'cmp.l  #(3+4),d1'
	cmp.l	#(3+4),d1
	dc.b 'cmp.l  #(3+4),d2'
	cmp.l	#(3+4),d2
	dc.b 'cmp.l  #(3+4),d3'
	cmp.l	#(3+4),d3
	dc.b 'cmp.l  #(3+4),d4'
	cmp.l	#(3+4),d4
	dc.b 'cmp.l  #(3+4),d5'
	cmp.l	#(3+4),d5
	dc.b 'cmp.l #-1,d1'
	cmp.l	#-1,d1
	dc.b 'cmp.l #-1,d2'
	cmp.l	#-1,d2
	dc.b 'cmp.l #-1,d3'
	cmp.l	#-1,d3
	dc.b 'cmp.l #-1,d4'
	cmp.l	#-1,d4
	dc.b 'cmp.l #-1,d5'
	cmp.l	#-1,d5
	dc.b 'cmp.l #-2,d1'
	cmp.l	#-2,d1
	dc.b 'cmp.l #-2,d2'
	cmp.l	#-2,d2
	dc.b 'cmp.l #-2,d3'
	cmp.l	#-2,d3
	dc.b 'cmp.l #-2,d4'
	cmp.l	#-2,d4
	dc.b 'cmp.l #-2,d5'
	cmp.l	#-2,d5
	dc.b 'cmp.w  #0,a1'
	cmp.w	#0,a1
	dc.b 'cmp.w  #0,a2'
	cmp.w	#0,a2
	dc.b 'cmp.w  #0,a3'
	cmp.w	#0,a3
	dc.b 'cmp.w  #0,a4'
	cmp.w	#0,a4
	dc.b 'cmp.w  #0,a5'
	cmp.w	#0,a5
	dc.b 'cmp.w  #0,a6'
	cmp.w	#0,a6
	dc.b 'cmp.w  #0,a7'
	cmp.w	#0,a7
	dc.b 'cmp.w  #0,sp'
	cmp.w	#0,sp
	dc.b 'cmp.w  #4,a1'
	cmp.w	#4,a1
	dc.b 'cmp.w  #4,a2'
	cmp.w	#4,a2
	dc.b 'cmp.w  #4,a3'
	cmp.w	#4,a3
	dc.b 'cmp.w  #4,a4'
	cmp.w	#4,a4
	dc.b 'cmp.w  #4,a5'
	cmp.w	#4,a5
	dc.b 'cmp.w  #4,a6'
	cmp.w	#4,a6
	dc.b 'cmp.w  #4,a7'
	cmp.w	#4,a7
	dc.b 'cmp.w  #4,sp'
	cmp.w	#4,sp
	dc.b 'cmp.w  #$FF,a1'
	cmp.w	#$FF,a1
	dc.b 'cmp.w  #$FF,a2'
	cmp.w	#$FF,a2
	dc.b 'cmp.w  #$FF,a3'
	cmp.w	#$FF,a3
	dc.b 'cmp.w  #$FF,a4'
	cmp.w	#$FF,a4
	dc.b 'cmp.w  #$FF,a5'
	cmp.w	#$FF,a5
	dc.b 'cmp.w  #$FF,a6'
	cmp.w	#$FF,a6
	dc.b 'cmp.w  #$FF,a7'
	cmp.w	#$FF,a7
	dc.b 'cmp.w  #$FF,sp'
	cmp.w	#$FF,sp
	dc.b 'cmp.w #"XY",a1'
	cmp.w	#"XY",a1
	dc.b 'cmp.w #"XY",a2'
	cmp.w	#"XY",a2
	dc.b 'cmp.w #"XY",a3'
	cmp.w	#"XY",a3
	dc.b 'cmp.w #"XY",a4'
	cmp.w	#"XY",a4
	dc.b 'cmp.w #"XY",a5'
	cmp.w	#"XY",a5
	dc.b 'cmp.w #"XY",a6'
	cmp.w	#"XY",a6
	dc.b 'cmp.w #"XY",a7'
	cmp.w	#"XY",a7
	dc.b 'cmp.w #"XY",sp'
	cmp.w	#"XY",sp
	dc.b 'cmp.w  #$2700,a1'
	cmp.w	#$2700,a1
	dc.b 'cmp.w  #$2700,a2'
	cmp.w	#$2700,a2
	dc.b 'cmp.w  #$2700,a3'
	cmp.w	#$2700,a3
	dc.b 'cmp.w  #$2700,a4'
	cmp.w	#$2700,a4
	dc.b 'cmp.w  #$2700,a5'
	cmp.w	#$2700,a5
	dc.b 'cmp.w  #$2700,a6'
	cmp.w	#$2700,a6
	dc.b 'cmp.w  #$2700,a7'
	cmp.w	#$2700,a7
	dc.b 'cmp.w  #$2700,sp'
	cmp.w	#$2700,sp
	dc.b 'cmp.w  #$7FFF,a1'
	cmp.w	#$7FFF,a1
	dc.b 'cmp.w  #$7FFF,a2'
	cmp.w	#$7FFF,a2
	dc.b 'cmp.w  #$7FFF,a3'
	cmp.w	#$7FFF,a3
	dc.b 'cmp.w  #$7FFF,a4'
	cmp.w	#$7FFF,a4
	dc.b 'cmp.w  #$7FFF,a5'
	cmp.w	#$7FFF,a5
	dc.b 'cmp.w  #$7FFF,a6'
	cmp.w	#$7FFF,a6
	dc.b 'cmp.w  #$7FFF,a7'
	cmp.w	#$7FFF,a7
	dc.b 'cmp.w  #$7FFF,sp'
	cmp.w	#$7FFF,sp
	dc.b 'cmp.w  #$FFFF,a1'
	cmp.w	#$FFFF,a1
	dc.b 'cmp.w  #$FFFF,a2'
	cmp.w	#$FFFF,a2
	dc.b 'cmp.w  #$FFFF,a3'
	cmp.w	#$FFFF,a3
	dc.b 'cmp.w  #$FFFF,a4'
	cmp.w	#$FFFF,a4
	dc.b 'cmp.w  #$FFFF,a5'
	cmp.w	#$FFFF,a5
	dc.b 'cmp.w  #$FFFF,a6'
	cmp.w	#$FFFF,a6
	dc.b 'cmp.w  #$FFFF,a7'
	cmp.w	#$FFFF,a7
	dc.b 'cmp.w  #$FFFF,sp'
	cmp.w	#$FFFF,sp
	dc.b 'cmp.l  #0,a1'
	cmp.l	#0,a1
	dc.b 'cmp.l  #0,a2'
	cmp.l	#0,a2
	dc.b 'cmp.l  #0,a3'
	cmp.l	#0,a3
	dc.b 'cmp.l  #0,a4'
	cmp.l	#0,a4
	dc.b 'cmp.l  #0,a5'
	cmp.l	#0,a5
	dc.b 'cmp.l  #0,a6'
	cmp.l	#0,a6
	dc.b 'cmp.l  #0,a7'
	cmp.l	#0,a7
	dc.b 'cmp.l  #0,sp'
	cmp.l	#0,sp
	dc.b 'cmp.l  #4,a1'
	cmp.l	#4,a1
	dc.b 'cmp.l  #4,a2'
	cmp.l	#4,a2
	dc.b 'cmp.l  #4,a3'
	cmp.l	#4,a3
	dc.b 'cmp.l  #4,a4'
	cmp.l	#4,a4
	dc.b 'cmp.l  #4,a5'
	cmp.l	#4,a5
	dc.b 'cmp.l  #4,a6'
	cmp.l	#4,a6
	dc.b 'cmp.l  #4,a7'
	cmp.l	#4,a7
	dc.b 'cmp.l  #4,sp'
	cmp.l	#4,sp
	dc.b 'cmp.l  #$FF,a1'
	cmp.l	#$FF,a1
	dc.b 'cmp.l  #$FF,a2'
	cmp.l	#$FF,a2
	dc.b 'cmp.l  #$FF,a3'
	cmp.l	#$FF,a3
	dc.b 'cmp.l  #$FF,a4'
	cmp.l	#$FF,a4
	dc.b 'cmp.l  #$FF,a5'
	cmp.l	#$FF,a5
	dc.b 'cmp.l  #$FF,a6'
	cmp.l	#$FF,a6
	dc.b 'cmp.l  #$FF,a7'
	cmp.l	#$FF,a7
	dc.b 'cmp.l  #$FF,sp'
	cmp.l	#$FF,sp
	dc.b 'cmp.l  #$7FFF,a1'
	cmp.l	#$7FFF,a1
	dc.b 'cmp.l  #$7FFF,a2'
	cmp.l	#$7FFF,a2
	dc.b 'cmp.l  #$7FFF,a3'
	cmp.l	#$7FFF,a3
	dc.b 'cmp.l  #$7FFF,a4'
	cmp.l	#$7FFF,a4
	dc.b 'cmp.l  #$7FFF,a5'
	cmp.l	#$7FFF,a5
	dc.b 'cmp.l  #$7FFF,a6'
	cmp.l	#$7FFF,a6
	dc.b 'cmp.l  #$7FFF,a7'
	cmp.l	#$7FFF,a7
	dc.b 'cmp.l  #$7FFF,sp'
	cmp.l	#$7FFF,sp
	dc.b 'cmp.l  #$FFFF,a1'
	cmp.l	#$FFFF,a1
	dc.b 'cmp.l  #$FFFF,a2'
	cmp.l	#$FFFF,a2
	dc.b 'cmp.l  #$FFFF,a3'
	cmp.l	#$FFFF,a3
	dc.b 'cmp.l  #$FFFF,a4'
	cmp.l	#$FFFF,a4
	dc.b 'cmp.l  #$FFFF,a5'
	cmp.l	#$FFFF,a5
	dc.b 'cmp.l  #$FFFF,a6'
	cmp.l	#$FFFF,a6
	dc.b 'cmp.l  #$FFFF,a7'
	cmp.l	#$FFFF,a7
	dc.b 'cmp.l  #$FFFF,sp'
	cmp.l	#$FFFF,sp
	dc.b 'cmp.l  #$FFFFFFFF,a1'
	cmp.l	#$FFFFFFFF,a1
	dc.b 'cmp.l  #$FFFFFFFF,a2'
	cmp.l	#$FFFFFFFF,a2
	dc.b 'cmp.l  #$FFFFFFFF,a3'
	cmp.l	#$FFFFFFFF,a3
	dc.b 'cmp.l  #$FFFFFFFF,a4'
	cmp.l	#$FFFFFFFF,a4
	dc.b 'cmp.l  #$FFFFFFFF,a5'
	cmp.l	#$FFFFFFFF,a5
	dc.b 'cmp.l  #$FFFFFFFF,a6'
	cmp.l	#$FFFFFFFF,a6
	dc.b 'cmp.l  #$FFFFFFFF,a7'
	cmp.l	#$FFFFFFFF,a7
	dc.b 'cmp.l  #$FFFFFFFF,sp'
	cmp.l	#$FFFFFFFF,sp
	dc.b 'cmp.l #"WXYZ",a1'
	cmp.l	#"WXYZ",a1
	dc.b 'cmp.l #"WXYZ",a2'
	cmp.l	#"WXYZ",a2
	dc.b 'cmp.l #"WXYZ",a3'
	cmp.l	#"WXYZ",a3
	dc.b 'cmp.l #"WXYZ",a4'
	cmp.l	#"WXYZ",a4
	dc.b 'cmp.l #"WXYZ",a5'
	cmp.l	#"WXYZ",a5
	dc.b 'cmp.l #"WXYZ",a6'
	cmp.l	#"WXYZ",a6
	dc.b 'cmp.l #"WXYZ",a7'
	cmp.l	#"WXYZ",a7
	dc.b 'cmp.l #"WXYZ",sp'
	cmp.l	#"WXYZ",sp
	dc.b 'cmp.l  #1+1,a1'
	cmp.l	#1+1,a1
	dc.b 'cmp.l  #1+1,a2'
	cmp.l	#1+1,a2
	dc.b 'cmp.l  #1+1,a3'
	cmp.l	#1+1,a3
	dc.b 'cmp.l  #1+1,a4'
	cmp.l	#1+1,a4
	dc.b 'cmp.l  #1+1,a5'
	cmp.l	#1+1,a5
	dc.b 'cmp.l  #1+1,a6'
	cmp.l	#1+1,a6
	dc.b 'cmp.l  #1+1,a7'
	cmp.l	#1+1,a7
	dc.b 'cmp.l  #1+1,sp'
	cmp.l	#1+1,sp
	dc.b 'cmp.l  #(3+4),a1'
	cmp.l	#(3+4),a1
	dc.b 'cmp.l  #(3+4),a2'
	cmp.l	#(3+4),a2
	dc.b 'cmp.l  #(3+4),a3'
	cmp.l	#(3+4),a3
	dc.b 'cmp.l  #(3+4),a4'
	cmp.l	#(3+4),a4
	dc.b 'cmp.l  #(3+4),a5'
	cmp.l	#(3+4),a5
	dc.b 'cmp.l  #(3+4),a6'
	cmp.l	#(3+4),a6
	dc.b 'cmp.l  #(3+4),a7'
	cmp.l	#(3+4),a7
	dc.b 'cmp.l  #(3+4),sp'
	cmp.l	#(3+4),sp
	dc.b 'cmp.l #-1,a1'
	cmp.l	#-1,a1
	dc.b 'cmp.l #-1,a2'
	cmp.l	#-1,a2
	dc.b 'cmp.l #-1,a3'
	cmp.l	#-1,a3
	dc.b 'cmp.l #-1,a4'
	cmp.l	#-1,a4
	dc.b 'cmp.l #-1,a5'
	cmp.l	#-1,a5
	dc.b 'cmp.l #-1,a6'
	cmp.l	#-1,a6
	dc.b 'cmp.l #-1,a7'
	cmp.l	#-1,a7
	dc.b 'cmp.l #-1,sp'
	cmp.l	#-1,sp
	dc.b 'cmp.l #-2,a1'
	cmp.l	#-2,a1
	dc.b 'cmp.l #-2,a2'
	cmp.l	#-2,a2
	dc.b 'cmp.l #-2,a3'
	cmp.l	#-2,a3
	dc.b 'cmp.l #-2,a4'
	cmp.l	#-2,a4
	dc.b 'cmp.l #-2,a5'
	cmp.l	#-2,a5
	dc.b 'cmp.l #-2,a6'
	cmp.l	#-2,a6
	dc.b 'cmp.l #-2,a7'
	cmp.l	#-2,a7
	dc.b 'cmp.l #-2,sp'
	cmp.l	#-2,sp

; edge cases and so on

; labels
label_end:

; equs and defines
