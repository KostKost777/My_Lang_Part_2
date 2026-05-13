#ifndef ORIG_LEXICON_OF_LANG
#define ORIG_LEXICON_OF_LANG

#include "lexical_analysis.h"

const int NUM_OF_KEYWORDS = 40;

const int NUM_OF_OPERATORS = 32;

const int NUM_OF_SPEC_SYM  = 4;

struct BaseLexeme
{
    Type type;
    const char* name;
    size_t hash;
};

BaseLexeme* FindInKeyWordArr(char* name);

BaseLexeme* FindInOpArr(char* name);

BaseLexeme* FindInSpecSymArr(char* name);

extern BaseLexeme keywords_arr[NUM_OF_KEYWORDS];

extern BaseLexeme operator_arr[NUM_OF_OPERATORS];

extern BaseLexeme spec_sym_arr[NUM_OF_OPERATORS];

#endif

