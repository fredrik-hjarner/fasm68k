;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; PARSE_REG_LIST                                                             ;;
;; TODO: Currently, I first check if signle register, then check if reg range ;;
;; then I check reg group... but in reg range I also check single reg, so     ;;
;; I could probably check in reg group if reg range and in reg range if       ;;
;; single reg, then I could rename the reg group function be the top-level    ;;
;; function, if that makes any sense, i.e. instead of checking bottom-up      ;;
;; perform checks top-down, I think the code would look nicer.                ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Define variable/namespace where parse_reg_list will store its results,
; for example @reg_list1.type
; Use parse_reg_list by suffixing it will either @reg_list1 or @reg_list2 like this:
;     parse_reg_list@reg_list1 some_operand_to_parse
define @reg_list1 @reg_list1
define @reg_list2 @reg_list2

iterate reg_list, @reg_list1,@reg_list2
    namespace reg_list
        ;; Define values in the @reg_list1 and @reg_list2 namespaces. ;;;;;;;;;;;;;;;;;;;;;;

        ; populated by parse_single_register
        define single_reg_found ; TODO: Comment
        define single_reg_mask_word ; TODO: Comment
        define single_reg_mask_word_reverse ; TODO: Comment

        ; populated by parse_reg_list
        define is_reg_list ; TODO: Comment
        define mask_word ; TODO: Comment
        define mask_word_reverse ; TODO: Comment

        ; populated by parse_register_range
        define reg_range_found ; TODO: Comment
        define reg_range_mask_word ; TODO: Comment
        define reg_range_mask_word_reverse ; TODO: Comment

        ; populated by parse_reg_groups
        define reg_groups_found ; TODO: Comment
        define reg_groups_mask_word ; TODO: Comment
        define reg_groups_mask_word_reverse ; TODO: Comment

        ; Supposed to be call:ed.
        ;
        ; Side-effects:
        ;     is_reg_list
        ;         1 if operand was a register list
        ;         0 otherwise
        ;     mask_word
        ;         Stores the `register mask` for the found register
        ;         Example:
        ;           a7 would be:
        ;               1000 0000 0000 0000b or
        ;               1 shl 15
        ;     mask_word_reverse
        ;         single_reg_mask_word but reversed
        calminstruction m68k.parse_reg_list#reg_list operand*
                    local tmp1
                    local tmp2
                    local opstr
                    local tail
                    local head

                ; Init default values
                    compute is_reg_list, 0
                    compute mask_word, 0
                    compute mask_word_reverse, 0

                ; Display operand
                    ; arrange opstr, operand
                    ; stringify opstr
                    ; display 10
                    ; display opstr bappend ":" bappend 10

                ; Check if operator is a single register token
                    call m68k.parse_single_register#reg_list, operand
                    check single_reg_found = 1
                    jno register_range
                ; is_single_register_token:
                    compute is_reg_list, 1
                    ; we should also compute the mask here
                    compute mask_word, single_reg_mask_word
                    compute mask_word_reverse, single_reg_mask_word_reverse
                    jump done
                ; Check if operator is a `register range`
                register_range:
                    call m68k.parse_register_range#reg_list, operand
                    check reg_range_found = 1
                    jno reg_groups
                    compute is_reg_list, 1
                    compute mask_word, reg_range_mask_word
                    compute mask_word_reverse, reg_range_mask_word_reverse
                    jump done ; temporary. TODO: DO checks for other stuff
                reg_groups:
                    call m68k.parse_reg_groups#reg_list, operand
                    check reg_groups_found = 1
                    jno done
                    compute is_reg_list, 1
                    compute mask_word, reg_groups_mask_word
                    compute mask_word_reverse, reg_groups_mask_word_reverse
                    jump done
                done:
                    ; ;; Log stuff ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

                    ; ; is_reg_list
                    ; arrange tmp1, is_reg_list
                    ; stringify tmp1
                    ; display 'is_reg_list:                  ' bappend tmp1 bappend 10

                    ; ; mask_word
                    ; arrange tmp1, mask_word
                    ; stringify tmp1
                    ; display 'mask_word:                    ' bappend tmp1 bappend 10

                    ; ; mask_word_reverse
                    ; arrange tmp1, mask_word_reverse
                    ; stringify tmp1
                    ; display 'mask_word_reverse:            ' bappend tmp1 bappend 10
        end calminstruction

