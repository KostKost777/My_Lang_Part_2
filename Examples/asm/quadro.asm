extern MyPrintf 

extern MyScanf 

extern PutChar 

global _start  

section .text  

_start:        

push rbp
mov rbp, rsp
sub rsp, 32

push 0

;˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜˜˜˜ |Àíòîíû÷| 
pop rax
mov [rbp - 8], rax

push 0

;˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜˜˜˜ |Áîãäàíû÷| 
pop rax
mov [rbp - 16], rax

push 0

;˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜˜˜˜ |Ñåðåãû÷| 
pop rax
mov [rbp - 24], rax

call MyScanf  
push rax

;˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜˜˜˜ |Àíòîíû÷| 
pop rax
mov [rbp - 8], rax

call MyScanf  
push rax

;˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜˜˜˜ |Áîãäàíû÷| 
pop rax
mov [rbp - 16], rax

call MyScanf  
push rax

;˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜˜˜˜ |Ñåðåãû÷| 
pop rax
mov [rbp - 24], rax

;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Àíòîíû÷|
mov rax, [rbp - 8]
push rax

push 0

; == 
xor rcx, rcx
pop rax
pop rbx
cmp rbx, rax
jne .not_equal_0
mov rcx, 1
.not_equal_0:
push rcx

;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Áîãäàíû÷|
mov rax, [rbp - 16]
push rax

push 0

; == 
xor rcx, rcx
pop rax
pop rbx
cmp rbx, rax
jne .not_equal_1
mov rcx, 1
.not_equal_1:
push rcx

; &&
xor rcx, rcx
pop rax
pop rbx
test rax, rax
je .bad_0
test rbx, rbx
je .bad_0
mov rcx, 1
.bad_0:
push rcx

;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Ñåðåãû÷|
mov rax, [rbp - 24]
push rax

push 0

; == 
xor rcx, rcx
pop rax
pop rbx
cmp rbx, rax
jne .not_equal_2
mov rcx, 1
.not_equal_2:
push rcx

; &&
xor rcx, rcx
pop rax
pop rbx
test rax, rax
je .bad_1
test rbx, rbx
je .bad_1
mov rcx, 1
.bad_1:
push rcx

pop rax
cmp rax, 0
je .end_if_0

push -1

call MyPrintf  


mov rsp, rbp
pop rbp

mov rax, 60
mov rdi, 0
syscall

.end_if_0:
;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Àíòîíû÷|
mov rax, [rbp - 8]
push rax

push 0

; == 
xor rcx, rcx
pop rax
pop rbx
cmp rbx, rax
jne .not_equal_3
mov rcx, 1
.not_equal_3:
push rcx

;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Áîãäàíû÷|
mov rax, [rbp - 16]
push rax

push 0

; == 
xor rcx, rcx
pop rax
pop rbx
cmp rbx, rax
jne .not_equal_4
mov rcx, 1
.not_equal_4:
push rcx

; &&
xor rcx, rcx
pop rax
pop rbx
test rax, rax
je .bad_2
test rbx, rbx
je .bad_2
mov rcx, 1
.bad_2:
push rcx

;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Ñåðåãû÷|
mov rax, [rbp - 24]
push rax

push 0

; != 
xor rcx, rcx
pop rax
pop rbx
cmp rbx, rax
je .equal_0
mov rcx, 1
.equal_0:
push rcx

; &&
xor rcx, rcx
pop rax
pop rbx
test rax, rax
je .bad_3
test rbx, rbx
je .bad_3
mov rcx, 1
.bad_3:
push rcx

pop rax
cmp rax, 0
je .end_if_1

push 0

call MyPrintf  


mov rsp, rbp
pop rbp

mov rax, 60
mov rdi, 0
syscall

.end_if_1:
;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Àíòîíû÷|
mov rax, [rbp - 8]
push rax

push 0

; == 
xor rcx, rcx
pop rax
pop rbx
cmp rbx, rax
jne .not_equal_5
mov rcx, 1
.not_equal_5:
push rcx

;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Áîãäàíû÷|
mov rax, [rbp - 16]
push rax

push 0

; != 
xor rcx, rcx
pop rax
pop rbx
cmp rbx, rax
je .equal_1
mov rcx, 1
.equal_1:
push rcx

; &&
xor rcx, rcx
pop rax
pop rbx
test rax, rax
je .bad_4
test rbx, rbx
je .bad_4
mov rcx, 1
.bad_4:
push rcx

;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Ñåðåãû÷|
mov rax, [rbp - 24]
push rax

push 0

; == 
xor rcx, rcx
pop rax
pop rbx
cmp rbx, rax
jne .not_equal_6
mov rcx, 1
.not_equal_6:
push rcx

