;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; ENDIANNESS                                                                 ;;
;; fasmg emits bytes in little-endian format, so we need to swap the bytes    ;;
;; to emit in big-endian which is what the Motorola 68000 uses.               ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

macro calminstruction?.emit_be? num_bytes*, value*
    emit (num_bytes), (value) bswap (num_bytes)
end macro