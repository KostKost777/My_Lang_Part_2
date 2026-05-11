;========MAIN=======
global _start

buf_size equ 6

section .text

_start:

push rbp     
mov rbp, rsp 

sub rsp, 32 

push 0 ;Запушил константу

;Запись в переменную |Антоныч| 
pop rax                   
mov [rbp - 8], rax       

push 0 ;Запушил константу

;Запись в переменную |Богданыч| 
pop rax                   
mov [rbp - 16], rax       

push 0 ;Запушил константу

;Запись в переменную |Серегыч| 
pop rax                   
mov [rbp - 24], rax       

call MyScanf  

push rax  ; Возвращаемое значение в rax

;Запись в переменную |Антоныч| 
pop rax                   
mov [rbp - 8], rax       

call MyScanf  

push rax  ; Возвращаемое значение в rax

;Запись в переменную |Богданыч| 
pop rax                   
mov [rbp - 16], rax       

call MyScanf  

push rax  ; Возвращаемое значение в rax

;Запись в переменную |Серегыч| 
pop rax                   
mov [rbp - 24], rax       

mov rax, [rbp - 8] ;Получили данные из переменной |Антоныч|
push rax          

push 0 ;Запушил константу

; ==         
xor rcx, rcx 
pop rax      
pop rbx      
cmp rbx, rax 
setz cl      
push rcx     

mov rax, [rbp - 16] ;Получили данные из переменной |Богданыч|
push rax          

push 0 ;Запушил константу

; ==         
xor rcx, rcx 
pop rax      
pop rbx      
cmp rbx, rax 
setz cl      
push rcx     

; &&          
xor rcx, rcx  
pop rax       
pop rbx       
test rax, rax 
jz .false_0  
test rbx, rbx 
jz .false_0  
mov rcx, 1    
.false_0:    
push rcx      

mov rax, [rbp - 24] ;Получили данные из переменной |Серегыч|
push rax          

push 0 ;Запушил константу

; ==         
xor rcx, rcx 
pop rax      
pop rbx      
cmp rbx, rax 
setz cl      
push rcx     

; &&          
xor rcx, rcx  
pop rax       
pop rbx       
test rax, rax 
jz .false_1  
test rbx, rbx 
jz .false_1  
mov rcx, 1    
.false_1:    
push rcx      

pop rax                
cmp rax, 0             
je .end_if_0          
push -1 ;Запушил константу

call MyPrintf  

mov rsp, rbp 
pop rbp      

mov rax, 60 
mov rdi, 0  
syscall     

.end_if_0:

mov rax, [rbp - 8] ;Получили данные из переменной |Антоныч|
push rax          

push 0 ;Запушил константу

; ==         
xor rcx, rcx 
pop rax      
pop rbx      
cmp rbx, rax 
setz cl      
push rcx     

mov rax, [rbp - 16] ;Получили данные из переменной |Богданыч|
push rax          

push 0 ;Запушил константу

; ==         
xor rcx, rcx 
pop rax      
pop rbx      
cmp rbx, rax 
setz cl      
push rcx     

; &&          
xor rcx, rcx  
pop rax       
pop rbx       
test rax, rax 
jz .false_2  
test rbx, rbx 
jz .false_2  
mov rcx, 1    
.false_2:    
push rcx      

mov rax, [rbp - 24] ;Получили данные из переменной |Серегыч|
push rax          

push 0 ;Запушил константу

; !=         
xor rcx, rcx 
pop rax      
pop rbx      
cmp rbx, rax 
setnz cl     
push rcx     

; &&          
xor rcx, rcx  
pop rax       
pop rbx       
test rax, rax 
jz .false_3  
test rbx, rbx 
jz .false_3  
mov rcx, 1    
.false_3:    
push rcx      

pop rax                
cmp rax, 0             
je .end_if_1          
push 0 ;Запушил константу

call MyPrintf  

mov rsp, rbp 
pop rbp      

mov rax, 60 
mov rdi, 0  
syscall     

.end_if_1:

mov rax, [rbp - 8] ;Получили данные из переменной |Антоныч|
push rax          

push 0 ;Запушил константу

; ==         
xor rcx, rcx 
pop rax      
pop rbx      
cmp rbx, rax 
setz cl      
push rcx     

mov rax, [rbp - 16] ;Получили данные из переменной |Богданыч|
push rax          

push 0 ;Запушил константу

; !=         
xor rcx, rcx 
pop rax      
pop rbx      
cmp rbx, rax 
setnz cl     
push rcx     

