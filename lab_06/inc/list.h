#ifndef __LIST_H__
#define __LIST_H__

#include <stdlib.h>

typedef struct node_t node_t;
struct node_t
{
    void *data;
    node_t *next;
};

node_t *node_create(void *data);
void node_free(node_t **node);

void list_push(node_t **head, node_t *elem);
void list_wipe(node_t **head);
void list_del(node_t **head_ref, char *str, size_t *oper);
void list_print(node_t *head);

node_t *list_find(node_t *head, void *data, int (*comparator)(const char *, const char *), size_t *oper);

int list_check(node_t *head, node_t *elem);
int list_len(node_t *head);

#endif // __LIST_H__