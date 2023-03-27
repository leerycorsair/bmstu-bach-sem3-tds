#ifndef MY_REAL_H
#define MY_REAL_H

#define MAX_MANTISSE 30
#define MAX_EXP 99999
#define MIN_EXP -99999
#include <stdlib.h>
typedef struct
{
    char num_sign;
    int mantisse[MAX_MANTISSE];
    size_t mantisse_size;
    int exp;
} my_real_t;



#endif