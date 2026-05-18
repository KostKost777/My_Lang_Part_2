#ifndef EMITTER_FUNCS
#define EMITTER_FUNCS

#include "create_elf_file_funcs.h"

const int MOV_BYTE_CODE_LEN = 10;
const int MAX_LABEL_LEN     = 64;

enum RegName
{
    rax,
    rcx,
    rdx,
    rbx,
    rsp,
    rbp,
    rsi,
    rdi
};

enum JmpName{
    jo,
    jno,
    jb,
    jae,
    je,
    jne,
    jbe,
    ja,
    js,
    jns,
    jp,
    jnp,
    jl,
    jge,
    jle,
    jg,
    jmp
};

struct Reg
{
    RegName type;
    char*   name;
}; 

struct Jmp
{
    JmpName type;
    char*   name;
}; 

void Emit_MovRegInt(ElfBuffer* bin_buf, RegName reg, int64_t value);

void Emit_MovRegReg(ElfBuffer* bin_buf, RegName reg_dest, RegName reg_src);

void Emit_PushInt(ElfBuffer* bin_buf, int32_t value);

void Emit_PushReg(ElfBuffer* bin_buf, RegName reg);

void Emit_PopReg(ElfBuffer* bin_buf, RegName reg);

void Emit_SubRegReg(ElfBuffer* bin_buf, RegName reg_dest, RegName reg_src);

void Emit_SubRegInt(ElfBuffer* bin_buf, RegName reg, int32_t value);

void Emit_AddRegReg(ElfBuffer* bin_buf, RegName reg_dest, RegName reg_src);

void Emit_AddRegInt(ElfBuffer* bin_buf, RegName reg, int32_t value);

void Emit_Syscall(ElfBuffer* bin_buf); 

void Emit_Call(ElfBuffer* bin_buf, char* func_name);

void Emit_Ret(ElfBuffer* bin_buf);

void Emit_CmpRegReg(ElfBuffer* bin_buf, RegName reg_dest, RegName reg_src);

void Emit_CmpRegInt(ElfBuffer* bin_buf, RegName reg, int32_t value);

void Emit_CondJmp(ElfBuffer* bin_buf, JmpName jmp, char* label_name);

void Emit_Jmp(ElfBuffer* bin_buf, char* label_name);

void Emit_XorRegReg(ElfBuffer* bin_buf, RegName reg_dest, RegName reg_src);

void Emit_XorRegInt(ElfBuffer* bin_buf, RegName reg, int32_t value);

void Emit_TestRegInt(ElfBuffer* bin_buf, RegName reg, int32_t value);

void Emit_TestRegReg(ElfBuffer* bin_buf, RegName reg_1, RegName reg_2); 

void Emit_ImulReg(ElfBuffer* bin_buf, RegName reg);

void Emit_ImulRegReg(ElfBuffer* bin_buf, RegName reg_dest, RegName reg_src);

void Emit_Cqo(ElfBuffer* bin_buf);

void Emit_IdivReg(ElfBuffer* bin_buf, RegName reg);

void Emit_IncReg(ElfBuffer* bin_buf, RegName reg);

void Emit_MovRegMem(ElfBuffer* bin_buf, RegName reg, RegName base, int32_t offset);

void Emit_MovMemReg(ElfBuffer* bin_buf, RegName reg_dest, int32_t offset, RegName reg_src);

void AddLableInArr(Label* label_arr, size_t* size, size_t pos, char* label_name);

void Emit_Label(ElfBuffer* bin_buf, char* label_name);

void Emit_LabelsAddr(ElfBuffer* bin_buf);

void Emit_CallMyPrintf(ElfBuffer* bin_buf);

void Emit_CallMyScanf(ElfBuffer* bin_buf);

void Emit_CallPutChar(ElfBuffer* bin_buf);

size_t FindLabelInitPos(ElfBuffer* bin_buf, Label call_label);

void PrintLabelArrs(ElfBuffer* bin_buf);

bool IsEqualLabel(Label label_1, Label label_2);

void LabelArrDtor(Label* label_arr, size_t size);

char* GetRegName(RegName reg);

char* GetJmpName(JmpName jmp);

#endif