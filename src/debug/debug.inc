;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; DEBUG.INC                                                                  ;;
;; Contains functions that makes it easier to find bugs                       ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; `compute` but asserts that `dest` is defined
macro calminstruction?.compute_assert_defined? dest*, src&
        new @defined
        check defined dest
        @ jyes @defined
    ; not_defined
        local tmp_compute
        arrange tmp_compute, =dest
        stringify tmp_compute
        nice_err tmp_compute bappend ' is not defined'
        exit
    @ @defined:
        compute dest, src
end macro