PUSH 100

PUSH 0  ;Адрес для переменной |Евген_Шпала|
PUSHREG HX 
ADD
POPREG GX
POPM [GX]

PUSH 100

PUSH 1  ;Адрес для переменной |Ержан_Гном|
PUSHREG HX 
ADD
POPREG GX
POPM [GX]

PUSH 20

PUSH 2  ;Адрес для переменной |Серега_Радиус|
PUSHREG HX 
ADD
POPREG GX
POPM [GX]


PUSH 0  ;Получили адрес переменной |Евген_Шпала|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 2
DIV

PUSH 3  ;Адрес для переменной |Центр_Аркадич|
PUSHREG HX 
ADD
POPREG GX
POPM [GX]


PUSH 1  ;Получили адрес переменной |Ержан_Гном|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 2
DIV

PUSH 4  ;Адрес для переменной |Центр_Олегыч|
PUSHREG HX 
ADD
POPREG GX
POPM [GX]

PUSH 0

PUSH 5  ;Адрес для переменной |Счетчик_Макарыч|
PUSHREG HX 
ADD
POPREG GX
POPM [GX]

PUSH 0

PUSH 6  ;Адрес для переменной |Счетчик_Евген_Шпала|
PUSHREG HX 
ADD
POPREG GX
POPM [GX]

PUSH 0

PUSH 7  ;Адрес для переменной |Счетчик_Ержан_Гном|
PUSHREG HX 
ADD
POPREG GX
POPM [GX]


:begin_while_0

PUSH 5  ;Получили адрес переменной |Счетчик_Макарыч|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]


PUSH 0  ;Получили адрес переменной |Евген_Шпала|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]


PUSH 1  ;Получили адрес переменной |Ержан_Гном|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

MUL

JB :L_less_0
PUSH 0
:L_less_0


PUSH 5  ;Получили адрес переменной |Счетчик_Макарыч|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]


PUSH 0  ;Получили адрес переменной |Евген_Шпала|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]


PUSH 1  ;Получили адрес переменной |Ержан_Гном|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

MUL

JA :L_bigger_0
PUSH 1
:L_bigger_0


PUSH 0
JE :endwhile_0


PUSH 3  ;Получили адрес переменной |Центр_Аркадич|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]


PUSH 6  ;Получили адрес переменной |Счетчик_Евген_Шпала|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

SUB

PUSH 3  ;Получили адрес переменной |Центр_Аркадич|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]


PUSH 6  ;Получили адрес переменной |Счетчик_Евген_Шпала|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

SUB
MUL

PUSH 4  ;Получили адрес переменной |Центр_Олегыч|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]


PUSH 7  ;Получили адрес переменной |Счетчик_Ержан_Гном|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

SUB

PUSH 4  ;Получили адрес переменной |Центр_Олегыч|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]


PUSH 7  ;Получили адрес переменной |Счетчик_Ержан_Гном|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

SUB
MUL
ADD

PUSH 8  ;Адрес для переменной |Андрюха_Расстояние|
PUSHREG HX 
ADD
POPREG GX
POPM [GX]


PUSH 8  ;Получили адрес переменной |Андрюха_Расстояние|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]


PUSH 2  ;Получили адрес переменной |Серега_Радиус|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]


PUSH 2  ;Получили адрес переменной |Серега_Радиус|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

MUL

JB :L_less_1
PUSH 0
:L_less_1


PUSH 8  ;Получили адрес переменной |Андрюха_Расстояние|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]


PUSH 2  ;Получили адрес переменной |Серега_Радиус|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]


PUSH 2  ;Получили адрес переменной |Серега_Радиус|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

MUL

JA :L_bigger_1
PUSH 1
:L_bigger_1


PUSH 0
JE :endif_0

PUSH 7  ;Получили адрес переменной |Счетчик_Ержан_Гном|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]


PUSH 1  ;Получили адрес переменной |Ержан_Гном|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

MUL

PUSH 6  ;Получили адрес переменной |Счетчик_Евген_Шпала|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

ADD
PUSH 3
MUL

PUSH 9  ;Адрес для переменной |Максон_Координаты|
PUSHREG HX 
ADD
POPREG GX
POPM [GX]


PUSH 9  ;Получили адрес переменной |Максон_Координаты|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]


POPREG BX
PUSH 255
POPM [BX]
PUSH 1
PUSHREG BX
ADD
POPREG BX
PUSH 128
POPM [BX]
PUSH 1
PUSHREG BX
ADD
POPREG BX
PUSH 255
POPM [BX]
:endif_0


PUSH 5  ;Получили адрес переменной |Счетчик_Макарыч|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 1
ADD

PUSH 5  ;Адрес для переменной |Счетчик_Макарыч|
PUSHREG HX 
ADD
POPREG GX
POPM [GX]


PUSH 6  ;Получили адрес переменной |Счетчик_Евген_Шпала|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]


PUSH 0  ;Получили адрес переменной |Евген_Шпала|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]


JE :E_equal_0
PUSH 0
:E_equal_0


PUSH 6  ;Получили адрес переменной |Счетчик_Евген_Шпала|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]


PUSH 0  ;Получили адрес переменной |Евген_Шпала|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]


JNE :E_not_equal_0
PUSH 1
:E_not_equal_0


PUSH 0
JE :endif_with_else_0

PUSH 0

PUSH 6  ;Адрес для переменной |Счетчик_Евген_Шпала|
PUSHREG HX 
ADD
POPREG GX
POPM [GX]


PUSH 7  ;Получили адрес переменной |Счетчик_Ержан_Гном|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 1
ADD

PUSH 7  ;Адрес для переменной |Счетчик_Ержан_Гном|
PUSHREG HX 
ADD
POPREG GX
POPM [GX]


:endif_with_else_0

PUSH 6  ;Получили адрес переменной |Счетчик_Евген_Шпала|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 1
ADD

PUSH 6  ;Адрес для переменной |Счетчик_Евген_Шпала|
PUSHREG HX 
ADD
POPREG GX
POPM [GX]




JMP :begin_while_0

:endwhile_0

DRAW
HLT

