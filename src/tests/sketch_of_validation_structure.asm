;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; IN THIS FILE I TRY TO FIGURE OUT A WAY TO VALIDATE INSTRUCTIONS            ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; TODO: There is one problem and that rergard labels (I think). When the
; specification says label then I think that size suffix is not allowed!
; Here in this code I don't have `label` specifically but I have abs.w and abs.l
; which I thinnk will work but I might need an extra check for instructions that
; take a label as an operand to make sure it does not have a size suffix.

; This is a structure that contains all valid instruction variants.
; It is used to validate instructions.
; It is structured as a tree, or nested namespaces, in 4 levels:
;     1. instruction level
;       2. size level
;         3. op1 level
;           4. op2 level
;     That is:
;         `<inst>.<size>.<op1>.<op2>`.
;     For example:
;         movep.w.an_displace.dn
;
; (Remember that each level needs to be defined before one can add stuff to it).
;     Those same characters are of course allowed in strings though.
; `_` at size level means no size suffix.
; `_` at op1 level means the instruction has no first operand.
; `_` at op2 level means the instruction has no second operand.
;
; These are all the different op types/addressing modes are:
;     dn                an      indir_an        an_post_incr    an_pre_decr
;     an_displace       an_idx  abs_w           abs_l           pc_displace
;     pc_idx            imm     reg_list        ccr             sr
;     usp
; Observe that we only have one type of imm so imm8, imm16 etc we just handle
;     here as imm!
; Observe that `label` does not exist in this list, we use `abs.l` here instead
;     of `label`!
; Observe that the dc.b, dc.w and dc.l are not included because they are just
;     special cases for data declaration directives and not instructions!
;
; The reason why I have `an_displace` instead of `d(an)` is because these
;     characters are not allowed in identifiers in fasmg:
;         +-/*=<>()[]{}:?!,.|&~#`\
define m68k
define m68k.valid_instructions
namespace m68k.valid_instructions
        define movep

        define movep.w
        define movep.w.an_displace
        define movep.w.an_displace.dn

        define movep.l
        define movep.l.dn
        define movep.l.dn.an_displace
        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        define stop

        define stop._
        define stop._.imm
        define stop._.imm._
        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        define exg

        define exg.l
        define exg.l.dn
        define exg.l.dn.dn
        define exg.l.dn.an
        define exg.l.an
        define exg.l.an.dn
        define exg.l.an.an

        define exg._
        define exg._.dn
        define exg._.dn.dn
        define exg._.dn.an
        define exg._.an
        define exg._.an.dn
        define exg._.an.an
end namespace

; `validate` examines if an instruction uses a valid combination of
;     instruction, size and operands.
; Parameters:
;     instr: movep, stop, exg etc.
;     size: b | w | l | _
;     op1:  an_displace, d, an, imm et cetera. _ means empty.
;     op2:  an_displace, d, an, imm et cetera. _ means empty.
; Supposed to be `call`:ed.
calminstruction validate inst*, size*, op1*, op2*
        local tokens
        arrange tokens, inst.size.op1.op2


        local thing_to_check
        arrange thing_to_check, =m68k.=valid_instructions.tokens
        check defined thing_to_check
        jyes valid
    ; invalid:
        local str
        arrange str, tokens
        stringify str
        display 'invalid:  ' bappend str bappend 10
        exit
    valid:
        display 'valid' bappend 10
end calminstruction

calminstruction test instr*, size*, op1*, op2*
        call validate, instr, size, op1, op2
end calminstruction

display 10 ; just for nicer output.

; These need to be defined in this play example. Don't mind them, they will not
;     be used in the real code.
define exg
define movep
define stop
define _
define l
define dn
define an
define exdadwg

; about 16 million instructions in total (700000*23)
; executed this 5 times in terminal and got the following results:
; fastest was 5.1s 
; slowest was 5.4s
; repeat 700000
        test movep, w, an_displace, dn  ; valid
        test stop, _, imm, _    ; valid
        test stop, _, imm, _    ; valid
        test stop, _, imm, _    ; valid
        test stop, _, imm, _    ; valid
        test stop, _, imm, _    ; valid
        test stop, _, imm, _    ; valid
        test stop, _, imm, _    ; valid
        test stop, _, imm, _    ; valid
        test stop, _, imm, _    ; valid
        test exg, l, dn, an     ; valid
        test exg, l, dn, an     ; valid
        test exg, l, dn, an    ; valid
        test exg, l, dn, an    ; valid
        test exg, l, dn, an    ; valid
        test exg, l, dn, an    ; valid
        test exg, l, dn, an    ; valid
        test exg, l, dn, an    ; valid
        test exg, l, dn, an    ; valid
        test exg, l, dn, an    ; valid
        test exdadwg, l, dn, dn ; invalid
        test exdadwg, l, dn, dn ; invalid
        test exdadwg, l, dn, dn ; invalid
; end repeat