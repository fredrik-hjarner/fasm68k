;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; 68000 Register Definitions                                                 ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Registers are defined as famsg `elements` with their 3-bit encoding        ;;
;; embedded.                                                                  ;;
;; Using fasmg's element type allows us to:                                   ;;
;;   1. Distinguish register types (data vs address registers)                ;;
;;   2. Extract the register number (0-7) for instruction encoding            ;;
;;   3. Prevent invalid register usage via type checking                      ;;
;;                                                                            ;;
;; Example: d2 = m68k.data_reg + 010b means register d2 has encoding 2.       ;;
;; We can extract this with: d2 relativeto m68k.data_reg -> gives 2           ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Data Registers (D0-D7)                                                     ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Used for data operations, arithmetic, logic, etc.                          ;;
;; Each register gets a 3-bit encoding (000b-111b) for instruction encoding.  ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

element m68k.data_reg       ; Base element for data register type
d0? := m68k.data_reg + 000b ; Data register 0 (encoding: 000)
d1? := m68k.data_reg + 001b ; Data register 1 (encoding: 001)
d2? := m68k.data_reg + 010b ; Data register 2 (encoding: 010)
d3? := m68k.data_reg + 011b ; Data register 3 (encoding: 011)
d4? := m68k.data_reg + 100b ; Data register 4 (encoding: 100)
d5? := m68k.data_reg + 101b ; Data register 5 (encoding: 101)
d6? := m68k.data_reg + 110b ; Data register 6 (encoding: 110)
d7? := m68k.data_reg + 111b ; Data register 7 (encoding: 111)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Address Registers (A0-A7)                                                  ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Used for addressing operations, pointer arithmetic, stack operations.      ;;
;; A7 is the stack pointer (SP).                                              ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

element m68k.address_reg    ; Base element for address register type
a0? := m68k.address_reg + 000b ; Address register 0 (encoding: 000)
a1? := m68k.address_reg + 001b ; Address register 1 (encoding: 001)
a2? := m68k.address_reg + 010b ; Address register 2 (encoding: 010)
a3? := m68k.address_reg + 011b ; Address register 3 (encoding: 011)
a4? := m68k.address_reg + 100b ; Address register 4 (encoding: 100)
a5? := m68k.address_reg + 101b ; Address register 5 (encoding: 101)
a6? := m68k.address_reg + 110b ; Address register 6 (encoding: 110)
a7? := m68k.address_reg + 111b ; Address register 7 (encoding: 111)
sp? := m68k.address_reg + 111b ; Stack pointer (alias for a7)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Special Registers                                                          ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; These are unique registers that need their own element types for           ;;
;; identification in instruction parsing (e.g., move to/from sr, ccr, usp).   ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

element pc?  ; Program Counter - used in PC-relative addressing
element sr?  ; Status Register - contains condition codes and control bits
element ccr? ; Condition Code Register - lower byte of SR
element usp? ; User Stack Pointer - the stack pointer used in user mode

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; PC-Relative Decorator Element                                              ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; In PC-relative addressing modes like d(pc) or d(pc,xn), we can't calculate ;;
;; the actual displacement during operand parsing because we don't know the   ;;
;; final instruction size yet (depends on extension words).                   ;;
;;                                                                            ;;
;; Solution: Multiply the displacement 'd' by this decorator element. Later,  ;;
;; in emit_ext_words, we can detect PC-relative operands by checking if the   ;;
;; displacement is "relativeto pc_relative_decorator", then calculate the     ;;
;; actual displacement from the current PC.                                   ;;
;;                                                                            ;;
;; Example: For "jmp $1000(pc)", parse_operand stores displacement as:        ;;
;;          $1000 * pc_relative_decorator                                     ;;
;;          Later, emit_ext_words detects this and computes: $1000 - $        ;;
;;          (where $ is already at the extension word position)               ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

element pc_relative_decorator