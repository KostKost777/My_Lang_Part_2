#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <ctype.h>

#include "parse_tree_in_asm_funcs.h"
#include "tree_funcs.h"
#include "lexical_analysis.h"
#include "dump_funcs.h"
#include "hash_funcs.h"

extern const char* asm_file_name;
FILE* asm_file = NULL;

void ParseAsmTreeInAsmFile(Tree* tree, Node* node, const char* asm_file_name)
{
    assert(tree);
    assert(node);

    fprintf(log_file, "Enter ParseAsmTreeInAsmFile\n");

    asm_file = fopen(asm_file_name, "w");
    assert(asm_file);

    Lexeme main = GetMainLexeme();
    ParseMain(tree, node, &main);

    while(node->type == KEY_LBRACE)
    {
        ParseAsmFunc(tree, node->left);
        node = node->right;
    }

    free(main.str.name);
    fclose(asm_file);
    printf("\nEND");
}

void ParseMain(Tree* tree, Node* node, Lexeme* main)
{
    assert(tree);
    assert(node);
    assert(main);

    while(node->type == KEY_LBRACE)
        node = node->right;

    
    fprintf(asm_file, ";========MAIN=======\n\n");
    fprintf(asm_file, "push rbp     \n");
    fprintf(asm_file, "mov rbp, rsp \n\n");

    size_t var_in_main = CountVarInFunc(tree->name_table, "main");

    fprintf(asm_file, "sub rsp, %zu \n\n", var_in_main * 8);

    ParseAsmOperator(tree, node, main);        
}

void ParseAsmFunc(Tree* tree, Node* node)
{
    assert(tree);
    assert(node);

    fprintf(log_file, "Enter ParseAsmFunc\n");

    Lexeme func_info = node->lexeme;

    ParseAsmFuncLabel(tree->name_table, &func_info);

    ParseAsmOperator(tree, node->right, &func_info);
}

void ParseAsmOperator(Tree* tree, Node* node, Lexeme* func_info)
{
    assert(tree);
    assert(func_info);

    while (node != NULL)
    {
        fprintf(log_file, "Enter ParseAsmOperator\n");

        if (node->type == KEY_END)
        {
            ParseAsmEnd(tree, node, func_info);
            return;
        }

        if (node->left->type == KEY_DRAW)
            ParseAsmDraw(tree, node->left, func_info);

        if (node->left->type == OP_ASSIGNED)
            ParseAsmAssigned(tree, node->left, func_info);

        if (node->left->type == KEY_IF && node->left->right->type == KEY_ELSE)
            ParseAsmIfElse(tree, node->left, func_info);

        if (node->left->type == KEY_IF && node->left->right->type != KEY_ELSE)
            ParseAsmIf(tree, node->left, func_info);

        if (node->left->type == KEY_WHILE)
            ParseAsmWhile(tree, node->left, func_info);

        if (node->left->type == KEY_IN)
            ParseAsmIn(tree, node->left, func_info);

        if (node->left->type == KEY_OUT)
            ParseAsmOut(tree, node->left, func_info);

        if (node->left->type == KEY_RETURN)
            ParseAsmReturn(tree, node->left, func_info);

        node = node->right;
    }
}

void ParseAsmAssigned(Tree* tree, Node* node, Lexeme* func_info)
{
    assert(tree);
    assert(node);
    assert(func_info);

    fprintf(log_file, "Enter ParseAsmAssigned\n");

    ParseAsmExpression(tree, node->right, func_info);

    ParseAsmInVar(tree, node->left, func_info);
}

void ParseAsmDraw(Tree* tree, Node* node, Lexeme* func_info)   //FIX
{
    assert(tree);
    assert(node);
    assert(func_info);

    fprintf(log_file, "Enter ParseAsmDraw\n");

    ParseAsmOutVar(tree, node->left, func_info);

    fprintf(asm_file, "\nPOPREG BX\n");
    fprintf(asm_file, "PUSH 255\n");
    fprintf(asm_file, "POPM [BX]\n");

    fprintf(asm_file, "PUSH 1\n");
    fprintf(asm_file, "PUSHREG BX\n");
    fprintf(asm_file, "ADD\n");
    fprintf(asm_file, "POPREG BX\n");
    fprintf(asm_file, "PUSH 128\n");
    fprintf(asm_file, "POPM [BX]\n");

    fprintf(asm_file, "PUSH 1\n");
    fprintf(asm_file, "PUSHREG BX\n");
    fprintf(asm_file, "ADD\n");
    fprintf(asm_file, "POPREG BX\n");
    fprintf(asm_file, "PUSH 255\n");
    fprintf(asm_file, "POPM [BX]\n");

    tree->is_draw = true;
}

