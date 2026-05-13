global _start  

buf_size equ 6 

section .text  

_start:        

;========MAIN=======

push rbp     
mov rbp, rsp 

sub rsp, 72 

push 20 ;Запушил константу

;Запись в переменную |Евген_Шпала| 
pop rax                   
mov [rbp - 8], rax       

push 20 ;Запушил константу

;Запись в переменную |Ержан_Гном| 
pop rax                   
mov [rbp - 16], rax       

push 5 ;Запушил константу

;Запись в переменную |Серега_Радиус| 
pop rax                   
mov [rbp - 24], rax       

mov rax, [rbp - 8] ;Получили данные из переменной |Евген_Шпала|
push rax          

push 2 ;Запушил константу

;деление двух чисел
pop rbx   
pop rax   
cqo   
idiv rbx   
push rax  

;Запись в переменную |Центр_Аркадич| 
pop rax                   
mov [rbp - 32], rax       

mov rax, [rbp - 16] ;Получили данные из переменной |Ержан_Гном|
push rax          

push 2 ;Запушил константу

;деление двух чисел
pop rbx   
pop rax   
cqo   
idiv rbx   
push rax  

;Запись в переменную |Центр_Олегыч| 
pop rax                   
mov [rbp - 40], rax       

push 0 ;Запушил константу

;Запись в переменную |Счетчик_Макарыч| 
pop rax                   
mov [rbp - 48], rax       

push 0 ;Запушил константу

;Запись в переменную |Счетчик_Евген_Шпала| 
pop rax                   
mov [rbp - 56], rax       

push 0 ;Запушил константу

;Запись в переменную |Счетчик_Ержан_Гном| 
pop rax                   
mov [rbp - 64], rax       

.begin_while_0:       
mov rax, [rbp - 48] ;Получили данные из переменной |Счетчик_Макарыч|
push rax          

mov rax, [rbp - 8] ;Получили данные из переменной |Евген_Шпала|
push rax          

mov rax, [rbp - 16] ;Получили данные из переменной |Ержан_Гном|
push rax          

;умножение двух чисел
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

mov rax, [rbp - 32] ;Получили данные из переменной |Центр_Аркадич|
push rax          

mov rax, [rbp - 56] ;Получили данные из переменной |Счетчик_Евген_Шпала|
push rax          

; разность двух чисел
pop rax      
pop rbx      
sub rbx, rax 
push rbx     

mov rax, [rbp - 32] ;Получили данные из переменной |Центр_Аркадич|
push rax          

mov rax, [rbp - 56] ;Получили данные из переменной |Счетчик_Евген_Шпала|
push rax          

; разность двух чисел
pop rax      
pop rbx      
sub rbx, rax 
push rbx     

;умножение двух чисел
pop rax   
pop rbx   
imul rbx   
push rax  

mov rax, [rbp - 40] ;Получили данные из переменной |Центр_Олегыч|
push rax          

mov rax, [rbp - 64] ;Получили данные из переменной |Счетчик_Ержан_Гном|
push rax          

; разность двух чисел
pop rax      
pop rbx      
sub rbx, rax 
push rbx     

mov rax, [rbp - 40] ;Получили данные из переменной |Центр_Олегыч|
push rax          

mov rax, [rbp - 64] ;Получили данные из переменной |Счетчик_Ержан_Гном|
push rax          

; разность двух чисел
pop rax      
pop rbx      
sub rbx, rax 
push rbx     

;умножение двух чисел
pop rax   
pop rbx   
imul rbx   
push rax  

; сумма двух чисел
pop rax      
pop rbx      
add rax, rbx 
push rax     

;Запись в переменную |Андрюха_Расстояние| 
pop rax                   
mov [rbp - 72], rax       

mov rax, [rbp - 72] ;Получили данные из переменной |Андрюха_Расстояние|
push rax          

mov rax, [rbp - 24] ;Получили данные из переменной |Серега_Радиус|
push rax          

mov rax, [rbp - 24] ;Получили данные из переменной |Серега_Радиус|
push rax          

;умножение двух чисел
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

mov rax, [rbp - 48] ;Получили данные из переменной |Счетчик_Макарыч|
push rax          

push 1 ;Запушил константу

; сумма двух чисел
pop rax      
pop rbx      
add rax, rbx 
push rax     

;Запись в переменную |Счетчик_Макарыч| 
pop rax                   
mov [rbp - 48], rax       

mov rax, [rbp - 56] ;Получили данные из переменной |Счетчик_Евген_Шпала|
push rax          

mov rax, [rbp - 8] ;Получили данные из переменной |Евген_Шпала|
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

push 0 ;Запушил константу

;Запись в переменную |Счетчик_Евген_Шпала| 
pop rax                   
mov [rbp - 56], rax       

mov rax, [rbp - 64] ;Получили данные из переменной |Счетчик_Ержан_Гном|
push rax          

push 1 ;Запушил константу

; сумма двух чисел
pop rax      
pop rbx      
add rax, rbx 
push rax     

;Запись в переменную |Счетчик_Ержан_Гном| 
pop rax                   
mov [rbp - 64], rax       

mov rax, 10
call PutChar

jmp .skip_else_1      
.skip_if_1:           

mov rax, [rbp - 56] ;Получили данные из переменной |Счетчик_Евген_Шпала|
push rax          

push 1 ;Запушил константу

; сумма двух чисел
pop rax      
pop rbx      
add rax, rbx 
push rax     

;Запись в переменную |Счетчик_Евген_Шпала| 
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

PutChar:
                push rbp
                mov rbp, rsp

                mov [char_buffer], al 
    
                mov rsi, char_buffer  
                mov rdx, 1
                mov rdi, 1
                mov rax, 1
                syscall

                mov rsp, rbp
                pop rbp

                ret

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
                mov cl, [rsi]         
                cmp cl, 10     
                je .done
                
                sub cl, '0'           
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
    char_buffer     db 1
    newline         db 10