#include "vector.h"

int vector_init(vector_t *vector)
{
    void **array = calloc(DEFAULT_SIZE, sizeof(void *));
    if (!array)
    {
        vector->data = NULL;
        return UNSUCCESSFUL_MEMORY_ALLOCATION;
    }
    else
    {
        vector->curr_len = 0;
        vector->max_len = DEFAULT_SIZE;
        vector->data = array;
    }
    return SUCCESS;
}

int vector_add(vector_t *vector, void *elem)
{
    if (vector->curr_len == vector->max_len)
    {
        size_t new_max_len = vector->max_len * 2;
        void **tmp = realloc(vector->data, new_max_len * sizeof(void *));
        if (!tmp)
            return UNSUCCESSFUL_MEMORY_ALLOCATION;
        vector->max_len = new_max_len;
        vector->data = tmp;
    }
    vector->data[vector->curr_len++] = elem;
    return SUCCESS;
}

void vector_free(vector_t *vector)
{
    if (!vector->data)
        return;
    free(vector->data);
    vector->curr_len = 0;
    vector->max_len = 0;
}