void ParseAsmEnd(Tree* tree, Node* node, Lexeme* func_info)
{
    assert(tree);
    assert(node);
    assert(func_info);

    fprintf(log_file, "Enter ParseAsmEnd\n");

    if (tree->is_draw)
        fprintf(asm_file, "call PrintVRAM\n\n");      //FIX

    fprintf(asm_file, "mov rsp, rbp \n");
    fprintf(asm_file, "pop rbp      \n\n");

    fprintf(asm_file, "mov rax, 60 \n");         
    fprintf(asm_file, "mov rdi, 0  \n");         
    fprintf(asm_file, "syscall     \n\n"); 
}

void ParseAsmReturn(Tree* tree, Node* node, Lexeme* func_info)
{
    assert(tree);
    assert(node);
    assert(func_info);

    fprintf(log_file, "Enter ParseAsmReturn\n");

    ParseAsmExpression(tree, node->left, func_info);

    fprintf(asm_file, "pop rax      \n");
    fprintf(asm_file, "mov rsp, rbp \n");
    fprintf(asm_file, "pop rbp      \n\n");

    fprintf(asm_file, "ret          \n\n");
}

void ParseAsmIn(Tree* tree, Node* node, Lexeme* func_info)
{
    assert(tree);
    assert(node);
    assert(func_info);

    fprintf(log_file, "Enter ParseAsmIn\n");


    fprintf(asm_file, "call MyScanf  \n");
    fprintf(asm_file, "push rax  ; Возвращаемое значение в rax\n\n"); 

    ParseAsmInVar(tree, node->left, func_info);
}

void ParseAsmOut(Tree* tree, Node* node, Lexeme* func_info)
{
    assert(tree);
    assert(node);
    assert(func_info);

    fprintf(log_file, "Enter ParseAsmOut\n");

    ParseAsmExpression(tree, node->left, func_info);

    fprintf(asm_file, "call MyPrintf  \n\n"); 
}

void ParseAsmIf(Tree* tree, Node* node, Lexeme* func_info)
{
    assert(tree);
    assert(node);
    assert(func_info);

    fprintf(log_file, "Enter ParseAsmIf\n");

    static int counter = 0;

    ParseAsmExpression(tree, node->left, func_info);

    fprintf(asm_file, "pop rax                \n"           );
    fprintf(asm_file, "cmp rax, 0             \n"           );
    fprintf(asm_file, "je .end_if_%d          \n", counter  );

    ParseAsmOperator(tree, node->right, func_info);

    fprintf(asm_file, ".end_if_%d:\n\n", counter);

    counter++;
}

void ParseAsmWhile(Tree* tree, Node* node, Lexeme* func_info)
{
    assert(tree);
    assert(node);
    assert(func_info);

    fprintf(log_file, "Enter ParseAsmWhile\n");

    static int counter = 0;

    fprintf(asm_file, ".begin_while_%d:       \n",    counter);

    ParseAsmExpression(tree, node->left, func_info);

    fprintf(asm_file, "pop rax                \n"           );
    fprintf(asm_file, "cmp rax, 0             \n"           );
    fprintf(asm_file, "je .end_while_%d       \n\n", counter);

    ParseAsmOperator(tree, node->right, func_info);

    fprintf(asm_file, "jmp .begin_while_%d    \n",   counter);

    fprintf(asm_file, ".end_while_%d:          \n\n", counter);

    counter++;
}

