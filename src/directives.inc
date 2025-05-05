;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; DIRECTIVES                                                                 ;;
;; TODO: Have these in alphabetical order.                                    ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

calminstruction dc.b? tail&
        local head, tail, length, last_argument
        compute last_argument, 0
    next:
        match head=,tail, tail
        jyes at_least_two_arguments
    ; last argument:
        match head, tail
        compute last_argument, 1
    at_least_two_arguments:
        check head eqtype ''
        jyes string
        emit 1, head
        jump maybe_next
    string:
        compute length, lengthof head
        emit length, head bswap length
    maybe_next:
        check last_argument = 0
        jyes next
end calminstruction

; TODO: This alias is mentioned in the vasm manual.
;       Does it exist in other assemblers?
; macro db? line&
;     dc.b line
; end macro

calminstruction dc.w? tail&
        local head, tail, last_argument
        compute last_argument, 0
    next:
        match head=,tail, tail
        jyes at_least_two_arguments
    ; last argument:
        match head, tail
        compute last_argument, 1
    at_least_two_arguments:
        emit 2, head
    maybe_next:
        check last_argument = 0
        jyes next
end calminstruction

; TODO: This alias is mentioned in the vasm manual.
;       Does it exist in other assemblers?
; macro dw? line&
;     dc.w line
; end macro

calminstruction dc.l? tail&
        local head, tail, last_argument
        compute last_argument, 0
    next:
        match head=,tail, tail
        jyes at_least_two_arguments
    ; last argument:
        match head, tail
        compute last_argument, 1
    at_least_two_arguments:
        emit 4, head
    maybe_next:
        check last_argument = 0
        jyes next
end calminstruction

; TODO: This alias is mentioned in the vasm manual.
;       Does it exist in other assemblers?
; macro dl? line&
;     dc.l line
; end macro

;; 32-bit quad-word
calminstruction dc.q? tail&
        local head, tail, last_argument
        compute last_argument, 0
    next:
        match head=,tail, tail
        jyes at_least_two_arguments
    ; last argument:
        match head, tail
        compute last_argument, 1
    at_least_two_arguments:
        emit 8, head
    maybe_next:
        check last_argument = 0
        jyes next
end calminstruction

iterate <size, bytes>, \
        b,     1, \
        w,     2, \
        l,     4, \
        q,     8

        ; dcb.b <exp>[,<fill>]
        ;     Insert <exp> zero or <fill> bytes into the current section.
        ; TODO: Test this.
        calminstruction dcb.size? exp*, fill:1
            local i
            compute i, fill
            emit_next:
                check i > 0
                jno done
                emit bytes, exp
                compute i, i - 1
                jump emit_next
            done:
        end calminstruction

end iterate ; <size_suffix, size>

; TODO: This alias is mentioned in the vasm manual.
;       Does it exist in other assemblers?
macro fail line&
    err line
end macro