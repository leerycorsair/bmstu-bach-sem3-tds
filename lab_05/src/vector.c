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

double check_unique(vector_t vector)
{
    size_t unique_count = 0;
    for (size_t i = 0; i < vector.curr_len; i++)
    {
        int check = 1;
        for (size_t j = i + 1; j < vector.curr_len; j++)
            if (vector.data[i] == vector.data[j])
            {
                check = 0;
                break;
            }
        if (check)
            unique_count++;
    }
    return vector.curr_len == 0 ? 0 : unique_count / (double)vector.curr_len;
}
