                section         .text

                global          _start
                extern          write_char
                extern          read_long
                extern          write_long
                extern          exit

_start:

                sub             rsp, 2 * 128 * 8
                lea             rdi, [rsp + 128 * 8]
                mov             rcx, 128
                call            read_long
                mov             rdi, rsp
                call            read_long
                lea             rsi, [rsp + 128 * 8]
                call            sub_long_long

                call            write_long

                mov             al, 0x0a
                call            write_char

                jmp             exit


; subs two long numbers
;    rdi -- address of left subband (long number)
;    rsi -- address of right subband (long number)
;    rcx -- length of long numbers in qwords
; result:
;    sub is written to rdi
sub_long_long:
                push            rdi
                push            rsi
                push            rcx

                clc
.loop:
                mov             rax, [rdi]
                lea             rdi, [rdi + 8]
                sbb             [rsi], rax
                lea             rsi, [rsi + 8]
                dec             rcx
                jnz             .loop

                pop             rcx
                pop             rsi
                pop             rdi
                xchg            rdi, rsi

                ret