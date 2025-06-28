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

iterate <size,  size_str,    bytes,  max_size>, \
        w,      'word',      2,      $FFFF, \
        l,      'longword',  4,      $FFFFFFFF, \
        q,      'quadword',  8,      $FFFFFFFFFFFFFFFF

    calminstruction dc.size? line&
            assert_word_aligned "Attempting to place a " bappend size_str \
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
            ; TODO: Warn if does not fit in word
            ; TODO: Add test cases with too large numbers
            emit_be bytes, head and max_size
        maybe_next:
            check last_argument = 0
            jyes next
    end calminstruction

end iterate ; <size, size_str, max_size>

; TODO: This alias is mentioned in the vasm manual.
;       Does it exist in other assemblers?
; macro dw? line&
;     dc.w line
; end macro

; TODO: This alias is mentioned in the vasm manual.
;       Does it exist in other assemblers?
; macro dl? line&
;     dc.l line
; end macro

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
        ;    Reserve n times size bytes.
        ;    The address of the reserved space
        ; TODO: Make into a calm instruction
        struc rs.size? n:1
            if (`size <> 'b') & (__rs mod 2 <> 0)
                 ; TODO: This could be toggled by a setting since you may want
                 ;       to control whether it's an error or a warning at least.
                local err_msg
                err_msg = "Attempting to place a " bappend \
                          size_str bappend " on an odd address"
                warn err_msg
            end if
            . := __rs
            ; Manually increment the `rs` counter
            __rs = __rs + n * bytes
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