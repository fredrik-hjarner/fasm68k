; INIT
; this command can be used to give an initial numeric value to local variable
; at the time when the CALM instruction is defined
calminstruction calminstruction?.init? var*, val:0
	compute val, val
	publish var, val
end calminstruction


; Unique labels in CALM with `new` and `@`.
; From https://board.flatassembler.net/topic.php?p=234192#234192
; Example:
;     macro calminstruction?.dispsymbol? sym
;             new empty
;             new cont
;             match , sym
;             @ jyes empty
;             display '<not empty>'
;             @ jump cont
;         @ empty:
;             display '<empty>'
;         @ cont:
;     end macro
;     calminstruction test arg1
;             dispsymbol arg1
;     end calminstruction
define ___loc? ___loc?
calminstruction calminstruction?.new? name*
        local   new, i
        init    i, 0
        compute i, i+1
        arrange new, name#i
        arrange name, ___loc.name
        publish name, new
end calminstruction
calminstruction calminstruction?.@? statement&
        transform statement, ___loc
        assemble statement
end calminstruction

; arguments:
;     reg_nr: register number: 0-23d
;     value:  value: 8 bits
calminstruction set_vdp_register reg_nr, value
    local set_reg
    local reg
    local res
    local cmd

    compute set_reg, 1 shl 15
    compute reg, reg_nr shl 8
    compute res, set_reg or reg or value
    arrange cmd,=move.=w #res,=vdp_ctrl.=l
    assemble cmd
end calminstruction

calminstruction meta_version
        local tmp, quote, s_since_2025, m_since_2025

        arrange quote, '

        compute tmp, __time__
        compute s_since_2025, tmp - 1735686000
        compute m_since_2025, s_since_2025 / 60
        arrange tmp, =GM m_since_2025
        stringify tmp
        emit lengthof tmp, tmp
end calminstruction

; TODO: Explain exactly what this does and how it is intended to be used.
; arguments:
;     r: 0-7
;     g: 0-7
;     b: 0-7
; TODO: The name kinda sucks.
; TODO: This would be better as an inline fasmg macro.
calminstruction set_palette_color? r, g, b
    local tmp
    ; bbb0 ggg0 rrr0
    compute tmp, (b shl 9) or (g shl 5) or (r shl 1)
    arrange tmp, =move.=w= =#tmp,=vdp_data.=l
    assemble tmp
end calminstruction
define set_palette_color +set_palette_color

; arguments:
;     addr: address: $0000-$FFFF
; https://segaretro.org/Sega_Mega_Drive/VDP_general_usage
calminstruction set_write_vram? addr
    local tmp
    ; TODO: compute does not work here because it can't work in preprocess.asm.
    ; compute tmp, $40000000 + ((addr and $3FFF) shl 16)+((addr and $C000) shr 14)
    arrange tmp, =move.=l= =#$40000000+(((addr)&$3FFF)<<16)+(((addr)&$C000)>>14),=vdp_ctrl.=l
    assemble tmp
end calminstruction
define set_write_vram +set_write_vram

; arguments:
;     addr: address: $00-$FF
; https://segaretro.org/Sega_Mega_Drive/VDP_general_usage
calminstruction set_write_vsram? addr
    local tmp
    ; TODO: compute does not work here because it can't work in preprocess.asm.
    ; compute tmp, $40000010+((addr)<<16)
    arrange tmp, =move.=l= =#$40000010+((addr)<<16),=vdp_ctrl.=l
    assemble tmp
end calminstruction
define set_write_vsram +set_write_vsram

; bappend
; Util macro for CALM to concatenate strings with shorter syntax.
; Only works when added to preprocess.asm
; Example:
;     calminstruction tester
;         local tmp, tmp2
;         bappend tmp, 13, 10
;         display tmp ; Output: empty line
;         bappend tmp, "a", "b", "c", 13, 10
;         display tmp ; Output: abc
;         compute tmp2, "$"
;         bappend tmp, tmp2, "a", "b", "c", 13, 10
;         display tmp ; Output: $abc
;     end calminstruction
;     tester
; OBSERVE! I managed to make a version of append that works without
; preprocess.asm so I am using that instead.
; macro bappend dest*, strings&
;     emit compute dest, ""
;     iterate string, strings
;         emit compute dest, dest bappend string
;     end iterate
; end macro

; Make visible to the preprocessor
; define bappend +bappend
define set_vdp_register +set_vdp_register
define meta_version +meta_version

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; PLANE STUFF                                                                ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; TODO: Explain what this is and why it is.
virtual at 0
    string_tile_row::
    rb 64 ; 40h
end virtual
; TODO: Explain what this is and why it is.
virtual at 0
    char_to_tile_map::
    rb 256 ; covers all ascii values
end virtual
iterate <char, tile>, \
        ' ',   0, \
        '0',   0, \
        '1',   1, \
        '2',   2, \
        '3',   3, \
        '4',   4, \
        '5',   5, \
        '6',   6, \
        '7',   7, \
        '8',   8, \
        '9',   9, \
        'A',   10, \
        'B',   11, \
        'C',   12, \
        'D',   13, \
        'E',   14, \
        'F',   15

        store tile:1 at char_to_tile_map:char
end iterate

calminstruction str_to_tile_indices str
        local tmp
        compute tmp, str
        ; Store the string in the string_tile_row
        store string_tile_row:0, \  ; offset to store at
              64, \                 ; number of bytes to store
              tmp                   ; the value to store (numeric or string)
        ; now go through all of them and emit each
        local i
        compute i, 0
    next:
        check i >= 64
        jyes done
        ; Quote: The loaded value is always a string of the specified length.
        load tmp, \                     ; target variable
             string_tile_row:i, \       ; offset to load from
             1                          ; number of bytes to load
        compute tmp, +tmp
        arrange tmp, tmp
        load tmp, \                     ; target variable
             char_to_tile_map:tmp, \    ; offset to load from
             1                          ; number of bytes to load

        compute tmp, tmp bswap 2 ; TODO: Use emit_be when possible in future.
        emit 2, tmp
        ; compute tmp, +tmp
        ; arrange tmp, tmp
        ; arrange tmp, =dc.=w tmp
        ; assemble tmp

        compute i, i + 1
        jump next
    done:
end calminstruction
define str_to_tile_indices +str_to_tile_indices

; arguments:
;     c: color: 0-15
; TODO: This is not working.
calminstruction create_single_color_tile? c
    local tmp
    arrange tmp, =move.=l= =#=$#c#c#c#c#c#c#c#c,=vdp_data.=l
    transform tmp
    assemble tmp
end calminstruction
define create_single_color_tile +create_single_color_tile
