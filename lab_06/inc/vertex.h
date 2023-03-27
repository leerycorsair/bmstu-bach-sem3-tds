#ifndef __VERTEX_H__
#define __VERTEX_H__

#include <stdlib.h>

typedef struct vertex vertex_t;
struct vertex
{
    void *data;
    int height;
    vertex_t *left;
    vertex_t *right;
};

vertex_t *vertex_create(void *data);
vertex_t *vertex_balance(vertex_t *vertex);
vertex_t *vertex_rotate_right(vertex_t *vertex);
vertex_t *vertex_rotate_left(vertex_t *vertex);

void vertex_del(vertex_t **vertex);
void vertex_height(vertex_t *vertex);

int vertex_get_height(vertex_t *vertex);
int vertex_balance_factor(vertex_t *vertex);

#endif // __VERTEX_H__