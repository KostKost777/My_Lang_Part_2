global _start  

buf_size equ 6 

section .text  

_start:        

;========MAIN=======

push rbp     
mov rbp, rsp 

sub rsp, 72 

push 20 ;������� ���������

;������ � ���������� |�����_�����| 
pop rax                   
mov [rbp - 8], rax       

push 20 ;������� ���������

;������ � ���������� |�����_����| 
pop rax                   
mov [rbp - 16], rax       

push 5 ;������� ���������

;������ � ���������� |������_������| 
pop rax                   
mov [rbp - 24], rax       

mov rax, [rbp - 8] ;�������� ������ �� ���������� |�����_�����|
push rax          

push 2 ;������� ���������

;������� ���� �����
pop rbx   
pop rax   
cqo   
idiv rbx   
push rax  

;������ � ���������� |�����_�������| 
pop rax                   
mov [rbp - 32], rax       

mov rax, [rbp - 16] ;�������� ������ �� ���������� |�����_����|
push rax          

push 2 ;������� ���������

;������� ���� �����
pop rbx   
pop rax   
cqo   
idiv rbx   
push rax  

;������ � ���������� |�����_������| 
pop rax                   
mov [rbp - 40], rax       

push 0 ;������� ���������

;������ � ���������� |�������_�������| 
pop rax                   
mov [rbp - 48], rax       

push 0 ;������� ���������

;������ � ���������� |�������_�����_�����| 
pop rax                   
mov [rbp - 56], rax       

push 0 ;������� ���������

;������ � ���������� |�������_�����_����| 
pop rax                   
mov [rbp - 64], rax       

.begin_while_0:       
mov rax, [rbp - 48] ;�������� ������ �� ���������� |�������_�������|
push rax          

mov rax, [rbp - 8] ;�������� ������ �� ���������� |�����_�����|
push rax          

mov rax, [rbp - 16] ;�������� ������ �� ���������� |�����_����|
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
setl cl      
push rcx     

pop rax                
cmp rax, 0             
je .end_while_0       

mov rax, [rbp - 32] ;�������� ������ �� ���������� |�����_�������|
push rax          

mov rax, [rbp - 56] ;�������� ������ �� ���������� |�������_�����_�����|
push rax          

; �������� ���� �����
pop rax      
pop rbx      
sub rbx, rax 
push rbx     

mov rax, [rbp - 32] ;�������� ������ �� ���������� |�����_�������|
push rax          

mov rax, [rbp - 56] ;�������� ������ �� ���������� |�������_�����_�����|
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

mov rax, [rbp - 40] ;�������� ������ �� ���������� |�����_������|
push rax          

mov rax, [rbp - 64] ;�������� ������ �� ���������� |�������_�����_����|
push rax          

; �������� ���� �����
pop rax      
pop rbx      
sub rbx, rax 
push rbx     

mov rax, [rbp - 40] ;�������� ������ �� ���������� |�����_������|
push rax          

mov rax, [rbp - 64] ;�������� ������ �� ���������� |�������_�����_����|
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

mov rax, [rbp - 72] ;�������� ������ �� ���������� |�������_����������|
push rax          

mov rax, [rbp - 24] ;�������� ������ �� ���������� |������_������|
push rax          

mov rax, [rbp - 24] ;�������� ������ �� ���������� |������_������|
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
setl cl      
push rcx     

pop rax                
cmp rax, 0             
je .skip_if_0         

mov rax, 'a'
call PutChar

jmp .skip_else_0      
.skip_if_0:           

mov rax, ' '
call PutChar

.skip_else_0:         

mov rax, [rbp - 48] ;�������� ������ �� ���������� |�������_�������|
push rax          

push 1 ;������� ���������

; ����� ���� �����
pop rax      
pop rbx      
add rax, rbx 
push rax     

;������ � ���������� |�������_�������| 
pop rax                   
mov [rbp - 48], rax       

mov rax, [rbp - 56] ;�������� ������ �� ���������� |�������_�����_�����|
push rax          

mov rax, [rbp - 8] ;�������� ������ �� ���������� |�����_�����|
push rax          

; ==         
xor rcx, rcx 
pop rax      
pop rbx      
cmp rbx, rax 
setz cl      
push rcx     

pop rax                
cmp rax, 0             
je .skip_if_1         

push 0 ;������� ���������

;������ � ���������� |�������_�����_�����| 
pop rax                   
mov [rbp - 56], rax       

mov rax, [rbp - 64] ;�������� ������ �� ���������� |�������_�����_����|
push rax          

push 1 ;������� ���������

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

mov rax, [rbp - 56] ;�������� ������ �� ���������� |�������_�����_�����|
push rax          

push 1 ;������� ���������

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