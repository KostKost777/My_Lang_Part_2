PUSH 0

PUSH 0  ;ббнд гмювемхъ оепелеммни |юМРНМШВ|
PUSHREG HX 
ADD
POPREG GX
POPM [GX]

PUSH 0

PUSH 1  ;ббнд гмювемхъ оепелеммни |аНЦДЮМШВ|
PUSHREG HX 
ADD
POPREG GX
POPM [GX]

PUSH 0

PUSH 2  ;ббнд гмювемхъ оепелеммни |яЕПЕЦШВ|
PUSHREG HX 
ADD
POPREG GX
POPM [GX]

IN

PUSH 0  ;ббнд гмювемхъ оепелеммни |юМРНМШВ|
PUSHREG HX 
ADD
POPREG GX
POPM [GX]

IN

PUSH 1  ;ббнд гмювемхъ оепелеммни |аНЦДЮМШВ|
PUSHREG HX 
ADD
POPREG GX
POPM [GX]

IN

PUSH 2  ;ббнд гмювемхъ оепелеммни |яЕПЕЦШВ|
PUSHREG HX 
ADD
POPREG GX
POPM [GX]


PUSH 0  ;бшбнд гмювемхъ оепелеммни |юМРНМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JE :E_equal_0
PUSH 0
:E_equal_0


PUSH 0  ;бшбнд гмювемхъ оепелеммни |юМРНМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JNE :E_not_equal_0
PUSH 1
:E_not_equal_0


PUSH 1  ;бшбнд гмювемхъ оепелеммни |аНЦДЮМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JE :E_equal_1
PUSH 0
:E_equal_1


PUSH 1  ;бшбнд гмювемхъ оепелеммни |аНЦДЮМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JNE :E_not_equal_1
PUSH 1
:E_not_equal_1


MUL
PUSH 0
JE :A_and_0
PUSH 1
:A_and_0


PUSH 0  ;бшбнд гмювемхъ оепелеммни |юМРНМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JE :E_equal_2
PUSH 0
:E_equal_2


PUSH 0  ;бшбнд гмювемхъ оепелеммни |юМРНМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JNE :E_not_equal_2
PUSH 1
:E_not_equal_2


PUSH 1  ;бшбнд гмювемхъ оепелеммни |аНЦДЮМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JE :E_equal_3
PUSH 0
:E_equal_3


PUSH 1  ;бшбнд гмювемхъ оепелеммни |аНЦДЮМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JNE :E_not_equal_3
PUSH 1
:E_not_equal_3


MUL
PUSH 0

JNE :A_n_and_0
PUSH 0
:A_n_and_0


PUSH 2  ;бшбнд гмювемхъ оепелеммни |яЕПЕЦШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JE :E_equal_4
PUSH 0
:E_equal_4


PUSH 2  ;бшбнд гмювемхъ оепелеммни |яЕПЕЦШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JNE :E_not_equal_4
PUSH 1
:E_not_equal_4


MUL
PUSH 0
JE :A_and_1
PUSH 1
:A_and_1


PUSH 0  ;бшбнд гмювемхъ оепелеммни |юМРНМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JE :E_equal_5
PUSH 0
:E_equal_5


PUSH 0  ;бшбнд гмювемхъ оепелеммни |юМРНМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JNE :E_not_equal_5
PUSH 1
:E_not_equal_5


PUSH 1  ;бшбнд гмювемхъ оепелеммни |аНЦДЮМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JE :E_equal_6
PUSH 0
:E_equal_6


PUSH 1  ;бшбнд гмювемхъ оепелеммни |аНЦДЮМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JNE :E_not_equal_6
PUSH 1
:E_not_equal_6


MUL
PUSH 0
JE :A_and_1
PUSH 1
:A_and_1


PUSH 0  ;бшбнд гмювемхъ оепелеммни |юМРНМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JE :E_equal_7
PUSH 0
:E_equal_7


