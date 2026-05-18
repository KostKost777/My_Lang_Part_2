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

;˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜˜˜˜ |Åáàíüêî| 
pop rax
mov [rbp - 8], rax

call MyScanf

push rax

;˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜˜˜˜ |Åáàíüêî| 
pop rax
mov [rbp - 8], rax

;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Åáàíüêî|
mov rax, [rbp - 8]
push rax

call func_0
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

push 0

;˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜˜˜˜ |Åâãåí| 
pop rax
mov [rbp - 8], rax

;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Ïèäîğàññî|
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

;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Ïèäîğàññî|
mov rax, [rbp + 16]
push rax

push 1

; < 
xor rcx, rcx
pop rax
pop rbx
cmp rbx, rax
jge .skip_less_0
mov rcx, 1
.skip_less_0:
push rcx

; ||
xor rcx, rcx
pop rax
pop rbx
test rax, rax
jne .good_0
test rbx, rbx
je .bad_0
.good_0:
mov rcx, 1
.bad_0:
push rcx

pop rax
cmp rax, 0
je .end_if_0

;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Ïèäîğàññî|
mov rax, [rbp + 16]
push rax

pop rax
mov rsp, rbp
pop rbp
ret

.end_if_0:

;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Ïèäîğàññî|
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

;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Ïèäîğàññî|
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
ret

