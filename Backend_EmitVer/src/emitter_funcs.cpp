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

void Emit_MovRegInt(Buffer* bin_buf, RegName reg, int value)
{
    assert(bin_buf);

    WRITE_ASM("mov %s, %d\n", GetRegName(reg), value);
    
    BUF[POS++] = 0x48;
    BUF[POS++] = 0xB8 + reg;
    memcpy(BUF + POS, &value, 8);
    POS += 8;

    _EMIT_NOP();
}

void Emit_MovRegReg(Buffer* bin_buf, RegName reg_dest, RegName reg_src)
{
    assert(bin_buf);

    WRITE_ASM("mov %s, %s\n", GetRegName(reg_dest), GetRegName(reg_src));
    
    BUF[POS++] = 0x48;
    BUF[POS++] = 0x89;
    BUF[POS++] = 0xC0 | (reg_src << 3) | reg_dest;

    _EMIT_NOP();
}

void Emit_PushInt(Buffer* bin_buf, int value)
{
    assert(bin_buf);

    WRITE_ASM("push %d", value);

    BUF[POS++] = 0x68;              
    memcpy(BUF + POS, &value, 4);   
    POS += 4;

    _EMIT_NOP();
}

void Emit_PushReg(Buffer* bin_buf, RegName reg)
{
    assert(bin_buf);

    WRITE_ASM("push %s", GetRegName(reg));
    
    BUF[POS++] = 0x50 + reg;

    _EMIT_NOP();
}

void Emit_SubRegReg(Buffer* bin_buf, RegName reg_dest, RegName reg_src)
{
    assert(bin_buf);

    WRITE_ASM("sub %s, %s\n", GetRegName(reg_dest), GetRegName(reg_src));
    
    BUF[POS++] = 0x48;     
    BUF[POS++] = 0x29;   
    BUF[POS++] = 0xC0 | (reg_src << 3) | reg_dest;

    _EMIT_NOP();
}

void Emit_SubRegInt(Buffer* bin_buf, RegName reg, int value)
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

void Emit_AddRegReg(Buffer* bin_buf, RegName reg_dest, RegName reg_src)
{
    assert(bin_buf);

    WRITE_ASM("add %s, %s\n", GetRegName(reg_dest), GetRegName(reg_src));
    
    BUF[POS++] = 0x48;     
    BUF[POS++] = 0x01;   
    BUF[POS++] = 0xC0 | (reg_src << 3) | reg_dest;

    _EMIT_NOP();
}

void Emit_AddRegInt(Buffer* bin_buf, RegName reg, int value)
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

void Emit_PopReg(Buffer* bin_buf, RegName reg)
{
    assert(bin_buf);

    WRITE_ASM("pop %s\n", GetRegName(reg));
    
    BUF[POS++] = 0x58 + reg;

    _EMIT_NOP();
}

void Emit_Syscall(Buffer* bin_buf) 
{
    assert(bin_buf);

    WRITE_ASM("syscall\n");
    
    BUF[POS++] = 0x0F;
    BUF[POS++] = 0x05;

    _EMIT_NOP();
}

void Emit_Call(Buffer* bin_buf, char* func_name) 
{
    assert(bin_buf);

    WRITE_ASM("call .%s\n", func_name);
    
    BUF[POS++] = 0xE8;

    BUF[POS++] = 0x00;
    BUF[POS++] = 0x00;
    BUF[POS++] = 0x00;
    BUF[POS++] = 0x00;

    _EMIT_NOP();
}

void Emit_Ret(Buffer* bin_buf)
{
    assert(bin_buf);

    WRITE_ASM("ret\n");

    BUF[POS++] = 0xC3;

    _EMIT_NOP();
}

void Emit_CmpRegReg(Buffer* bin_buf, RegName reg_1, RegName reg_2) 
{
    assert(bin_buf);

    WRITE_ASM("cmp %s, %s\n", GetRegName(reg_1), GetRegName(reg_2));
    
    BUF[POS++] = 0x48;     
    BUF[POS++] = 0x39;   
    BUF[POS++] = 0xC0 | (reg_1 << 3) | reg_2;

    _EMIT_NOP();
}

void Emit_CmpRegInt(Buffer* bin_buf, RegName reg, int value) 
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

void Emit_CondJmp(Buffer* bin_buf, JmpName jmp, char* label_name) 
{
    assert(bin_buf);

    WRITE_ASM("%s %s\n", GetJmpName(jmp), label_name);
    
    BUF[POS++] = 0x0F;  
    BUF[POS++] = 0x80 + jmp;

    BUF[POS++] = 0x00;
    BUF[POS++] = 0x00;
    BUF[POS++] = 0x00;
    BUF[POS++] = 0x00;

    _EMIT_NOP();
}

void Emit_Jmp(Buffer* bin_buf, char* label_name) 
{
    assert(bin_buf);

    WRITE_ASM("jmp %s\n", label_name);
    
    BUF[POS++] = 0xE9;  

    BUF[POS++] = 0x00;
    BUF[POS++] = 0x00;
    BUF[POS++] = 0x00;
    BUF[POS++] = 0x00;

    _EMIT_NOP();
}

