; =====================================================================
; VECTORS - Exception Vectors (Required for hardware initialization)
; 64 vectors x 4 (long) = 256d bytes = $100 bytes
; https://web.archive.org/web/20240616180841/https://wiki.megadrive.org/index.php?title=68k_vector_table&t=20170119115405
; =====================================================================
    dc.l    0                           ; #0 Initial Stack Address
    dc.l    Start                       ; #1 Start of program Code
    dc.l    int2_bus_error              ; #2 Bus error
    dc.l    int3_address_error          ; #3 Address error
    dc.l    int4_illegal_instruction    ; #4 Illegal instruction
    dc.l    error          ; #5 Division by zero
    dc.l    error          ; #6 CHK exception
    dc.l    error          ; #7 TRAPV exception
    dc.l    error          ; #8 Privilage violation
    dc.l    error          ; #9 TRACE exception
    dc.l    0              ; #10 Line-A emulator
    dc.l    0              ; #11 Line-F emulator
    dc.l    0              ; #12 Reserved (NOT USED)
    dc.l    error          ; #13 Co-processor protocol violation
    dc.l    error          ; #14 Format error
    dc.l    error          ; #15 Uninitialized Interrupt

    ; Reserved (NOT USED)
    dc.l    0,0,0,0,0,0,0,0 ; #16-#23

    dc.l    0             ; #24 Spurious Interrupt
    dc.l    0             ; #25 IRQ Level 1
    dc.l    0             ; #26 IRQ Level 2 (EXT Interrupt)
    dc.l    0             ; #27 IRQ Level 3
    dc.l    hblank        ; #28 IRQ Level 4 (VDP Horizontal Interrupt)
    dc.l    0             ; #29 IRQ Level 5
    dc.l    vblank        ; #30 IRQ Level 6 (VDP Vertical Interrupt)
    dc.l    0             ; #31 IRQ Level 7
    dc.l    0             ; #32 TRAP #00 Exception
    dc.l    0             ; #33 TRAP #01 Exception
    dc.l    0             ; #34 TRAP #02 Exception
    dc.l    0             ; #35 TRAP #03 Exception
    dc.l    0             ; #36 TRAP #04 Exception
    dc.l    0             ; #37 TRAP #05 Exception
    dc.l    0             ; #38 TRAP #06 Exception
    dc.l    0             ; #39 TRAP #07 Exception
    dc.l    0             ; #40 TRAP #08 Exception
    dc.l    0             ; #41 TRAP #09 Exception
    dc.l    0             ; #42 TRAP #10 Exception
    dc.l    0             ; #43 TRAP #11 Exception
    dc.l    0             ; #44 TRAP #12 Exception
    dc.l    0             ; #45 TRAP #13 Exception
    dc.l    0             ; #46 TRAP #14 Exception
    dc.l    0             ; #47 TRAP #15 Exception
    dc.l    0             ; #48 (FP) Branch or Set on Unordered Condition
    dc.l    0             ; #49 (FP) Inexact Result
    dc.l    0             ; #50 (FP) Divide by Zero
    dc.l    0             ; #51 (FP) Underflow
    dc.l    0             ; #52 (FP) Operand Error
    dc.l    0             ; #53 (FP) Overflow
    dc.l    0             ; #54 (FP) Signaling NAN
    dc.l    0             ; #55 (FP) Unimplemented Data Type
    dc.l    0             ; #56 MMU Configuration Error
    dc.l    0             ; #57 MMU Illegal Operation Error
    dc.l    0             ; #58 MMU Access Violation Error
    
    ; Reserved (NOT USED)
    dc.l   0,0,0,0,0              ; #59, #60, #61, #62, #63