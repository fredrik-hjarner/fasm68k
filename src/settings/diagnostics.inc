redefine m68k.settings?
namespace m68k.settings?
    iterate <setting, default_value, description>, \
        \ ; TODO: Comment.
        \ ; TODO: 0 = disabled, 1 = warn, 2 = error
        diag_absolute_too_big, 0, ""
            
            setting? = default_value

    end iterate ; <setting, default_value, description>
end namespace

; Not intended to be used directly. Helper for the other macros
; TODO: Rename warn -> _warn
macro calminstruction?.warn? line&
    local line_str
    compute line_str, __line__
    arrange line_str, line_str
    stringify line_str
    display __file__ bappend ' [' bappend line_str bappend ']:'
    display 13 bappend 10 bappend 9
    display 'Warning: ' bappend line
    display 13 bappend 10
end macro

if m68k.settings.diag_absolute_too_big = 1
    macro calminstruction?.diag_absolute_too_big? line&
        warn line
    end macro
else if m68k.settings.diag_absolute_too_big = 2
    macro calminstruction?.diag_absolute_too_big? line&
        nice_err line
    end macro
else
    macro calminstruction?.diag_absolute_too_big? line&
    end macro
end if
