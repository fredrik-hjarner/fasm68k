; TODO: Should probably be moved into xxcalm.inc
; Supposed to be called
; Side-effects:
;     xxcalm.ret - 0 if false
;                  1 if true
calminstruction m68k.is_one_token? source_text*
    local a
    local b

    ; check_zero_tokens:
        match ,source_text
        jno check_more_than_one
        compute xxcalm.ret, 0
        exit
    check_more_than_one:
        match a b,source_text
        jno is_one_token
        compute xxcalm.ret, 0
        exit
    is_one_token:
        compute xxcalm.ret, 1
end calminstruction