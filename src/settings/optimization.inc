;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; OPTIMIZATION.INC                                                          ;;
;; Contains settings for optimizations. I handle optimizations separately   ;;
;; from auto-fixes. An auto-fix is when illegal instructions can be fixed    ;;
;; into legal instructions. Optimizations is when legal but suboptimal        ;;
;; instructions are changed to more optimal instructions.                     ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

redefine m68k.settings?
namespace m68k.settings?
    iterate <setting, default_value, description>, \
        \ ; TODO: Comment.
        \ ; TODO: 0 = don't optimize
        \ ; TODO: 1 = optimize with warning
        \ ; TODO: 2 = optimize without warning
        optimize_cmp_to_cmpi, 0, "", \
        \
        \ ; TODO: 
        optimize_add_to_addi, 0, "", \
        \
        \ ; TODO: 
        optimize_sub_to_subi, 0, "", \
        \
        \ ; TODO: 
        optimize_or_to_ori, 0, "", \
        \
        \ ; TODO: 
        optimize_and_to_andi, 0, ""
            
            setting? = default_value

    end iterate ; <setting, default_value, description>
end namespace

;; optimize_cmp_to_cmpi ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

if m68k.settings.optimize_cmp_to_cmpi = 1
    macro calminstruction?.diag_cmp_to_cmpi? line&
        warn 'Using `cmp` when the first operand is an immediate is ' \
             bappend 'less efficient than using `cmpi`. Auto-fixing to `cmpi`!'
    end macro
else
    macro calminstruction?.diag_cmp_to_cmpi? line&
    end macro
end if