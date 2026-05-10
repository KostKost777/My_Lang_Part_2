========MAIN=======

push rbp     
mov rbp, rsp 

sub rsp, 32 

push 0 ;Запушил константу

pop rax ;Запись в переменную |Антоныч| 
mov [rbp - 0], rax 

push 0 ;Запушил константу

pop rax ;Запись в переменную |Богданыч| 
mov [rbp - 8], rax 

push 0 ;Запушил константу

pop rax ;Запись в переменную |Серегыч| 
mov [rbp - 16], rax 

call .my_scanf  

pop rax ;Запись в переменную |Антоныч| 
mov [rbp - 0], rax 

call .my_scanf  

pop rax ;Запись в переменную |Богданыч| 
mov [rbp - 8], rax 

call .my_scanf  

pop rax ;Запись в переменную |Серегыч| 
mov [rbp - 16], rax 

mov rax, [rbp - 0] ;Получили данные из переменной |Антоныч|
push rax          

push 0 ;Запушил константу

; ==         
xor rcx, rcx 
pop rax      
pop rbx      
cmp rax, rbx 
setz cl      
push rcx     

mov rax, [rbp - 8] ;Получили данные из переменной |Богданыч|
push rax          

push 0 ;Запушил константу

; ==         
xor rcx, rcx 
pop rax      
pop rbx      
cmp rax, rbx 
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

mov rax, [rbp - 16] ;Получили данные из переменной |Серегыч|
push rax          

push 0 ;Запушил константу

; ==         
xor rcx, rcx 
pop rax      
pop rbx      
cmp rax, rbx 
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
je :end_if_0          
push -1 ;Запушил константу

call .my_printf  

mov rax, 60 
mov rdi, 0  
syscall     

:end_if_0

mov rax, [rbp - 0] ;Получили данные из переменной |Антоныч|
push rax          

push 0 ;Запушил константу

; ==         
xor rcx, rcx 
pop rax      
pop rbx      
cmp rax, rbx 
setz cl      
push rcx     

mov rax, [rbp - 8] ;Получили данные из переменной |Богданыч|
push rax          

push 0 ;Запушил константу

; ==         
xor rcx, rcx 
pop rax      
pop rbx      
cmp rax, rbx 
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

mov rax, [rbp - 16] ;Получили данные из переменной |Серегыч|
push rax          

push 0 ;Запушил константу

; !=         
xor rcx      
pop rax      
pop rbx      
cmp rax, rbx 
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
je :end_if_1          
push 0 ;Запушил константу

call .my_printf  

mov rax, 60 
mov rdi, 0  
syscall     

:end_if_1

mov rax, [rbp - 0] ;Получили данные из переменной |Антоныч|
push rax          

push 0 ;Запушил константу

; ==         
xor rcx, rcx 
pop rax      
pop rbx      
cmp rax, rbx 
setz cl      
push rcx     

mov rax, [rbp - 8] ;Получили данные из переменной |Богданыч|
push rax          

push 0 ;Запушил константу

; !=         
xor rcx      
pop rax      
pop rbx      
cmp rax, rbx 
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

mov rax, [rbp - 16] ;Получили данные из переменной |Серегыч|
push rax          

push 0 ;Запушил константу

; !=         
xor rcx      
pop rax      
pop rbx      
cmp rax, rbx 
setnz cl     
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
je :end_if_2          
push 1 ;Запушил константу

call .my_printf  

push -1 ;Запушил константу

mov rax, [rbp - 16] ;Получили данные из переменной |Серегыч|
push rax          

;умножение двух чисел
pop rax   
pop rbx   
mul rbx   
push rax  

mov rax, [rbp - 8] ;Получили данные из переменной |Богданыч|
push rax          

;деление двух чисел
pop rax   
pop rbx   
div rbx   
push rax  

call .my_printf  

mov rax, 60 
mov rdi, 0  
syscall     

:end_if_2

mov rax, [rbp - 8] ;Получили данные из переменной |Богданыч|
push rax          

