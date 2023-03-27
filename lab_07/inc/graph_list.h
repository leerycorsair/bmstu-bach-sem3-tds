#ifndef __GRAPH_LIST_H__
#define __GRAPH_LIST_H__

#include <stdio.h>

#include "err_codes.h"
#include "list.h"

typedef struct
{
    node_t **matrix;
    size_t nodes;
} graph_list_t;

int graph_list_create(graph_list_t *graph, size_t nodes);
int graph_list_fread(graph_list_t *graph, char *file_name);
int graph_list_is_connected(graph_list_t graph, size_t start);
int graph_list_is_eulerian(graph_list_t graph);
int graph_list_find_eulerian_path(graph_list_t src_graph);
int graph_list_is_bridge(graph_list_t graph, size_t j);
int graph_list_edges(graph_list_t graph);
int graph_list_check(graph_list_t graph);
int graph_list_copy(graph_list_t src_graph, graph_list_t *dst_graph);

size_t graph_list_value_by_pos(graph_list_t graph, size_t i, size_t j);
size_t graph_list_mem(graph_list_t graph);

void graph_list_push(graph_list_t *graph, size_t index, node_t *elem);
void graph_list_print_eulerian_path(graph_list_t *graph, size_t node);
void graph_list_init(graph_list_t *graph);
void graph_list_free(graph_list_t *graph);
void graph_list_dfs(graph_list_t graph, size_t node, size_t *visited);

#endif //__GRAPH_LIST_H__