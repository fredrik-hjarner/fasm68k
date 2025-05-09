; =====================================================================
; ROM METADATA
; 256d bytes = $100 bytes
; https://segaretro.org/ROM_header#Mega_Drive
; https://plutiedev.com/rom-header
; =====================================================================
    dc.b "SEGA GENESIS    "      ; 16 bytes: Console name
    ; 16d = 10h


    dc.b "                "      ; 16 bytes: Copyright/date
    ; 32d = 20h


    dc.b "EPIC LEGENDS OF DESTINY                         " ; 48 bytes: Domestic name
    ; 80d = 50h


    dc.b "EPIC LEGENDS OF DESTINY                         " ; 48 bytes: International name
    ; 128d = 80h


    ; dc.b "GM XXXXXXXX-XX"        ; 14 bytes: Version number
    meta_version
    ; 142d = 8Eh

    ; org $18E                     ; Just to be 100% sure we're at the right place
    cnop 0,$18E              ; org works differently on fasmg and clownassembler

    dc.w $0000                   ; 2 bytes: Checksum
    ; 144d = 90h


    dc.b "J               "      ; 16 bytes: I/O support
    ; 160d = A0h


    dc.l $00000000               ; 4 bytes: ROM start address
    ; 164d
    dc.l $00100000               ; 4 bytes: ROM end address
    ; 168d
    dc.l $00FF0000               ; 4 bytes: Start of RAM
    ; 172d
    dc.l $00FFFFFF               ; 4 bytes: End of RAM
    ; 176d = B0h


    ; Extra memory 12 bytes
    dc.l $00000000               ; 4 bytes
    ; 180d
    dc.l $00000000               ; 4 bytes
    ; 184d
    dc.l $00000000               ; 4 bytes
    ; 188d
    dc.b "    "                  ; 4 bytes: Modem info
    ; 192d = C0h


    dc.b "        "                  ; 8 bytes: Modem info
    dc.b "        "                  ; 8 bytes: Space
    ; 208d = D0h


    dc.b "                "         ; 16 bytes: Space
    ; 224d = E0h


    dc.b "                "         ; 16 bytes: Space
    ; 240d = F0h


    dc.b "JUE             "      ; 16 bytes: Country codes
    ; 256d = 100h