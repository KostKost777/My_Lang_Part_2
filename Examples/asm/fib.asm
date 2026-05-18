extern MyPrintf 

extern MyScanf  

extern PutChar  

extern MyExit   

global _start   

section .text   

_start:         

push rbp
mov rbp, rsp
sub rsp, 8

push 0

;˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜˜˜˜ |Àðêàäè÷| 
pop rax
mov [rbp - 8], rax

call MyScanf

push rax

;˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜˜˜˜ |Àðêàäè÷| 
pop rax
mov [rbp - 8], rax

;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Àðêàäè÷|
mov rax, [rbp - 8]
push rax

call func_0
push rax

call MyPrintf


mov rsp, rbp
pop rbp

call MyExit


func_0:
push rbp
mov rbp, rsp
sub rsp, 0

;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Ïèäîðàññî|
mov rax, [rbp + 16]
push rax

push 1

; <= 
xor rcx, rcx
pop rax
pop rbx
cmp rbx, rax
jg .skip_less_or_equal_0
mov rcx, 1
.skip_less_or_equal_0:
push rcx

pop rax
cmp rax, 0
je .end_if_0

;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Ïèäîðàññî|
mov rax, [rbp + 16]
push rax

pop rax
mov rsp, rbp
pop rbp
ret 8

.end_if_0:

;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Ïèäîðàññî|
mov rax, [rbp + 16]
push rax

push 1

; ˜˜˜˜˜˜˜˜ ˜˜˜˜ ˜˜˜˜˜
pop rax
pop rbx
sub rbx, rax
push rbx

call func_0
push rax

;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Ïèäîðàññî|
mov rax, [rbp + 16]
push rax

push 2

; ˜˜˜˜˜˜˜˜ ˜˜˜˜ ˜˜˜˜˜
pop rax
pop rbx
sub rbx, rax
push rbx

call func_0
push rax

; ˜˜˜˜˜ ˜˜˜˜ ˜˜˜˜˜
pop rax
pop rbx
add rax, rbx
push rax

pop rax
mov rsp, rbp
pop rbp
ret 8

