#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdlib.h>

#include "list_queue.h"
#include "array_queue.h"

#include "time.h"
#include "numbers.h"
#include "request.h"
#include <inttypes.h>
typedef struct
{
    list_queue_t list_queue;
    array_queue_t array_queue;
    avg_t avg_len;
    size_t curr_len;
    size_t array_mem;
    size_t list_mem;
    uint64_t array_time;
    uint64_t list_time;
} queue_t;

int queue_create(queue_t *queue);
void queue_del(queue_t *queue);
int queue_f_insert(queue_t *queue, void *data);
int queue_s_insert(queue_t *queue, void *data);
request_t *queue_del_elem(queue_t *queue);

#endif //__QUEUE_H__