#ifndef __LIST_H__
#define __LIST_H__

#include <stdlib.h>

typedef struct node_t node_t;
struct node_t
{
    size_t data;
    node_t *next;
};

node_t *node_create(size_t data);
void node_free(node_t **node);

void list_push(node_t **head, node_t *elem);
void list_wipe(node_t **head);
void list_del(node_t **head_ref, size_t key);

int list_check(node_t *head, size_t data);
int list_len(node_t *head);

#endif // __LIST_H__