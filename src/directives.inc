;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; ASSEMBLER DIRECTIVES                                                       ;;
;; TODO: Have these in alphabetical order.                                    ;;
;; TODO: Regarding this file... it should be split up because some of them    ;;
;;       are only relevant for supporting speficic assemblers (for example    ;;
;;       vasm). A loy of the stuff should probably be move into compat file   ;;
;;       or a compat folder.                                                  ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; This file implements assembler directives commonly found in 68k assemblers.;;
;; These directives control data generation, memory layout, and assembly      ;;
;; behavior rather than generating actual machine code instructions.          ;;
;;                                                                            ;;
;; Main directive families:                                                   ;;
;;   dc.b/w/l/q  - Define Constant (emit data bytes/words/longs/quads)        ;;
;;   dcb.b/w/l/q - Define Constant Block (emit repeated values)               ;;
;;   rs.b/w/l/q  - Reserve Space (define structure offsets, no actual data)   ;;
;;   rsset       - Set the RS counter to a specific address                   ;;
;;   rseven      - Align the RS counter to word boundary                      ;;
;;   even        - Align current address to word boundary (defined in         ;;
;;                 compat/compat.inc)                                         ;;
;;                                                                            ;;
;; Note: Some of these directives provide compatibility with other assemblers ;;
;; like vasm and asm68k. Future refactoring may move compatibility-specific   ;;
;; directives to the compat/ folder.                                          ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; RS (Reserve Space) Counter and Related Directives                          ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; The RS counter (__rs) is used for defining data structure layouts without  ;;
;; actually allocating memory. This is useful for creating offset definitions.;;
;;                                                                            ;;
;; Important: The RS counter operates in a separate address space from the    ;;
;; main assembly address ($). Use 'org' to set $, and 'rsset' to set __rs.    ;;
;;                                                                            ;;
;; Example:                                                                   ;;
;;   rsset 0           ; Start structure at offset 0                          ;;
;;   sprite_x rs.w 1   ; sprite_x = 0, __rs becomes 2                         ;;
;;   sprite_y rs.w 1   ; sprite_y = 2, __rs becomes 4                         ;;
;;   sprite_tile rs.w 1 ; sprite_tile = 4, __rs becomes 6                     ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

define rs?      ; Define the namespace for rs.b, rs.w, rs.l, rs.q
__rs? = 0       ; The RS counter - tracks the current "reserve space" offset

; Word-align the RS counter to an even address.
; If __rs is odd, add 1 to make it even.
macro rseven?
    __rs = __rs + (__rs mod 2)
end macro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; DC (Define Constant) - Emit Data into Binary                               ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; These directives emit literal data values into the assembled output.       ;;
;; They accept comma-separated lists of values and/or strings.                ;;
;;                                                                            ;;
;; Usage:                                                                     ;;
;;   dc.b $12, $34, "Hello", 0    ; Emit bytes                                ;;
;;   dc.w $1234, $5678            ; Emit words (16-bit, big-endian)           ;;
;;   dc.l $12345678               ; Emit longword (32-bit, big-endian)        ;;
;;   dc.q $123456789ABCDEF0       ; Emit quadword (64-bit, big-endian)        ;;
;;                                                                            ;;
;; Note: dc.w/l/q enforce word-alignment (even addresses) and maye warn or    ;;
;; give error if placed on odd addresses.                                     ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

define dc?  ; Define namespace for dc.b, dc.w, dc.l, dc.q

; dc.b - Define Constant Byte(s)
; Can emit individual bytes or strings. No alignment required.
calminstruction dc.b? line&
        local head, tail, length, last_argument
        compute last_argument, 0
        arrange tail, line
        massage_expression tail
    next:
        match head=,tail, tail
        jyes at_least_two_arguments
    ; last argument:
        match head, tail
        compute last_argument, 1
    at_least_two_arguments:
        check head eqtype ''     ; Is it a string?
        jyes string
        ; It's a number - emit low byte only
        ; TODO: Warn if value doesn't fit in byte (> $FF)
        ; TODO: Add test cases with too large numbers
        emit 1, head and $FF
        jump maybe_next
    string:
        ; It's a string - emit all characters
        compute length, lengthof head
        emit_be length, head bswap length
    maybe_next:
        check last_argument = 0
        jyes next
end calminstruction

; dc.w, dc.l, dc.q - Define Constant Word/Long/Quad
; These are generated by the iterate block below.
; All (optionally) enforce word-alignment (even addresses) since the 68000
; requires word-aligned access for word/long data.
iterate <size,  size_str,    bytes,  max_size>, \
        w,      'word',      2,      $FFFF, \
        l,      'longword',  4,      $FFFFFFFF, \
        q,      'quadword',  8,      $FFFFFFFFFFFFFFFF

    calminstruction dc.size? line&
            ; Ensure word-alignment (68000 hardware requirement)
            assert_data_word_aligned "Attempting to place a " bappend size_str \
                                     bappend " on an odd address!"
            local head, tail, last_argument
            compute last_argument, 0
            arrange tail, line
            massage_expression tail
        next:
            match head=,tail, tail
            jyes at_least_two_arguments
        ; last argument:
            match head, tail
            compute last_argument, 1
        at_least_two_arguments:
            ; TODO: Warn if value doesn't fit in the specified size
            ; TODO: Add test cases with too large number
            emit_be bytes, head and max_size
        maybe_next:
            check last_argument = 0
            jyes next
    end calminstruction

