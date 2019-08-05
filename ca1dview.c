#include"ca1dview.h"

// --------------------------------------------------------
// FUNCTION PROTOTYPES
// --------------------------------------------------------
void onchange(ca1d* ca)
{
    if(ca->iteration == 0)
    {
        printf("Rule:        %d\nRule binary: %s\nIterations:  %d\n\n", ca->rule, ca->rule_binary, ca->iterations);
    }

    printf("|%-2d| ", ca->iteration);

    for(int i = 0; i < ca->cellcount; i++)
    {
        if(ca->cells[i] == '0')
            putchar(OFF_CHAR);
        else
            putchar(ON_CHAR);
    }

    puts("");
}
