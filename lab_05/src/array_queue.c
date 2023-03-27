#include "array_queue.h"

int array_queue_create(array_queue_t *array_queue, size_t size)
{
    if (size == 0)
        return CREATE_ERROR;
    array_queue->array = malloc(size * sizeof(void *));
    if (!array_queue->array)
        return CREATE_ERROR;
    array_queue->head = 0;
    array_queue->tail = 0;
    array_queue->max_size = size;
    array_queue->curr_size = 0;
    return SUCCESS;
}

void array_queue_del(array_queue_t *array_queue)
{
    if (array_queue->array)
        free(array_queue->array);
    array_queue->array = NULL;
    array_queue->head = 0;
    array_queue->tail = 0;
    array_queue->curr_size = 0;
    array_queue->max_size = 0;
}

void array_queue_f_insert(array_queue_t *array_queue, void *data)
{
    array_queue->array[array_queue->head] = data;
    if (array_queue->curr_size == array_queue->max_size)
        array_queue->tail = (array_queue->tail + 1) % array_queue->max_size;
    else
        array_queue->curr_size++;
    array_queue->head = (array_queue->head + 1) % array_queue->max_size;
}

void array_queue_s_insert(array_queue_t *array_queue, void *data)
{
    if (array_queue->curr_size < 4)
        array_queue_f_insert(array_queue, data);
    else
    {
        array_queue->array[(array_queue->head + 1) % array_queue->max_size] = array_queue->array[array_queue->head];
        array_queue->array[array_queue->head] = array_queue->array[(array_queue->head - 1) % array_queue->max_size];
        array_queue->array[(array_queue->head - 1) % array_queue->max_size] = array_queue->array[(array_queue->head - 2 ) % array_queue->max_size];
        array_queue->array[(array_queue->head - 2 ) % array_queue->max_size] = data;
        array_queue->head = (array_queue->head + 1) % array_queue->max_size;
    }
}

void *array_queue_del_elem(array_queue_t *array_queue)
{
    if (array_queue->curr_size == 0)
        return NULL;
    void *data = array_queue->array[array_queue->tail];
    array_queue->tail = (array_queue->tail + 1) % array_queue->max_size;
    array_queue->curr_size--;
    return data;
}

size_t array_queue_mem_size(array_queue_t array_queue)
{
    return array_queue.max_size * sizeof(void *);
}