end iterate ; <size, size_str, bytes, max_size>

; Potential aliases for compatibility with other assemblers:
; db -> dc.b (vasm)
; dw -> dc.w (vasm)
; dl -> dc.l (vasm)
; These are commented out for now but could be enabled if needed.

; macro db? line&
;     dc.b line
; end macro

; macro dw? line&
;     dc.w line
; end macro

; macro dl? line&
;     dc.l line
; end macro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; DCB (Define Constant Block) - Emit Repeated Values                         ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; These directives emit a specified number of repeated values.               ;;
;; Useful for reserving and initializing blocks of memory.                    ;;
;;                                                                            ;;
;; Usage:                                                                     ;;
;;   dcb.b 100, 0      ; Emit 100 zero bytes                                  ;;
;;   dcb.w 50, $FFFF   ; Emit 50 words with value $FFFF                       ;;
;;   dcb.l 10          ; Emit 10 longwords with value 0 (default)             ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

define dcb?  ; Define namespace for dcb.b, dcb.w, dcb.l, dcb.q

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; RS (Reserve Space) - Define Structure Member Offsets                       ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; These directives don't emit any data - they just advance the __rs counter  ;;
;; and assign the current offset to a label. Used for defining data structure ;;
;; layouts.                                                                   ;;
;;                                                                            ;;
;; Usage:                                                                     ;;
;;   rsset 0               ; Start at offset 0                                ;;
;;   player_x rs.w 1       ; player_x = 0, __rs advances by 2                 ;;
;;   player_y rs.w 1       ; player_y = 2, __rs advances by 2                 ;;
;;   player_health rs.b 1  ; player_health = 4, __rs advances by 1            ;;
;;   player_name rs.b 20   ; player_name = 5, __rs advances by 20             ;;
;;                                                                            ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

iterate <size, size_str,   bytes>, \
        b,     'byte',     1, \
        w,     'word',     2, \
        l,     'longword', 4, \
        q,     'quadword', 8

        ; dcb.size count, fill_value
        ; Emits 'count' values of size 'size', each with value 'fill_value' (default 0)
        ; TODO: Test this.
        calminstruction dcb.size? count*, fill:0
            local i
            ; TODO: Use `massage_expression` here
            compute i, count
            emit_next:
                check i > 0
                jno done
                emit_be bytes, fill
                compute i, i - 1
                jump emit_next
            done:
        end calminstruction

        ; rs.size [count]
        ; Reserves 'count' (default 1) elements of 'size' in the RS space.
        ; The label is assigned the current __rs value, then __rs is incremented.
        ; For non-byte sizes, warns if __rs is not word-aligned.
        ; TODO: Make into a calm instruction
        struc rs.size? n:1
            ; Warn if trying to place word/long/quad on odd address in RS space
            if (`size <> 'b') & (__rs mod 2 <> 0)
                 ; TODO: This could be toggled by a setting since you may want
                 ;       to control whether it's an error or a warning at least.
                local err_msg
                err_msg = "Attempting to place a " bappend \
                          size_str bappend " on an odd RS address"
                diag_data_word_alignment err_msg
            end if
            . := __rs                    ; Assign current RS offset to this label
            __rs = __rs + n * bytes      ; Advance RS counter
        end struc

end iterate ; <size, size_str, bytes>

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; FAIL - Force Assembly Error                                                ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Compatibility directive (from vasm) that triggers an assembly error with   ;;
;; a custom message. Useful for conditional compilation checks.               ;;
;;                                                                            ;;
;; Usage:                                                                     ;;
;;   if some_condition                                                        ;;
;;       fail "This feature is not supported!"                                ;;
;;   end if                                                                   ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

macro fail? line&
    err line
end macro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; RSSET - Set RS Counter to Specific Address                                 ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Sets the RS (Reserve Space) counter to a specific value. This is typically ;;
;; used at the start of a structure definition.                               ;;
;;                                                                            ;;
;; Usage:                                                                     ;;
;;   rsset 0           ; Start structure at offset 0                          ;;
;;   rsset $FF0000     ; Start at a specific address                          ;;
;;                                                                            ;;
;; Note: The RS counter (__rs) is independent of the assembly address ($).    ;;
;; Use 'org' to set $ and 'rsset' to set __rs.                                ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

calminstruction rsset? addr*
    compute __rs, addr
end calminstruction