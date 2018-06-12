                section         .text

                global          main
                extern          write_char
                extern          read_long
                extern          write_long
                extern          mul_long_short
                extern          set_zero
                extern          print_string
                extern          exit

main:
                sub             rsp, 4 * 128 * 8
                lea             rdi, [rsp + 128 * 8]
                mov             rcx, 128
                call            read_long
                mov             rdi, rsp
                call            read_long

                lea             rsi, [rdi + 128 * 8]
                lea             rbp, [rsi + 128 * 8]
                lea             rdx, [rbp + 128 * 8]
                xchg            rdi, rsi
                call            mul_long_long
                call            write_long

                mov             al, 0x0a
                call            write_char

                jmp             exit



; muls two long numbers
;    rdi -- address of left long number
;    rsi -- address of right long number
;    rcx -- length of long numbers in qwords
;    rbp -- address of copy place for first long number
; result:
;    result is written to rdi (and copied in rdx)
mul_long_long:
                push            rdi
                push            rsi
                push            rbp
                push            rdx
                push            rax ; temp address
                push            rbx ; second argument for mul_long_short

                mov             r8, rcx

                ; set zero of rdx (result)
                mov             rax, rdi
                mov             rdi, rdx
                call            set_zero
                mov             rdi, rax

                clc
.loop:
                ; copy first long number to rbp
                call            copy_first_number

                ; mul current chunk of second long number(rsi) with rbp
                mov             rbx, [rsi]

                mov             rax, rdi
                mov             rdi, rbp

                push            rsi
                push            rdx
                call            mul_long_short
                pop             rdx
                pop             rsi

                mov             rdi, rax

                lea             rsi, [rsi + 8]
                
                ; add rbp to shifted result(rdx)
                mov             rax, rdi
                mov             rdi, rdx

                mov             rbx, rsi
                mov             rsi, rbp


                call            add_long_long

                mov             rsi, rbx
                mov             rdi, rax
                lea             rdx, [rdx + 8]
		
                
                dec             r8
                jnz             .loop


                pop             rbx
                pop             rax
                pop             rdx
                pop             rbp
                pop             rsi
                pop             rdi
                mov             rdi, rdx

                ret

; copies long number
;    rdi -- address of long number to copy
;    rcx -- length of long numbers in qwords
; result:
;    result is written to rbp
copy_first_number:
                push            rdi
                push            rcx
                push            rbp
                push            rax ; temp value

                clc
.loop:
                mov             rax, [rdi]
                mov             [rbp], rax

                lea             rdi, [rdi + 8]
                lea             rbp, [rbp + 8]
                dec             rcx
                jnz             .loop

                pop             rax
                pop             rbp
                pop             rcx
                pop             rdi
                ret

; adds two long number
;    rdi -- address of summand #1 (long number)
;    rsi -- address of summand #2 (long number)
;    rcx -- length of long numbers in qwords
; result:
;    sum is written to rdi
add_long_long:
                push            rdi
                push            rsi
                push            rcx
                push            rax

                clc
.loop:
                mov             rax, [rsi]
                lea             rsi, [rsi + 8]
                adc             [rdi], rax
                lea             rdi, [rdi + 8]
                dec             rcx
                jnz             .loop

                pop             rax
                pop             rcx
                pop             rsi
                pop             rdi
                ret