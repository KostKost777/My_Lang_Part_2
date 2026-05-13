#ifndef CREATE_ELF_FILE_FUNCS
#define CREATE_ELF_FILE_FUNCS

#include <stdint.h>
const int MAX_NUM_OF_LABELS = 100;

struct Label
{
    char*  name;
    size_t hash;
    size_t pos;
};

struct ElfBuffer
{
    uint8_t* data;
    size_t pos;
    size_t size;

    Label* init_label_arr;
    size_t init_label_size;

    Label* call_label_arr;
    size_t call_label_size;
};

void ElfBufferCtor(ElfBuffer* bin_buf, size_t size);

void ElfBufferDtor(ElfBuffer* bin_buf);

void WriteBufInFile(ElfBuffer* bin_buf, const char* elf_file_name);

#endif
