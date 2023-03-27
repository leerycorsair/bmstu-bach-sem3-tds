#include "vertex.h"

vertex_t *vertex_create(void *data)
{
    vertex_t *vertex = malloc(sizeof(vertex_t));
    if (!vertex)
        return NULL;

    vertex->data = data;
    vertex->height = 1;
    vertex->left = NULL;
    vertex->right = NULL;

    return vertex;
}
void vertex_del(vertex_t **vertex)
{
    if (!vertex || !*vertex)
        return;

    free(*vertex);
    *vertex = NULL;
}

void vertex_height(vertex_t *vertex)
{
    int hl = vertex_get_height(vertex->left);
    int hr = vertex_get_height(vertex->right);
    vertex->height = (hl > hr ? hl : hr) + 1;
}

int vertex_get_height(vertex_t *vertex)
{
    return vertex ? vertex->height : 0;
}

int vertex_balance_factor(vertex_t *vertex)
{
    return vertex_get_height(vertex->right) - vertex_get_height(vertex->left);
}

vertex_t *vertex_balance(vertex_t *vertex)
{
    vertex_height(vertex);
    if (vertex_balance_factor(vertex) == 2)
    {
        if (vertex_balance_factor(vertex->right) < 0)
            vertex->right = vertex_rotate_right(vertex->right);
        return vertex_rotate_left(vertex);
    }
    if (vertex_balance_factor(vertex) == -2)
    {
        if (vertex_balance_factor(vertex->left) > 0)
            vertex->left = vertex_rotate_left(vertex->left);
        return vertex_rotate_right(vertex);
    }
    return vertex;
}

vertex_t *vertex_rotate_right(vertex_t *vertex)
{
    vertex_t *tmp = vertex->left;
    vertex->left = tmp->right;
    tmp->right = vertex;
    vertex_height(vertex);
    vertex_height(tmp);
    return tmp;
}

vertex_t *vertex_rotate_left(vertex_t *vertex)
{
    vertex_t *tmp = vertex->right;
    vertex->right = tmp->left;
    tmp->left = vertex;
    vertex_height(vertex);
    vertex_height(tmp);
    return tmp;
}
