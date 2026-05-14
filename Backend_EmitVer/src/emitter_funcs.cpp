#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <ctype.h>

#include "parse_ast_tree_funcs.h"
#include "tree_funcs.h"
#include "lexical_analysis.h"
#include "dump_funcs.h"
#include "hash_funcs.h"
#include "emitter_funcs.h"
#include "emitter_DSL.h"

extern FILE* asm_file;

#define REG(type)     \
        {type, #type} \

#define JMP(type)     \
        {type, #type} \

struct Reg regs_arr[] = 
{  
    REG(rax), REG(rcx), REG(rdx), REG(rbx), 
    REG(rsp), REG(rbp), REG(rsi), REG(rdi)
};

struct Jmp jmp_arr[] = 
{  
    JMP(jo), JMP(jno), JMP(jb),  JMP(jae),
    JMP(je), JMP(jne), JMP(jbe), JMP(ja), 
    JMP(js), JMP(jns), JMP(jp),  JMP(jnp),
    JMP(jl), JMP(jge), JMP(jle), JMP(jg)
};

const int SIZE_OF_REGS_ARR = sizeof(regs_arr) / sizeof(Reg);
const int SIZE_OF_JMP_ARR  = sizeof(jmp_arr)  / sizeof(Jmp);

void Emit_MovRegInt(ElfBuffer* bin_buf, RegName reg, int64_t value)
{
    assert(bin_buf);

    WRITE_ASM("mov %s, %d\n", GetRegName(reg), value);
    
    BUF[POS++] = 0x48;
    BUF[POS++] = 0xB8 + reg;
    memcpy(BUF + POS, &value, 8);
    POS += 8;

    _EMIT_NOP();
}

void Emit_MovRegReg(ElfBuffer* bin_buf, RegName reg_dest, RegName reg_src)
{
    assert(bin_buf);

    WRITE_ASM("mov %s, %s\n", GetRegName(reg_dest), GetRegName(reg_src));
    
    BUF[POS++] = 0x48;
    BUF[POS++] = 0x89;
    BUF[POS++] = 0xC0 | (reg_src << 3) | reg_dest;

    _EMIT_NOP();
}

void Emit_PushInt(ElfBuffer* bin_buf, int value)
{
    assert(bin_buf);

    WRITE_ASM("push %d\n", value);

    BUF[POS++] = 0x68;              
    memcpy(BUF + POS, &value, 4);   
    POS += 4;

    _EMIT_NOP();
}

void Emit_PushReg(ElfBuffer* bin_buf, RegName reg)
{
    assert(bin_buf);

    WRITE_ASM("push %s\n", GetRegName(reg));
    
    BUF[POS++] = 0x50 + reg;

    _EMIT_NOP();
}

void Emit_SubRegReg(ElfBuffer* bin_buf, RegName reg_dest, RegName reg_src)
{
    assert(bin_buf);

    WRITE_ASM("sub %s, %s\n", GetRegName(reg_dest), GetRegName(reg_src));
    
    BUF[POS++] = 0x48;     
    BUF[POS++] = 0x29;   
    BUF[POS++] = 0xC0 | (reg_src << 3) | reg_dest;

    _EMIT_NOP();
}

void Emit_SubRegInt(ElfBuffer* bin_buf, RegName reg, int value)
{
    assert(bin_buf);

    WRITE_ASM("sub %s, %d\n", GetRegName(reg), value);
    
    BUF[POS++] = 0x48;
    BUF[POS++] = 0x81;
    BUF[POS++] = 0xE8 + reg;
    memcpy(BUF + POS, &value, 4);
    POS += 4;

    _EMIT_NOP();
}

void Emit_AddRegReg(ElfBuffer* bin_buf, RegName reg_dest, RegName reg_src)
{
    assert(bin_buf);

    WRITE_ASM("add %s, %s\n", GetRegName(reg_dest), GetRegName(reg_src));
    
    BUF[POS++] = 0x48;     
    BUF[POS++] = 0x01;   
    BUF[POS++] = 0xC0 | (reg_src << 3) | reg_dest;

    _EMIT_NOP();
}

void Emit_AddRegInt(ElfBuffer* bin_buf, RegName reg, int value)
{
    assert(bin_buf);

    WRITE_ASM("add %s, %d\n", GetRegName(reg), value);
    
    BUF[POS++] = 0x48;
    BUF[POS++] = 0x81;
    BUF[POS++] = 0xC0 + reg;
    memcpy(BUF + POS, &value, 4);
    POS += 4;

    _EMIT_NOP();
}

void Emit_PopReg(ElfBuffer* bin_buf, RegName reg)
{
    assert(bin_buf);

    WRITE_ASM("pop %s\n", GetRegName(reg));
    
    BUF[POS++] = 0x58 + reg;

    _EMIT_NOP();
}

void Emit_Syscall(ElfBuffer* bin_buf) 
{
    assert(bin_buf);

    WRITE_ASM("syscall\n");
    
    BUF[POS++] = 0x0F;
    BUF[POS++] = 0x05;

    _EMIT_NOP();
}

void Emit_Call(ElfBuffer* bin_buf, char* func_name) 
{
    assert(bin_buf);

    WRITE_ASM("call .%s\n", func_name);
    
    BUF[POS++] = 0xE8;

    AddLableInArr(bin_buf->call_label_arr, &bin_buf->call_label_size,
                  POS, func_name);

    BUF[POS++] = 0x00;
    BUF[POS++] = 0x00;
    BUF[POS++] = 0x00;
    BUF[POS++] = 0x00;

    _EMIT_NOP();
}

void Emit_Ret(ElfBuffer* bin_buf)
{
    assert(bin_buf);

    WRITE_ASM("ret\n");

    BUF[POS++] = 0xC3;

    _EMIT_NOP();
}

void Emit_CmpRegReg(ElfBuffer* bin_buf, RegName reg_1, RegName reg_2) 
{
    assert(bin_buf);

    WRITE_ASM("cmp %s, %s\n", GetRegName(reg_1), GetRegName(reg_2));
    
    BUF[POS++] = 0x48;     
    BUF[POS++] = 0x39;   
    BUF[POS++] = 0xC0 | (reg_1 << 3) | reg_2;

    _EMIT_NOP();
}

void Emit_CmpRegInt(ElfBuffer* bin_buf, RegName reg, int value) 
{
    assert(bin_buf);

    WRITE_ASM("cmp %s, %d\n", GetRegName(reg), value);
    
    BUF[POS++] = 0x48;     
    BUF[POS++] = 0x81;     
    BUF[POS++] = 0xF8 + reg;  
    memcpy(BUF + POS, &value, 4);     
    POS += 4;

    _EMIT_NOP();
}

void Emit_CondJmp(ElfBuffer* bin_buf, JmpName jmp, char* label_name) 
{
    assert(bin_buf);
    
    BUF[POS++] = 0x0F;  
    BUF[POS++] = 0x80 + jmp;

    AddLableInArr(bin_buf->call_label_arr, &bin_buf->call_label_size,
                  POS, label_name);

    BUF[POS++] = 0x00;
    BUF[POS++] = 0x00;
    BUF[POS++] = 0x00;
    BUF[POS++] = 0x00;

    _EMIT_NOP();
}

void Emit_Jmp(ElfBuffer* bin_buf, char* label_name) 
{
    assert(bin_buf);

    WRITE_ASM("jmp %s\n", label_name);
    
    BUF[POS++] = 0xE9;  

    AddLableInArr(bin_buf->call_label_arr, &bin_buf->call_label_size,
                  POS, label_name);

    BUF[POS++] = 0x00;
    BUF[POS++] = 0x00;
    BUF[POS++] = 0x00;
    BUF[POS++] = 0x00;

    _EMIT_NOP();
}

void Emit_XorRegReg(ElfBuffer* bin_buf, RegName reg_dest, RegName reg_src) 
{
    assert(bin_buf);

    WRITE_ASM("xor %s, %s\n", GetRegName(reg_dest), GetRegName(reg_src));
    
    BUF[POS++] = 0x48;     
    BUF[POS++] = 0x31;
    BUF[POS++] = 0xC0 | (reg_src << 3) | reg_dest;

    _EMIT_NOP();
}

void Emit_XorRegInt(ElfBuffer* bin_buf, RegName reg, int value) 
{
    assert(bin_buf);

    WRITE_ASM("xor %s, %d\n", GetRegName(reg), value);
    
    BUF[POS++] = 0x48;     
    BUF[POS++] = 0x81;     
    BUF[POS++] = 0xF0 + reg;  
    memcpy(BUF + POS, &value, 4); 
    POS += 4;
    
    _EMIT_NOP();
}

void Emit_TestRegInt(ElfBuffer* bin_buf, RegName reg, int value) 
{
    assert(bin_buf);

    WRITE_ASM("test %s, %d\n", GetRegName(reg), value);
    
    BUF[POS++] = 0x48;
    BUF[POS++] = 0xF7;
    BUF[POS++] = 0xC0 + reg;
    memcpy(BUF + POS, &value, 4);
    POS += 4;

    _EMIT_NOP();
}

void Emit_TestRegReg(ElfBuffer* bin_buf, RegName reg_1, RegName reg_2) 
{
    assert(bin_buf);

    WRITE_ASM("test %s, %s\n", GetRegName(reg_1),  GetRegName(reg_2));
    
    BUF[POS++] = 0x48;     
    BUF[POS++] = 0x85;     
    BUF[POS++] = 0xC0 | (reg_2 << 3) | reg_1;

    _EMIT_NOP();
}

void Emit_ImulReg(ElfBuffer* bin_buf, RegName reg) 
{
    assert(bin_buf);

    WRITE_ASM("imul %s\n", GetRegName(reg));
    
    BUF[POS++] = 0x48;                
    BUF[POS++] = 0xF7;                
    BUF[POS++] = 0xE8 + reg;  

    _EMIT_NOP();
}

void Emit_ImulRegReg(ElfBuffer* bin_buf, RegName reg_dest, RegName reg_src) 
{
    assert(bin_buf);

    WRITE_ASM("imul %s, %s\n", GetRegName(reg_dest), GetRegName(reg_src));
    
    BUF[POS++] = 0x48;     
    BUF[POS++] = 0x0F;     
    BUF[POS++] = 0xAF;     
    BUF[POS++] = 0xC0 | (reg_src << 3) | reg_dest; 

    _EMIT_NOP();
}

void Emit_Cqo(ElfBuffer* bin_buf) 
{
    assert(bin_buf);

    WRITE_ASM("cqo\n");
    
    BUF[POS++] = 0x48;
    BUF[POS++] = 0x99;

    _EMIT_NOP();
}

void Emit_IdivReg(ElfBuffer* bin_buf, RegName reg) 
{
    assert(bin_buf);
    
    WRITE_ASM("idiv %s\n", GetRegName(reg));
    
    BUF[POS++] = 0x48;                 
    BUF[POS++] = 0xF7;                 
    BUF[POS++] = 0xF8 + reg;

    _EMIT_NOP();
}

void Emit_IncReg(ElfBuffer* bin_buf, RegName reg) 
{
    assert(bin_buf);
    
    WRITE_ASM("inc %s\n", GetRegName(reg));
    
    BUF[POS++] = 0x48;                 
    BUF[POS++] = 0xFF;                 
    BUF[POS++] = 0xC0 + reg;

    _EMIT_NOP();
}

void Emit_MovRegMem(ElfBuffer* bin_buf, RegName reg_dest, RegName reg_src, int offset) 
{
    assert(bin_buf);

    if (offset < 0) WRITE_ASM("mov %s, [%s - %d]\n", GetRegName(reg_dest), 
                                                       GetRegName(reg_src), -offset);

    else            WRITE_ASM("mov %s, [%s + %d]\n", GetRegName(reg_dest), 
                                                       GetRegName(reg_src), offset);
    
    BUF[POS++] = 0x48;
    BUF[POS++] = 0x8B;
    BUF[POS++] = 0x80 | reg_src;
    memcpy(BUF + POS, &offset, 4);
    POS += 4;

    _EMIT_NOP();
}

void Emit_MovMemReg(ElfBuffer* bin_buf, RegName reg_dest, int offset, RegName reg_src) 
{
    assert(bin_buf);
    
    if (offset < 0)
        WRITE_ASM("mov [%s - %d], %s\n", GetRegName(reg_dest), -offset, 
                                           GetRegName(reg_src));
    else
        WRITE_ASM("mov [%s + %d], %s\n", GetRegName(reg_dest), offset, 
                                           GetRegName(reg_src));
    
    BUF[POS++] = 0x48;
    BUF[POS++] = 0x89;
    BUF[POS++] = 0x80 | reg_dest | (reg_src  << 3);
    
    memcpy(BUF + POS, &offset, 4);
    POS += 4;

    _EMIT_NOP();
}

void Emit_Label(ElfBuffer* bin_buf, char* label_name)
{
    assert(bin_buf);
    assert(label_name);

    WRITE_ASM("%s:\n", label_name);

    AddLableInArr(bin_buf->init_label_arr, &bin_buf->init_label_size,
                  POS, label_name);
}

void Emit_CallMyPrintf(ElfBuffer* bin_buf)
{
    assert(bin_buf);

    WRITE_ASM("call MyPrintf\n\n");

    uint32_t offset = 5 - (POS + 5);

    BUF[POS++] = 0xE8;

    memcpy(BUF + POS, &offset, 4);
    POS += 4;

    _EMIT_NOP();
}

void Emit_CallMyScanf(ElfBuffer* bin_buf)
{
    assert(bin_buf);

    WRITE_ASM("call MyScanf\n\n");

    uint32_t offset = 15 - (POS + 5);

    BUF[POS++] = 0xE8;

    memcpy(BUF + POS, &offset, 4);
    POS += 4;

    _EMIT_NOP();
}

void Emit_CallPutChar(ElfBuffer* bin_buf)
{
    assert(bin_buf);

    WRITE_ASM("call PutChar\n\n");

    uint32_t offset = 10 - (POS + 5);

    BUF[POS++] = 0xE8;

    memcpy(BUF + POS, &offset, 4);
    POS += 4;

    _EMIT_NOP();
}

void Emit_LabelsAddr(ElfBuffer* bin_buf)
{
    assert(bin_buf);

    for (int i = 0; i < bin_buf->call_label_size; ++i)
    {
        size_t call_pos = bin_buf->call_label_arr[i].pos;
        size_t init_pos = FindLabelInitPos(bin_buf, bin_buf->call_label_arr[i]);

        size_t dest_pos = init_pos - (call_pos + 4);

        memcpy(BUF + call_pos, &dest_pos, 4); 
    }
}

void AddLableInArr(Label* label_arr, size_t* size, size_t pos, char* label_name)
{
    assert(label_arr);
    assert(label_name);

    label_arr[*size].hash = GetHash(label_name);
    label_arr[*size].name = strdup (label_name);
    label_arr[*size].pos  = pos;

    *size += 1;
}

size_t FindLabelInitPos(ElfBuffer* bin_buf, Label call_label)
{
    assert(bin_buf);

    for (int i = 0; i < bin_buf->init_label_size; ++i)
    {
        Label init_label = bin_buf->init_label_arr[i];

        if (IsEqualLabel(call_label, init_label))
            return init_label.pos;
    }

    assert(false);
}

bool IsEqualLabel(Label label_1, Label label_2)
{
    if (label_1.hash == label_2.hash  && !strncmp(label_1.name, 
                                                  label_2.name, MAX_LABEL_LEN)) 
        return true;

    return false;
}

void LabelArrDtor(Label* label_arr, size_t size)
{
    assert(label_arr);

    for (int i = 0; i < size; ++i)
        free(label_arr[i].name);

    free(label_arr);
}

void PrintLabelArrs(ElfBuffer* bin_buf)
{
    assert(bin_buf);

    for (int i = 0; i < bin_buf->init_label_size; ++i)
    {
        Label init_label = bin_buf->init_label_arr[i];
        printf("INIT_NAME: |%s|, POS: %zu\n", bin_buf->init_label_arr[i].name,
                                              bin_buf->init_label_arr[i].pos);
    }

    printf("====================================\n\n");

    for (int i = 0; i < bin_buf->call_label_size; ++i)
    {
        Label init_label = bin_buf->call_label_arr[i];
        printf("CALL_NAME: |%s|, POS: %zu\n", bin_buf->call_label_arr[i].name,
                                              bin_buf->call_label_arr[i].pos);
    }
}

char* GetRegName(RegName reg)
{
    for (int i = 0; i < SIZE_OF_REGS_ARR; ++i)
        if (regs_arr[i].type == reg)
            return regs_arr[i].name;

    //unreachable;
    assert(false);
    return NULL;
}

char* GetJmpName(JmpName jmp)
{
    for (int i = 0; i < SIZE_OF_JMP_ARR; ++i)
        if (jmp_arr[i].type == jmp)
            return jmp_arr[i].name;

    //unreachable;
    assert(false);
    return NULL;
}