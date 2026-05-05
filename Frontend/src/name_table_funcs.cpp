#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>

#include "name_table_funcs.h"
#include "lexical_analysis.h"
#include "hash_funcs.h"

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
        if (name_table->arr[i].name != NULL)
            free(name_table->arr[i].name);
        name_table->arr[i].name = NULL;
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
        //printf("IDENT: %s   CUR_POS: %d \n", ident, *cur_pos);

        name_table->arr[name_table->size].name = strdup(ident);
        name_table->arr[name_table->size].hash = GetHash(ident);

        name_table->size++;
    }
}

size_t GetVarAddress()
{
    static int counter = -1;
    counter++;
    return (size_t)counter;
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
