global MyScanf

buf_size equ 6

section .text  

MyScanf:
                push rbp
                mov rbp, rsp

                push rsi

                mov rax, 0            
                mov rdi, 0            
                mov rsi, scanf_buffer       
                mov rdx, buf_size
                syscall

                mov rsi, scanf_buffer
                call StrToInt

                pop rsi

                mov rsp, rbp
                pop rbp
                ret

StrToInt:
                push rbp
                mov rbp, rsp

                xor rax, rax
                xor r8, r8
                mov rbx, 10

                cmp byte [rsi], '-'
                jne .parse
                mov r8, 1
                inc rsi 

.parse:
                xor rcx, rcx
                mov cl, [rsi]         
                cmp cl, 10     
                je .done
                
                sub cl, '0'           
                mul rbx               
                add rax, rcx          
                
                inc rsi
                jmp .parse

.done:
                cmp r8, 1
                jne .positive
                neg rax

.positive:
                mov rsp, rbp
                pop rbp
                ret

section .data

scanf_buffer    db buf_size dup(0)
        