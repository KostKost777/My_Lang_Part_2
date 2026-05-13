global _start  

buf_size equ 6 

section .text  

_start:        

;========MAIN=======

push rbp     
mov rbp, rsp 

sub rsp, 8 

push 0 ;Запушил константу

;Запись в переменную |Ефимыч| 
pop rax                   
mov [rbp - 8], rax       

call MyScanf  
push rax  ; Возвращаемое значение в rax

;Запись в переменную |Ефимыч| 
pop rax                   
mov [rbp - 8], rax       

mov rax, [rbp - 8] ;Получили данные из переменной |Ефимыч|
push rax          

call .func_0     
push rax  ; Возвращаемое значение в rax

call MyPrintf  

mov rsp, rbp 
pop rbp      

mov rax, 60 
mov rdi, 0  
syscall     

.func_0:         

push rbp     
mov rbp, rsp 
sub rsp, 8 

mov rax, [rbp + 16] ;Получили данные из аргумента |Серегыч|
push rax          

push 1 ;Запушил константу

; ==         
xor rcx, rcx 
pop rax      
pop rbx      
cmp rbx, rax 
setz cl      
push rcx     

pop rax                
cmp rax, 0             
je .skip_if_0         

push 1 ;Запушил константу

pop rax      
mov rsp, rbp 
pop rbp      

ret          

jmp .skip_else_0      
.skip_if_0:           

mov rax, [rbp + 16] ;Получили данные из аргумента |Серегыч|
push rax          

push 1 ;Запушил константу

; разность двух чисел
pop rax      
pop rbx      
sub rbx, rax 
push rbx     

call .func_0     
push rax  ; Возвращаемое значение в rax

;Запись в переменную |Олегыч| 
pop rax                   
mov [rbp - 8], rax       

mov rax, [rbp - 8] ;Получили данные из переменной |Олегыч|
push rax          

mov rax, [rbp + 16] ;Получили данные из аргумента |Серегыч|
push rax          

;умножение двух чисел
pop rax   
pop rbx   
imul rbx   
push rax  

pop rax      
mov rsp, rbp 
pop rbp      

ret          

.skip_else_0:



MyScanf:
                push rbp
                mov rbp, rsp

                push rsi

                mov rax, 0            
                mov rdi, 0            
                mov rsi, scanf_buffer       
                mov rdx, buf_size
                syscall

                mov rsi, scanf_buffer
                call StrToInt

                pop rsi

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
                mov cl, [rsi]         ; читаем байт
                cmp cl, 10     ; конец строки?
                je .done
                
                sub cl, '0'           ; ASCII -> число
                mul rbx               ; rax = rax * 10
                add rax, rcx          ; rax = rax + digit
                
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

;=========== ФУНКЦИЯ ВЫВОДА ЧИСЛА ===========

MyPrintf:
                push rbp
                mov rbp, rsp

                xor r8, r8
                xor rcx, rcx
                mov rbx, 10
                mov rax, [rbp + 16]
                mov rsi, printf_buffer

                test rax, rax
                jns .parse
                mov r8, 1
                neg rax

.parse:
                xor rdx, rdx
                idiv rbx

                add rdx, '0'

                mov [rsi], dl
                inc rcx
                
                test rax, rax
                jz .done

                inc rsi

                jmp .parse

.done:
                cmp r8, 1
                jne .print
                inc rsi
                inc rcx
                mov byte [rsi], '-'

.print:
                push rcx

                mov rax, 1       
                mov rdi, 1        
                mov rdx, 1 
                syscall

                pop rcx

                dec rsi
                loop .print

                mov rax, 1       
                mov rdi, 1  
                mov rsi, newline     
                mov rdx, 1 
                syscall

                mov rsp, rbp
                pop rbp

                ret 8

section .data
    scanf_buffer    db buf_size dup(0)
    printf_buffer   db buf_size dup(0)
    newline         db 10