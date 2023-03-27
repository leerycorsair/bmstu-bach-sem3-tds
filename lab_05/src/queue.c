#include "queue.h"
#include <stdio.h>

int queue_create(queue_t *queue)
{
    if (array_queue_create(&queue->array_queue, MAX_QUEUE_SIZE))
        return UNSUCCESSFUL_MEMORY_ALLOCATION;
    list_queue_create(&queue->list_queue);
    avg_wipe(&queue->avg_len);
    queue->curr_len = 0;
    queue->array_mem = array_queue_mem_size(queue->array_queue);
    queue->list_mem = list_queue_mem_size(queue->list_queue);
    queue->array_time = 0;
    queue->list_time = 0;
    return SUCCESS;
}

void queue_del(queue_t *queue)
{
    request_t *data = NULL;
    while ((data = list_queue_del_elem(&queue->list_queue)))
        request_free(&data);
    array_queue_del(&queue->array_queue);
    list_queue_del(&queue->list_queue);
    avg_wipe(&queue->avg_len);
    queue->curr_len = 0;
    queue->array_mem = 0;
    queue->list_mem = 0;
    queue->array_time = 0;
    queue->list_time = 0;
}

int queue_f_insert(queue_t *queue, void *data)
{
    uint64_t begin, end;

    begin = tick();
    array_queue_f_insert(&queue->array_queue, data);
    end = tick();
    queue->array_time += end - begin;
    size_t array_mem = array_queue_mem_size(queue->array_queue);
    if (array_mem > queue->array_mem)
        queue->array_mem = array_mem;

    begin = tick();
    node_t *node = node_create(data);
    if (!node)
        return UNSUCCESSFUL_MEMORY_ALLOCATION;
    node->data = data;
    list_queue_f_insert(&queue->list_queue, node);
    end = tick();
    queue->list_time += end - begin;
    size_t list_mem = list_queue_mem_size(queue->list_queue);
    if (list_mem > queue->list_mem)
        queue->list_mem = list_mem;

    queue->curr_len++;
    avg_add(&queue->avg_len, queue->curr_len);

    return SUCCESS;
}

int queue_s_insert(queue_t *queue, void *data)
{
    uint64_t begin, end;

    begin = tick();
    array_queue_s_insert(&queue->array_queue, data);
    end = tick();
    queue->array_time += end - begin;
    size_t array_mem = array_queue_mem_size(queue->array_queue);
    if (array_mem > queue->array_mem)
        queue->array_mem = array_mem;

    begin = tick();
    node_t *node = node_create(data);
    if (!node)
        return UNSUCCESSFUL_MEMORY_ALLOCATION;
    node->data = data;
    list_queue_s_insert(&queue->list_queue, node);
    end = tick();
    queue->list_time += end - begin;
    size_t list_mem = list_queue_mem_size(queue->list_queue);
    if (list_mem > queue->list_mem)
        queue->list_mem = list_mem;

    queue->curr_len++;
    avg_add(&queue->avg_len, queue->curr_len);

    return SUCCESS;
}

request_t *queue_del_elem(queue_t *queue)
{
    uint64_t begin, end;
    request_t *data;

    begin = tick();
    data = list_queue_del_elem(&queue->list_queue);
    if (!data)
        return NULL;
    end = tick();
    queue->list_time += end - begin;

    begin = tick();
    data = array_queue_del_elem(&queue->array_queue);
    if (!data)
        return NULL;
    end = tick();
    queue->array_time += end - begin;

    queue->curr_len--;
    avg_add(&queue->avg_len, queue->curr_len);
    return data;
}
