#ifndef NAME_TABLE_FUNCS
#define NAME_TABLE_FUNCS

const int MAX_NUM_OF_IDENT = 100;
const int MAX_LEN_OF_TYPE_NAME = 5;

enum IdentType
{
    VAR = 0,
    FUNC = 1
};

struct NameTableEl
{
    IdentType type;
    char* name;
    size_t hash;

    union
    {
        size_t visible_space;
        size_t address;
        char* func_ptr;
    };
};

struct NameTable
{
    NameTableEl* arr;
    size_t now_visible_space;
    size_t size;
};

NameTable* NameTableCtor();

void NameTableDtor(NameTable* name_table);

void FillNameTableFromBuffer(NameTable* name_table, char* cur_pos);

char* GetNewFuncPtr();

size_t GetVarAddress();

#endif
