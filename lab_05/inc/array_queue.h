#ifndef __ARRAY_QUEUE_H__
#define __ARRAY_QUEUE_H__

#include <stdlib.h>
#include "err_codes.h"

#define MAX_QUEUE_SIZE 1000

typedef struct
{
    void **array;
    size_t head;
    size_t tail;
    size_t curr_size;
    size_t max_size;
} array_queue_t;

int array_queue_create(array_queue_t *array_queue, size_t size);
void array_queue_del(array_queue_t *array_queue);
void array_queue_f_insert(array_queue_t *array_queue, void *data);
void array_queue_s_insert(array_queue_t *array_queue, void *data);
void *array_queue_del_elem(array_queue_t *array_queue);
size_t array_queue_mem_size(array_queue_t array_queue);

#endif //__ARRAY_QUEUE_H__