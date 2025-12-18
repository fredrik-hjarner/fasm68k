;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Extended CALM Utilities (xxcalm)                                           ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; This file provides utility functions and macros that extend fasmg's CALM   ;;
;; (Custom Assembly Language Macros) system to make writing macro code easier.;;
;;                                                                            ;;
;; Key features:                                                              ;;
;;   - Unique label generation (new/@ system)                                 ;;
;;   - Multi-parameter display                                                ;;
;;   - Tokenization and evaluation helpers                                    ;;
;;   - Nice error formatting                                                  ;;
;;   - Shorthand combinations (arr_ass, loc_com, etc.)                        ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

define xxcalm
namespace xxcalm
    ; DEPRECATED: Legacy return value holder (not currently used).
    ; In early development, this was used to pass boolean return values between
    ; macros. Modern approach uses direct 'check' and 'jyes'/'jno' instead.
    ret = -1
end namespace

; DEPRECATED: Jump if xxcalm.ret equals 1 (true).
; This was part of an early return value system. No longer used in current code.
macro calminstruction?.jyup? label*
    check xxcalm.ret = 1
    compute xxcalm.ret, -1
    jyes label
end macro

; DEPRECATED: Jump if xxcalm.ret equals 0 (false).
; This was part of an early return value system. No longer used in current code.
macro calminstruction?.jnope? label*
    check xxcalm.ret = 0
    compute xxcalm.ret, -1
    jyes label
end macro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Unique Label Generation System (new/@)                                     ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; CALM doesn't have built-in support for unique labels like fasmg's regular  ;;
;; macros do. This system provides that functionality.                        ;;
;;                                                                            ;;
;; Usage:                                                                     ;;
;;   new labelname           - Declares a unique label                        ;;
;;   @ labelname:            - Defines the unique label                       ;;
;;   @ jyes labelname        - Jumps to the unique label                      ;;
;;                                                                            ;;
;; Example:                                                                   ;;
;;   calminstruction?.dispsymbol? sym                                         ;;
;;       new empty                                                            ;;
;;       new cont                                                             ;;
;;       match , sym                                                          ;;
;;       @ jyes empty              ; Jump to unique 'empty' label             ;;
;;       display '<not empty>'                                                ;;
;;       @ jump cont               ; Jump to unique 'cont' label              ;;
;;   @ empty:                      ; Define unique 'empty' label              ;;
;;       display '<empty>'                                                    ;;
;;   @ cont:                       ; Define unique 'cont' label               ;;
;;   end calminstruction                                                      ;;
;;                                                                            ;;
;; Implementation: Uses a counter to generate unique names (labelname1,       ;;
;; labelname2, etc.) and transforms statements prefixed with @ to use them.   ;;
;; Credit: https://board.flatassembler.net/topic.php?p=234192#234192          ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Marker for the unique label namespace
define ___loc? ___loc?

; Declares a unique label by generating a unique name (name1, name2, etc.)
calminstruction calminstruction?.new? name*
        local   new, i
        init    i, 0
        compute i, i+1
        arrange new, name#i
        arrange name, ___loc.name
        publish name, new
end calminstruction

; Transforms statements prefixed with @ to use unique labels
; Example: "@ jyes done" becomes "jyes done1" (if done was declared via 'new done')
calminstruction calminstruction?.@? statement&
        transform statement, ___loc
        assemble statement
end calminstruction

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Multi-parameter Display                                                    ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; CALM's display normally only accepts one parameter. This version allows    ;;
;; multiple comma-separated parameters like normal fasmg display.             ;;
;;                                                                            ;;
;; Example:                                                                   ;;
;;   display "Value: ", value, 13, 10  ; Displays string, value, and newline  ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

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

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Evaluation and Boolean Utilities                                           ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Execute a statement in the normal (non-CALM) assembly context.
; Useful for evaluating expressions or executing regular macros from CALM.
macro calminstruction?.eval? str*
    asm eval str
end macro

; Helper structure for the bool macro (see below).
; Evaluates an expression and defines the result as 1 (true) or 0 (false).
; TODO: Make into a calminstruction?
struc xxcalm._bool? expr*
    if expr
        eval 'define . 1'
    else
        eval 'define . 0'
    endif
end struc

; Converts a boolean expression to 1 or 0 in CALM context.
; Usage: bool result, (some_value = expected_value)
; Result will be 1 if condition is true, 0 if false.
macro calminstruction?.bool? result*, bool_expr*
    asm result xxcalm._bool? bool_expr
end macro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Tokenization                                                               ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Converts a string into tokens that can be matched/manipulated.             ;;
;; Credit: https://board.flatassembler.net/topic.php?p=243916#243907          ;;
;;                                                                            ;;
;; Example: tokenize "1 + 2" produces the tokens: 1, +, 2                     ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

struc tokenize? string*
        eval 'define . ',string
end struc
macro calminstruction?.tokenize? val*
    asm val tokenize val
end macro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Formatted Error Messages                                                   ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Displays errors with file name and line number for better debugging.       ;;
;;                                                                            ;;
;; Format:                                                                    ;;
;;   filename.asm [123]:                                                      ;;
;;       Error message here                                                   ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

macro calminstruction?.nice_err? line&
    local line_str
    compute line_str, __line__
    arrange line_str, line_str
    stringify line_str
    err 13 bappend 10 bappend \
        9 bappend __file__ bappend ' [' bappend line_str bappend ']:' bappend \
        13 bappend 10 bappend \
        9 bappend line
    exit ; Automatically exit after error
end macro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Full Transform                                                             ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Repeatedly transforms a variable until no more transformations are possible;;
;; Useful when a variable may contain multiple levels of substitutions.       ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

macro calminstruction?.full_transform? var*
        new @next
    @ @next:
        transform var
        @ jyes @next
end macro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Shorthand Utility Combinations                                             ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; These combine common CALM operations into single commands to reduce        ;;
;; boilerplate code and improve readability.                                  ;;
;;                                                                            ;;
;; Naming convention: operation1_operation2                                   ;;
;;   arr = ARRange    (arrange - build code from parts)                       ;;
;;   ass = ASSemble   (execute assembled code)                                ;;
;;   com = COMpute    (evaluate expression)                                   ;;
;;   str = STRingify  (convert to string)                                     ;;
;;   tra = TRAnsform  (apply symbol substitutions)                            ;;
;;   loc = LOCal      (declare local variable)                                ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; ARRange -> ASSemble
macro calminstruction?.arr_ass? var*, val*
    arrange var, val
    assemble var
end macro

; ARRange -> COMpute
macro calminstruction?.arr_com? var*, val*
    arrange var, val
    compute var, var
end macro

; ARRange -> STRingify
macro calminstruction?.arr_str? var*, val*
    arrange var, val
    stringify var
end macro

; ARRange -> TRAnsform
macro calminstruction?.arr_tra? var*, val*
    arrange var, val
    transform var
end macro

; LOCal -> ARRange -> COMpute
macro calminstruction?.loc_arr_com? var*, val*
    local var
    arrange var, val
    compute var, var
end macro

; LOCal -> ARRange -> STRingify
macro calminstruction?.loc_arr_str? var*, val*
    local var
    arrange var, val
    stringify var
end macro

; LOCal -> COMpute
macro calminstruction?.loc_com? var*, val*
    local var
    compute var, val
end macro


