#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdlib.h>
#include "err_codes.h"

#define DEFAULT_SIZE 64

typedef struct
{
    size_t curr_len;
    size_t max_len;
    void **data;
} vector_t;

int vector_init(vector_t* vector);
int vector_add(vector_t *vector, void *elem);

void vector_free(vector_t *vector);

#endif //__VECTOR_H__