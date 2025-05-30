virtual
    reversed_bytes::
    db $00, $80, $40, $c0, $20, $a0, $60, $e0
	db $10, $90, $50, $d0, $30, $b0, $70, $f0
	db $08, $88, $48, $c8, $28, $a8, $68, $e8
	db $18, $98, $58, $d8, $38, $b8, $78, $f8
	db $04, $84, $44, $c4, $24, $a4, $64, $e4
	db $14, $94, $54, $d4, $34, $b4, $74, $f4
	db $0c, $8c, $4c, $cc, $2c, $ac, $6c, $ec
	db $1c, $9c, $5c, $dc, $3c, $bc, $7c, $fc
	db $02, $82, $42, $c2, $22, $a2, $62, $e2
	db $12, $92, $52, $d2, $32, $b2, $72, $f2
	db $0a, $8a, $4a, $ca, $2a, $aa, $6a, $ea
	db $1a, $9a, $5a, $da, $3a, $ba, $7a, $fa
	db $06, $86, $46, $c6, $26, $a6, $66, $e6
	db $16, $96, $56, $d6, $36, $b6, $76, $f6
	db $0e, $8e, $4e, $ce, $2e, $ae, $6e, $ee
	db $1e, $9e, $5e, $de, $3e, $be, $7e, $fe
	db $01, $81, $41, $c1, $21, $a1, $61, $e1
	db $11, $91, $51, $d1, $31, $b1, $71, $f1
	db $09, $89, $49, $c9, $29, $a9, $69, $e9
	db $19, $99, $59, $d9, $39, $b9, $79, $f9
	db $05, $85, $45, $c5, $25, $a5, $65, $e5
	db $15, $95, $55, $d5, $35, $b5, $75, $f5
	db $0d, $8d, $4d, $cd, $2d, $ad, $6d, $ed
	db $1d, $9d, $5d, $dd, $3d, $bd, $7d, $fd
	db $03, $83, $43, $c3, $23, $a3, $63, $e3
	db $13, $93, $53, $d3, $33, $b3, $73, $f3
	db $0b, $8b, $4b, $cb, $2b, $ab, $6b, $eb
	db $1b, $9b, $5b, $db, $3b, $bb, $7b, $fb
	db $07, $87, $47, $c7, $27, $a7, $67, $e7
	db $17, $97, $57, $d7, $37, $b7, $77, $f7
	db $0f, $8f, $4f, $cf, $2f, $af, $6f, $ef
	db $1f, $9f, $5f, $df, $3f, $bf, $7f, $ff
end virtual

macro calminstruction?.reverse_bit_in_byte? val*
    ; TODO: Assert that is a byte
    load val, reversed_bytes:val, 1
end macro

macro calminstruction?.reverse_bit_in_word? val*
    ; TODO: Assert that is a word
    local upper_byte
    local lower_byte
    compute upper_byte, val shr 8
    compute lower_byte, val and $FF
    load upper_byte, reversed_bytes:upper_byte, 1
    load lower_byte, reversed_bytes:lower_byte, 1
    compute val, lower_byte shl 8 or upper_byte
end macro