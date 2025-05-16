;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; DIRECTIVES                                                                 ;;
;; TODO: Have these in alphabetical order.                                    ;;
;; TODO: Regarding this file... it should be split up because some of them    ;;
;;       are only relevant for supporting speficic assemblers (for example    ;;
;;       vasm). A loy of the stuff should probably be move into compat file   ;;
;;       or a compat folder.                                                  ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; rs address counter for "reserved" data.
; TODO: The implementation of rs.[bwl] and rsset is too simplistic.
;       Seems that `dcb` and `rs` are in separate address spaces
;       where `org` sets the address for `dcb` and `rsset` sets the address for
;       `rs`.
define m68k.rs
m68k.rs = 0
; I use this to save the org address counter when switching between address
; spaces.
define m68k.old_org
m68k.old_org = 0

calminstruction dc.b? line&
        local head, tail, length, last_argument
        compute last_argument, 0
        arrange tail, line
        replace_legacy_operators tail
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
        emit_be length, head bswap length
    maybe_next:
        check last_argument = 0
        jyes next
end calminstruction

; TODO: This alias is mentioned in the vasm manual.
;       Does it exist in other assemblers?
; macro db? line&
;     dc.b line
; end macro

calminstruction dc.w? line&
        local head, tail, last_argument
        compute last_argument, 0
        arrange tail, line
        replace_legacy_operators tail
    next:
        match head=,tail, tail
        jyes at_least_two_arguments
    ; last argument:
        match head, tail
        compute last_argument, 1
    at_least_two_arguments:
        emit_be 2, head
    maybe_next:
        check last_argument = 0
        jyes next
end calminstruction

; TODO: This alias is mentioned in the vasm manual.
;       Does it exist in other assemblers?
; macro dw? line&
;     dc.w line
; end macro

calminstruction dc.l? line&
        local head, tail, last_argument
        compute last_argument, 0
        arrange tail, line
        replace_legacy_operators tail
    next:
        match head=,tail, tail
        jyes at_least_two_arguments
    ; last argument:
        match head, tail
        compute last_argument, 1
    at_least_two_arguments:
        emit_be 4, head
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
        emit_be 8, head
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
        calminstruction dcb.size? count*, fill:0
            local i
            compute i, count
            emit_next:
                check i > 0
                jno done
                emit_be bytes, fill
                compute i, i - 1
                jump emit_next
            done:
        end calminstruction

        ; label rs.[bwlq] n
        ;    Reserve n n times size bytes.
        ;    The address of the reserved space
        struc rs.size? n
            ; Switch from `org` address space to `rs` address space
            m68k.old_org = $
            org m68k.rs
            .:
            ; Manually increment the `rs` counter
            m68k.rs = m68k.rs + n * bytes
            ; Switch back to `org address space`
            org m68k.old_org
        end struc

end iterate ; <size_suffix, size>


; TODO: This alias is mentioned in the vasm manual.
;       Does it exist in other assemblers?
macro fail? line&
    err line
end macro

; TODO: The implementation of rs.[bwl] might not be the best.
;       Seems that `dcb` and `rs` are in separate address spaces
;       where `org` sets the address for `dcb` and `rsset` sets the address for
;       `rs`.
calminstruction rsset? addr*
    compute m68k.rs, addr
end calminstruction