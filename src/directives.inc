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
;       where `org` sets the address for `dc` and `rsset` sets the address for
;       `rs`.
define rs? ; define the namespace that of rs.b, rs.w and rs.l
__rs? = 0  ; the RS counter.
; I use this to save the org address counter when switching between address
; spaces.
define m68k.old_org
m68k.old_org = 0

; rseven word-aligns the `__rs` counter.
macro rseven?
    __rs = __rs + (__rs mod 2)
end macro

define dc?
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
        check head eqtype ''
        jyes string
        ; TODO: Warn if does not fit in byte
        ; TODO: Add test cases with too large numbers
        emit 1, head and $FF
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
        assert_word_aligned "Attempting to place a word on an odd address!"
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
        ; TODO: Warn if does not fit in word
        ; TODO: Add test cases with too large numbers
        emit_be 2, head and $FFFF
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
        assert_word_aligned "Attempting to place a longword on an odd address!"
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
        ; TODO: Warn if does not fit in longword
        ; TODO: Add test cases with too large numbers
        emit_be 4, head and $FFFFFFFF
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

define dcb?
iterate <size, size_str,   bytes>, \
        b,     'byte',     1, \
        w,     'word',     2, \
        l,     'longword', 4, \
        q,     'quadword', 8

        ; dcb.b <exp>[,<fill>]
        ;     Insert <exp> zero or <fill> bytes into the current section.
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

        ; label rs.[bwlq] n
        ;    Reserve n n times size bytes.
        ;    The address of the reserved space
        ; TODO: Make into a calm instruction
        struc rs.size? n:1
            if (`size <> 'b') & (__rs mod 2 <> 0)
                local err_msg
                err_msg = "Attempting to place a " bappend \
                          size_str bappend " on an odd address"
                err err_msg
            end if
            ; Switch from `org` address space to `rs` address space
            m68k.old_org = $
            org __rs
            .:
            ; Manually increment the `rs` counter
            __rs = __rs + n * bytes
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
    compute __rs, addr
end calminstruction