#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <ctype.h>

#include "tree_funcs.h"
#include "lexical_analysis.h"
#include "dump_funcs.h"
#include "hash_funcs.h"
#include "emitter_funcs.h"
#include "emitter_DSL.h"
#include "create_elf_file_funcs.h"

void WriteBufInFile(ElfBuffer* bin_buf, const char* elf_file_name)
{
    assert(bin_buf);
    assert(elf_file_name);

    FILE* elf_file = fopen(elf_file_name, "w");
    assert(elf_file);

    size_t written_sym = fwrite(bin_buf->data, 1, bin_buf->pos, elf_file);
    
    assert(written_sym == bin_buf->pos);
    
    fclose(elf_file);
}

void ElfBufferDtor(ElfBuffer* bin_buf)
{
    assert(bin_buf);

    LabelArrDtor(bin_buf->init_label_arr, bin_buf->init_label_size);
    LabelArrDtor(bin_buf->call_label_arr, bin_buf->call_label_size);

    free(bin_buf->data);

    bin_buf->pos = 0;
    bin_buf->size = 0;
}

void ElfBufferCtor(ElfBuffer* bin_buf, size_t size)
{
    assert(bin_buf);

    bin_buf->size = size;

    bin_buf->data = (uint8_t* )calloc(bin_buf->size + 1, sizeof(uint8_t));
    assert(bin_buf->data != NULL);

    bin_buf->init_label_arr  = (Label* )calloc(MAX_NUM_OF_LABELS, sizeof(Label));
    bin_buf->init_label_size = 0;

    bin_buf->call_label_arr  = (Label* )calloc(MAX_NUM_OF_LABELS, sizeof(Label));
    bin_buf->call_label_size = 0;

    bin_buf->pos = 0;
}