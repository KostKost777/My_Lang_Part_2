#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>

#include "lexical_analysis.h"
#include "syntactic_analysis.h"
#include "read_from_file_funcs.h"
#include "tree_funcs.h"
#include "dump_funcs.h"
#include "write_tree_in_file_funcs.h"

const char* source_file_name = "../Examples/src/factorial.txt";
const char* out_file_name = "../Examples/tree/outfile_tree.txt";

int main(const int argv, const char** argc)
{
    atexit(CloseLogFile);
    OpenLogFile();

    if (argv > 1)  source_file_name = argc[1];
    if (argv > 2)  out_file_name    = argc[2];

    Buffer buffer = {};
    GetDataFromFile(&buffer, source_file_name);

    printf("BUFFER: %s \n", buffer.data);
    TokenArray tokens = {};
    TokenArrayCtor(&tokens);

    size_t pos = 0;

    MakeLexicalAnalysis(&buffer, &pos, &tokens);
    BufferDtor(&buffer);
    PrintTokenArray(&tokens, 0);

    Tree tree = {};
    TreeCtor(&tree);

    MakeSyntacticAnalysis(&tree, &tokens);

    TreeDump(&tree);

    WriteTreeInFile(&tree, out_file_name);

    TokenArrayDtor(&tokens);
    NameTableDtor(tree.name_table);
    TreeDtor(&tree);
}