void Emit_Jmp(Buffer* bin_buf, char* label_name) 
{
    assert(bin_buf);

    WRITE_ASM("jmp %s\n", label_name);
    
    BUF[POS++] = 0xE9;  

    BUF[POS++] = 0x00;
    BUF[POS++] = 0x00;
    BUF[POS++] = 0x00;
    BUF[POS++] = 0x00;

    _EMIT_NOP();
}

void Emit_Jmp(Buffer* bin_buf, char* label_name) 
{
    assert(bin_buf);

    WRITE_ASM("jmp %s\n", label_name);
    
    BUF[POS++] = 0xE9;  

    BUF[POS++] = 0x00;
    BUF[POS++] = 0x00;
    BUF[POS++] = 0x00;
    BUF[POS++] = 0x00;

    _EMIT_NOP();
}

void Emit_XorRegReg(Buffer* bin_buf, RegName reg_dest, RegName reg_src) 
{
    assert(bin_buf);

    WRITE_ASM("xor %s, %s\n", GetRegName(reg_dest), GetRegName(reg_src));
    
    BUF[POS++] = 0x48;     
    BUF[POS++] = 0x31;
    BUF[POS++] = 0xC0 | (reg_src << 3) | reg_dest;

    _EMIT_NOP();
}

void Emit_XorRegInt(Buffer* bin_buf, RegName reg, int value) 
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

void Emit_TestRegInt(Buffer* bin_buf, RegName reg, int value) 
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

void Emit_TestRegReg(Buffer* bin_buf, RegName reg_1, RegName reg_2) 
{
    assert(bin_buf);

    WRITE_ASM("test %s, %s\n", GetRegName(reg_1),  GetRegName(reg_2));
    
    BUF[POS++] = 0x48;     
    BUF[POS++] = 0x85;     
    BUF[POS++] = 0xC0 | (reg_2 << 3) | reg_1;

    _EMIT_NOP();
}

void Emit_ImulReg(Buffer* bin_buf, RegName reg) 
{
    assert(bin_buf);

    WRITE_ASM("imul %s\n", GetRegName(reg));
    
    BUF[POS++] = 0x48;                
    BUF[POS++] = 0xF7;                
    BUF[POS++] = 0xE8 + reg;  

    _EMIT_NOP();
}

void Emit_ImulRegReg(Buffer* bin_buf, RegName reg_dest, RegName reg_src) 
{
    assert(bin_buf);

    WRITE_ASM("imul %s, %s\n", GetRegName(reg_dest), GetRegName(reg_src));
    
    BUF[POS++] = 0x48;     
    BUF[POS++] = 0x0F;     
    BUF[POS++] = 0xAF;     
    BUF[POS++] = 0xC0 | (reg_src << 3) | reg_dest; 

    _EMIT_NOP();
}

void Emit_Cqo(Buffer* bin_buf) 
{
    assert(bin_buf);

    WRITE_ASM("cqo\n");
    
    BUF[POS++] = 0x48;
    BUF[POS++] = 0x99;

    _EMIT_NOP();
}

void Emit_IdivReg(Buffer* bin_buf, RegName reg) 
{
    assert(bin_buf);
    
    WRITE_ASM("idiv %s\n", GetRegName(reg));
    
    BUF[POS++] = 0x48;                 
    BUF[POS++] = 0xF7;                 
    BUF[POS++] = 0xF8 + reg;

    _EMIT_NOP();
}

void Emit_IncReg(Buffer* bin_buf, RegName reg) 
{
    assert(bin_buf);
    
    WRITE_ASM("inc %s\n", GetRegName(reg));
    
    BUF[POS++] = 0x48;                 
    BUF[POS++] = 0xFF;                 
    BUF[POS++] = 0xC0 + reg;

    _EMIT_NOP();
}

void Emit_MovRegMem(Buffer* bin_buf, RegName reg_dest, RegName reg_src, int offset) 
{
    assert(bin_buf);

    if (offset < 0) WRITE_ASM("mov %s, [%s - 0x%x]\n", GetRegName(reg_dest), 
                                                       GetRegName(reg_src), -offset);

    else            WRITE_ASM("mov %s, [%s + 0x%x]\n", GetRegName(reg_dest), 
                                                       GetRegName(reg_src), offset);
    
    BUF[POS++] = 0x48;
    BUF[POS++] = 0x8B;
    BUF[POS++] = 0x80 | reg_src;
    memcpy(BUF + POS, &offset, 4);
    POS += 4;

    _EMIT_NOP();
}

void Emit_MovMemReg(Buffer* bin_buf, RegName reg_dest, int offset, RegName reg_src) 
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
    BUF[POS++] =  0x80 | reg_dest | (reg_src  << 3);
    
    memcpy(BUF + POS, &offset, 4);
    POS += 4;

    _EMIT_NOP();
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