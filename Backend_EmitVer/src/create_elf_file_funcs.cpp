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

    Elf64_Ehdr elf_header = {};
    InitElfHeader(&elf_header, bin_buf);

    Elf64_Phdr prog_header = {};
    InitProgHeader(&prog_header, bin_buf);

    WriteBufInFile(bin_buf, elf_file_name);
}

void InitElfHeader(Elf64_Ehdr* elf_header, ElfBuffer* bin_buf)
{
    assert(elf_header);
    assert(bin_buf);    
    
    elf_header->e_ident[EI_MAG0]       = ELFMAG0;     
    elf_header->e_ident[EI_MAG1]       = ELFMAG1;     
    elf_header->e_ident[EI_MAG2]       = ELFMAG2;     
    elf_header->e_ident[EI_MAG3]       = ELFMAG3;     
    elf_header->e_ident[EI_CLASS]      = ELFCLASS64; 
    elf_header->e_ident[EI_DATA]       = ELFDATA2LSB; 
    elf_header->e_ident[EI_VERSION]    = EV_CURRENT; 
    elf_header->e_ident[EI_OSABI]      = ELFOSABI_SYSV; 
    elf_header->e_ident[EI_ABIVERSION] = 0;     
    
    for (int i = EI_PAD; i < EI_NIDENT; i++)
        elf_header->e_ident[i] = 0;

    elf_header->e_type      = ET_EXEC;              
    elf_header->e_machine   = EM_X86_64;         
    elf_header->e_version   = EV_CURRENT;        
    elf_header->e_entry     = 0x400000 + sizeof(Elf64_Ehdr) + sizeof(Elf64_Phdr);
    elf_header->e_phoff     = sizeof(Elf64_Ehdr);   
    elf_header->e_shoff     = 0;                   
    elf_header->e_flags     = 0;                   
    elf_header->e_ehsize    = sizeof(Elf64_Ehdr);  
    elf_header->e_phentsize = sizeof(Elf64_Phdr); 
    elf_header->e_phnum     = 1;                   
    elf_header->e_shentsize = 0;               
    elf_header->e_shnum     = 0;                   
    elf_header->e_shstrndx  = 0;                

    memcpy(BUF, elf_header, sizeof(Elf64_Ehdr)); 
}

void InitProgHeader(Elf64_Phdr* prog_header, ElfBuffer* bin_buf)
{
    assert(prog_header);
    assert(bin_buf);

    memset(prog_header, 0, sizeof(Elf64_Phdr));
    
    prog_header->p_type   = PT_LOAD;
    prog_header->p_flags  = PF_R | PF_X | PF_W;
    prog_header->p_offset = 0;                
    prog_header->p_vaddr  = 0x400000;        
    prog_header->p_paddr  = 0x400000;
    prog_header->p_filesz = POS - sizeof(Elf64_Ehdr) - sizeof(Elf64_Phdr);
    prog_header->p_memsz  = POS - sizeof(Elf64_Ehdr) - sizeof(Elf64_Phdr);
    prog_header->p_align  = 0x1000;

    memcpy(BUF + sizeof(Elf64_Ehdr), prog_header, sizeof(Elf64_Phdr));             
}

void WriteLibIntFile(ElfBuffer* bin_buf)
{
    assert(bin_buf);

    memcpy(BUF + POS, jmp_to_main,      sizeof(jmp_to_main));
    POS += sizeof(jmp_to_main) - 1;

    memcpy(BUF + POS, jmp_to_my_printf, sizeof(jmp_to_my_printf));
    POS += sizeof(jmp_to_my_printf) - 1;

    memcpy(BUF + POS, jmp_to_my_putchar,   sizeof(jmp_to_my_putchar));
    POS += sizeof(jmp_to_my_putchar) - 1;

    memcpy(BUF + POS, jmp_to_my_scanf,   sizeof(jmp_to_my_scanf));
    POS += sizeof(jmp_to_my_scanf) - 1;

    memcpy(BUF + POS, jmp_to_my_exit,   sizeof(jmp_to_my_exit));
    POS += sizeof(jmp_to_my_exit) - 1;

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

    bin_buf->pos = sizeof(Elf64_Ehdr) + sizeof(Elf64_Phdr);
}