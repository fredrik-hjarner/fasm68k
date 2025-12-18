;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; SETTINGS.INC                                                               ;;
;;                                                                            ;;
;; This file contains the settings for the fasm68k.                           ;;
;; Use `m68k.set` to enable/disable a setting.                                ;;
;; TODO: Warn or error if trying to set a non-existent setting and inform     ;;
;;       the user of all the available settings.                              ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

redefine m68k.settings?
namespace m68k.settings?
    iterate <setting, default_value, description>, \
        \ ;; GENERAL SETTINGS ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        \
        \ ; TODO: Better comment.
        \ ; Transforms << to shl and >> to shr etc.
        compat_operators, 0, "", \
        \ ; TODO: Better comment.
        \ ; Supports syntax like this: v_levseldelay: equ $FFFFFF80
        \ ; Observe the colon between the label and the equ.
        compat_colon_equs, 0, "", \
        \ ; Assumably `compat_word_align_instructions` is meant to automatically
        \ ; word align instructions.
        \ ; TODO: Actually use this setting in code.
        compat_word_align_instructions, 0, "", \
        \ ; TODO: Comment.
        compat_colonless_labels, 0, "", \
        \ ; TODO: Comment.
        \ ; `lbl1: something`
        \ ; will be replace with
        \ ; `lbl1:` 
        \ ; `something`
        \ ; TODO: Implement compat_labels_on_separate_line
        \ ; `compat_labels_on_separate_line` is neede to handle such things as:
        \ ; Ani_Bas:  dc.w .still-Ani_Bas
        \ ; where the the righ-hand side contains a local label, otherwise
        \ ; will *not* get Ani_Bas as it's parent but instead a preceeding label
        compat_labels_on_separate_line, 0, "", \
        \ ; TODO: Comment.
        \ ; Replace %01010101 with 01010101b in "some" situations.
        \ ; Only use this when you need to (for example when it's to tedious to
        \ ; replace all % with b in an old codebase you convert from another
        \ ; assembler to fasm68k).
        compat_binary_percent_prefix, 0, "", \
        \
        \ ;; VASM SPECIFIC ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        \
        \ ; TODO: Explain.
        \ ; Changes the behaviour of `ORG` to behave like it does in `vasm`.
        compat_vasm_org, 0, "", \
        \
        \ ; TODO: Explain.
        \ ; compat_vasm_org_label, 0, "", \
        \ ; TODO: Explain.
        \ ; In vasm align works a bit differently. vasm align takes 1 and
        \ ; bit shifts it to the left argument number of times.
        compat_vasm_align, 0, ""
            
        setting? = default_value
    end iterate ; <setting, default_value, description>
end namespace

; TODO: Make into a calminstruction.
; TODO: Should validate that the setting exists.
; TODO: Remove m68k.enable, it won't work for anything but 0 and 1 so wont work.
; TODO: enable is used in some of the examples, so they need to be updated then
;       enable can be removed.
macro m68k.enable? setting
    m68k.settings.setting = 1
end macro

; TODO: Comment.
; TODO: Should validate that the setting exists.
; TODO: Use this instead of m68k.enable.
macro m68k.set? setting*, value*
    ; Check if the setting exists.
    ; Check if the value is an allowed value for the setting.
    m68k.settings.setting = value
end macro