if m68k.settings.compat_vasm_org = 1
    ; TODO: Comment/explain.
    ; TODO: I should probably not keep the current behaviour for when the
    ;       "diff is negative". What I do now is that I just set it to zero
    ;       if the the user attempts to go to a previous address with org
    ;       (as far as I can understand setting org to a previous/earlier
    ;       address in vasm makes no sense at all and should probably produce
    ;       an error in vasm but it does not).
    ; TODO: Remove logging.
    calminstruction org? addr*
            ; display 10 ; TODO: Remove.

            ; local addr_token ; TODO: remove.

            local computed_addr ; TODO: remove.
            ; local computed_addr_str ; TODO: remove.

            local computed_pc ; TODO: remove.
            ; local computed_pc_str ; TODO: remove.

            local diff ; TODO: remove.
            ; local diff_str ; TODO: remove.

            ; arrange addr_token, addr
            ; transform addr_token
            ; stringify addr_token
            ; display 'addr_token: ' bappend addr_token bappend 10

            compute computed_addr, addr
            ; arrange computed_addr_str, computed_addr
            ; stringify computed_addr_str
            ; display 'computed_addr: ' bappend computed_addr_str bappend 10

            compute computed_pc, $
            ; arrange computed_pc_str, computed_pc
            ; stringify computed_pc_str
            ; display 'computed_pc: ' bappend computed_pc_str bappend 10

            compute diff, computed_addr - computed_pc
            check diff < 0
            jyes diff_is_negative

            ; arrange diff_str, diff
            ; stringify diff_str
            ; display 'diff: ' bappend diff_str bappend 10

            ; ; TODO: I could add some safety checks here. You can't ORG to previous
            ; ;       addresses in vasm for example since that makes no sense in vasm.
            emit diff, 0
            exit
        diff_is_negative:
            ; compute diff, -diff
            ; arrange diff_str, -diff
            ; stringify diff_str
            ; display 'diff: ' bappend diff_str bappend 10
            warn 'Attempting to remove bytes with ORG directive!' \
                     bappend ' This usage of ORG will be ignored!'
    end calminstruction

end if ; m68k.settings.compat_vasm_org = 1

; TODO: This code beneath might not be needed. Remove?
; if m68k.settings.compat_vasm_org_label = 1
;     ; TODO: Comment/explain.
;     ; In vasm a label preceeding an org gets the address that the org sets.
;     ; TODO: Can I do this with a calminstruction?
;     struc org? addr*
;         org addr
;         . := $
;         repeat 1, i:.
;             display '. is ', `i
;         end repeat
;     end struc
;     ; calminstruction (label) org? addr
;     ;         asm org addr
;     ;         publish label:, val
;     ; end calminstruction

; end if ; m68k.settings.compat_vasm_org_label = 1

if m68k.settings.compat_vasm_align = 1
    ; TODO: Comment/explain.
    ; Copy quote from vasm docs regarding align.
    ; calminstruction (label) org? addr
    ;         asm org addr
    ;         publish label:, val
    ; end calminstruction
    macro align? bitcount*
        fasm2.align 1 shl (bitcount)
    end macro
else
    macro align? line&
        fasm2.align line
    end macro
end if ; m68k.settings.compat_vasm_align = 1