;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; TIMERS.INC                                                                 ;;
;;                                                                            ;;
;; This file contains logic for organizing timers.                            ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; CONSTANTS                                                                  ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

hblanks_per_100Hz_tick  equ 156
hblanks_per_50Hz_tick   equ 312
hblanks_per_1Hz_tick    equ 15600 ; $3CF0

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; VARIABLES                                                                  ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; All words because I am lazy.
; 0 -> 1 -> 2 -> 3 -> 4 -> 5 -> ... -> 155 -> 0
timer_100Hz_counter rs.w 1
timer_50Hz_counter  rs.w 1
timer_1Hz_counter   rs.w 1

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; HBLANK INTERRUPT HANDLER                                                   ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; TODO: Instead of calling the timer callbacks I should have bools in memory
; or somnething so that that code is NOT executed in the hblank interrupt!!!
hblank:
        ; Save registers we'll be modifying
        move.w d0, -(sp)         ; Only saving d0 as we'll use it for comparisons
        
        ; Increment and check 100Hz timer (occurs the most, so check it first)
        addi.w   #1, timer_100Hz_counter.l
        move.w  timer_100Hz_counter.l, d0
        cmpi.w   #hblanks_per_100Hz_tick, d0
        blt.w   .skip100HzCallback
    ; Reset counter and call callback
        move.w  #0, timer_100Hz_counter.l
        jsr     timer_100Hz_callback.l
    .skip100HzCallback:
        ; Increment and check 50Hz timer
        addi.w   #1, timer_50Hz_counter.l
        move.w  timer_50Hz_counter.l, d0
        cmpi.w   #hblanks_per_50Hz_tick, d0
        blt.w   .skip50HzCallback
    ; Reset counter and call callback
        move.w  #0, timer_50Hz_counter.l
        jsr     timer_50Hz_callback.l
    .skip50HzCallback:
        ; Increment and check 1Hz timer
        addi.w   #1, timer_1Hz_counter.l
        move.w  timer_1Hz_counter.l, d0
        cmpi.w   #hblanks_per_1Hz_tick, d0
        blt.w   .skip1HzCallback
    ; Reset counter and call callback
        move.w  #0, timer_1Hz_counter.l
        jsr     timer_1Hz_callback.l
    .skip1HzCallback:

        ; Restore registers
        move.w (sp)+, d0
        rte

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; TIMERS                                                                     ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

timer_100Hz_callback:
    rts

timer_50Hz_callback:
    rts

timer_1Hz_callback:
    rts