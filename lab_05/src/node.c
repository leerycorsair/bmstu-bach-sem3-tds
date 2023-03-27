#include "node.h"

node_t *node_create(void *data)
{
    node_t *node = malloc(sizeof(node_t));
    if (!node)
        return NULL;

    node->data = data;
    node->next = NULL;

    return node;
}
void *node_del(node_t **node)
{
    if (!node || !*node)
        return NULL;

    void *data = (*node)->data;

    free(*node);
    *node = NULL;

    return data;
}