; &&
xor rcx, rcx
pop rax
pop rbx
test rax, rax
je .bad_5
test rbx, rbx
je .bad_5
mov rcx, 1
.bad_5:
push rcx

pop rax
cmp rax, 0
je .end_if_2

push 1

call MyPrintf  


push 0

call MyPrintf  


mov rsp, rbp
pop rbp

mov rax, 60
mov rdi, 0
syscall

.end_if_2:
;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Àíòîíû÷|
mov rax, [rbp - 8]
push rax

push 0

; != 
xor rcx, rcx
pop rax
pop rbx
cmp rbx, rax
je .equal_2
mov rcx, 1
.equal_2:
push rcx

;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Áîãäàíû÷|
mov rax, [rbp - 16]
push rax

push 0

; == 
xor rcx, rcx
pop rax
pop rbx
cmp rbx, rax
jne .not_equal_7
mov rcx, 1
.not_equal_7:
push rcx

; &&
xor rcx, rcx
pop rax
pop rbx
test rax, rax
je .bad_6
test rbx, rbx
je .bad_6
mov rcx, 1
.bad_6:
push rcx

;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Ñåðåãû÷|
mov rax, [rbp - 24]
push rax

push 0

; == 
xor rcx, rcx
pop rax
pop rbx
cmp rbx, rax
jne .not_equal_8
mov rcx, 1
.not_equal_8:
push rcx

; &&
xor rcx, rcx
pop rax
pop rbx
test rax, rax
je .bad_7
test rbx, rbx
je .bad_7
mov rcx, 1
.bad_7:
push rcx

pop rax
cmp rax, 0
je .end_if_3

push 1

call MyPrintf  


push 0

call MyPrintf  


mov rsp, rbp
pop rbp

mov rax, 60
mov rdi, 0
syscall

.end_if_3:
;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Àíòîíû÷|
mov rax, [rbp - 8]
push rax

push 0

; != 
xor rcx, rcx
pop rax
pop rbx
cmp rbx, rax
je .equal_3
mov rcx, 1
.equal_3:
push rcx

;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Áîãäàíû÷|
mov rax, [rbp - 16]
push rax

push 0

; != 
xor rcx, rcx
pop rax
pop rbx
cmp rbx, rax
je .equal_4
mov rcx, 1
.equal_4:
push rcx

; &&
xor rcx, rcx
pop rax
pop rbx
test rax, rax
je .bad_8
test rbx, rbx
je .bad_8
mov rcx, 1
.bad_8:
push rcx

;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Ñåðåãû÷|
mov rax, [rbp - 24]
push rax

push 0

; == 
xor rcx, rcx
pop rax
pop rbx
cmp rbx, rax
jne .not_equal_9
mov rcx, 1
.not_equal_9:
push rcx

; &&
xor rcx, rcx
pop rax
pop rbx
test rax, rax
je .bad_9
test rbx, rbx
je .bad_9
mov rcx, 1
.bad_9:
push rcx

pop rax
cmp rax, 0
je .end_if_4

push 2

call MyPrintf  


push 0

call MyPrintf  


push -1

;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Áîãäàíû÷|
mov rax, [rbp - 16]
push rax

;˜˜˜˜˜˜˜˜˜ ˜˜˜˜ ˜˜˜˜˜
pop rax
pop rbx
imul rbx
push rax

;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Àíòîíû÷|
mov rax, [rbp - 8]
push rax

;˜˜˜˜˜˜˜ ˜˜˜˜ ˜˜˜˜˜
pop rbx
pop rax
cqo
idiv rbx
push rax

call MyPrintf  


mov rsp, rbp
pop rbp

mov rax, 60
mov rdi, 0
syscall

.end_if_4:
;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Àíòîíû÷|
mov rax, [rbp - 8]
push rax

push 0

; != 
xor rcx, rcx
pop rax
pop rbx
cmp rbx, rax
je .equal_5
mov rcx, 1
.equal_5:
push rcx

;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Áîãäàíû÷|
mov rax, [rbp - 16]
push rax

push 0

; == 
xor rcx, rcx
pop rax
pop rbx
cmp rbx, rax
jne .not_equal_10
mov rcx, 1
.not_equal_10:
push rcx

; &&
xor rcx, rcx
pop rax
pop rbx
test rax, rax
je .bad_10
test rbx, rbx
je .bad_10
mov rcx, 1
.bad_10:
push rcx

;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Ñåðåãû÷|
mov rax, [rbp - 24]
push rax

push 0

; != 
xor rcx, rcx
pop rax
pop rbx
cmp rbx, rax
je .equal_6
mov rcx, 1
.equal_6:
push rcx

; &&
xor rcx, rcx
pop rax
pop rbx
test rax, rax
je .bad_11
test rbx, rbx
je .bad_11
mov rcx, 1
.bad_11:
push rcx

pop rax
cmp rax, 0
je .end_if_5