; &&          
xor rcx, rcx  
pop rax       
pop rbx       
test rax, rax 
jz .false_4  
test rbx, rbx 
jz .false_4  
mov rcx, 1    
.false_4:    
push rcx      

mov rax, [rbp - 24] ;Получили данные из переменной |Серегыч|
push rax          

push 0 ;Запушил константу

; ==         
xor rcx, rcx 
pop rax      
pop rbx      
cmp rbx, rax 
setz cl      
push rcx     

; &&          
xor rcx, rcx  
pop rax       
pop rbx       
test rax, rax 
jz .false_5  
test rbx, rbx 
jz .false_5  
mov rcx, 1    
.false_5:    
push rcx      

pop rax                
cmp rax, 0             
je .end_if_2          
push 1 ;Запушил константу

call MyPrintf  

push 0 ;Запушил константу

call MyPrintf  

mov rsp, rbp 
pop rbp      

mov rax, 60 
mov rdi, 0  
syscall     

.end_if_2:

mov rax, [rbp - 8] ;Получили данные из переменной |Антоныч|
push rax          

push 0 ;Запушил константу

; !=         
xor rcx, rcx 
pop rax      
pop rbx      
cmp rbx, rax 
setnz cl     
push rcx     

mov rax, [rbp - 16] ;Получили данные из переменной |Богданыч|
push rax          

push 0 ;Запушил константу

; ==         
xor rcx, rcx 
pop rax      
pop rbx      
cmp rbx, rax 
setz cl      
push rcx     

; &&          
xor rcx, rcx  
pop rax       
pop rbx       
test rax, rax 
jz .false_6  
test rbx, rbx 
jz .false_6  
mov rcx, 1    
.false_6:    
push rcx      

mov rax, [rbp - 24] ;Получили данные из переменной |Серегыч|
push rax          

push 0 ;Запушил константу

; ==         
xor rcx, rcx 
pop rax      
pop rbx      
cmp rbx, rax 
setz cl      
push rcx     

; &&          
xor rcx, rcx  
pop rax       
pop rbx       
test rax, rax 
jz .false_7  
test rbx, rbx 
jz .false_7  
mov rcx, 1    
.false_7:    
push rcx      

pop rax                
cmp rax, 0             
je .end_if_3          
push 1 ;Запушил константу

call MyPrintf  

push 0 ;Запушил константу

call MyPrintf  

mov rsp, rbp 
pop rbp      

mov rax, 60 
mov rdi, 0  
syscall     

.end_if_3:

mov rax, [rbp - 8] ;Получили данные из переменной |Антоныч|
push rax          

push 0 ;Запушил константу

; !=         
xor rcx, rcx 
pop rax      
pop rbx      
cmp rbx, rax 
setnz cl     
push rcx     

mov rax, [rbp - 16] ;Получили данные из переменной |Богданыч|
push rax          

push 0 ;Запушил константу

; !=         
xor rcx, rcx 
pop rax      
pop rbx      
cmp rbx, rax 
setnz cl     
push rcx     

; &&          
xor rcx, rcx  
pop rax       
pop rbx       
test rax, rax 
jz .false_8  
test rbx, rbx 
jz .false_8  
mov rcx, 1    
.false_8:    
push rcx      

mov rax, [rbp - 24] ;Получили данные из переменной |Серегыч|
push rax          

push 0 ;Запушил константу

; ==         
xor rcx, rcx 
pop rax      
pop rbx      
cmp rbx, rax 
setz cl      
push rcx     

; &&          
xor rcx, rcx  
pop rax       
pop rbx       
test rax, rax 
jz .false_9  
test rbx, rbx 
jz .false_9  
mov rcx, 1    
.false_9:    
push rcx      

pop rax                
cmp rax, 0             
je .end_if_4          
push 2 ;Запушил константу

call MyPrintf  

push 0 ;Запушил константу

call MyPrintf  

push -1 ;Запушил константу

mov rax, [rbp - 16] ;Получили данные из переменной |Богданыч|
push rax          

;умножение двух чисел
pop rax   
pop rbx   
imul rbx   
push rax  

mov rax, [rbp - 8] ;Получили данные из переменной |Антоныч|
push rax          

;деление двух чисел
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

mov rax, [rbp - 8] ;Получили данные из переменной |Антоныч|
push rax          

push 0 ;Запушил константу

; !=         
xor rcx, rcx 
pop rax      
pop rbx      
cmp rbx, rax 
setnz cl     
push rcx     

