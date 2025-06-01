;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; AUTOFIXES.INC                                                              ;;
;; Contains settings for auto-fixes. I handle auto-fixing separately from     ;;
;; optimizations. An auto-fix is when illegal instructions can be fixed into  ;;
;; legal instructions. Optimizations is when legal but suboptimal             ;;
;; instructions are changed to more optimal instructions.                     ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

redefine m68k.settings?
namespace m68k.settings?
    iterate <setting, default_value, description>, \
        \ ; TODO: Comment.
        \ ; TODO: 0 = error/dont autofix
        \ ; TODO: 1 = autofix with warning
        \ ; TODO: 2 = silently autofix
        \ ; TODO: Check if this NEEDS to be autofixed? Yes it does. Confirmed.
        autofix_eor_to_eori, 2, "", \
        autofix_cmp_to_cmpa, 2, ""
            
            setting? = default_value

    end iterate ; <setting, default_value, description>
end namespace

;; autofix_eor_to_eori ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

if m68k.settings.autofix_eor_to_eori = 0
    macro calminstruction?.diag_eor_to_eori? line&
        nice_err '`eor` does not allow the first operand to' \
                 bappend ' be an immediate. Use `eori` instead'
    end macro
else if m68k.settings.autofix_eor_to_eori = 1
    macro calminstruction?.diag_eor_to_eori? line&
        warn '`eor` does not allow the first operand to' \
             bappend ' be an immediate. Auto-fixing to `eori`.'
    end macro
else
    macro calminstruction?.diag_eor_to_eori? line&
    end macro
end if

;; autofix_cmp_to_cmpa ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

if m68k.settings.autofix_cmp_to_cmpa = 0
    macro calminstruction?.diag_cmp_to_cmpa?
        nice_err '`cmp` does not allow the second operand to' \
                 bappend ' be an address register. Use `cmpa` instead'
    end macro
else if m68k.settings.autofix_cmp_to_cmpa = 1
    macro calminstruction?.diag_cmp_to_cmpa?
        warn '`cmp` does not allow the second operand to' \
             bappend ' be an address register. Auto-fixing to `cmpa`.'
    end macro
else
    macro calminstruction?.diag_cmp_to_cmpa?
    end macro
end if