;; parse_reg_groups ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

        ; TODO: Comment
        ; What I mean with `reg_group` is `reg_group1/reg_group2/reg_group3`
        ; i.e. split with `/`
        calminstruction m68k.parse_reg_groups#reg_list? operand*
                local head
                local tail
                local dups

                ; Init default values
                compute reg_groups_found, 0
                compute reg_groups_mask_word, 0
                compute reg_groups_mask_word_reverse, 0

                arrange tail, operand
    
            next_group:
                ; display '---- next_group' bappend 10
                match head / tail, tail
                jno last_group
                ; display '---- next_group -> matched' bappend 10
                call m68k.parse_register_range#reg_list, head
                check reg_range_found = 1
                jno not_reg_range
                ; display '---- next_group -> was_reg_range' bappend 10
                ; TODO: Too long lines
                ; Check if ranges overlap
                compute dups, reg_groups_mask_word and reg_range_mask_word
                check dups <> 0
                jyes dup_error
                compute reg_groups_mask_word, reg_groups_mask_word or reg_range_mask_word
                compute reg_groups_mask_word_reverse, reg_groups_mask_word_reverse or reg_range_mask_word_reverse
                jump next_group
            last_group:
                ; display '---- last_group' bappend 10
                call m68k.parse_register_range#reg_list, tail
                check reg_range_found = 1
                jno not_reg_range
                ; display '---- last_group -> was_reg_range' bappend 10
                ; TODO: Too long lines
                ; Check if ranges overlap
                compute dups, reg_groups_mask_word and reg_range_mask_word
                check dups <> 0
                jyes dup_error
                compute reg_groups_mask_word, reg_groups_mask_word or reg_range_mask_word
                compute reg_groups_mask_word_reverse, reg_groups_mask_word_reverse or reg_range_mask_word_reverse
                
                compute reg_groups_found, 1

                exit
            not_reg_range:
                ; display '---- not_reg_range' bappend 10
                exit
            dup_error:
                err "duplicated registers in register list"
        end calminstruction


        ; movem uses a 16-bit word to store the regs it's moving and each bit
        ; represents a register.
        ; The `single_reg_mask_words` namespace contains the mask bit for each
        ; register.
        ; For some odd reason for the specific case of `-(an)` addressing mode
        ; the register mask must be encoded in reverse, so that's why I have
        ; two set of masks here.
        define single_reg_mask_words
        define single_reg_mask_words_reverse

        iterate reg, d0,d1,d2,d3,d4,d5,d6,d7,a0,a1,a2,a3,a4,a5,a6,a7
            define single_reg_mask_words.reg         1 shl (%-1)
            define single_reg_mask_words_reverse.reg 1 shl (%%-%)
        end iterate

;; parse_single_register ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

        ; TODO: Comment
        ;
        ; Side-effects:
        ;     @reg_list1.single_reg_found
        ;         1 if operand was a single register
        ;         0 otherwise
        ;
        ;     @reg_list1.single_reg_mask_word
        ;         Stores the `register mask` for the found register
        ;         Example:
        ;           a7 would be:
        ;               1000 0000 0000 0000b or
        ;               1 shl 15
        ;
        ;     @reg_list1.single_reg_mask_word_reverse
        ;         single_reg_mask_word but reversed
        ;
        calminstruction m68k.parse_single_register#reg_list operand*
                local tmp1
                local tmp2

            ; Init default values
                compute single_reg_found, 0
                compute single_reg_mask_word, 0
                compute single_reg_mask_word_reverse, 0

            ; Validate is not empty
                match , operand
                jno at_least_one_token
                err 'operand is empty'
            at_least_one_token:

            ; Check if only one token.
                match tmp1 tmp2, operand
                jyes done
                ; display '== was single token ==' bappend 10
                check operand relativeto m68k.data_reg | operand relativeto m68k.address_reg
                jno done
                ; display '== was a single register ==' bappend 10

                ; mask
                arrange single_reg_mask_word, operand
                transform single_reg_mask_word, single_reg_mask_words
                ; TODO: Is compute needed here?
                compute single_reg_mask_word, single_reg_mask_word

                ; mask reverse
                arrange single_reg_mask_word_reverse, operand
                transform single_reg_mask_word_reverse, single_reg_mask_words_reverse
                ; TODO: Is compute needed here?
                compute single_reg_mask_word_reverse, single_reg_mask_word_reverse

                ; "return true" so to speak
                compute single_reg_found, 1
            done:
                ;; Display log ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

                ; ; single_reg_found
                ; arrange tmp1, single_reg_found
                ; stringify tmp1
                ; display 'single_reg_found:             ' bappend tmp1 bappend 10

                ; ; single_reg_mask_word
                ; arrange tmp1, single_reg_mask_word
                ; stringify tmp1
                ; display 'single_reg_mask_word:         ' bappend tmp1 bappend 10

                ; ; single_reg_mask_word_reverse
                ; arrange tmp1, single_reg_mask_word_reverse
                ; stringify tmp1
                ; display 'single_reg_mask_word_reverse: ' bappend tmp1 bappend 10

        end calminstruction

