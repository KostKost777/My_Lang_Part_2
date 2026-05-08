#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>

#include "hash_funcs.h"

size_t GetHash(const char* str)
{
    size_t hash = 5381;
    int c = 0;

    while ((c = *str++) != '\0')
        hash = ((hash << 5) + hash) + c;

    return hash;
}
