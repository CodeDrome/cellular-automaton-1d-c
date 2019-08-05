
#include<stdlib.h>
#include<stdbool.h>
#include<stdio.h>
#include<string.h>
#include<math.h>

#include"ca1d.h"

// --------------------------------------------------------
// FUNCTION PROTOTYPES
// --------------------------------------------------------
static void set_rule_binary(ca1d* ca);
static void calculate_next_state(ca1d* ca);

// --------------------------------------------------------
// FUNCTION ca1d_init
// --------------------------------------------------------
ca1d* ca1d_init(int cellcount, char* init_pattern, unsigned char rule, int iterations, void(*onchange)(ca1d* ca))
{
    ca1d* ca = malloc(sizeof(ca1d));

    if(ca != NULL)
    {
        *ca = (ca1d){.cells = malloc(cellcount * sizeof(char)),
                    .next_state = malloc(cellcount * sizeof(char)),
                    .cellcount = cellcount,
                    .rule = rule,
                    .iterations = iterations,
                    .iteration = 0,
                    .rule_binary = "",
                    .onchange = onchange};

        if(ca->cells != NULL && ca->next_state != NULL)
        {
            set_rule_binary(ca);

            for(int i = 0; i < cellcount; i++)
            {
                if(init_pattern[i] == '0')
                {
                    ca->cells[i] = '0';
                }
                else if(init_pattern[i] == '1')
                {
                    ca->cells[i] = '1';
                }
            }

            ca->onchange(ca);

            return ca;
        }
        else
        {
            ca1d_free(ca);

            return NULL;
        }
    }
    else
    {
        return NULL;
    }
}

// --------------------------------------------------------
// FUNCTION ca1d_start
// --------------------------------------------------------
void ca1d_start(ca1d* ca)
{
    for(int i = 0; i < ca->iterations; i++)
    {
        calculate_next_state(ca);

        ca->iteration++;

        ca->onchange(ca);
    }
}

// --------------------------------------------------------
// FUNCTION set_rule_binary
// --------------------------------------------------------
static void set_rule_binary(ca1d* ca)
{
    for(int p = 0; p <= 7; p++)
    {
        if((int)(pow(2, p)) & ca->rule)
        {
            ca->rule_binary[abs(p - 7)] = '1';
        }
        else
        {
            ca->rule_binary[abs(p - 7)] = '0';
        }
    }

    ca->rule_binary[8] = '\0';
}

// --------------------------------------------------------
// FUNCTION calculate_next_state
// --------------------------------------------------------
static void calculate_next_state(ca1d* ca)
{
    int prev_index;
    int next_index;
    char neighbourhood[4];

    for(int i = 0; i < ca->cellcount; i++)
    {
        if (i == 0)
            // roll beginning round to end
            prev_index = ca->cellcount - 1;
        else
            prev_index = i - 1;

        if (i == (ca->cellcount - 1))
            // roll end round to beginning
            next_index = 0;
        else
            next_index = i + 1;

        // set neighbourhood of 3 cells
        neighbourhood[0] = ca->cells[prev_index];
        neighbourhood[1] = ca->cells[i];
        neighbourhood[2] = ca->cells[next_index];
        neighbourhood[3] = '\0';

        // set next cell state depending on neighbourhood
        if(strcmp(neighbourhood, "111") == 0)
            ca->next_state[i] = ca->rule_binary[0];
        else if(strcmp(neighbourhood, "110") == 0)
            ca->next_state[i] = ca->rule_binary[1];
        else if(strcmp(neighbourhood, "101") == 0)
            ca->next_state[i] = ca->rule_binary[2];
        else if(strcmp(neighbourhood, "100") == 0)
            ca->next_state[i] = ca->rule_binary[3];
        else if(strcmp(neighbourhood, "011") == 0)
            ca->next_state[i] = ca->rule_binary[4];
        else if(strcmp(neighbourhood, "010") == 0)
            ca->next_state[i] = ca->rule_binary[5];
        else if(strcmp(neighbourhood, "001") == 0)
            ca->next_state[i] = ca->rule_binary[6];
        else if(strcmp(neighbourhood, "000") == 0)
            ca->next_state[i] = ca->rule_binary[7];
    }

    // copy next state to current
    for (int i = 0; i < ca->cellcount; ca->cells[i] = ca->next_state[i], i++);
}

// --------------------------------------------------------
// FUNCTION ca1d_free
// --------------------------------------------------------
void ca1d_free(ca1d* ca)
{
    if(ca != NULL)
    {
        if(ca->cells != NULL)
            free(ca->cells);

        if(ca->next_state != NULL)
            free(ca->next_state);

        free(ca);
    }
}
