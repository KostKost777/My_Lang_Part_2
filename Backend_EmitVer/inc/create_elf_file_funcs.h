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

struct ElfHeader 
{
    uint8_t       e_ident[16];         // 0-15: магические числа + информация
    uint16_t      e_type;              // 16-17: ET_EXEC (2), ET_DYN (3)
    uint16_t      e_machine;           // 18-19: EM_X86_64 (62)
    uint32_t      e_version;           // 20-23: 1 (EV_CURRENT)
    uint64_t      e_entry;             // 24-31: точка входа (вирт. адрес)
    uint64_t      e_phoff;             // 32-39: смещение до program headers (обычно 64)
    uint64_t      e_shoff;             // 40-47: смещение до section headers (0 если нет)
    uint32_t      e_flags;             // 48-51: флаги (обычно 0)
    uint16_t      e_ehsize;            // 52-53: размер ELF header (64)
    uint16_t      e_phentsize;         // 54-55: размер одного program header (56)
    uint16_t      e_phnum;             // 56-57: количество program headers (минимум 1)
    uint16_t      e_shentsize;         // 58-59: размер section header (0 если нет)
    uint16_t      e_shnum;             // 60-61: количество section headers (0)
    uint16_t      e_shstrndx;          // 62-63: индекс строковой таблицы (0)
};

struct ProgHeader
{
    uint32_t   type;   // 0-3:   PT_LOAD (1), PT_INTERP (3) и т.д.
    uint32_t   flags;  // 4-7:   PF_X (1), PF_W (2), PF_R (4)
    uint64_t   offset; // 8-15:  смещение в файле
    uint64_t   vaddr;  // 16-23: виртуальный адрес в памяти
    uint64_t   paddr;  // 24-31: физический адрес (обычно = p_vaddr)
    uint64_t   filesz; // 32-39: размер в файле
    uint64_t   memsz;  // 40-47: размер в памяти
    uint64_t   align;  // 48-55: выравнивание (обычно 0x1000 для LOAD)
};

void WriteLibIntFile(ElfBuffer* bin_buf);

void InitElfHeader(ElfHeader* elf_header, ElfBuffer* bin_buf);

void InitProgHeader(ProgHeader* prog_header, ElfBuffer* bin_buf);

void ElfBufferCtor(ElfBuffer* bin_buf, size_t size);

void ElfBufferDtor(ElfBuffer* bin_buf);

void BuildElfFile(ElfBuffer* bin_buf, const char* elf_file_name);

void WriteBufInFile(ElfBuffer* bin_buf, const char* elf_file_name);

#endif
