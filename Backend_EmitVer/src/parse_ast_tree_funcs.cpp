#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <ctype.h>

#include "parse_ast_tree_funcs.h"
#include "tree_funcs.h"
#include "lexical_analysis.h"
#include "dump_funcs.h"
#include "hash_funcs.h"
#include "emitter_funcs.h"
#include "emitter_DSL.h"

extern const char* asm_file_name;
extern struct Reg regs_arr;
FILE* asm_file = NULL;

void Parse_AST_Tree(Tree* tree, Node* node, const char* asm_file_name,
                                            const char* bin_file_name)
{
    assert(tree);
    assert(node);
    assert(asm_file_name);
    assert(bin_file_name);

    fprintf(log_file, "Enter Parse_AST_Tree\n");

    asm_file = fopen(asm_file_name, "w");
    assert(asm_file);

    InputHeadOfAsmFile();

    Buffer bin_buf = {};
    BufferCtor(&bin_buf, MAX_SIZE_OF_ELF_FILE);

    Lexeme main = GetMainLexeme();
    ParseMain(tree, node, &main, &bin_buf);

    while(node->type == KEY_LBRACE)
    {
        ParseAsmFunc(tree, node->left);
        node = node->right;
    }

    free(main.str.name);
    fclose(asm_file);
    printf("\nEND");
}

void InputHeadOfAsmFile()
{
    WRITE_ASM("global _start  \n\n"
              "section .text  \n\n"
              "_start:        \n\n");
}

