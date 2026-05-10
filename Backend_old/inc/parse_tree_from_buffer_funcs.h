#ifndef PARSE_TREE_FROM_BUFFER_FUNCS
#define PARSE_TREE_FROM_BUFFER_FUNCS

#include "tree_funcs.h"
#include "read_from_file_funcs.h"

void SkipSpaces(char** cur_pos);

Node* FillNodeDataFromBuffer(char** cur_pos, size_t* size, Node* parent);

bool IsNil(char* cur_pos);

void RaedNode(char** cur_pos, Node* node);

Type GetNodeType(char* ident_name);


#endif
