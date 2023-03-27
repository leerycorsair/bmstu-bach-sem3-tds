#ifndef __TREE_H__
#define __TREE_H__

#include <stdlib.h>
#include "vertex.h"
#include "data.h"
#include "tools.h"

vertex_t *tree_search(vertex_t *root, void *key, int (*comparator)(const char *, const char *), size_t *compared);
vertex_t *tree_insert(vertex_t *root, vertex_t *vertex, int (*comparator)(const char *, const char *));
vertex_t *tree_delete(vertex_t *root, void *key, int (*comparator)(const char *, const char *));
vertex_t *tree_balanced_insert(vertex_t *root, vertex_t *vertex, int (*comparator)(const char *, const char *));
vertex_t *tree_balanced_delete(vertex_t *root, void *key, int (*comparator)(const char *, const char *));
vertex_t *tree_min_vertex(vertex_t *vertex);
vertex_t *tree_findmin(vertex_t *root);
vertex_t *tree_removemin(vertex_t *root);

int tree_form(vertex_t **root, data_t data);
int tree_balanced_form(vertex_t **root, data_t data);

void tree_init(vertex_t *root);
void tree_fprint_graph(vertex_t *root, void *file_name);
void tree_post_apply(vertex_t *root, void (*f)(vertex_t *, void *), void *arg);
void tree_wipe(vertex_t **root);

#endif // __TREE_H__