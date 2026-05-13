#ifndef KEY_WORDS_BACKEND
#define KEY_WORDS_BACKEND

#include "lexical_analysis.h"
#include "stdlib.h"

const int NUM_OF_BASEWORDS = 31;

struct BaseWord
{
    Type type;
    const char* name;
    size_t hash;
};

extern BaseWord basewords_arr[NUM_OF_BASEWORDS];

#endif