mov rax, [rbp - 8] ;Получили данные из переменной |Богданыч|
push rax          

;умножение двух чисел
pop rax   
pop rbx   
mul rbx   
push rax  

push 4 ;Запушил константу

mov rax, [rbp - 0] ;Получили данные из переменной |Антоныч|
push rax          

;умножение двух чисел
pop rax   
pop rbx   
mul rbx   
push rax  

mov rax, [rbp - 16] ;Получили данные из переменной |Серегыч|
push rax          

;умножение двух чисел
pop rax   
pop rbx   
mul rbx   
push rax  

; разность двух чисел
pop rax      
pop rbx      
sub rax, rbx 
push rax     

pop rax ;Запись в переменную |Дискриминантыч| 
mov [rbp - 24], rax 

mov rax, [rbp - 24] ;Получили данные из переменной |Дискриминантыч|
push rax          

push 0 ;Запушил константу

; ==         
xor rcx, rcx 
pop rax      
pop rbx      
cmp rax, rbx 
setz cl      
push rcx     

pop rax                
cmp rax, 0             
je :end_if_3          
push 1 ;Запушил константу

call .my_printf  

push -1 ;Запушил константу

mov rax, [rbp - 8] ;Получили данные из переменной |Богданыч|
push rax          

;умножение двух чисел
pop rax   
pop rbx   
mul rbx   
push rax  

push 2 ;Запушил константу

;деление двух чисел
pop rax   
pop rbx   
div rbx   
push rax  

mov rax, [rbp - 0] ;Получили данные из переменной |Антоныч|
push rax          

;деление двух чисел
pop rax   
pop rbx   
div rbx   
push rax  

call .my_printf  

mov rax, 60 
mov rdi, 0  
syscall     

:end_if_3

mov rax, [rbp - 24] ;Получили данные из переменной |Дискриминантыч|
push rax          

push 0 ;Запушил константу

; <         
xor rcx      
pop rax      
pop rbx      
cmp rax, rbx 
setl cl      
push rcx     

pop rax                
cmp rax, 0             
je .endif_with_else_0 

push 0 ;Запушил константу

call .my_printf  

mov rax, 60 
mov rdi, 0  
syscall     

.endif_with_else_0     
push 2 ;Запушил константу

call .my_printf  

push -1 ;Запушил константу

mov rax, [rbp - 8] ;Получили данные из переменной |Богданыч|
push rax          

;умножение двух чисел
pop rax   
pop rbx   
mul rbx   
push rax  

mov rax, [rbp - 24] ;Получили данные из переменной |Дискриминантыч|
push rax          

;корень как побитовый сдвиг вправо
pop rax    
shr rax, 1 
push rax   

; разность двух чисел
pop rax      
pop rbx      
sub rax, rbx 
push rax     

push 2 ;Запушил константу

;деление двух чисел
pop rax   
pop rbx   
div rbx   
push rax  

mov rax, [rbp - 0] ;Получили данные из переменной |Антоныч|
push rax          

;деление двух чисел
pop rax   
pop rbx   
div rbx   
push rax  

call .my_printf  

push -1 ;Запушил константу

mov rax, [rbp - 8] ;Получили данные из переменной |Богданыч|
push rax          

;умножение двух чисел
pop rax   
pop rbx   
mul rbx   
push rax  

mov rax, [rbp - 24] ;Получили данные из переменной |Дискриминантыч|
push rax          

;корень как побитовый сдвиг вправо
pop rax    
shr rax, 1 
push rax   

; сумма двух чисел
pop rax      
pop rbx      
add rax, rbx 
push rax     

push 2 ;Запушил константу

;деление двух чисел
pop rax   
pop rbx   
div rbx   
push rax  

mov rax, [rbp - 0] ;Получили данные из переменной |Антоныч|
push rax          

;деление двух чисел
pop rax   
pop rbx   
div rbx   
push rax  

call .my_printf  

mov rax, 60 
mov rdi, 0  
syscall     



mov rax, 60 
mov rdi, 0  
syscall     

