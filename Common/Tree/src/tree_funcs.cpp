#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>

#include "tree_funcs.h"
#include "name_table_funcs.h"

extern FILE* log_file;

Status TreeCtor(Tree* tree)
{
    assert(tree);

    tree->size = 0;
    tree->root = NULL;
    tree->is_draw = false;

    tree->name_table = NameTableCtor();

    return success;
}

void TreeDtor(Tree* tree)
{
    DeleteNode(tree, tree->root);

    tree->root = NULL;
    tree->size = 0;
}

void DeleteNode(Tree* tree, Node* node)
{
    assert(node);
    assert(tree);

    if (node->left)
        DeleteNode(tree, node->left);

    if (node->right)
        DeleteNode(tree, node->right);

    FreeNode(tree, node);
}

void FreeNode(Tree* tree, Node* node)
{
    assert(node);

    if (node->type != NUM && node->lexeme.str.name)
    { 
        free(node->lexeme.str.name);
        node->lexeme.str.name = NULL;
    }

    free(node);

    tree->size--;
    node = NULL;
}

Node* NewNode(Token token, Node* left, Node* right, Tree* tree)
{
    assert(tree);
    assert(log_file);

    fprintf(log_file, "\n\n<strong>CREATE NEW NODE</strong>\n");
    fprintf(log_file, "<strong0>TOKEN TYPE:     %d</strong0>\n", token.type);

    if (token.type == NUM)
        fprintf(log_file, "<strong0>NUM : |%d|</strong0>\n", token.lexeme.num);
    else
        fprintf(log_file, "<strong0>NAME: |%s|</strong0>\n", token.lexeme.str.name);

    fprintf(log_file, "<strong0>NEW TREE SIZE:  %zu</strong0>\n\n", tree->size + 1);

    Node* new_node = (Node*)calloc(1, sizeof(Node));
    assert(new_node);

    new_node->left = left;
    new_node->right = right;

    if (left) left->parent   = new_node;
    if (right) right->parent = new_node;

    new_node->type = token.type;

    if (token.type != NUM && token.lexeme.str.name) 
    {
        new_node->lexeme.str.name = strdup(token.lexeme.str.name);
        new_node->lexeme.str.hash = token.lexeme.str.hash;
    } 
    else
        new_node->lexeme.num = token.lexeme.num;

    tree->size++;

    return new_node;
}

