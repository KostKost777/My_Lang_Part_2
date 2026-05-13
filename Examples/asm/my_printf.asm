global MyPrintf
buf_size equ 6
section .text  

MyPrintf:
                push rbp
                mov rbp, rsp

                xor r8, r8
                xor rcx, rcx
                mov rbx, 10
                mov rax, [rbp + 16]
                mov rsi, printf_buffer

                test rax, rax
                jns .parse
                mov r8, 1
                neg rax

.parse:
                xor rdx, rdx
                idiv rbx

                add rdx, '0'

                mov [rsi], dl
                inc rcx
                
                test rax, rax
                jz .done

                inc rsi

                jmp .parse

.done:
                cmp r8, 1
                jne .print
                inc rsi
                inc rcx
                mov byte [rsi], '-'

.print:
                push rcx

                mov rax, 1       
                mov rdi, 1        
                mov rdx, 1 
                syscall

                pop rcx

                dec rsi
                loop .print

                mov rax, 1       
                mov rdi, 1  
                mov rsi, newline     
                mov rdx, 1 
                syscall

                mov rsp, rbp
                pop rbp

                ret 8
section .data
    printf_buffer   db buf_size dup(0)
    newline         db 10