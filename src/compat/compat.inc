; `even` directive is common in m68k assemblers.
macro even
    fasm2.align 2
end macro

; TODO: I might be going to far with this.
macro endif!
    end if
end macro
macro endc!
    end if
end macro
macro elseif! line&
    else if line
end macro

; TODO: I might be going to far with this.
; TODO: I am not sure why I needed this to be an unconditional macro.
macro endm?!
    esc end macro
end macro

; TODO: I might be going to far with this.
macro endr
    end rept
end macro

macro incbin line&
    file line
end macro

; Insert as many zero bytes as required to reach an address which can be divided
; by `alignment`. Then add `offset` zero bytes. May fill the padding-bytes with
; no-operation instructions for certain cpus.
; TODO: Maybe what it fills with should be configurable.
macro cnop offset,alignment
    fasm2.align alignment | offset
end macro

; Adds support for operators commonly used in m68k assemblers.
; For example << is shl in fasmg. 
; Example:
;     input:  (((l1)  &  $3FFF) <<  16) + (((l1)  &  $C000) >>  14)
;     output: (((l1) and $3FFF) shl 16) + (((l1) and $C000) shr 14)
; TODO: Is it too slow when it's a `macro calminstruction?.` construction?
; TODO: Rename to something like `tranform_expression`
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

    ;; Replace %0 with 0b ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        check m68k.settings.compat_binary_percent_prefix = 1
        jno skip_binary_percent_prefix
        binary_percent_prefix expr
    skip_binary_percent_prefix:
end macro

; TODO: Comment/explain.
; binary_percent_prefix uses this virtual output area.
virtual at 0
    test_area::
    rb 512
end virtual
; TODO: Comment/explain.
macro calminstruction?.binary_percent_prefix? __expr*
        local __tmp
        local __expr_str
        local res
        local length
        local i
        local bin_num

        compute bin_num, 0

        arrange __expr_str, __expr
        stringify __expr_str

        ; log __expr
        ; display "__expr: " bappend __expr_str bappend 10

        compute length, lengthof __expr_str
        check length < 2
    ; length_at_least_two_characters:
        jyes no
        store test_area:0, length, __expr_str
        load __tmp, test_area:0, 1
        check __tmp = '%'
        jno no
    ; has_percent_prefix:
        ; display "has_percent_prefix" bappend 10
        compute i, 1
    next_character:
        load __tmp, test_area:i, 1
        check __tmp = '0' | __tmp = '1'
        ; display 'dawdadawd' bappend 10
        jno no
        compute bin_num, bin_num + (((+__tmp) - (+'0')) shl (length - i-1))
        compute i, i+1
        check i >= length
        jno next_character
    ; yes:
        ; display 'yes start' bappend 10
        ; load __tmp, test_area:1, length-1

        ; local log
        ; arrange log, __tmp
        ; stringify log
        ; display 'yes' bappend 10
        ; local y
        arrange __expr, bin_num
        ; display 'yes end' bappend 10
        ; stringify y
        ; display 'y: ' bappend y bappend 10

        ; compute __tmp, __tmp
        ; compute __tmp, __tmp bappend 'b'
        ; asm ref tokenize __tmp
        ; tokenize __tmp
        ; local x
        ; asm x tokenize __tmp
        ; arrange __expr, x=b
        ; asm eval 'define res __tmp'
        ; initsym __tmpz, __tmp
        ; publish res, __tmpz
        ; local log
        ; arrange log, __tmp
        ; stringify log
        ; display 'yes' bappend 10
        ; display '__tmp: ' bappend log bappend 10
        jump done_bin
    no:
        ; display "no" bappend 10
    done_bin:
end macro

; Replace @ with $ since fasmg uses $ for location counter and some m68k
; assemblers uses @ instead.
; I am not sure this will work well, otherwise I need to come up with another
; solution.
; TODO: Place this behind a setting.
define @ $

if m68k.settings.compat_colonless_labels = 1
    ; Adds support for colonless labels.
    ; TODO: I want to be able to via a setting to enable/disable this.
    ; The below code is taken from:
    ;     https://flatassembler.net/docs.php?article=fasmg
    ; struc ? tail&
    ;         match :, tail 
    ;                 .: 
    ;         else match : instruction, tail
    ;                 .: instruction
    ;         else match == value, tail
    ;                 . = value
    ;         else 
    ;                 .: tail
    ;         end match 
    ; end struc
    ; A more conservative approach.
    ; TODO: Is this faster/better as a calminstruction?
    ;       Not sure but rewrite this into a calminstruction anyway!
    ;       btw labeled macroinstructions can't catch `equ`s
    struc (name) ? tail&
            match , tail 
                    .:
            else 
                    . tail
                    ; TODO: remove. just some logging what this would catch.
                    ;       it catches both `equ`s and `=` I think.
                    ; match :, tail
                    ; else
                    ;     display 'label:', `name, ' ', `tail, 10
                    ; end match
            end match 
    end struc
end if ; m68k.settings.compat_colonless_labels = 1

include "compat_vasm.inc"