PUSH 0  ;бшбнд гмювемхъ оепелеммни |юМРНМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JNE :E_not_equal_7
PUSH 1
:E_not_equal_7


PUSH 1  ;бшбнд гмювемхъ оепелеммни |аНЦДЮМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JE :E_equal_8
PUSH 0
:E_equal_8


PUSH 1  ;бшбнд гмювемхъ оепелеммни |аНЦДЮМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JNE :E_not_equal_8
PUSH 1
:E_not_equal_8


MUL
PUSH 0

JNE :A_n_and_1
PUSH 0
:A_n_and_1


PUSH 2  ;бшбнд гмювемхъ оепелеммни |яЕПЕЦШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JE :E_equal_9
PUSH 0
:E_equal_9


PUSH 2  ;бшбнд гмювемхъ оепелеммни |яЕПЕЦШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JNE :E_not_equal_9
PUSH 1
:E_not_equal_9


MUL
PUSH 0

JNE :A_n_and_2
PUSH 0
:A_n_and_2


PUSH 0
JE :endif_0
PUSH -1
OUT
HLT
:endif_0


PUSH 0  ;бшбнд гмювемхъ оепелеммни |юМРНМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JE :E_equal_10
PUSH 0
:E_equal_10


PUSH 0  ;бшбнд гмювемхъ оепелеммни |юМРНМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JNE :E_not_equal_10
PUSH 1
:E_not_equal_10


PUSH 1  ;бшбнд гмювемхъ оепелеммни |аНЦДЮМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JE :E_equal_11
PUSH 0
:E_equal_11


PUSH 1  ;бшбнд гмювемхъ оепелеммни |аНЦДЮМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JNE :E_not_equal_11
PUSH 1
:E_not_equal_11


MUL
PUSH 0
JE :A_and_3
PUSH 1
:A_and_3


PUSH 0  ;бшбнд гмювемхъ оепелеммни |юМРНМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JE :E_equal_12
PUSH 0
:E_equal_12


PUSH 0  ;бшбнд гмювемхъ оепелеммни |юМРНМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JNE :E_not_equal_12
PUSH 1
:E_not_equal_12


PUSH 1  ;бшбнд гмювемхъ оепелеммни |аНЦДЮМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JE :E_equal_13
PUSH 0
:E_equal_13


PUSH 1  ;бшбнд гмювемхъ оепелеммни |аНЦДЮМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JNE :E_not_equal_13
PUSH 1
:E_not_equal_13


MUL
PUSH 0

JNE :A_n_and_3
PUSH 0
:A_n_and_3


PUSH 2  ;бшбнд гмювемхъ оепелеммни |яЕПЕЦШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JNE :NE_equal_0
PUSH 0
:NE_equal_0


PUSH 2  ;бшбнд гмювемхъ оепелеммни |яЕПЕЦШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JE :NE_not_equal_0
PUSH 1
:NE_not_equal_0


MUL
PUSH 0
JE :A_and_4
PUSH 1
:A_and_4


PUSH 0  ;бшбнд гмювемхъ оепелеммни |юМРНМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JE :E_equal_14
PUSH 0
:E_equal_14


PUSH 0  ;бшбнд гмювемхъ оепелеммни |юМРНМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JNE :E_not_equal_14
PUSH 1
:E_not_equal_14


PUSH 1  ;бшбнд гмювемхъ оепелеммни |аНЦДЮМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JE :E_equal_15
PUSH 0
:E_equal_15


PUSH 1  ;бшбнд гмювемхъ оепелеммни |аНЦДЮМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JNE :E_not_equal_15
PUSH 1
:E_not_equal_15


MUL
PUSH 0
JE :A_and_4
PUSH 1
:A_and_4


PUSH 0  ;бшбнд гмювемхъ оепелеммни |юМРНМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JE :E_equal_16
PUSH 0
:E_equal_16


PUSH 0  ;бшбнд гмювемхъ оепелеммни |юМРНМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JNE :E_not_equal_16
PUSH 1
:E_not_equal_16


