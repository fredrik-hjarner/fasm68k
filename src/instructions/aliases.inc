;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; ALIAS MACROS FOR INSTRUCTIONS THAT ONLY HAVE ONE SIZE                      ;;
;; TODO: Would these be faster as calminstructions??                          ;;
;; TODO: Setting boolean to enable/disable these??                            ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; TODO: ori to ccr

;; TODO: ori to sr

;; TODO: andi to ccr

;; TODO: andi to sr

;; TODO: eori to ccr

;; TODO: eori to sr

;; TODO: move from sr

;; TODO: move to ccr

;; TODO: move to sr

macro nbcd line&
    nbcd.b line
end macro

macro swap line&
    swap.w line
end macro

macro pea line&
    pea.l line
end macro

macro tas line&
    tas.b line
end macro

macro link line&
    link.w line
end macro

;; TODO: move usp

macro lea line&
    lea.l line
end macro

macro chk line&
    chk.w line
end macro

; scc
iterate cc, t,f,    hi,ls,cc,hs,cs,lo,ne,eq,vc,vs,pl,mi,ge,lt,gt,le
    macro s#cc? line&
        s#cc.b line
    end macro
end iterate

; dbcc
iterate cc,  t,f,ra,hi,ls,cc,hs,cs,lo,ne,eq,vc,vs,pl,mi,ge,lt,gt,le
    macro db#cc? line&
        db#cc.w line
    end macro
end iterate

macro moveq line&
    moveq.l line
end macro

macro divu line&
    divu.w line
end macro

macro divs line&
    divs.w line
end macro

macro sbcd line&
    sbcd.b line
end macro

macro mulu line&
    mulu.w line
end macro

macro muls line&
    muls.w line
end macro

macro abcd line&
    abcd.b line
end macro

macro exg line&
    exg.l line
end macro

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; SOME INSTRUCTIONS CAN HAVE .S SUFFIX INSTEAD OF .B                         ;;
;; TODO: Which instructions? All, some?                                       ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

macro bra.s line&
    bra.b line
end macro

macro bsr.s line&
    bsr.b line
end macro

; TODO: I have alias baked in somewhere in some instruction. Move it here!

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; DEFAULT SIZES FOR SOME INSTRUCTIONS                                        ;;
;; TODO: Move this into a separate file.                                      ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

macro btst line&
    ; TODO: I have no idea which is the correct one or even what the difference
    ;       between btst.b and btst.l is. The tests does not seem to have cases
    ;       where the difference comes to light!
    ; btst.b line
    btst.l line
end macro

macro bchg line&
    ; TODO: I have no idea which is the correct one or even what the difference
    ;       between bchg.b and bchg.l is. The tests does not seem to have cases
    ;       where the difference comes to light!
    ; bchg.b line
    bchg.l line
end macro

macro bclr line&
    ; TODO: I have no idea which is the correct one or even what the difference
    ;       between bclr.b and bclr.l is. The tests does not seem to have cases
    ;       where the difference comes to light!
    ; bclr.b line
    bclr.l line
end macro

macro bset line&
    ; TODO: I have no idea which is the correct one or even what the difference
    ;       between bset.b and bset.l is. The tests does not seem to have cases
    ;       where the difference comes to light!
    ; bset.b line
    bset.l line
end macro

iterate d, l,r

    macro as#d line&
        ; TODO: I have no idea which is the correct one or even what the difference
        ;       between asl.b, asl.w, asl.l is. The tests does not have cases
        ;       where the difference comes to light!
        ; as#d.b line
        as#d.w line
        ; as#d.l line
    end macro

    macro ls#d line&
        ; TODO: I have no idea which is the correct one or even what the difference
        ;       between lsl.b, lsl.w, lsl.l is. The tests does not have cases
        ;       where the difference comes to light!
        ; ls#d.b line
        ls#d.w line
        ; ls#d.l line
    end macro

    macro rox#d line&
        ; TODO: I have no idea which is the correct one or even what the difference
        ;       between roxl.b, roxl.w, roxl.l is. The tests does not have cases
        ;       where the difference comes to light!
        ; rox#d.b line
        rox#d.w line
        ; rox#d.l line
    end macro

    macro ro#d line&
        ; TODO: I have no idea which is the correct one or even what the difference
        ;       between rol.b, rol.w, rol.l is. The tests does not have cases
        ;       where the difference comes to light!
        ; ro#d.b line
        ro#d.w line
        ; ro#d.l line
    end macro

end iterate

macro bra? line&
    bra.w line
end macro

macro bsr? line&
    bsr.w line
end macro