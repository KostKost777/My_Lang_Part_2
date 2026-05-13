#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <ctype.h>

#include "dump_funcs.h"
#include "tree_funcs.h"
#include "read_from_file_funcs.h"
#include "parse_tree_from_buffer_funcs.h"
#include "parse_ast_tree_funcs.h"

const char* source_file_name = "../Examples/tree/outfile.txt";
const char* asm_file_name    = "../Examples/asm/outfile.asm";
const char* bin_file_name    = "../Examples/elfs/oufile.bin";

int main (const int argc, const char** argv)
{
    atexit(CloseLogFile);
    OpenLogFile();

    if (argc > 1) source_file_name = argv[1];
    if (argc > 2) asm_file_name    = argv[2];
    if (argc > 3) bin_file_name    = argv[3];

    Buffer buffer = {};
    GetDataFromFile(&buffer, source_file_name);

    Tree tree = {};

    TreeCtor(&tree);

    char* cur_pos = buffer.data;
    tree.root = FillNodeDataFromBuffer(&cur_pos, &tree.size, tree.root);

    FillNameTableFromBuffer(tree.name_table, cur_pos);
    PrintNameTableInAsm(tree.name_table);

    TreeDump(&tree);

    Parse_AST_Tree(&tree, tree.root, asm_file_name, bin_file_name);

    NameTableDtor(tree.name_table);
    TreeDtor(&tree);
    BufferDtor(&buffer);
}
