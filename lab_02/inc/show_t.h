#ifndef __SHOW_T__
#define __SHOW_T__

#include <stdlib.h>

#define MAX_STR_SIZE 64

typedef struct
{
    int min_age;
    int genre;
} kid_show_t;

typedef struct
{
    int genre;
} adult_show_t;

typedef struct
{
    char compositor[MAX_STR_SIZE + 1];
    char country[MAX_STR_SIZE + 1];
    int min_age, duration;
} music_show_t;

typedef union
{
    kid_show_t kids;
    adult_show_t adults;
    music_show_t music;
} type_t;

typedef struct
{
    char theatre[MAX_STR_SIZE + 1];
    char title[MAX_STR_SIZE + 1];
    char director[MAX_STR_SIZE + 1];
    int min_price, max_price;
    int show_type;
    type_t type;

} show_t;

typedef struct
{
    char title[MAX_STR_SIZE + 1];
    int index;
} key_t;

#endif