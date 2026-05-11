#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>

#include "name_table_funcs.h"
#include "lexical_analysis.h"
#include "hash_funcs.h"

extern FILE* log_file;

NameTable* NameTableCtor()
{
    NameTable* name_table = (NameTable*)calloc(1, sizeof(NameTable));

    name_table->size = 0;
    name_table->now_visible_space = 0;

    name_table->arr = (NameTableEl*)calloc(MAX_NUM_OF_IDENT, sizeof(NameTableEl));
    return name_table;
}

void NameTableDtor(NameTable* name_table)
{
    assert(name_table);

    for (size_t i = 0; i < name_table->size; ++i)
    {
        if (name_table->arr[i].name)
        {
            free(name_table->arr[i].name);
            name_table->arr[i].name = NULL;
        }

        if (name_table->arr[i].type == FUNC)
        {
            free(name_table->arr[i].func_ptr);
            name_table->arr[i].func_ptr = NULL;
        }
    }

    free(name_table->arr);
    free(name_table);
}

void FillNameTableFromBuffer(NameTable* name_table, char* cur_pos)
{
    assert(name_table);
    assert(cur_pos);

    while (true)
    {
        char type_name[MAX_LEN_OF_TYPE_NAME] = {};
        int len = 0;
        sscanf (cur_pos, "%s%n", type_name, &len);

        if (len == 0) break;

        if (strcmp(type_name, "VAR") == 0)
        {
            name_table->arr[name_table->size].type = VAR;
            name_table->arr[name_table->size].address = GetVarAddress();
        }
        else
        {
            name_table->arr[name_table->size].type = FUNC;
            name_table->arr[name_table->size].func_ptr = GetNewFuncPtr();
        }

        cur_pos += len;

        char ident[MAX_LEN_OF_WORD] = {};
        len = 0;
        sscanf (cur_pos, "%s%n", ident, &len);
        cur_pos += len;

        name_table->arr[name_table->size].name = strdup(ident);
        name_table->arr[name_table->size].hash = GetHash(ident);

        name_table->size++;
    }
}

size_t GetVarAddress()
{
    static size_t counter = 0;
    counter++;
    return counter;
}

char* GetNewFuncPtr()
{
    char str_func_ptr[MAX_LEN_OF_WORD] = {};
    static int counter = 0;

    snprintf(str_func_ptr, sizeof(str_func_ptr),
             "func_%d", counter);

    counter++;
    return strdup(str_func_ptr);
}

void PrintTokenArray(TokenArray* tokens, size_t begin_pos)
{
    assert(begin_pos < tokens->size);

    for (size_t i = begin_pos; i < tokens->size; ++i)
    {
        fprintf(log_file, "TOKEN[%zu]:\n", i);

        if (tokens->arr[i].type == NUM)
            fprintf(log_file, "NUM NAME: |%d| ", tokens->arr[i].lexeme.num);

        else
            fprintf(log_file, "(%d) NAME: |%s| ", tokens->arr[i].type, tokens->arr[i].lexeme.str.name);

        fprintf(log_file, " LINE: %zu COLUMN: %zu",
                                   tokens->arr[i].line,
                                   tokens->arr[i].column);

        fprintf(log_file, "\n----------------------------\n\n");
    }
}

void PrintNameTable(NameTable* name_table)
{
    fprintf(log_file, "NOW_VISIBLE_SPACE: %zu\n",
                        name_table->now_visible_space);

    for (size_t i = 0; i < name_table->size; ++i)
    {
        fprintf(log_file, "TYPE: %d | NAME: |%s| | VISIBLE: %zu\n",
                                    name_table->arr[i].type,
                                    name_table->arr[i].name,
                                    name_table->arr[i].visible_space);
    }
}

void PrintNameTableInAsm(NameTable* name_table)
{
    for (size_t i = 0; i < name_table->size; ++i)
    {
        if (name_table->arr[i].type == VAR)
            fprintf(log_file, "TYPE: %d | NAME: |%s| | ADDRESS: %zu\n",
                                    name_table->arr[i].type,
                                    name_table->arr[i].name,
                                    name_table->arr[i].address);
        else
            fprintf(log_file, "TYPE: %d | NAME: |%s| | FUNC_PTR: %s\n",
                                    name_table->arr[i].type,
                                    name_table->arr[i].name,
                                    name_table->arr[i].func_ptr);

    }
}

size_t CountVarInFunc(NameTable* name_table, const char* func_name)
{
    assert(name_table);
    assert(func_name);

    size_t index = 0;
    size_t num_of_vars = 0;

    while(index < name_table->size)
    {
        printf("MY_FUNC: |%s|, NOW_FUNC: |%s|\n", func_name, name_table->arr[index].name);

        if (name_table->arr[index].type == FUNC
            && strcmp(name_table->arr[index].name, func_name) == 0)
            break;
        
        index++;
    }
        

    if (index >= name_table->size)
    {
        printf("\n\nDo not find func |%s|\n\n", func_name);
        assert(false);
    }

    index++;

    while(index < name_table->size && name_table->arr[index].type == VAR)
    {
        num_of_vars++;
        printf("NOW_VAR: |%s|, COUNTER: %d\n", name_table->arr[index].name, num_of_vars);
        index++;
    }

    return num_of_vars;
}