PUSH 1  ;бшбнд гмювемхъ оепелеммни |аНЦДЮМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JE :E_equal_17
PUSH 0
:E_equal_17


PUSH 1  ;бшбнд гмювемхъ оепелеммни |аНЦДЮМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JNE :E_not_equal_17
PUSH 1
:E_not_equal_17


MUL
PUSH 0

JNE :A_n_and_4
PUSH 0
:A_n_and_4


PUSH 2  ;бшбнд гмювемхъ оепелеммни |яЕПЕЦШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JNE :NE_equal_1
PUSH 0
:NE_equal_1


PUSH 2  ;бшбнд гмювемхъ оепелеммни |яЕПЕЦШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JE :NE_not_equal_1
PUSH 1
:NE_not_equal_1


MUL
PUSH 0

JNE :A_n_and_5
PUSH 0
:A_n_and_5


PUSH 0
JE :endif_1
PUSH 0
OUT
HLT
:endif_1


PUSH 0  ;бшбнд гмювемхъ оепелеммни |юМРНМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JE :E_equal_18
PUSH 0
:E_equal_18


PUSH 0  ;бшбнд гмювемхъ оепелеммни |юМРНМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JNE :E_not_equal_18
PUSH 1
:E_not_equal_18


PUSH 1  ;бшбнд гмювемхъ оепелеммни |аНЦДЮМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JNE :NE_equal_2
PUSH 0
:NE_equal_2


PUSH 1  ;бшбнд гмювемхъ оепелеммни |аНЦДЮМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JE :NE_not_equal_2
PUSH 1
:NE_not_equal_2


MUL
PUSH 0
JE :A_and_6
PUSH 1
:A_and_6


PUSH 0  ;бшбнд гмювемхъ оепелеммни |юМРНМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JE :E_equal_19
PUSH 0
:E_equal_19


PUSH 0  ;бшбнд гмювемхъ оепелеммни |юМРНМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JNE :E_not_equal_19
PUSH 1
:E_not_equal_19


PUSH 1  ;бшбнд гмювемхъ оепелеммни |аНЦДЮМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JNE :NE_equal_3
PUSH 0
:NE_equal_3


PUSH 1  ;бшбнд гмювемхъ оепелеммни |аНЦДЮМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JE :NE_not_equal_3
PUSH 1
:NE_not_equal_3


MUL
PUSH 0

JNE :A_n_and_6
PUSH 0
:A_n_and_6


PUSH 2  ;бшбнд гмювемхъ оепелеммни |яЕПЕЦШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JNE :NE_equal_4
PUSH 0
:NE_equal_4


PUSH 2  ;бшбнд гмювемхъ оепелеммни |яЕПЕЦШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JE :NE_not_equal_4
PUSH 1
:NE_not_equal_4


MUL
PUSH 0
JE :A_and_7
PUSH 1
:A_and_7


PUSH 0  ;бшбнд гмювемхъ оепелеммни |юМРНМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JE :E_equal_20
PUSH 0
:E_equal_20


PUSH 0  ;бшбнд гмювемхъ оепелеммни |юМРНМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JNE :E_not_equal_20
PUSH 1
:E_not_equal_20


PUSH 1  ;бшбнд гмювемхъ оепелеммни |аНЦДЮМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JNE :NE_equal_5
PUSH 0
:NE_equal_5


PUSH 1  ;бшбнд гмювемхъ оепелеммни |аНЦДЮМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JE :NE_not_equal_5
PUSH 1
:NE_not_equal_5


MUL
PUSH 0
JE :A_and_7
PUSH 1
:A_and_7


PUSH 0  ;бшбнд гмювемхъ оепелеммни |юМРНМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JE :E_equal_21
PUSH 0
:E_equal_21


PUSH 0  ;бшбнд гмювемхъ оепелеммни |юМРНМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JNE :E_not_equal_21
PUSH 1
:E_not_equal_21


