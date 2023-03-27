#ifndef __NODE_H__
#define __NODE_H__

#include <stdlib.h>

typedef struct node node_t;
struct node
{
    void *data;
    node_t *next;
};

node_t *node_create(void *data);
void *node_del(node_t **node);

#endif //__NODE_H__