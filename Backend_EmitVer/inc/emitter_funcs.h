#ifndef EMITTER_FUNCS
#define EMITTER_FUNCS

const int SIZE_OF_REGS_ARR = sizeof(regs_arr) / sizeof(Reg);
const int SIZE_OF_JMP_ARR  = sizeof(jmp_arr)  / sizeof(Jmp);

const int MOV_BYTE_CODE_LEN = 10;

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

void Emit_MovRegInt(Buffer* bin_buf, RegName reg, int value);

void Emit_MovRegReg(Buffer* bin_buf, RegName reg_dest, RegName reg_src);

void Emit_PushInt(Buffer* bin_buf, int value);

void Emit_PushReg(Buffer* bin_buf, RegName reg);

void Emit_PopReg(Buffer* bin_buf, RegName reg);

void Emit_SubRegReg(Buffer* bin_buf, RegName reg_dest, RegName reg_src);

void Emit_SubRegInt(Buffer* bin_buf, RegName reg, int value);

void Emit_AddRegReg(Buffer* bin_buf, RegName reg_dest, RegName reg_src);

void Emit_AddRegInt(Buffer* bin_buf, RegName reg, int value);

void Emit_Syscall(Buffer* bin_buf); 

void Emit_Call(Buffer* bin_buf, char* func_name);

void Emit_Ret(Buffer* bin_buf);

void Emit_CmpRegReg(Buffer* bin_buf, RegName reg_dest, RegName reg_src);

void Emit_CmpRegInt(Buffer* bin_buf, RegName reg, int value);

void Emit_CondJmp(Buffer* bin_buf, JmpName jmp, char* label_name);

void Emit_Jmp(Buffer* bin_buf, char* label_name);

void Emit_XorRegReg(Buffer* bin_buf, RegName reg_dest, RegName reg_src);

void Emit_XorRegInt(Buffer* bin_buf, RegName reg, int value);

void Emit_TestRegInt(Buffer* bin_buf, RegName reg, int value);

void Emit_TestRegReg(Buffer* bin_buf, RegName reg_1, RegName reg_2); 

void Emit_ImulReg(Buffer* bin_buf, RegName reg);

void Emit_ImulRegReg(Buffer* bin_buf, RegName reg_dest, RegName reg_src);

void Emit_Cqo(Buffer* bin_buf);

void Emit_IdivReg(Buffer* bin_buf, RegName reg);

void Emit_IncReg(Buffer* bin_buf, RegName reg);

void Emit_MovRegMem(Buffer* bin_buf, RegName reg, RegName base, int offset);

void Emit_MovMemReg(Buffer* bin_buf, RegName reg_dest, int offset, RegName reg_src);


#endif