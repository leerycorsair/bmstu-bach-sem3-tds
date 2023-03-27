#ifndef __GRAPH_MATRIX_H__
#define __GRAPH_MATRIX_H__

#include <stdlib.h>
#include <stdio.h>

#include "err_codes.h"

typedef struct
{
    size_t **matrix;
    size_t nodes;
} graph_matrix_t;

int graph_matrix_create(graph_matrix_t *graph, size_t nodes);
int graph_matrix_fread(graph_matrix_t *graph, char *file_name);
int graph_matrix_fprint(graph_matrix_t graph, char *file_name);

int graph_matrix_is_connected(graph_matrix_t graph, size_t start);
int graph_matrix_is_eulerian(graph_matrix_t graph);
int graph_matrix_find_eulerian_path(graph_matrix_t src_graph);
int graph_matrix_is_bridge(graph_matrix_t graph, size_t j);
int graph_matrix_edges(graph_matrix_t graph);
int graph_matrix_check(graph_matrix_t graph);

size_t graph_matrix_mem(graph_matrix_t graph);

void graph_matrix_print_eulerian_path(graph_matrix_t *graph, size_t node);
void graph_matrix_init(graph_matrix_t *graph);
void graph_matrix_free(graph_matrix_t *graph);
void graph_matrix_dfs(graph_matrix_t graph, size_t node, size_t *visited);
void graph_matrix_copy(graph_matrix_t src_graph, graph_matrix_t *dst_graph);

#endif //__GRAPH_MATRIX_H__