mov rax, [rbp - 16] ;Получили данные из переменной |Богданыч|
push rax          

push 0 ;Запушил константу

; ==         
xor rcx, rcx 
pop rax      
pop rbx      
cmp rbx, rax 
setz cl      
push rcx     

; &&          
xor rcx, rcx  
pop rax       
pop rbx       
test rax, rax 
jz .false_10  
test rbx, rbx 
jz .false_10  
mov rcx, 1    
.false_10:    
push rcx      

mov rax, [rbp - 24] ;Получили данные из переменной |Серегыч|
push rax          

push 0 ;Запушил константу

; !=         
xor rcx, rcx 
pop rax      
pop rbx      
cmp rbx, rax 
setnz cl     
push rcx     

; &&          
xor rcx, rcx  
pop rax       
pop rbx       
test rax, rax 
jz .false_11  
test rbx, rbx 
jz .false_11  
mov rcx, 1    
.false_11:    
push rcx      

pop rax                
cmp rax, 0             
je .end_if_5          
mov rax, [rbp - 24] ;Получили данные из переменной |Серегыч|
push rax          

push 0 ;Запушил константу

; >          
xor rcx, rcx 
pop rax      
pop rbx      
cmp rbx, rax 
setg cl      
push rcx     

pop rax                
cmp rax, 0             
je .skip_if_0         

push 0 ;Запушил константу

call MyPrintf  

jmp .skip_else_0      
.skip_if_0:           

push 2 ;Запушил константу

call MyPrintf  

push -1 ;Запушил константу

mov rax, [rbp - 24] ;Получили данные из переменной |Серегыч|
push rax          

;умножение двух чисел
pop rax   
pop rbx   
imul rbx   
push rax  

mov rax, [rbp - 8] ;Получили данные из переменной |Антоныч|
push rax          

;деление двух чисел
pop rbx   
pop rax   
cqo   
idiv rbx   
push rax  

;корень перебор в цикле
pop rax               
xor rcx, rcx          
.sqvrt_0:            
push rcx              
imul rcx, rcx         
cmp  rcx, rax         
jge  .end_sqvrt_0    
pop rcx               
inc rcx               
jmp .sqvrt_0         
.end_sqvrt_0:        

call MyPrintf  

push -1 ;Запушил константу

push -1 ;Запушил константу

mov rax, [rbp - 24] ;Получили данные из переменной |Серегыч|
push rax          

;умножение двух чисел
pop rax   
pop rbx   
imul rbx   
push rax  

mov rax, [rbp - 8] ;Получили данные из переменной |Антоныч|
push rax          

;деление двух чисел
pop rbx   
pop rax   
cqo   
idiv rbx   
push rax  

;корень перебор в цикле
pop rax               
xor rcx, rcx          
.sqvrt_1:            
push rcx              
imul rcx, rcx         
cmp  rcx, rax         
jge  .end_sqvrt_1    
pop rcx               
inc rcx               
jmp .sqvrt_1         
.end_sqvrt_1:        

;умножение двух чисел
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

mov rax, [rbp - 8] ;Получили данные из переменной |Антоныч|
push rax          

push 0 ;Запушил константу

; ==         
xor rcx, rcx 
pop rax      
pop rbx      
cmp rbx, rax 
setz cl      
push rcx     

mov rax, [rbp - 16] ;Получили данные из переменной |Богданыч|
push rax          

push 0 ;Запушил константу

; !=         
xor rcx, rcx 
pop rax      
pop rbx      
cmp rbx, rax 
setnz cl     
push rcx     

; &&          
xor rcx, rcx  
pop rax       
pop rbx       
test rax, rax 
jz .false_12  
test rbx, rbx 
jz .false_12  
mov rcx, 1    
.false_12:    
push rcx      

mov rax, [rbp - 24] ;Получили данные из переменной |Серегыч|
push rax          

push 0 ;Запушил константу

; !=         
xor rcx, rcx 
pop rax      
pop rbx      
cmp rbx, rax 
setnz cl     
push rcx     

; &&          
xor rcx, rcx  
pop rax       
pop rbx       
test rax, rax 
jz .false_13  
test rbx, rbx 
jz .false_13  
mov rcx, 1    
.false_13:    
push rcx      

pop rax                
cmp rax, 0             
je .end_if_6          
push 1 ;Запушил константу

call MyPrintf  

push -1 ;Запушил константу

mov rax, [rbp - 24] ;Получили данные из переменной |Серегыч|
push rax          

