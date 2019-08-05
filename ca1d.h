
#include<stdlib.h>
#include<stdio.h>

//--------------------------------------------------------
// STRUCT ca1d
//--------------------------------------------------------
typedef struct ca1d ca1d;

struct ca1d
{
    char* cells;
    char* next_state;
    int cellcount;
    unsigned char rule;
    int iterations;
    int iteration;
    char rule_binary[9];
    void(*onchange)(ca1d* ca);
};

//--------------------------------------------------------
// FUNCTION PROTOTYPES
//--------------------------------------------------------
ca1d* ca1d_init(int cellcount, char* init_pattern, unsigned char rule, int iterations, void(*onchange)(ca1d* ca));
void ca1d_start(ca1d* ca);
void ca1d_free(ca1d* ca);
