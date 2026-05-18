extern MyPrintf 

extern MyScanf 

extern PutChar 

global _start  

section .text  

_start:        

push rbp
mov rbp, rsp
sub rsp, 8

push 0

;   |Ετθμϋχ| 
pop rax
mov [rbp - 8], rax

call MyScanf

push rax

;   |Ετθμϋχ| 
pop rax
mov [rbp - 8], rax

;    |Ετθμϋχ|
mov rax, [rbp - 8]
push rax

call .func_0
push rax

call MyPrintf


mov rsp, rbp
pop rbp

mov rax, 60
mov rdi, 0
syscall

func_0:
push rbp
mov rbp, rsp
sub rsp, 8

;    |Ρεπεγϋχ|
mov rax, [rbp + 16]
push rax

push 1

; == 
xor rcx, rcx
pop rax
pop rbx
cmp rbx, rax
jne .not_equal_0
mov rcx, 1
.not_equal_0:
push rcx

pop rax
cmp rax, 0
je .skip_if_0

push 1

pop rax
mov rsp, rbp
pop rbp
ret

jmp .skip_else_0
.skip_if_0:

;    |Ρεπεγϋχ|
mov rax, [rbp + 16]
push rax

push 1

;   
pop rax
pop rbx
sub rbx, rax
push rbx

call .func_0
push rax

;   |Ξλεγϋχ| 
pop rax
mov [rbp - 8], rax

;    |Ξλεγϋχ|
mov rax, [rbp - 8]
push rax

;    |Ρεπεγϋχ|
mov rax, [rbp + 16]
push rax

;  
pop rax
pop rbx
imul rbx
push rax

pop rax
mov rsp, rbp
pop rbp
ret

.skip_else_0:

