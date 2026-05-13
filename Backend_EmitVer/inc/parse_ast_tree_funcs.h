#ifndef PARSE_AST_TREE_FUNCS
#define PARSE_AST_TREE_FUNCS

#include <stdlib.h>
#include "create_elf_file_funcs.h"

#include "tree_funcs.h"
#include "dump_funcs.h"

extern const char* asm_file_name;

const int SIZE_OF_FRAME = 5;
const int MAX_PTR = 1000;
const int MAX_SIZE_OF_ELF_FILE = 50000;

void Parse_AST_Tree(Tree* tree, Node* node, const char* asm_file_name,
                                            const char* bin_file_name);

void ParseAsmFunc(Tree* tree, Node* node, ElfBuffer* bin_buf);

void ParseAsmOperator(Tree* tree, Node* node, Lexeme* func_info, ElfBuffer* bin_buf);

void ParseAsmAssigned(Tree* tree, Node* node, Lexeme* func_info, ElfBuffer* bin_buf);

void ParseAsmReturn(Tree* tree, Node* node, Lexeme* func_info, ElfBuffer* bin_buf);

void ParseAsmIn(Tree* tree, Node* node, Lexeme* func_info, ElfBuffer* bin_buf);

void ParseAsmOut(Tree* tree, Node* node, Lexeme* func_info, ElfBuffer* bin_buf);

void ParseAsmIf(Tree* tree, Node* node, Lexeme* func_info, ElfBuffer* bin_buf);

void ParseAsmWhile(Tree* tree, Node* node, Lexeme* func_info, ElfBuffer* bin_buf);

void ParseAsmIfElse(Tree* tree, Node* node, Lexeme* func_info, ElfBuffer* bin_buf);

void ParseAsmExpression(Tree* tree, Node* node, Lexeme* func_info, ElfBuffer* bin_buf);

void PrintNodeInAsmFile(Tree* tree, Node* node, Lexeme* func_info, ElfBuffer* bin_buf);

void InputHeadOfAsmFile();

Status ParseAsmBigger(Tree* tree, Node* node, Lexeme* func_info, ElfBuffer* bin_buf);

Status ParseAsmEqual(Tree* tree, Node* node, Lexeme* func_info, ElfBuffer* bin_buf);

Status ParseAsmNotEqual(Tree* tree, Node* node, Lexeme* func_info, ElfBuffer* bin_buf);

Status ParseAsmLess(Tree* tree, Node* node, Lexeme* func_info, ElfBuffer* bin_buf);

bool IsInvalidNum(int mem_ptr);

Status ParseAsmNumber(Tree* tree, Node* node, ElfBuffer* bin_buf);

void ParseAsmEnd(Tree* tree, Node* node, Lexeme* func_info, ElfBuffer* bin_buf);

Status ParseAsmAnd(Tree* tree, Node* node, Lexeme* func_info, ElfBuffer* bin_buf);

Status ParseAsmOr(Tree* tree, Node* node, Lexeme* func_info, ElfBuffer* bin_buf);

Status ParseAsmADD(Tree* tree, Node* node, ElfBuffer* bin_buf);

Status ParseAsmSUB(Tree* tree, Node* node, ElfBuffer* bin_buf);

Status ParseAsmMUL(Tree* tree, Node* node, ElfBuffer* bin_buf);

Status ParseAsmDIV(Tree* tree, Node* node, ElfBuffer* bin_buf);

Status ParseAsmPOW(Tree* tree, Node* node, ElfBuffer* bin_buf);

Status ParseAsmSQRT(Tree* tree, Node* node, ElfBuffer* bin_buf);

Status ParseAsmPARAM(Tree* tree, Node* node, ElfBuffer* bin_buf);

void ParseAsmPutCharArg(Tree* tree, Node* node, ElfBuffer* bin_buf);

void ParseAsmPutChar(Tree* tree, Node* node, Lexeme* func_info, ElfBuffer* bin_buf);

Status ParseAsmOutVar(Tree* tree, Node* node, Lexeme* func_info, ElfBuffer* bin_buf);

Status ParseAsmInVar(Tree* tree, Node* node, Lexeme* func_info, ElfBuffer* bin_buf);

int GetMemPtrOfVar(Node* node, NameTable* name_table, size_t start_index);

IdentType GetTypeOfVar(Node* node, NameTable* name_table, size_t start_index);

size_t GetIndexOfFuncInNameTable(NameTable* name_table, Lexeme* func_info);

Status ParseAsmCallFunc(Tree* tree, Node* node, Lexeme* func_info, ElfBuffer* bin_buf);

void ParseAsmFuncLabel(NameTable* name_table, Lexeme* func_info, ElfBuffer* bin_buf);

void ParseMain(Tree* tree, Node* node, Lexeme* main, ElfBuffer* bin_buf);

Lexeme GetMainLexeme();

#define WRITE_ASM(...)              \
    fprintf(asm_file, __VA_ARGS__)  \

#endif
