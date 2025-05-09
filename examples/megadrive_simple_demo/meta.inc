; =====================================================================
; ROM METADATA
; 256d bytes = $100 bytes
; https://segaretro.org/ROM_header#Mega_Drive
; https://plutiedev.com/rom-header
; =====================================================================

dc.b "SEGA GENESIS    "      ; 16 bytes: Console name
assert $ = $110
dc.b "                "      ; 16 bytes: Copyright/date
assert $ = $120
dc.b "FASM68K                                         " ; 48 bytes: Domestic name
assert $ = $150
dc.b "FASM68K                                         " ; 48 bytes: International name
assert $ = $180
dc.b "GM XXXXXXXX-XX"        ; 14 bytes: Version number
assert $ = $18E
dc.w $0000                   ; 2 bytes: Checksum
assert $ = $190
dc.b "J               "      ; 16 bytes: I/O support
assert $ = $1A0
dc.l $00000000               ; 4 bytes: ROM start address
assert $ = $1A4
dc.l $00100000               ; 4 bytes: ROM end address
assert $ = $1A8
dc.l $00FF0000               ; 4 bytes: Start of RAM
assert $ = $1AC
dc.l $00FFFFFF               ; 4 bytes: End of RAM
assert $ = $1B0

; Extra memory 12 bytes
dc.l $00000000               ; 4 bytes
; 180d
dc.l $00000000               ; 4 bytes
; 184d
dc.l $00000000               ; 4 bytes
; 188d

dc.b "            "          ; 8 bytes: Modem info
dc.b "                                        " ; 16 bytes: Space
assert $ = $1F0
dc.b "JUE             "      ; 16 bytes: Country codes
assert $ = $200