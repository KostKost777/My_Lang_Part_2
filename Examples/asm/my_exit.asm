global MyExit

section .text  

MyExit:
            mov rax, 60
            mov rdi, 1     
            syscall

            db '$', '$', '$'