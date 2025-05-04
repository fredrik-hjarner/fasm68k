; `even` directive is common in m68k assemblers.
macro even
    align 2
end macro

; Insert as many zero bytes as required to reach an address which can be divided
; by `alignment`. Then add `offset` zero bytes. May fill the padding-bytes with
; no-operation instructions for certain cpus.
macro cnop offset,alignment
    align alignment | offset
end macro

; Adds support for operators commonly used in m68k assemblers.
; For example << is shl in fasmg. 
; Example:
;     input:  (((l1)  &  $3FFF) <<  16) + (((l1)  &  $C000) >>  14)
;     output: (((l1) and $3FFF) shl 16) + (((l1) and $C000) shr 14)
macro calminstruction?.replace_legacy_operators? expr*
    ;; Replace << with shl ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    next_shl:
        match a? =<=< b?, expr
        jno done_shl
        arrange expr, a =shl b
        jump next_shl
    done_shl:

    ;; Replace >> with shr ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    next_shr:
        match a? =>=> b?, expr
        jno done_shr
        arrange expr, a =shr b
        jump next_shr
    done_shr:

    ;; Replace & with and ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    next_and:
        match a? =& b?, expr
        jno done_and
        arrange expr, a =and b
        jump next_and
    done_and:

    ;; Replace | with or ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    next_or:
        match a? =| b?, expr
        jno done_or
        arrange expr, a =or b
        jump next_or
    done_or:
end macro

; Replace @ with $ since fasmg uses $ for location counter and some m68k
; assemblers uses @ instead.
; I am not sure this will work well, otherwise I need to come up with another
; solution.
define @ $