;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Ñåðåãû÷|
mov rax, [rbp - 24]
push rax

push 0

; > 
xor rcx, rcx
pop rax
pop rbx
cmp rbx, rax
jle .skip_big_0
mov rcx, 1
.skip_big_0:
push rcx

pop rax
cmp rax, 0
je .skip_if_0

push 0

call MyPrintf  


jmp .skip_else_0
.skip_if_0:
push 2

call MyPrintf  


push -1

;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Ñåðåãû÷|
mov rax, [rbp - 24]
push rax

;˜˜˜˜˜˜˜˜˜ ˜˜˜˜ ˜˜˜˜˜
pop rax
pop rbx
imul rbx
push rax

;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Àíòîíû÷|
mov rax, [rbp - 8]
push rax

;˜˜˜˜˜˜˜ ˜˜˜˜ ˜˜˜˜˜
pop rbx
pop rax
cqo
idiv rbx
push rax

;˜˜˜˜˜˜ ˜˜˜˜˜˜˜ ˜ ˜˜˜˜˜
pop rax
xor rcx, rcx
.sqvrt_0: 
push rcx
imul rcx, rcx
cmp rcx, rax
jge .end_sqvrt_0
pop rcx
inc rcx
jmp .sqvrt_0
.end_sqvrt_0: 

call MyPrintf  


push -1

push -1

;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Ñåðåãû÷|
mov rax, [rbp - 24]
push rax

;˜˜˜˜˜˜˜˜˜ ˜˜˜˜ ˜˜˜˜˜
pop rax
pop rbx
imul rbx
push rax

;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Àíòîíû÷|
mov rax, [rbp - 8]
push rax

;˜˜˜˜˜˜˜ ˜˜˜˜ ˜˜˜˜˜
pop rbx
pop rax
cqo
idiv rbx
push rax

;˜˜˜˜˜˜ ˜˜˜˜˜˜˜ ˜ ˜˜˜˜˜
pop rax
xor rcx, rcx
.sqvrt_1: 
push rcx
imul rcx, rcx
cmp rcx, rax
jge .end_sqvrt_1
pop rcx
inc rcx
jmp .sqvrt_1
.end_sqvrt_1: 

;˜˜˜˜˜˜˜˜˜ ˜˜˜˜ ˜˜˜˜˜
pop rax
pop rbx
imul rbx
push rax

call MyPrintf  


.skip_else_0:
mov rsp, rbp
pop rbp

mov rax, 60
mov rdi, 0
syscall

.end_if_5:
;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Àíòîíû÷|
mov rax, [rbp - 8]
push rax

push 0

; == 
xor rcx, rcx
pop rax
pop rbx
cmp rbx, rax
jne .not_equal_11
mov rcx, 1
.not_equal_11:
push rcx

;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Áîãäàíû÷|
mov rax, [rbp - 16]
push rax

push 0

; != 
xor rcx, rcx
pop rax
pop rbx
cmp rbx, rax
je .equal_7
mov rcx, 1
.equal_7:
push rcx

; &&
xor rcx, rcx
pop rax
pop rbx
test rax, rax
je .bad_12
test rbx, rbx
je .bad_12
mov rcx, 1
.bad_12:
push rcx

;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Ñåðåãû÷|
mov rax, [rbp - 24]
push rax

push 0

; != 
xor rcx, rcx
pop rax
pop rbx
cmp rbx, rax
je .equal_8
mov rcx, 1
.equal_8:
push rcx

; &&
xor rcx, rcx
pop rax
pop rbx
test rax, rax
je .bad_13
test rbx, rbx
je .bad_13
mov rcx, 1
.bad_13:
push rcx

pop rax
cmp rax, 0
je .end_if_6

push 1

call MyPrintf  


push -1

;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Ñåðåãû÷|
mov rax, [rbp - 24]
push rax

;˜˜˜˜˜˜˜˜˜ ˜˜˜˜ ˜˜˜˜˜
pop rax
pop rbx
imul rbx
push rax

;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Áîãäàíû÷|
mov rax, [rbp - 16]
push rax

;˜˜˜˜˜˜˜ ˜˜˜˜ ˜˜˜˜˜
pop rbx
pop rax
cqo
idiv rbx
push rax

call MyPrintf  


mov rsp, rbp
pop rbp

mov rax, 60
mov rdi, 0
syscall

.end_if_6:
;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Áîãäàíû÷|
mov rax, [rbp - 16]
push rax

;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Áîãäàíû÷|
mov rax, [rbp - 16]
push rax

;˜˜˜˜˜˜˜˜˜ ˜˜˜˜ ˜˜˜˜˜
pop rax
pop rbx
imul rbx
push rax

push 4

;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Àíòîíû÷|
mov rax, [rbp - 8]
push rax

