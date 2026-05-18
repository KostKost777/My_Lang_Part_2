
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <ctype.h>
#include <stdint.h>

const int MAX_BUF_SIZE     = 1000;
const int BASE_OFFSET      = 0x1000;
const int SIZE_OF_JMP_CODE = 5;

#define WRITE_LIB(...)                 \
        fprintf(lib_file, __VA_ARGS__) \

struct Buffer
{
    uint8_t* data;
    size_t capacity;
    size_t size;
};

struct SrcFileInfo
{
    const char* name;
    FILE* ptr;
    int  size;
};

struct SrcFileArr
{
    SrcFileInfo* data;
    int size;
};

static void        BufferCtor           (Buffer* buf, size_t capacity);

static void        BufferDtor           (Buffer* buf);

static void        SrcFileArrCtor       (SrcFileArr* src_file_arr, size_t capacity);

static void        SrcFileArrDtor       (SrcFileArr* src_file_arr);

static bool        IsSrcFileEnd         (FILE* file);

static void        FillBufFromFile      (Buffer* buf, const char* file_name);

static void        GenerateLibFile      (Buffer* buf, const char* lib_file_name, 
                                         SrcFileArr* src_file_arr);

static const char* GenerateBinLibFile   (SrcFileArr* src_file_arr);

static void        InitSrcFileArr       (const int argc, const char** argv, 
                                         SrcFileArr* src_file_arr);

static void        WriteJmpByte         (FILE* lib_file, const char* jmp_name, 
                                         int32_t offset);


int main(const int argc, const char** argv)
{
    const char* stdlib_file_name = NULL;
    SrcFileArr src_file_arr = {};

    SrcFileArrCtor(&src_file_arr, argc - 2);

    if (argc > 1) stdlib_file_name = argv[1];
    assert(stdlib_file_name);

    InitSrcFileArr(argc, argv, &src_file_arr);
    const char* bin_file_name = GenerateBinLibFile(&src_file_arr);

    Buffer buf = {};
    BufferCtor(&buf, MAX_BUF_SIZE);

    FillBufFromFile(&buf, bin_file_name);

    GenerateLibFile(&buf, stdlib_file_name, &src_file_arr);

    BufferDtor(&buf);
    SrcFileArrDtor(&src_file_arr);
}

static const char* GenerateBinLibFile (SrcFileArr* src_file_arr)
{
    assert(src_file_arr);

    const char* bin_file_name = "stdlib.bin";
    FILE* bin_file = fopen(bin_file_name, "wb");

    for (int i = 0; i < src_file_arr->size; ++i)
    {
        assert(src_file_arr->data[i].ptr);
        fseek(src_file_arr->data[i].ptr, BASE_OFFSET, SEEK_SET);

        while (!IsSrcFileEnd(src_file_arr->data[i].ptr))
        {
            uint8_t byte = fgetc(src_file_arr->data[i].ptr);
            fputc(byte, bin_file);
            src_file_arr->data[i].size++;
        }

        fclose(src_file_arr->data[i].ptr);
    }

    fclose(bin_file);

    return bin_file_name;
}

bool IsSrcFileEnd(FILE* file)
{
    long position = ftell(file);

    uint8_t byte_1 = fgetc(file);
    uint8_t byte_2 = fgetc(file);
    uint8_t byte_3 = fgetc(file);

    printf("BYTE_1 = %02X BYTE_2 = %02X BYTE_3 = %02X\n", 
            byte_1, byte_2, byte_3);

    if (byte_1 == '$' && byte_2 == '$' && byte_3 == '$')
    {
        fseek(file, position, SEEK_SET);
        return true;
    }

    fseek(file, position, SEEK_SET);
    return false;
}

static void InitSrcFileArr(const int argc, const char** argv, SrcFileArr* src_file_arr)
{
    assert(argv);
    assert(src_file_arr);

    for (int argv_i = 2, arr_i = 0; argv_i < argc; ++argv_i, ++arr_i)
    {
        src_file_arr->data[arr_i].name = argv[argv_i];
        src_file_arr->data[arr_i].ptr  = fopen(argv[argv_i], "rb");
        assert(src_file_arr->data[arr_i].ptr);
    }
}

static void GenerateLibFile (Buffer* buf, const char* lib_file_name, 
                             SrcFileArr* src_file_arr)
{
    assert(buf);
    assert(lib_file_name);
    assert(src_file_arr);

    FILE* lib_file = fopen(lib_file_name, "wb");
    assert(lib_file);

    WRITE_LIB ("#ifndef MY_STDLIB_FILE\n");
    WRITE_LIB ("#define MY_STDLIB_FILE\n");

    WRITE_LIB ("#include <stdint.h>\n\n");

    int follow_jmp_size = src_file_arr->size * SIZE_OF_JMP_CODE;
    int before_funcs_size = 0;

    WriteJmpByte (lib_file, "main", buf->size + follow_jmp_size);

    follow_jmp_size -= SIZE_OF_JMP_CODE;

    for (int i = 0; i < src_file_arr->size; ++i)
    {
        WriteJmpByte(lib_file, src_file_arr->data[i].name, 
                     before_funcs_size + follow_jmp_size);

        before_funcs_size += src_file_arr->data[i].size;
        follow_jmp_size -= SIZE_OF_JMP_CODE;
    }

    WRITE_LIB ("\n\n");
    WRITE_LIB ("uint8_t lib_bytes_arr[] = \"");

    for (int i = 0; i < buf->size; ++i)
        WRITE_LIB ("\\x%02X", buf->data[i]);

    WRITE_LIB ("\";\n\n");

    WRITE_LIB ("#endif MY_STDLIB_FILE\n");
    fclose(lib_file);
}

static void WriteJmpByte(FILE* lib_file, const char* jmp_name, int32_t offset)
{
    assert(jmp_name);

    WRITE_LIB ("uint8_t jmp_to_%s[] = \"\\xE9", jmp_name);

    for (int i = 0; i < 4; ++i)
    {
        uint8_t byte = (offset >> i * 8) & 0xFF;
        WRITE_LIB ("\\x%02X", byte);
    }

    WRITE_LIB ("\";\n");
}


static void FillBufFromFile(Buffer* buf, const char* file_name)
{
    assert(buf);
    assert(file_name);

    FILE* file = fopen(file_name, "rb");
    assert(file);

    size_t bytes_read = fread(buf->data, sizeof(uint8_t), buf->capacity, file);

    buf->size = bytes_read;
}

static void BufferCtor(Buffer* buf, size_t capacity)
{
    assert(buf);

    buf->data     = (uint8_t*)calloc(capacity, sizeof(uint8_t));
    buf->capacity = capacity;
    buf->size     = 0;
}

static void BufferDtor(Buffer* buf)
{
    assert(buf);

    free(buf->data);
    buf->capacity = 0;
    buf->size     = 0;
}

static void SrcFileArrCtor(SrcFileArr* src_file_arr, size_t size)
{
    assert(src_file_arr);

    src_file_arr->data = (SrcFileInfo*)calloc(size, sizeof(SrcFileInfo));
    src_file_arr->size = size;

}

static void SrcFileArrDtor(SrcFileArr* src_file_arr)
{
    assert(src_file_arr);

    free(src_file_arr->data);
    src_file_arr->size = 0;
}

