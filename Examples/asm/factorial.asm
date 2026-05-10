PUSH 0

PUSH 2  ;Адрес для переменной |Ефимыч|
PUSHREG HX 
ADD
POPREG GX
POPM [GX]

IN

PUSH 2  ;Адрес для переменной |Ефимыч|
PUSHREG HX 
ADD
POPREG GX
POPM [GX]


PUSH 2  ;Получили адрес переменной |Ефимыч|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

CALL :func_0
PUSHREG AX
OUT
HLT
HLT

:func_0

PUSH 5     ;Создаём кадр функции
PUSHREG HX
ADD
POPREG HX
PUSH 0  ;Адрес для переменной |Серегыч|
PUSHREG HX 
ADD
POPREG GX
POPM [GX]


PUSH 0  ;Получили адрес переменной |Серегыч|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 1

JE :E_equal_0
PUSH 0
:E_equal_0


PUSH 0  ;Получили адрес переменной |Серегыч|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 1

JNE :E_not_equal_0
PUSH 1
:E_not_equal_0


PUSH 0
JE :endif_with_else_0

PUSH 1


POPREG AX    ;Через AX возвращаем значение
PUSHREG HX
PUSH 5     ;Возвращаем указатель стека
SUB
POPREG HX
RET


:endif_with_else_0

PUSH 0  ;Получили адрес переменной |Серегыч|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 1
SUB
CALL :func_0
PUSHREG AX

PUSH 1  ;Адрес для переменной |Олегыч|
PUSHREG HX 
ADD
POPREG GX
POPM [GX]


PUSH 1  ;Получили адрес переменной |Олегыч|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]


PUSH 0  ;Получили адрес переменной |Серегыч|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

MUL


POPREG AX    ;Через AX возвращаем значение
PUSHREG HX
PUSH 5     ;Возвращаем указатель стека
SUB
POPREG HX
RET