void ParseMain(Tree* tree, Node* node, Lexeme* main, Buffer* bin_buf)
{
    assert(tree);
    assert(node);
    assert(main);

    while(node->type == KEY_LBRACE)
        node = node->right;

    _PUSH_REG(rbp);
    _MOV_REG_REG(rbp, rsp);

    size_t var_in_main = CountVarInFunc(tree->name_table, "main");

    _SUB_REG_INT(rsp, var_in_main * 8);
    
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

        if (node->left->type == KEY_PUTCHAR)
            ParseAsmPutChar(tree, node->left, func_info);

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

void ParseAsmPutChar(Tree* tree, Node* node, Lexeme* func_info)   //FIX
{
    assert(tree);
    assert(node);
    assert(func_info);

    fprintf(log_file, "Enter ParseAsmPutChar\n");

    ParseAsmPutCharArg(tree, node->left);

    WRITE_ASM( "call PutChar\n\n");
}

void ParseAsmPutCharArg(Tree* tree, Node* node, Buffer* bin_buf)
{
    assert(tree);
    assert(node);

    if      (node->type == SPEC_SYM_SPACE) _MOV_REG_INT(rax, ' ')
    else if (node->type == SPEC_SYM_ENTER) _MOV_REG_INT(rax, '\n')
    else 
    {
        char sym = *node->lexeme.str.name;
        _MOV_REG_INT(rax, sym);
    }
}

void ParseAsmEnd(Tree* tree, Node* node, Lexeme* func_info,  Buffer* bin_buf)
{
    assert(tree);
    assert(node);
    assert(func_info);

    fprintf(log_file, "Enter ParseAsmEnd\n");

    _MOV_REG_REG(rsp, rbp);
    _POP_REG(rbp);

    _MOV_REG_INT(rax, 60);
    _MOV_REG_INT(rdi, 0);
    _SYSCALL();
}

void ParseAsmReturn(Tree* tree, Node* node, Lexeme* func_info, Buffer* bin_buf)
{
    assert(tree);
    assert(node);
    assert(func_info);

    fprintf(log_file, "Enter ParseAsmReturn\n");

    ParseAsmExpression(tree, node->left, func_info);

    _POP_REG(rax);

    _MOV_REG_REG(rsp, rbp);
    _POP_REG(rbp);

    _RET();
}

void ParseAsmIn(Tree* tree, Node* node, Lexeme* func_info, Buffer* bin_buf)
{
    assert(tree);
    assert(node);
    assert(func_info);

    fprintf(log_file, "Enter ParseAsmIn\n");

    WRITE_ASM( "call MyScanf  \n");

    _PUSH_REG(rax);

    ParseAsmInVar(tree, node->left, func_info);
}

void ParseAsmOut(Tree* tree, Node* node, Lexeme* func_info)
{
    assert(tree);
    assert(node);
    assert(func_info);

    fprintf(log_file, "Enter ParseAsmOut\n");

    ParseAsmExpression(tree, node->left, func_info);

    WRITE_ASM( "call MyPrintf  \n\n"); 
}

void ParseAsmIf(Tree* tree, Node* node, Lexeme* func_info, Buffer* bin_buf)
{
    assert(tree);
    assert(node);
    assert(func_info);

    fprintf(log_file, "Enter ParseAsmIf\n");

    static int counter = 0;
    char label_name[64] = {};
    sprintf(label_name, ".end_if_%d", counter);

    ParseAsmExpression(tree, node->left, func_info);

    _POP_REG(rax);
    _CMP_REG_INT(rax, 0);
    _COND_JMP(je, label_name);

    ParseAsmOperator(tree, node->right, func_info);

    WRITE_ASM("%s:", label_name);

    counter++;
}

void ParseAsmWhile(Tree* tree, Node* node, Lexeme* func_info, Buffer* bin_buf)
{
    assert(tree);
    assert(node);
    assert(func_info);

    fprintf(log_file, "Enter ParseAsmWhile\n");

    static int counter   = 0;

    char while_begin[64] = {};
    char while_end[64]   = {};

    sprintf(while_begin, ".begin_while_%d", counter);
    sprintf(while_end,   ".end_while_%d", counter);

    WRITE_ASM("%s:", while_begin);

    ParseAsmExpression(tree, node->left, func_info);

    _POP_REG(rax);
    _CMP_REG_INT(rax, 0);
    _COND_JMP(je, while_end);

    ParseAsmOperator(tree, node->right, func_info);

    _JMP(while_begin);

    WRITE_ASM("%s:", while_end);

    counter++;
}

void ParseAsmIfElse(Tree* tree, Node* node, Lexeme* func_info, Buffer* bin_buf)
{
    assert(tree);
    assert(node);
    assert(func_info);

    fprintf(log_file, "Enter ParseAsmIfElse\n");

    static int counter  = 0;

    char skip_if[64]    = {};
    char skip_else[64] = {};

    sprintf(skip_if,   ".skip_if_%d", counter);
    sprintf(skip_else, ".skip_else_%d", counter);

    ParseAsmExpression(tree, node->left, func_info);

    _POP_REG(rax);
    _CMP_REG_INT(rax, 0);
    _COND_JMP(je, skip_if);

    ParseAsmOperator(tree, node->right->left, func_info);

    _JMP(skip_else);
    WRITE_ASM("%s:", skip_if);

    ParseAsmOperator(tree, node->right->right, func_info);

    WRITE_ASM("%s:", skip_else);

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

Status ParseAsmOr(Tree* tree, Node* node, Lexeme* func_info, Buffer* bin_buf)
{
    assert(tree);
    assert(node);
    static int counter = 0;

    if (node->type != OP_OR)
        return error;

    fprintf(log_file, "Enter ParseAsmOr\n");

    WRITE_ASM    ( "; ||          \n"          );
    _XOR_REG_REG (rcx, rcx);
    _POP_REG     (rax);
    _POP_REG     (rbx);
    
    WRITE_ASM( "test rax, rax \n"          );    
    WRITE_ASM( "jnz .good_%d  \n", counter );    
    WRITE_ASM( "test rbx, rbx \n"          );
    WRITE_ASM( "jz .false_%d  \n", counter );   
    WRITE_ASM( ".good_%d:     \n", counter ); 
    WRITE_ASM( "mov rcx, 1    \n"          ); 
    WRITE_ASM( ".false_%d:    \n", counter ); 
    WRITE_ASM( "push rcx    \n\n"          ); 

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

    WRITE_ASM( "; &&          \n"          );
    WRITE_ASM( "xor rcx, rcx  \n"          ); 
    WRITE_ASM( "pop rax       \n"          );     
    WRITE_ASM( "pop rbx       \n"          );     
    WRITE_ASM( "test rax, rax \n"          );    
    WRITE_ASM( "jz .false_%d  \n", counter );    
    WRITE_ASM( "test rbx, rbx \n"          );    
    WRITE_ASM( "jz .false_%d  \n", counter );    
    WRITE_ASM( "mov rcx, 1    \n"          );    
    WRITE_ASM( ".false_%d:    \n", counter );   
    WRITE_ASM( "push rcx      \n\n"        );

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

    WRITE_ASM( "; >          \n");
    WRITE_ASM( "xor rcx, rcx \n");
    WRITE_ASM( "pop rax      \n");
    WRITE_ASM( "pop rbx      \n");
    WRITE_ASM( "cmp rbx, rax \n");
    WRITE_ASM( "setg cl      \n");
    WRITE_ASM( "push rcx     \n\n");

    return success;
}

Status ParseAsmEqual(Tree* tree, Node* node, Lexeme* func_info)
{
    assert(tree);
    assert(node);

    if (node->type != OP_EQUAL)
        return error;

    fprintf(log_file, "Enter ParseAsmEqual\n");

    WRITE_ASM( "; ==         \n");
    WRITE_ASM( "xor rcx, rcx \n");
    WRITE_ASM( "pop rax      \n");
    WRITE_ASM( "pop rbx      \n");
    WRITE_ASM( "cmp rbx, rax \n");
    WRITE_ASM( "setz cl      \n");
    WRITE_ASM( "push rcx     \n\n");

    return success;
}

Status ParseAsmNotEqual(Tree* tree, Node* node, Lexeme* func_info)
{
    assert(tree);
    assert(node);

    if (node->type != OP_NOT_EQUAL)
        return error;

    fprintf(log_file, "Enter ParseAsmNotEqual\n");

    WRITE_ASM( "; !=         \n");
    WRITE_ASM( "xor rcx, rcx \n");
    WRITE_ASM( "pop rax      \n");
    WRITE_ASM( "pop rbx      \n");
    WRITE_ASM( "cmp rbx, rax \n");
    WRITE_ASM( "setnz cl     \n");
    WRITE_ASM( "push rcx     \n\n");

    return success;
}

Status ParseAsmLess(Tree* tree, Node* node, Lexeme* func_info)
{
    assert(tree);
    assert(node);

    if (node->type != OP_LESS)
        return error;

    fprintf(log_file, "Enter ParseAsmLess\n");

    WRITE_ASM( "; <          \n");
    WRITE_ASM( "xor rcx, rcx \n");
    WRITE_ASM( "pop rax      \n");
    WRITE_ASM( "pop rbx      \n");
    WRITE_ASM( "cmp rbx, rax \n");
    WRITE_ASM( "setl cl      \n");
    WRITE_ASM( "push rcx     \n\n");

    return success;
}

Status ParseAsmNumber(Tree* tree, Node* node)
{
    assert(tree);
    assert(node);

    if (node->type != NUM) return error;

    fprintf(log_file, "Enter ParseAsmNumber\n");
    WRITE_ASM( "push %d ;������� ���������\n\n", node->lexeme.num);
    return success;
}

Status ParseAsmADD(Tree* tree, Node* node)
{
    assert(tree);
    assert(node);

    if (node->type != OP_ADD) return error;
    
    fprintf(log_file, "Enter ParseAsmADD \n");
    WRITE_ASM( "; ����� ���� �����\n");

    WRITE_ASM( "pop rax      \n");
    WRITE_ASM( "pop rbx      \n");
    WRITE_ASM( "add rax, rbx \n");
    WRITE_ASM( "push rax     \n\n");

    return success;
}

Status ParseAsmSUB(Tree* tree, Node* node)
{
    assert(tree);
    assert(node);

    if (node->type != OP_SUB) return error;
    
    fprintf(log_file, "Enter ParseAsmSUB    \n");
    WRITE_ASM( "; �������� ���� �����\n");

    WRITE_ASM( "pop rax      \n");
    WRITE_ASM( "pop rbx      \n");
    WRITE_ASM( "sub rbx, rax \n");
    WRITE_ASM( "push rbx     \n\n");

    return success;
}

Status ParseAsmMUL(Tree* tree, Node* node)
{
    assert(tree);
    assert(node);

    if (node->type != OP_MUL) return error;
    
    fprintf(log_file, "Enter ParseAsmMUL    \n");
    WRITE_ASM( ";��������� ���� �����\n");

    WRITE_ASM( "pop rax   \n");
    WRITE_ASM( "pop rbx   \n");
    WRITE_ASM( "imul rbx   \n");
    WRITE_ASM( "push rax  \n\n");

    return success;
}

Status ParseAsmDIV(Tree* tree, Node* node)
{
    assert(tree);
    assert(node);

    if (node->type != OP_DIV) return error;
    
    fprintf(log_file, "Enter ParseAsmDIV  \n");
    WRITE_ASM( ";������� ���� �����\n");

    WRITE_ASM( "pop rbx   \n");
    WRITE_ASM( "pop rax   \n");
    WRITE_ASM( "cqo   \n");
    WRITE_ASM( "idiv rbx   \n");
    WRITE_ASM( "push rax  \n\n");

    return success;
}

Status ParseAsmPOW(Tree* tree, Node* node)
{
    assert(tree);
    assert(node);

    if (node->type != OP_POW) return error;
    
    fprintf(log_file, "Enter ParseAsmPOW\n");
    WRITE_ASM( ";���������� � ������� ������\n");

    WRITE_ASM( "pop rax     \n");
    WRITE_ASM( "pop rcx     \n");
    WRITE_ASM( "shl rax, cl \n");
    WRITE_ASM( "push rax    \n\n");

    return success;
}

Status ParseAsmSQRT(Tree* tree, Node* node)
{
    assert(tree);
    assert(node);

    if (node->type != OP_SQRT) return error;

    static int counter = 0;
    
    fprintf(log_file, "Enter ParseAsmSQRT\n");
    WRITE_ASM( ";������ ������� � �����\n");

    WRITE_ASM( "pop rax               \n");
    WRITE_ASM( "xor rcx, rcx          \n");
    WRITE_ASM( ".sqvrt_%d:            \n",   counter);
    WRITE_ASM( "push rcx              \n");
    WRITE_ASM( "imul rcx, rcx         \n");
    WRITE_ASM( "cmp  rcx, rax         \n");
    WRITE_ASM( "jge  .end_sqvrt_%d    \n",   counter);
    WRITE_ASM( "pop rcx               \n");
    WRITE_ASM( "inc rcx               \n");
    WRITE_ASM( "jmp .sqvrt_%d         \n",   counter);
    WRITE_ASM( ".end_sqvrt_%d:        \n\n", counter);

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
        WRITE_ASM( "mov rax, [rbp - %d] ;�������� ������ �� ���������� |%s|\n", 
                                                                          mem_ptr * 8, 
                                                                          node->lexeme.str.name);
    else
        WRITE_ASM( "mov rax, [rbp + %d] ;�������� ������ �� ��������� |%s|\n", 
                                                                         mem_ptr * 8, 
                                                                         node->lexeme.str.name);
            
    WRITE_ASM( "push rax          \n\n");

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
        fprintf(log_file, "��� ���������� |%s|", node->lexeme.str.name);
        return error;
    }

    fprintf(log_file, "Enter ParseAsmInVar\n");

    WRITE_ASM( ";������ � ���������� |%s| \n", node->lexeme.str.name);
    WRITE_ASM( "pop rax                   \n");
    
    WRITE_ASM( "mov [rbp - %d], rax       \n\n", mem_ptr * 8);
    
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

    WRITE_ASM( "call .%s     \n", tree->name_table->arr[index].func_ptr);
    WRITE_ASM( "push rax  ; ������������ �������� � rax\n\n"); 
    

    return success;
}

void ParseAsmFuncLabel(NameTable* name_table, Lexeme* func_info)
{
    assert(name_table);
    assert(func_info);

    size_t index = GetIndexOfFuncInNameTable(name_table, func_info);

    WRITE_ASM( ".%s:         \n\n", name_table->arr[index].func_ptr);

    WRITE_ASM( "push rbp     \n");
    WRITE_ASM( "mov rbp, rsp \n");

    //����� ������ ����������
    size_t var_addres = name_table->arr[index + 1].address;

    size_t var_in_main = CountVarInFunc(name_table, name_table->arr[index].name);
    WRITE_ASM( "sub rsp, %zu \n\n", var_in_main * 8);
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