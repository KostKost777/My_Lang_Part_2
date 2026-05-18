
global MyPrintf

MyPrintf:
    push rbp
    mov rbp, rsp
    
    sub rsp, 32          
    
    mov rax, [rbp + 16]      
    mov rbx, 10
    mov rcx, rsp
    add rcx, 31              
    mov byte [rcx], 0        
    
    xor r8, r8               
    test rax, rax
    jns .convert
    mov r8, 1
    neg rax              
    
.convert:
    dec rcx
    xor rdx, rdx
    div rbx
    add dl, '0'
    mov [rcx], dl
    test rax, rax
    jnz .convert
    
    cmp r8, 1
    jne .print
    dec rcx
    mov byte [rcx], '-'
    
.print:
    mov rsi, rcx             
    mov rdx, rsp
    add rdx, 31
    sub rdx, rcx             
    
    mov rax, 1
    mov rdi, 1
    syscall
    
    mov byte [rsp], 10
    mov rax, 1
    mov rdi, 1
    mov rsi, rsp
    mov rdx, 1
    syscall
    
    mov rsp, rbp
    pop rbp
    ret 8