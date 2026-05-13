extern MyPrintf 

extern MyScanf 

extern PutChar 

global _start  

section .text  

_start:        

push rbp
mov rbp, rsp
sub rsp, 72

push 20

;������ � ���������� |�����_�����| 
pop rax
mov [rbp - 8], rax

push 20

;������ � ���������� |�����_����| 
pop rax
mov [rbp - 16], rax

push 5

;������ � ���������� |������_������| 
pop rax
mov [rbp - 24], rax

;�������� ������ �� ���������� |�����_�����|
mov rax, [rbp - 8]
push rax

push 2

;������� ���� �����
pop rbx
pop rax
cqo
idiv rbx
push rax

;������ � ���������� |�����_�������| 
pop rax
mov [rbp - 32], rax

;�������� ������ �� ���������� |�����_����|
mov rax, [rbp - 16]
push rax

push 2

;������� ���� �����
pop rbx
pop rax
cqo
idiv rbx
push rax

;������ � ���������� |�����_������| 
pop rax
mov [rbp - 40], rax

push 0

;������ � ���������� |�������_�������| 
pop rax
mov [rbp - 48], rax

push 0

;������ � ���������� |�������_�����_�����| 
pop rax
mov [rbp - 56], rax

push 0

;������ � ���������� |�������_�����_����| 
pop rax
mov [rbp - 64], rax

.begin_while_0:
;�������� ������ �� ���������� |�������_�������|
mov rax, [rbp - 48]
push rax

;�������� ������ �� ���������� |�����_�����|
mov rax, [rbp - 8]
push rax

;�������� ������ �� ���������� |�����_����|
mov rax, [rbp - 16]
push rax

;��������� ���� �����
pop rax
pop rbx
imul rbx
push rax

; < 
xor rcx, rcx
pop rax
pop rbx
cmp rbx, rax
jge .skip_less_0
mov rcx, 1
.skip_less_0:
push rcx

pop rax
cmp rax, 0
je .end_while_0

;�������� ������ �� ���������� |�����_�������|
mov rax, [rbp - 32]
push rax

;�������� ������ �� ���������� |�������_�����_�����|
mov rax, [rbp - 56]
push rax

; �������� ���� �����
pop rax
pop rbx
sub rbx, rax
push rbx

;�������� ������ �� ���������� |�����_�������|
mov rax, [rbp - 32]
push rax

;�������� ������ �� ���������� |�������_�����_�����|
mov rax, [rbp - 56]
push rax

; �������� ���� �����
pop rax
pop rbx
sub rbx, rax
push rbx

;��������� ���� �����
pop rax
pop rbx
imul rbx
push rax

;�������� ������ �� ���������� |�����_������|
mov rax, [rbp - 40]
push rax

;�������� ������ �� ���������� |�������_�����_����|
mov rax, [rbp - 64]
push rax

; �������� ���� �����
pop rax
pop rbx
sub rbx, rax
push rbx

;�������� ������ �� ���������� |�����_������|
mov rax, [rbp - 40]
push rax

;�������� ������ �� ���������� |�������_�����_����|
mov rax, [rbp - 64]
push rax

; �������� ���� �����
pop rax
pop rbx
sub rbx, rax
push rbx

;��������� ���� �����
pop rax
pop rbx
imul rbx
push rax

; ����� ���� �����
pop rax
pop rbx
add rax, rbx
push rax

;������ � ���������� |�������_����������| 
pop rax
mov [rbp - 72], rax

;�������� ������ �� ���������� |�������_����������|
mov rax, [rbp - 72]
push rax

;�������� ������ �� ���������� |������_������|
mov rax, [rbp - 24]
push rax

;�������� ������ �� ���������� |������_������|
mov rax, [rbp - 24]
push rax

;��������� ���� �����
pop rax
pop rbx
imul rbx
push rax

; < 
xor rcx, rcx
pop rax
pop rbx
cmp rbx, rax
jge .skip_less_1
mov rcx, 1
.skip_less_1:
push rcx

pop rax
cmp rax, 0
je .skip_if_0

mov rax, 79
call PutChar

jmp .skip_else_0
.skip_if_0:
mov rax, 32
call PutChar

.skip_else_0:
;�������� ������ �� ���������� |�������_�������|
mov rax, [rbp - 48]
push rax

push 1

; ����� ���� �����
pop rax
pop rbx
add rax, rbx
push rax

;������ � ���������� |�������_�������| 
pop rax
mov [rbp - 48], rax

;�������� ������ �� ���������� |�������_�����_�����|
mov rax, [rbp - 56]
push rax

;�������� ������ �� ���������� |�����_�����|
mov rax, [rbp - 8]
push rax

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
je .skip_if_1

push 0

;������ � ���������� |�������_�����_�����| 
pop rax
mov [rbp - 56], rax

;�������� ������ �� ���������� |�������_�����_����|
mov rax, [rbp - 64]
push rax

push 1

; ����� ���� �����
pop rax
pop rbx
add rax, rbx
push rax

;������ � ���������� |�������_�����_����| 
pop rax
mov [rbp - 64], rax

mov rax, 10
call PutChar

jmp .skip_else_1
.skip_if_1:
;�������� ������ �� ���������� |�������_�����_�����|
mov rax, [rbp - 56]
push rax

push 1

; ����� ���� �����
pop rax
pop rbx
add rax, rbx
push rax

;������ � ���������� |�������_�����_�����| 
pop rax
mov [rbp - 56], rax

.skip_else_1:
jmp .begin_while_0
.end_while_0:
mov rsp, rbp
pop rbp

mov rax, 60
mov rdi, 0
syscall

