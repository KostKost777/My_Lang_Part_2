
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <ctype.h>
#include <stdint.h>

const int MAX_BUF_SIZE = 1000;

#define WRITE_LIB(...)                 \
        fprintf(lib_file, __VA_ARGS__) \

struct Buffer
{
    uint8_t* data;
    size_t capacity;
    size_t size;
};

static void BufferCtor      (Buffer* buf, size_t capacity);
static void BufferDtor      (Buffer* buf);
static void FillBufFromFile (Buffer* buf, const char* file_name);
static void GenerateLibFile (Buffer* buf, const char* lib_file_name);

int main(const int argc, const char** argv)
{
    const char* stdlib_file_name = "";
    const char* bin_file_name    = "";

    if (argc > 1) stdlib_file_name = argv[1];
    if (argc > 2) bin_file_name    = argv[2];

    assert(stdlib_file_name);
    assert(bin_file_name);

    Buffer buf = {};
    BufferCtor(&buf, MAX_BUF_SIZE);

    FillBufFromFile(&buf, bin_file_name);

    GenerateLibFile(&buf, stdlib_file_name);

    BufferDtor(&buf);
}

static void GenerateLibFile (Buffer* buf, const char* lib_file_name)
{
    assert(buf);
    assert(lib_file_name);

    FILE* lib_file = fopen(lib_file_name, "wb");
    assert(lib_file);

    WRITE_LIB ("#ifndef MY_STDLIB_FILE\n");
    WRITE_LIB ("#define MY_STDLIB_FILE\n");

    WRITE_LIB ("#include <stdint.h>\n\n");

    //TODO: автоматизировать
    // printf: scanf: 

    WRITE_LIB ("uint8_t jmp_main[]      = \"\\xE9\\x35\\x01\\x00\\x00\";\n");
    WRITE_LIB ("uint8_t jmp_my_printf[] = \"\\xE9\\x0A\\x00\\x00\\x00\";\n"); 
    WRITE_LIB ("uint8_t jmp_putchar[]   = \"\\xE9\\x8B\\x00\\x00\\x00\";\n");
    WRITE_LIB ("uint8_t jmp_myscanf[]   = \"\\xE9\\xAA\\x00\\x00\\x00\";\n\n");

    WRITE_LIB ("uint8_t lib_bytes_arr[] = \"");

    for (int i = 0; i < buf->size; ++i)
        WRITE_LIB ("\\x%02X", buf->data[i]);

    WRITE_LIB ("\";\n\n");


    WRITE_LIB ("#endif MY_STDLIB_FILE\n");
    fclose(lib_file);
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

