global PutChar

section .text  
   
PutChar:
                push rbp
                mov rbp, rsp

                mov [char_buffer], al 
    
                mov rsi, char_buffer  
                mov rdx, 1
                mov rdi, 1
                mov rax, 1
                syscall

                mov rsp, rbp
                pop rbp

                ret

char_buffer     db 1
