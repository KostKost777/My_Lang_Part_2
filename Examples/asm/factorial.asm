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

