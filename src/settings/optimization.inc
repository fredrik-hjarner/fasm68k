;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; OPTIMIZATION.INC                                                           ;;
;; Contains settings for optimizations. I handle optimizations separately     ;;
;; from auto-fixes. An auto-fix is when illegal instructions can be fixed     ;;
;; into legal instructions. Optimizations is when legal but suboptimal        ;;
;; instructions are changed to more optimal instructions.                     ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

redefine m68k.settings?
namespace m68k.settings?
    iterate <setting, default_value, description>, \
        \ ; TODO: Comment.
        \ ; 0 = don't optimize
        \ ; 1 = optimize with warning
        \ ; 2 = optimize without warning
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

iterate instr,    cmp, add, sub, or, and

    if m68k.settings.optimize_#instr#_to_#instr#i = 1
        macro calminstruction?.diag_#instr#_to_#instr#i? line&
            warn 'Using `' bappend \ 
                 `instr bappend \
                 '` when the first operand is an immediate is ' bappend \
                 'less efficient than using `' bappend \
                 `instr bappend 'i`. Optimizing to `' bappend \
                 `instr bappend 'i`!'
        end macro
    else
        macro calminstruction?.diag_#instr#_to_#instr#i? line&
        end macro
    end if

end iterate