;умножение двух чисел
pop rax   
pop rbx   
imul rbx   
push rax  

mov rax, [rbp - 16] ;Получили данные из переменной |Богданыч|
push rax          

;деление двух чисел
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

mov rax, [rbp - 16] ;Получили данные из переменной |Богданыч|
push rax          

mov rax, [rbp - 16] ;Получили данные из переменной |Богданыч|
push rax          

;умножение двух чисел
pop rax   
pop rbx   
imul rbx   
push rax  

push 4 ;Запушил константу

mov rax, [rbp - 8] ;Получили данные из переменной |Антоныч|
push rax          

;умножение двух чисел
pop rax   
pop rbx   
imul rbx   
push rax  

mov rax, [rbp - 24] ;Получили данные из переменной |Серегыч|
push rax          

;умножение двух чисел
pop rax   
pop rbx   
imul rbx   
push rax  

; разность двух чисел
pop rax      
pop rbx      
sub rbx, rax 
push rbx     

;Запись в переменную |Дискриминантыч| 
pop rax                   
mov [rbp - 32], rax       

mov rax, [rbp - 32] ;Получили данные из переменной |Дискриминантыч|
push rax          

push 0 ;Запушил константу

; ==         
xor rcx, rcx 
pop rax      
pop rbx      
cmp rbx, rax 
setz cl      
push rcx     

pop rax                
cmp rax, 0             
je .end_if_7          
push 1 ;Запушил константу

call MyPrintf  

push -1 ;Запушил константу

mov rax, [rbp - 16] ;Получили данные из переменной |Богданыч|
push rax          

;умножение двух чисел
pop rax   
pop rbx   
imul rbx   
push rax  

push 2 ;Запушил константу

;деление двух чисел
pop rbx   
pop rax   
cqo   
idiv rbx   
push rax  

mov rax, [rbp - 8] ;Получили данные из переменной |Антоныч|
push rax          

;деление двух чисел
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

mov rax, [rbp - 32] ;Получили данные из переменной |Дискриминантыч|
push rax          

push 0 ;Запушил константу

; <          
xor rcx, rcx 
pop rax      
pop rbx      
cmp rbx, rax 
setl cl      
push rcx     

pop rax                
cmp rax, 0             
je .skip_if_1         

push 0 ;Запушил константу

call MyPrintf  

jmp .skip_else_1      
.skip_if_1:           

push 2 ;Запушил константу

call MyPrintf  

push -1 ;Запушил константу

mov rax, [rbp - 16] ;Получили данные из переменной |Богданыч|
push rax          

;умножение двух чисел
pop rax   
pop rbx   
imul rbx   
push rax  

mov rax, [rbp - 32] ;Получили данные из переменной |Дискриминантыч|
push rax          

;корень перебор в цикле
pop rax               
xor rcx, rcx          
.sqvrt_2:            
push rcx              
imul rcx, rcx         
cmp  rcx, rax         
jge  .end_sqvrt_2    
pop rcx               
inc rcx               
jmp .sqvrt_2         
.end_sqvrt_2:        

; разность двух чисел
pop rax      
pop rbx      
sub rbx, rax 
push rbx     

push 2 ;Запушил константу

;деление двух чисел
pop rbx   
pop rax   
cqo   
idiv rbx   
push rax  

mov rax, [rbp - 8] ;Получили данные из переменной |Антоныч|
push rax          

;деление двух чисел
pop rbx   
pop rax   
cqo   
idiv rbx   
push rax  

call MyPrintf  

push -1 ;Запушил константу

mov rax, [rbp - 16] ;Получили данные из переменной |Богданыч|
push rax          

;умножение двух чисел
pop rax   
pop rbx   
imul rbx   
push rax  

mov rax, [rbp - 32] ;Получили данные из переменной |Дискриминантыч|
push rax          

;корень перебор в цикле
pop rax               
xor rcx, rcx          
.sqvrt_3:            
push rcx              
imul rcx, rcx         
cmp  rcx, rax         
jge  .end_sqvrt_3    
pop rcx               
inc rcx               
jmp .sqvrt_3         
.end_sqvrt_3:        

; сумма двух чисел
pop rax      
pop rbx      
add rax, rbx 
push rax     

push 2 ;Запушил константу

;деление двух чисел
pop rbx   
pop rax   
cqo   
idiv rbx   
push rax  

mov rax, [rbp - 8] ;Получили данные из переменной |Антоныч|
push rax          

;деление двух чисел
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