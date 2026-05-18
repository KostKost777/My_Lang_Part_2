
#ifndef EMITTER_DSL
#define EMITTER_DSL

extern ElfBuffer* bin_buf;

#define BUF bin_buf->data
#define POS bin_buf->pos

const uint8_t _INSTR_64BIT     = 0x48;

const uint32_t MY_SCANF_ADDR   = sizeof(ElfHeader) + sizeof(ProgHeader) + 15 - (POS + 5);
const uint32_t MY_PRINTF_ADDR  = sizeof(ElfHeader) + sizeof(ProgHeader) + 5  - (POS + 5);
const uint32_t MY_PUTCHAR_ADDR = sizeof(ElfHeader) + sizeof(ProgHeader) + 10 - (POS + 5);

#define _EMIT_NOP()        \
        BUF[POS++] = 0x90; \

#define _MOV_REG_INT(reg_src, value)              \
        Emit_MovRegInt(bin_buf, reg_src, value);  \

#define _MOV_REG_REG(reg_src, reg_dest)              \
        Emit_MovRegReg(bin_buf, reg_src, reg_dest);  \

#define _PUSH_INT(value)               \
        Emit_PushInt(bin_buf, value);  \

#define _PUSH_REG(reg)               \
        Emit_PushReg(bin_buf, reg);  \

#define _POP_REG(reg)               \
        Emit_PopReg(bin_buf, reg);  \

#define _SUB_REG_INT(reg, value)              \
        Emit_SubRegInt(bin_buf, reg, value);  \

#define _SUB_REG_REG(reg_src, reg_dest)              \
        Emit_SubRegReg(bin_buf, reg_src, reg_dest);  \

#define _ADD_REG_INT(reg, value)              \
        Emit_AddRegInt(bin_buf, reg, value);  \

#define _ADD_REG_REG(reg_src, reg_dest)              \
        Emit_AddRegReg(bin_buf, reg_src, reg_dest);  \

#define _SYSCALL()              \
        Emit_Syscall(bin_buf);  \

#define _CALL(func_name)               \
        Emit_Call(bin_buf, func_name); \

#define _RET()             \
        Emit_Ret(bin_buf); \

#define _CMP_REG_REG(reg_1, reg_2)              \
        Emit_CmpRegReg(bin_buf, reg_1, reg_2);  \

#define _CMP_REG_INT(reg, value)             \
        Emit_CmpRegInt(bin_buf, reg, value); \

#define _JE(label_name)                       \
        Emit_Je(bin_buf, label_name);         \

#define _COND_JMP(jmp, label_name)               \
        Emit_CondJmp(bin_buf, jmp, label_name);  \

#define _JMP(label_name)                \
        Emit_Jmp(bin_buf, label_name);  \

#define _XOR_REG_REG(reg_dest, reg_src)             \
        Emit_XorRegReg(bin_buf, reg_dest, reg_src); \

#define _XOR_REG_INT(reg, value)             \
        Emit_XorRegInt(bin_buf, reg, value); \

#define _TEST_REG_REG(reg_1, reg_2)             \
        Emit_TestRegReg(bin_buf, reg_1, reg_2); \

#define _TEST_REG_INT(reg, value)             \
        Emit_TestRegInt(bin_buf, reg, value); \

#define _IMUL_REG(reg)                \
        Emit_ImulReg(bin_buf, reg);   \

#define _CPO()            \
        Emit_Cqo(bin_buf); \

#define _IDIV_REG(reg)             \
        Emit_IdivReg(bin_buf, reg); \
    
#define _IMUL_REG_REG(reg_dest, reg_src)           \
        Emit_ImulRegReg(bin_buf, reg_dest, reg_src); \

#define _INC_REG(reg)              \
        Emit_IncReg(bin_buf, reg); \

#define _MOV_REG_MEM(reg_dest, reg_src, offset)            \
        Emit_MovRegMem(bin_buf, reg_dest, reg_src, offset) \

#define _MOV_MEM_REG(reg_dest, offset, reg_src)            \
        Emit_MovMemReg(bin_buf, reg_dest, offset, reg_src) \

#define _LABEL(label_name)               \
        Emit_Label(bin_buf, label_name); \

#define _CALL_MYPRINTF()            \
        Emit_CallMyPrintf(bin_buf); \

#define _CALL_MYSCANF()             \
        Emit_CallMyScanf(bin_buf); \

#define _CALL_PUTCHAR()             \
        Emit_CallPutChar(bin_buf);  \

#define _EMIT_BYTE(byte)   \
        BUF[POS++] = byte; \

#define _EMIT_INT64(value)            \
        memcpy(BUF + POS, &value, 8); \
        POS += 8;                     \

#define _EMIT_INT32(value)            \
        memcpy(BUF + POS, &value, 4); \
        POS += 4;                     \

#define _OPCODE(code) \
        code          \

#define _MOD_RM(mod) \
        mod          \

#endif 