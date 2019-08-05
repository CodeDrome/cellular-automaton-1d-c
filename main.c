
#include<stdio.h>
#include<stdlib.h>

#include"ca1dview.h"

//--------------------------------------------------------
// FUNCTION main
//--------------------------------------------------------
int main(int argc, char* argv[])
{
    int cellcount = 32;
    char initialpattern[] = "00000000000000001000000000000000";
    int rule = 18;
    int iterations = 16;

    puts("-------------------------");
    puts("| codedrome.com         |");
    puts("| Cellular Automaton 1D |");
    puts("-------------------------\n");

    ca1d* ca = ca1d_init(cellcount, initialpattern, rule, iterations, onchange);

    if(ca != NULL)
    {
        ca1d_start(ca);

        ca1d_free(ca);

        return EXIT_SUCCESS;
    }
    else
    {
        return EXIT_FAILURE;
    }
}