void ParseAsmIfElse(Tree* tree, Node* node, Lexeme* func_info)
{
    assert(tree);
    assert(node);
    assert(func_info);

    fprintf(log_file, "Enter ParseAsmIfElse\n");

    static int counter = 0;

    ParseAsmExpression(tree, node->left, func_info);

    fprintf(asm_file, "pop rax                \n");
    fprintf(asm_file, "cmp rax, 0             \n");
    fprintf(asm_file, "je .skip_if_%d         \n\n", counter);

    ParseAsmOperator(tree, node->right->left, func_info);
    fprintf(asm_file, "jmp .skip_else_%d      \n", counter);
    fprintf(asm_file, ".skip_if_%d:           \n\n", counter);

    ParseAsmOperator(tree, node->right->right, func_info);

    fprintf(asm_file, ".skip_else_%d:         \n\n", counter);

    counter++;
}

void ParseAsmExpression(Tree* tree, Node* node, Lexeme* func_info)
{
    assert(tree);
    assert(node);
    assert(func_info);

    fprintf(log_file, "Enter ParseAsmExpression\n");

    if (node->left != NULL && node->left->type != PARAM)
        ParseAsmExpression(tree, node->left, func_info);

    if (node->right != NULL)
        ParseAsmExpression(tree, node->right, func_info);

    PrintNodeInAsmFile(tree, node, func_info);
}

void PrintNodeInAsmFile(Tree* tree, Node* node, Lexeme* func_info)
{
    assert(tree);
    assert(node);
    assert(func_info);

    fprintf(log_file, "Enter PrintNodeInAsmFile\n");
  
    if ( ParseAsmPARAM    (tree, node)            == success ) return;
    if ( ParseAsmNumber   (tree, node)            == success ) return;
    if ( ParseAsmADD      (tree, node)            == success ) return;
    if ( ParseAsmSUB      (tree, node)            == success ) return;
    if ( ParseAsmMUL      (tree, node)            == success ) return;
    if ( ParseAsmDIV      (tree, node)            == success ) return;
    if ( ParseAsmPOW      (tree, node)            == success ) return;
    if ( ParseAsmSQRT     (tree, node)            == success ) return;
    if ( ParseAsmAnd      (tree, node, func_info) == success ) return;
    if ( ParseAsmOr       (tree, node, func_info) == success ) return;
    if ( ParseAsmOutVar   (tree, node, func_info) == success ) return;
    if ( ParseAsmBigger   (tree, node, func_info) == success ) return;
    if ( ParseAsmLess     (tree, node, func_info) == success ) return;
    if ( ParseAsmEqual    (tree, node, func_info) == success ) return;
    if ( ParseAsmNotEqual (tree, node, func_info) == success ) return;
    if ( ParseAsmCallFunc (tree, node, func_info) == success ) return;
}

Status ParseAsmOr(Tree* tree, Node* node, Lexeme* func_info)
{
    assert(tree);
    assert(node);
    static int counter = 0;

    if (node->type != OP_OR)
        return error;

    fprintf(log_file, "Enter ParseAsmOr\n");

    fprintf(asm_file, "; ||          \n"          );
    fprintf(asm_file, "xor rcx, rcx  \n"          ); 
    fprintf(asm_file, "pop rax       \n"          );     
    fprintf(asm_file, "pop rbx       \n"          );     
    fprintf(asm_file, "test rax, rax \n"          );    
    fprintf(asm_file, "jnz .good_%d  \n", counter );    
    fprintf(asm_file, "test rbx, rbx \n"          );
    fprintf(asm_file, "jz .false_%d  \n", counter );   
    fprintf(asm_file, ".good_%d:     \n", counter ); 
    fprintf(asm_file, "mov rcx, 1    \n"          ); 
    fprintf(asm_file, ".false_%d:    \n", counter ); 
    fprintf(asm_file, "push rcx    \n\n"          ); 

    counter++;

    return success;
}

Status ParseAsmAnd(Tree* tree, Node* node, Lexeme* func_info)
{
    assert(tree);
    assert(node);

    static int counter = 0;

    if (node->type != OP_AND)
        return error;

    fprintf(log_file, "Enter ParseAsmAnd\n");

    fprintf(asm_file, "; &&          \n"          );
    fprintf(asm_file, "xor rcx, rcx  \n"          ); 
    fprintf(asm_file, "pop rax       \n"          );     
    fprintf(asm_file, "pop rbx       \n"          );     
    fprintf(asm_file, "test rax, rax \n"          );    
    fprintf(asm_file, "jz .false_%d  \n", counter );    
    fprintf(asm_file, "test rbx, rbx \n"          );    
    fprintf(asm_file, "jz .false_%d  \n", counter );    
    fprintf(asm_file, "mov rcx, 1    \n"          );    
    fprintf(asm_file, ".false_%d:    \n", counter );   
    fprintf(asm_file, "push rcx      \n\n"        );

    counter++;

    return success;
}

