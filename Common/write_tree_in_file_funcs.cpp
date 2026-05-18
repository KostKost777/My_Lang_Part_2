#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>

#include "tree_funcs.h"
#include "dump_funcs.h"
#include "write_tree_in_file_funcs.h"

void WriteTreeInFile(Tree* tree, const char* out_file_name)
{
    assert(tree);
    assert(out_file_name);

    FILE* out_file = fopen(out_file_name, "w+");

    WriteNode(tree->root, out_file);

    fprintf(out_file, "\n");

    WriteNameTable(tree->name_table, out_file);

    fclose(out_file);
}

void WriteNode(Node* node, FILE* out_file)
{
    assert(node);
    assert(out_file);

    fprintf(out_file,"( ");
    WriteNodeData(node, out_file);

    if (node->left != NULL)
        WriteNode(node->left, out_file);
    else
        fprintf(out_file, "nil ");

    if (node->right != NULL)
        WriteNode(node->right, out_file);
    else
        fprintf(out_file, "nil ");

    fprintf(out_file, ") ");
}

void WriteNodeData(Node* node, FILE* out_file)
{
    assert(node);
    assert(out_file);

    if (node->type == NUM)
        fprintf(out_file,"%d ", node->lexeme.num);

    else if (node->type == IDENT)
        fprintf(out_file,"%s ", node->lexeme.str.name);

    else if (node->type == KEY_LBRACE)
        fprintf(out_file,"{ ");

    else if (node->type == KEY_RBRACE)
        fprintf(out_file,"} ");

    else if (node->type == OP_BIGGER)
        fprintf(out_file,"> ");

    else if (node->type == OP_LESS)
        fprintf(out_file,"< ");

    else if (node->type == OP_BIGGER_OR_EQUAL)
        fprintf(out_file,">= ");

    else if (node->type == OP_LESS_OR_EQUAL)
        fprintf(out_file,"<= ");

    else
        fprintf(out_file, "%s ", GetNodeTypeName(node));
}

void WriteNameTable(NameTable* name_table, FILE* out_file)
{
    assert(out_file);

    for (size_t i = 0; i < name_table->size; ++i)
    {
        if (IsPlaceForMain(name_table, i) || (i == 0 && name_table->arr[i].type == VAR))
            fprintf(out_file, "FUNC    main\n");

        fprintf(out_file, "%s    %s\n", GetTypeOfNameTableEl(name_table->arr[i].type),
                                        name_table->arr[i].name);
    }
}

const char* GetTypeOfNameTableEl(IdentType type)
{
    switch(type)
    {
        case FUNC: return "FUNC";
        case VAR:  return "VAR";
        case ARG:  return "ARG";

        default: return NULL;
    }

    return NULL;
}

bool IsPlaceForMain(NameTable* name_table, size_t index)
{
    assert(name_table);

    return index >= 1
           && name_table->arr[index - 1].type != FUNC
           && name_table->arr[index].visible_space
              != name_table->arr[index - 1].visible_space;
}
