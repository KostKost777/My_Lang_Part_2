#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <ctype.h>
#include <elf.h>

#include "tree_funcs.h"
#include "lexical_analysis.h"
#include "dump_funcs.h"
#include "hash_funcs.h"
#include "emitter_funcs.h"
#include "emitter_DSL.h"
#include "create_elf_file_funcs.h"
#include "my_stdlib.h"


void BuildElfFile(ElfBuffer* bin_buf, const char* elf_file_name)
{
    assert(bin_buf);
    assert(elf_file_name);

    struct ElfHeader elf_header = {};
    InitElfHeader(&elf_header, bin_buf);

    struct ProgHeader prog_header = {};
    InitProgHeader(&prog_header, bin_buf);

    WriteBufInFile(bin_buf, elf_file_name);
}

//REMAKE: elf.h

void InitProgHeader(ProgHeader* prog_header, ElfBuffer* bin_buf)
{
    assert(prog_header);

    prog_header->type   = 1;
    prog_header->flags  = 4 | 1;
    prog_header->offset = 0;       
    prog_header->vaddr  = 0x400000;
    prog_header->paddr  = 0x400000;
    prog_header->filesz = POS - sizeof(ElfHeader) - sizeof(ProgHeader);
    prog_header->memsz  = POS - sizeof(ElfHeader) - sizeof(ProgHeader);
    prog_header->align  = 0x1000;

    memcpy(BUF + sizeof(ElfHeader), prog_header, sizeof(ProgHeader));             
}

void InitElfHeader(ElfHeader* elf_header, ElfBuffer* bin_buf)
{
    assert(elf_header);
    
    elf_header->e_ident[0] = 0x7f;
    elf_header->e_ident[1] = 'E';
    elf_header->e_ident[2] = 'L';
    elf_header->e_ident[3] = 'F';
    elf_header->e_ident[4] = 2;
    elf_header->e_ident[5] = 1;
    elf_header->e_ident[6] = 1; 
    elf_header->e_ident[7] = 0; 
    elf_header->e_ident[8] = 0;  

    for (int i = 9; i < 16; i++)
        elf_header->e_ident[i] = 0;

    elf_header->e_type = 2;
    elf_header->e_machine = 62;
    elf_header->e_version = 1;
    elf_header->e_entry = 0x400000 + sizeof(ElfHeader) + sizeof(ProgHeader);
    elf_header->e_phoff = sizeof(ElfHeader);
    elf_header->e_shoff = 0;
    elf_header->e_flags = 0;
    elf_header->e_ehsize = sizeof(ElfHeader);
    elf_header->e_phentsize = sizeof(ProgHeader);
    elf_header->e_phnum = 1;
    elf_header->e_shentsize = 0;
    elf_header->e_shnum = 0;
    elf_header->e_shstrndx = 0;

    memcpy(BUF, elf_header, sizeof(ElfHeader)); 
}

void WriteLibIntFile(ElfBuffer* bin_buf)
{
    assert(bin_buf);

    memcpy(BUF + POS, jmp_main,      sizeof(jmp_main));
    POS += sizeof(jmp_main) - 1;

    memcpy(BUF + POS, jmp_my_printf, sizeof(jmp_my_printf));
    POS += sizeof(jmp_my_printf) - 1;

    memcpy(BUF + POS, jmp_putchar,   sizeof(jmp_putchar));
    POS += sizeof(jmp_putchar) - 1;

    memcpy(BUF + POS, jmp_myscanf,   sizeof(jmp_myscanf));
    POS += sizeof(jmp_myscanf) - 1;

    memcpy(BUF + POS, lib_bytes_arr, sizeof(lib_bytes_arr));
    POS += sizeof(lib_bytes_arr) - 1;
}

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

    bin_buf->pos = sizeof(ElfHeader) + sizeof(ProgHeader);
}