PUSH 1  ;бшбнд гмювемхъ оепелеммни |аНЦДЮМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JNE :NE_equal_6
PUSH 0
:NE_equal_6


PUSH 1  ;бшбнд гмювемхъ оепелеммни |аНЦДЮМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JE :NE_not_equal_6
PUSH 1
:NE_not_equal_6


MUL
PUSH 0

JNE :A_n_and_7
PUSH 0
:A_n_and_7


PUSH 2  ;бшбнд гмювемхъ оепелеммни |яЕПЕЦШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JNE :NE_equal_7
PUSH 0
:NE_equal_7


PUSH 2  ;бшбнд гмювемхъ оепелеммни |яЕПЕЦШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JE :NE_not_equal_7
PUSH 1
:NE_not_equal_7


MUL
PUSH 0

JNE :A_n_and_8
PUSH 0
:A_n_and_8


PUSH 0
JE :endif_2
PUSH 1
OUT
PUSH -1

PUSH 2  ;бшбнд гмювемхъ оепелеммни |яЕПЕЦШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

MUL

PUSH 1  ;бшбнд гмювемхъ оепелеммни |аНЦДЮМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

DIV
OUT
HLT
:endif_2


PUSH 1  ;бшбнд гмювемхъ оепелеммни |аНЦДЮМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]


PUSH 1  ;бшбнд гмювемхъ оепелеммни |аНЦДЮМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

MUL
PUSH 4

PUSH 0  ;бшбнд гмювемхъ оепелеммни |юМРНМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

MUL

PUSH 2  ;бшбнд гмювемхъ оепелеммни |яЕПЕЦШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

MUL
SUB

PUSH 3  ;ббнд гмювемхъ оепелеммни |дХЯЙПХЛХМЮМРШВ|
PUSHREG HX 
ADD
POPREG GX
POPM [GX]


PUSH 3  ;бшбнд гмювемхъ оепелеммни |дХЯЙПХЛХМЮМРШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JE :E_equal_22
PUSH 0
:E_equal_22


PUSH 3  ;бшбнд гмювемхъ оепелеммни |дХЯЙПХЛХМЮМРШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JNE :E_not_equal_22
PUSH 1
:E_not_equal_22


PUSH 0
JE :endif_3
PUSH 1
OUT
PUSH -1

PUSH 1  ;бшбнд гмювемхъ оепелеммни |аНЦДЮМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

MUL
PUSH 2
DIV

PUSH 0  ;бшбнд гмювемхъ оепелеммни |юМРНМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

DIV
OUT
HLT
:endif_3


PUSH 3  ;бшбнд гмювемхъ оепелеммни |дХЯЙПХЛХМЮМРШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JB :L_less_0
PUSH 0
:L_less_0


PUSH 3  ;бшбнд гмювемхъ оепелеммни |дХЯЙПХЛХМЮМРШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 0

JA :L_bigger_0
PUSH 1
:L_bigger_0


PUSH 0
JE :endif_with_else_0

PUSH 0
OUT
HLT

:endif_with_else_0
PUSH 2
OUT
PUSH -1

PUSH 1  ;бшбнд гмювемхъ оепелеммни |аНЦДЮМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

MUL

PUSH 3  ;бшбнд гмювемхъ оепелеммни |дХЯЙПХЛХМЮМРШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

SQVRT
SUB
PUSH 2
DIV

PUSH 0  ;бшбнд гмювемхъ оепелеммни |юМРНМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

DIV
OUT
PUSH -1

PUSH 1  ;бшбнд гмювемхъ оепелеммни |аНЦДЮМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

MUL

PUSH 3  ;бшбнд гмювемхъ оепелеммни |дХЯЙПХЛХМЮМРШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

SQVRT
ADD
PUSH 2
DIV

PUSH 0  ;бшбнд гмювемхъ оепелеммни |юМРНМШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

DIV
OUT
HLT


HLT
HLT