Status ParseAsmPARAM(Tree* tree, Node* node)
{
    assert(tree);
    assert(node);

    if (node->type == PARAM) return success;
    return error;
}

Status ParseAsmBigger(Tree* tree, Node* node, Lexeme* func_info)
{
    assert(tree);
    assert(node);

    if (node->type != OP_BIGGER)
        return error;

    fprintf(log_file, "Enter ParseAsmBigger\n");

    fprintf(asm_file, "; >          \n");
    fprintf(asm_file, "xor rcx, rcx \n");
    fprintf(asm_file, "pop rax      \n");
    fprintf(asm_file, "pop rbx      \n");
    fprintf(asm_file, "cmp rbx, rax \n");
    fprintf(asm_file, "setg cl      \n");
    fprintf(asm_file, "push rcx     \n\n");

    return success;
}

Status ParseAsmEqual(Tree* tree, Node* node, Lexeme* func_info)
{
    assert(tree);
    assert(node);

    if (node->type != OP_EQUAL)
        return error;

    fprintf(log_file, "Enter ParseAsmEqual\n");

    fprintf(asm_file, "; ==         \n");
    fprintf(asm_file, "xor rcx, rcx \n");
    fprintf(asm_file, "pop rax      \n");
    fprintf(asm_file, "pop rbx      \n");
    fprintf(asm_file, "cmp rbx, rax \n");
    fprintf(asm_file, "setz cl      \n");
    fprintf(asm_file, "push rcx     \n\n");

    return success;
}

Status ParseAsmNotEqual(Tree* tree, Node* node, Lexeme* func_info)
{
    assert(tree);
    assert(node);

    if (node->type != OP_NOT_EQUAL)
        return error;

    fprintf(log_file, "Enter ParseAsmNotEqual\n");

    fprintf(asm_file, "; !=         \n");
    fprintf(asm_file, "xor rcx, rcx \n");
    fprintf(asm_file, "pop rax      \n");
    fprintf(asm_file, "pop rbx      \n");
    fprintf(asm_file, "cmp rbx, rax \n");
    fprintf(asm_file, "setnz cl     \n");
    fprintf(asm_file, "push rcx     \n\n");

    return success;
}

Status ParseAsmLess(Tree* tree, Node* node, Lexeme* func_info)
{
    assert(tree);
    assert(node);

    if (node->type != OP_LESS)
        return error;

    fprintf(log_file, "Enter ParseAsmLess\n");

    fprintf(asm_file, "; <          \n");
    fprintf(asm_file, "xor rcx, rcx \n");
    fprintf(asm_file, "pop rax      \n");
    fprintf(asm_file, "pop rbx      \n");
    fprintf(asm_file, "cmp rbx, rax \n");
    fprintf(asm_file, "setl cl      \n");
    fprintf(asm_file, "push rcx     \n\n");

    return success;
}

Status ParseAsmNumber(Tree* tree, Node* node)
{
    assert(tree);
    assert(node);

    if (node->type != NUM) return error;

    fprintf(log_file, "Enter ParseAsmNumber\n");
    fprintf(asm_file, "push %d ;Запушил константу\n\n", node->lexeme.num);
    return success;
}

Status ParseAsmADD(Tree* tree, Node* node)
{
    assert(tree);
    assert(node);

    if (node->type != OP_ADD) return error;
    
    fprintf(log_file, "Enter ParseAsmADD \n");
    fprintf(asm_file, "; сумма двух чисел\n");

    fprintf(asm_file, "pop rax      \n");
    fprintf(asm_file, "pop rbx      \n");
    fprintf(asm_file, "add rax, rbx \n");
    fprintf(asm_file, "push rax     \n\n");

    return success;
}

