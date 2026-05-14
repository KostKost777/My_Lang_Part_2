global PutChar

section .text

PutChar:
    push rbp
    mov rbp, rsp
    
    sub rsp, 8               
    mov [rsp], al            
    
    mov rax, 1
    mov rdi, 1
    mov rsi, rsp
    mov rdx, 1
    syscall
    
    mov rsp, rbp
    pop rbp
    ret