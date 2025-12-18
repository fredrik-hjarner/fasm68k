;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; ENDIANNESS HANDLING - Big-Endian Byte Order                                ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; The Motorola 68000 uses big-endian byte order (most significant byte first);;
;; but fasmg's default emit/load/store operations use little-endian.          ;;
;;                                                                            ;;
;; These utilities use fasmg's 'bswap' (byte swap) operator to convert between;;
;; little-endian and big-endian representations.                              ;;
;;                                                                            ;;
;; Example:                                                                   ;;
;;   emit_be 2, $1234  ; Emits: $12 $34 (not $34 $12)                         ;;
;;   emit_be 4, $12345678  ; Emits: $12 $34 $56 $78 (not $78 $56 $34 $12)     ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Emit a value in big-endian byte order
; Parameters:
;   num_bytes - Number of bytes to emit (1, 2, 4, or 8)
;   value - The value to emit
macro calminstruction?.emit_be? num_bytes*, value*
    emit (num_bytes), (value) bswap (num_bytes)
end macro

; Load a value from memory and convert from big-endian to fasmg's native format
; Parameters:
;   var - Variable to store the loaded value
;   offset - Memory offset to load from
;   num_bytes - Number of bytes to load
macro calminstruction?.load_be? var*, offset*, num_bytes*
    load var, (offset), (num_bytes)
    compute var, +var bswap num_bytes
end macro

; Store a value to memory in big-endian byte order
; Parameters:
;   offset - Memory offset to store at
;   num_bytes - Number of bytes to store
;   value - The value to store
macro calminstruction?.store_be? offset*, num_bytes*, value*
    store (offset), (num_bytes), (value) bswap (num_bytes)
end macro