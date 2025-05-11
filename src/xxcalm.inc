; TODO: Move is_one_token into here because it may be a good util.
; TODO: A match_any util would be nice.

define xxcalm
namespace xxcalm
    ; Handling return values in fasmg can be a bit awkward so here I have
    ; defined a variable that you can use to hold a BOOLEAN return value for
    ; your custom macros.
    ; TODO: Override `jyes` and `jno` to look at this value if it is not -1
    ;       since -1 is the default "non-value" and what I reset it back to
    ;       when a `jyes`/`jno` check has been performed.
    ; TODO: I should remove this.
    ret = -1
end namespace

; TODO: Comment
; TODO: I should remove this.
macro calminstruction?.jyup? label*
    ; TODO: Check for -1 here because that would indicate error.
    check xxcalm.ret = 1
    compute xxcalm.ret, -1
    jyes label
end macro

; TODO: Comment
; TODO: I should remove this.
macro calminstruction?.jnope? label*
    ; TODO: Check for -1 here because that would indicate error.
    check xxcalm.ret = 0
    compute xxcalm.ret, -1
    jyes label
end macro

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

; Allows calminstruction?.display? to have multiple
; parameters just as normal display.
; Examples:
;   display "hello", 13, 10
calminstruction calminstruction?.display? list&
    local item
    loop:
        match item=,list, list
        jno final
        arrange item, =display item
        assemble item
        jump loop
    final:
        arrange item, =display list 
        assemble item
end calminstruction
; macro calminstruction?.display? list&
;     local head, tail
;     new @loop
;     new @final
;     arrange tail, list
;     @ @loop:
;         match head=,tail, tail
;         @ jno @final
;         arrange head, =display head
;         assemble head
;         @ jump @loop
;     @ @final:
;         arrange head, =display tail 
;         assemble head
; end macro

; ARRange, ASSemble
macro calminstruction?.arr_ass? var*, val*
    arrange var, val
    assemble var
end macro

; ARRange, STRingify
macro calminstruction?.arr_str? var*, val*
    arrange var, val
    stringify var
end macro

; ARRange, TRAnsform
macro calminstruction?.arr_tra? var*, val*
    arrange var, val
    transform var
end macro

; TODO: Comment/explain.
macro calminstruction?.eval? str*
    asm eval str
end macro

; TODO: Comment/explain.
; TODO: Make into a calminstruction?
; Just a helper for the `calminstruction?.bool?` util.
struc xxcalm._bool? expr*
    if expr
        eval 'define . 1'
    else
        eval 'define . 0'
    endif
end struc

macro calminstruction?.bool? result*, bool_expr*
    asm result xxcalm._bool? bool_expr
end macro