;˜˜˜˜˜˜˜˜˜ ˜˜˜˜ ˜˜˜˜˜
pop rax
pop rbx
imul rbx
push rax

;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Ñåðåãû÷|
mov rax, [rbp - 24]
push rax

;˜˜˜˜˜˜˜˜˜ ˜˜˜˜ ˜˜˜˜˜
pop rax
pop rbx
imul rbx
push rax

; ˜˜˜˜˜˜˜˜ ˜˜˜˜ ˜˜˜˜˜
pop rax
pop rbx
sub rbx, rax
push rbx

;˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜˜˜˜ |Äèñêðèìèíàíòû÷| 
pop rax
mov [rbp - 32], rax

;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Äèñêðèìèíàíòû÷|
mov rax, [rbp - 32]
push rax

push 0

; == 
xor rcx, rcx
pop rax
pop rbx
cmp rbx, rax
jne .not_equal_12
mov rcx, 1
.not_equal_12:
push rcx

pop rax
cmp rax, 0
je .end_if_7

push 1

call MyPrintf  


push -1

;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Áîãäàíû÷|
mov rax, [rbp - 16]
push rax

;˜˜˜˜˜˜˜˜˜ ˜˜˜˜ ˜˜˜˜˜
pop rax
pop rbx
imul rbx
push rax

push 2

;˜˜˜˜˜˜˜ ˜˜˜˜ ˜˜˜˜˜
pop rbx
pop rax
cqo
idiv rbx
push rax

;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Àíòîíû÷|
mov rax, [rbp - 8]
push rax

;˜˜˜˜˜˜˜ ˜˜˜˜ ˜˜˜˜˜
pop rbx
pop rax
cqo
idiv rbx
push rax

call MyPrintf  


mov rsp, rbp
pop rbp

mov rax, 60
mov rdi, 0
syscall

.end_if_7:
;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Äèñêðèìèíàíòû÷|
mov rax, [rbp - 32]
push rax

push 0

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
je .skip_if_1

push 0

call MyPrintf  


jmp .skip_else_1
.skip_if_1:
push 2

call MyPrintf  


push -1

;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Áîãäàíû÷|
mov rax, [rbp - 16]
push rax

;˜˜˜˜˜˜˜˜˜ ˜˜˜˜ ˜˜˜˜˜
pop rax
pop rbx
imul rbx
push rax

;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Äèñêðèìèíàíòû÷|
mov rax, [rbp - 32]
push rax

;˜˜˜˜˜˜ ˜˜˜˜˜˜˜ ˜ ˜˜˜˜˜
pop rax
xor rcx, rcx
.sqvrt_2: 
push rcx
imul rcx, rcx
cmp rcx, rax
jge .end_sqvrt_2
pop rcx
inc rcx
jmp .sqvrt_2
.end_sqvrt_2: 

; ˜˜˜˜˜˜˜˜ ˜˜˜˜ ˜˜˜˜˜
pop rax
pop rbx
sub rbx, rax
push rbx

push 2

;˜˜˜˜˜˜˜ ˜˜˜˜ ˜˜˜˜˜
pop rbx
pop rax
cqo
idiv rbx
push rax

;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Àíòîíû÷|
mov rax, [rbp - 8]
push rax

;˜˜˜˜˜˜˜ ˜˜˜˜ ˜˜˜˜˜
pop rbx
pop rax
cqo
idiv rbx
push rax

call MyPrintf  


push -1

;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Áîãäàíû÷|
mov rax, [rbp - 16]
push rax

;˜˜˜˜˜˜˜˜˜ ˜˜˜˜ ˜˜˜˜˜
pop rax
pop rbx
imul rbx
push rax

;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Äèñêðèìèíàíòû÷|
mov rax, [rbp - 32]
push rax

;˜˜˜˜˜˜ ˜˜˜˜˜˜˜ ˜ ˜˜˜˜˜
pop rax
xor rcx, rcx
.sqvrt_3: 
push rcx
imul rcx, rcx
cmp rcx, rax
jge .end_sqvrt_3
pop rcx
inc rcx
jmp .sqvrt_3
.end_sqvrt_3: 

; ˜˜˜˜˜ ˜˜˜˜ ˜˜˜˜˜
pop rax
pop rbx
add rax, rbx
push rax

push 2

;˜˜˜˜˜˜˜ ˜˜˜˜ ˜˜˜˜˜
pop rbx
pop rax
cqo
idiv rbx
push rax

;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ |Àíòîíû÷|
mov rax, [rbp - 8]
push rax

;˜˜˜˜˜˜˜ ˜˜˜˜ ˜˜˜˜˜
pop rbx
pop rax
cqo
idiv rbx
push rax

call MyPrintf  


.skip_else_1:
mov rsp, rbp
pop rbp

mov rax, 60
mov rdi, 0
syscall