Status ParseAsmSUB(Tree* tree, Node* node)
{
    assert(tree);
    assert(node);

    if (node->type != OP_SUB) return error;
    
    fprintf(log_file, "Enter ParseAsmSUB    \n");
    fprintf(asm_file, "; разность двух чисел\n");

    fprintf(asm_file, "pop rax      \n");
    fprintf(asm_file, "pop rbx      \n");
    fprintf(asm_file, "sub rbx, rax \n");
    fprintf(asm_file, "push rbx     \n\n");

    return success;
}

Status ParseAsmMUL(Tree* tree, Node* node)
{
    assert(tree);
    assert(node);

    if (node->type != OP_MUL) return error;
    
    fprintf(log_file, "Enter ParseAsmMUL    \n");
    fprintf(asm_file, ";умножение двух чисел\n");

    fprintf(asm_file, "pop rax   \n");
    fprintf(asm_file, "pop rbx   \n");
    fprintf(asm_file, "imul rbx   \n");
    fprintf(asm_file, "push rax  \n\n");

    return success;
}

Status ParseAsmDIV(Tree* tree, Node* node)
{
    assert(tree);
    assert(node);

    if (node->type != OP_DIV) return error;
    
    fprintf(log_file, "Enter ParseAsmDIV  \n");
    fprintf(asm_file, ";деление двух чисел\n");

    fprintf(asm_file, "pop rbx   \n");
    fprintf(asm_file, "pop rax   \n");
    fprintf(asm_file, "cqo   \n");
    fprintf(asm_file, "idiv rbx   \n");
    fprintf(asm_file, "push rax  \n\n");

    return success;
}

Status ParseAsmPOW(Tree* tree, Node* node)
{
    assert(tree);
    assert(node);

    if (node->type != OP_POW) return error;
    
    fprintf(log_file, "Enter ParseAsmPOW\n");
    fprintf(asm_file, ";возведение в степень двойки\n");

    fprintf(asm_file, "pop rax     \n");
    fprintf(asm_file, "pop rcx     \n");
    fprintf(asm_file, "shl rax, cl \n");
    fprintf(asm_file, "push rax    \n\n");

    return success;
}

Status ParseAsmSQRT(Tree* tree, Node* node)
{
    assert(tree);
    assert(node);

    if (node->type != OP_SQRT) return error;

    static int counter = 0;
    
    fprintf(log_file, "Enter ParseAsmSQRT\n");
    fprintf(asm_file, ";корень перебор в цикле\n");

    fprintf(asm_file, "pop rax               \n");
    fprintf(asm_file, "xor rcx, rcx          \n");
    fprintf(asm_file, ".sqvrt_%d:            \n",   counter);
    fprintf(asm_file, "push rcx              \n");
    fprintf(asm_file, "imul rcx, rcx         \n");
    fprintf(asm_file, "cmp  rcx, rax         \n");
    fprintf(asm_file, "jge  .end_sqvrt_%d    \n",   counter);
    fprintf(asm_file, "pop rcx               \n");
    fprintf(asm_file, "inc rcx               \n");
    fprintf(asm_file, "jmp .sqvrt_%d         \n",   counter);
    fprintf(asm_file, ".end_sqvrt_%d:        \n\n", counter);

    counter++;

    return success;
}

Status ParseAsmOutVar(Tree* tree, Node* node, Lexeme* func_info)
{
    assert(tree);
    assert(node);
    assert(func_info);

    size_t start_index = GetIndexOfFuncInNameTable(tree->name_table,
                                                   func_info);

    int mem_ptr        = GetMemPtrOfVar(node, tree->name_table, start_index);
    IdentType var_type = GetTypeOfVar  (node, tree->name_table, start_index);

    if (IsInvalidNum(mem_ptr) || var_type == FUNC)
        return error;

    fprintf(log_file, "Enter ParseAsmOutVar\n");

    if (var_type == VAR)
        fprintf(asm_file, "mov rax, [rbp - %d] ;Получили данные из переменной |%s|\n", 
                                                                          mem_ptr * 8, 
                                                                          node->lexeme.str.name);
    else
        fprintf(asm_file, "mov rax, [rbp + %d] ;Получили данные из аргумента |%s|\n", 
                                                                         mem_ptr * 8, 
                                                                         node->lexeme.str.name);
            
    fprintf(asm_file, "push rax          \n\n");

    return success;
}

