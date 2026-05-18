global MyScanf

section .text  

MyScanf:
            push rbp
            mov rbp, rsp
            
            sub rsp, 100        
            
            mov rsi, rsp       
            
            mov rax, 0          
            mov rdi, 0          
            mov rdx, 100        
            syscall
            
            mov byte [rsi + rax], 0
            
            call StrToInt

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
            cmp cl, 0           
            je .done
            cmp cl, 10          
            je .done
            cmp cl, 13          
            je .done
            
            sub cl, '0'         
            cmp cl, 9           
            ja .done            
            
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

            db '$', '$', '$'
        