#include "list_queue.h"

void list_queue_create(list_queue_t *list_queue)
{
    list_queue->head = NULL;
    list_queue->tail = NULL;
    list_queue->len = 0;
}

void list_queue_f_insert(list_queue_t *list_queue, node_t *elem)
{
    elem->next = NULL;
    if (!list_queue->head)
        list_queue->head = elem;
    if (list_queue->tail)
        list_queue->tail->next = elem;
    list_queue->tail = elem;
    list_queue->len++;
}

void list_queue_s_insert(list_queue_t *list_queue, node_t *elem)
{
    elem->next = NULL;
    if (!list_queue->head)
        list_queue->head = elem;
    if (list_queue->len < 4)
    {
        if (list_queue->tail)
            list_queue->tail->next = elem;
        list_queue->tail = elem;
        list_queue->len++;
    }
    else
    {
        elem->next = list_queue->head->next->next->next;
        list_queue->head->next->next->next = elem;
        list_queue->len++;
    }
}

void *list_queue_del_elem(list_queue_t *list_queue)
{
    if (list_queue->len == 0)
        return NULL;
    node_t *node = list_queue->head;
    list_queue->head = list_queue->head->next;
    list_queue->len--;
    if (list_queue->len == 0)
        list_queue->tail = NULL;
    return node_del(&node);
}

void list_queue_del(list_queue_t *list_queue)
{
    node_t *cur = list_queue->head;
    while (cur)
    {
        node_t *next = cur->next;
        free(node_del(&cur));
        cur = next;
    }
    list_queue->head = NULL;
    list_queue->tail = NULL;
    list_queue->len = 0;
}

size_t list_queue_mem_size(list_queue_t list_queue)
{
    size_t mem_size = sizeof(list_queue_t);
    node_t *tmp = list_queue.head;
    while (tmp)
    {
        mem_size += sizeof(node_t);
        tmp = tmp->next;
    }
    return mem_size;
}