Status ParseAsmInVar(Tree* tree, Node* node, Lexeme* func_info)
{
    assert(tree);
    assert(node);
    assert(func_info);

    if (node->type == KEY_INT) node = node->left;

    size_t start_index = GetIndexOfFuncInNameTable(tree->name_table,
                                                     func_info);

    int mem_ptr        = GetMemPtrOfVar(node, tree->name_table, start_index);

    if (IsInvalidNum(mem_ptr))
    {
        fprintf(log_file, "Нет переменной |%s|", node->lexeme.str.name);
        return error;
    }

    fprintf(log_file, "Enter ParseAsmInVar\n");

    fprintf(asm_file, ";Запись в переменную |%s| \n", node->lexeme.str.name);
    fprintf(asm_file, "pop rax                   \n");
    
    fprintf(asm_file, "mov [rbp - %d], rax       \n\n", mem_ptr * 8);
    
    return success;
}

int GetMemPtrOfVar(Node* node, NameTable* name_table, size_t start_index)
{
    assert(name_table);

    for (size_t i = start_index; i < name_table->size; ++i)
    {
        if (   node->lexeme.str.hash == name_table->arr[i].hash
            && strcmp(node->lexeme.str.name, name_table->arr[i].name) == 0)
            return (int)name_table->arr[i].address;
    }

    return -1;
}

IdentType GetTypeOfVar(Node* node, NameTable* name_table, size_t start_index)
{
    assert(name_table);

    for (size_t i = start_index; i < name_table->size; ++i)
    {
        printf("NODE_NAME: %s      NAME_TBALE_EL: %s\n", node->lexeme.str.name,
                                                         name_table->arr[i].name);
        if (strcmp(node->lexeme.str.name, name_table->arr[i].name) == 0)
            return name_table->arr[i].type;
    }

    return FUNC;
}

size_t GetIndexOfFuncInNameTable(NameTable* name_table, Lexeme* func_info)
{
    assert(name_table);
    assert(func_info);

    size_t i = 0;

    for (; i < name_table->size; ++i)
    {
        //printf("NOW_FUNC: %s  -  SRC_FUNC: %s\n", func_info->str.name,name_table->arr[i].name);
        //printf("HASH_NOW_FUNC: %llu  -  HASH_SRC_FUNC: %llu\n", func_info->str.hash, name_table->arr[i].hash);
        if (   func_info->str.hash == name_table->arr[i].hash
            && strcmp(func_info->str.name, name_table->arr[i].name) == 0)
            return i;
    }

    //unreachable
    assert(false);
    return 0;
}

Status ParseAsmCallFunc(Tree* tree, Node* node, Lexeme* func_info)
{
    assert(node);
    assert(tree);
    assert(func_info);

    if (node->type != IDENT) return error;

    fprintf(log_file, "Enter ParseAsmCallFunc\n");

    Lexeme now_func = node->lexeme;
    //printf("LEXEME: %s\n", node->lexeme.str.name);
    size_t index = GetIndexOfFuncInNameTable(tree->name_table, &now_func);

    ParseAsmExpression(tree, node->left->right, func_info);

    fprintf(asm_file, "call .%s     \n", tree->name_table->arr[index].func_ptr);
    fprintf(asm_file, "push rax  ; Возвращаемое значение в rax\n\n"); 
    

    return success;
}

void ParseAsmFuncLabel(NameTable* name_table, Lexeme* func_info)
{
    assert(name_table);
    assert(func_info);

    size_t index = GetIndexOfFuncInNameTable(name_table, func_info);

    fprintf(asm_file, ".%s:         \n\n", name_table->arr[index].func_ptr);

    fprintf(asm_file, "push rbp     \n");
    fprintf(asm_file, "mov rbp, rsp \n");

    //Адрес первой переменной
    size_t var_addres = name_table->arr[index + 1].address;

    size_t var_in_main = CountVarInFunc(name_table, name_table->arr[index].name);
    fprintf(asm_file, "sub rsp, %zu \n\n", var_in_main * 8);
}

Lexeme GetMainLexeme()
{
    Lexeme main = {};
    main.str.name = strdup ("main");
    main.str.hash = GetHash("main");
    return main;
}

bool IsInvalidNum(int mem_ptr)
{
    return mem_ptr < 0 || mem_ptr > MAX_PTR;
}