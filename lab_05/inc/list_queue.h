#ifndef __LIST_QUEUE_H__
#define __LIST_QUEUE_H__

#include "node.h"

typedef struct
{
    size_t len;
    node_t *head;
    node_t *tail;
} list_queue_t;

void list_queue_create(list_queue_t *list_queue);
void list_queue_f_insert(list_queue_t *list_queue, node_t *elem);
void list_queue_s_insert(list_queue_t *list_queue, node_t *elem);
void* list_queue_del_elem(list_queue_t *list_queue);
void list_queue_del(list_queue_t *list_queue);
size_t list_queue_mem_size(list_queue_t list_queue);


#endif //__LIST_QUEUE_H__