;; parse_register_range ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

        ; TODO: Comment.
        ; Side-effects:
        ;     reg_range_found
        ;         TODO: comment
        ;     reg_range_mask_word
        ;         TODO: comment
        ;     reg_range_mask_word_reverse
        ;         TODO: comment
        ;
        ; Examples of register ranges:
        ;     d0-d7
        ;     a2-a4
        calminstruction m68k.parse_register_range#reg_list operand*
                local tmp1
                local tmp2
                local reg1
                local reg2

            ; Init default values
                compute reg_range_found, 0
                compute reg_range_mask_word, 0
                compute reg_range_mask_word_reverse, 0

            ; Validate is not empty
            ; TODO: I could use my util function instead here.
            ;       Or actually I should have a count_tokens util function!
                match , operand
                jno at_least_one_token
                err 'operand is empty'
            at_least_one_token:

            ; Check if only one token.
            ; TODO: I think the code does a lot of stuff twice, so see if can be
            ;       performance optimized a bit.
            ;       Addmittedly this code is a bit messy.
                ; call m68k.is_one_token, operand
                call m68k.parse_single_register#reg_list, operand
                check single_reg_found = 1
                jno check_reg_range
                compute reg_range_found, 1
                compute reg_range_mask_word, single_reg_mask_word
                compute reg_range_mask_word_reverse, single_reg_mask_word_reverse
                jump done
            check_reg_range:
                match reg1 =- reg2, operand
                jno done

                ; TODO: This might be slow.
                call m68k.parse_single_register@reg_list1, reg1
                call m68k.parse_single_register@reg_list2, reg2

                ; TODO: Too long line.
                check @reg_list1.single_reg_found = 1 & @reg_list2.single_reg_found = 1
                jno done
            ; both_tokens_are_registers_of_same_type:
                ; Validate reg1 is less than reg2 by comparing constant terms.
                check (0 scaleof reg1) < (0 scaleof reg2)
                jno done ; TODO: Should probably display error or warning.
            ; is_valid_reg_range:
                compute reg_range_found, 1

                ; Compute mask
                arrange tmp1, reg1
                transform tmp1, single_reg_mask_words
                arrange tmp2, reg2
                transform tmp2, single_reg_mask_words
                ; This formula might seem like voodoo but it works.
                ; TODO: Explain why it works maybe.
                compute reg_range_mask_word, ((tmp2 shl 1)-1) xor (tmp1 - 1)

                ; Compute reverse mask
                arrange tmp1, reg1
                transform tmp1, single_reg_mask_words_reverse
                arrange tmp2, reg2
                transform tmp2, single_reg_mask_words_reverse
                compute reg_range_mask_word_reverse, ((tmp1 shl 1)-1) xor (tmp2 - 1)
            done:
                ; ;; Display log ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

                ; ; reg_range_found
                ; arrange tmp1, reg_range_found
                ; stringify tmp1
                ; display 'reg_range_found:              ' bappend tmp1 bappend 10

                ; ; reg_range_mask_word
                ; arrange tmp1, reg_range_mask_word
                ; stringify tmp1
                ; display 'reg_range_mask_word:          ' bappend tmp1 bappend 10

                ;  ; reg_range_mask_word_reverse
                ; arrange tmp1, reg_range_mask_word_reverse
                ; stringify tmp1
                ; display 'reg_range_mask_word_reverse:  ' bappend tmp1 bappend 10

        end calminstruction

    end namespace
end iterate