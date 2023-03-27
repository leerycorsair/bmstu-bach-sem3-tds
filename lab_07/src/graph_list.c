#include "graph_list.h"

size_t graph_list_value_by_pos(graph_list_t graph, size_t i, size_t j)
{
    return list_check(graph.matrix[i], j);
}

void graph_list_init(graph_list_t *graph)
{
    graph->matrix = NULL;
    graph->nodes = 0;
}

void graph_list_free(graph_list_t *graph)
{
    if (graph->matrix == NULL)
        return;
    for (size_t i = 0; i < graph->nodes; i++)
        list_wipe(&graph->matrix[i]);
    free(graph->matrix);
    graph->matrix = NULL;
    graph->nodes = 0;
}

int graph_list_create(graph_list_t *graph, size_t nodes)
{
    graph->matrix = calloc(nodes, sizeof(node_t *));
    if (graph->matrix == NULL)
        return UNSUCCESSFUL_MEMORY_ALLOCATION;
    return SUCCESS;
}

void graph_list_push(graph_list_t *graph, size_t index, node_t *elem)
{
    node_t *tmp_head = graph->matrix[index];
    list_push(&tmp_head, elem);
    graph->matrix[index] = tmp_head;
}

int graph_list_fread(graph_list_t *graph, char *file_name)
{
    FILE *f = fopen(file_name, "r");
    if (f == NULL)
        return INCORRECT_FILE;
    if (fscanf(f, "%zu", &graph->nodes) != 1 || graph->nodes == 0)
        return INCORRECT_CONTENT;
    if (graph_list_create(graph, graph->nodes))
        return UNSUCCESSFUL_MEMORY_ALLOCATION;
    for (size_t i = 0; i < graph->nodes; i++)
        for (size_t j = 0; j < graph->nodes; j++)
        {
            size_t tmp;
            if (fscanf(f, "%zu", &tmp) != 1 || (tmp != 1 && tmp != 0) || (i == j && tmp))
                return INCORRECT_CONTENT;
            if (tmp)
            {
                node_t *node = node_create(j);
                if (node == NULL)
                    return UNSUCCESSFUL_MEMORY_ALLOCATION;
                graph_list_push(graph, i, node);
            }
        }
    fclose(f);
    if (!graph_list_check(*graph))
        return INCORRECT_CONTENT;
    return SUCCESS;
}

void graph_list_dfs(graph_list_t graph, size_t node, size_t *visited)
{
    if (visited[node])
        return;
    visited[node] = 1;
    for (size_t i = 0; i < graph.nodes; i++)
        if (graph_list_value_by_pos(graph, node, i))
            graph_list_dfs(graph, i, visited);
}

#define NOT_CONNECTED 0
#define CONNECTED 1
int graph_list_is_connected(graph_list_t graph, size_t start)
{
    size_t *visited = calloc(graph.nodes, sizeof(size_t));
    if (visited == NULL)
        return UNSUCCESSFUL_MEMORY_ALLOCATION;
    graph_list_dfs(graph, start, visited);
    for (size_t i = 0; i < graph.nodes; i++)
        if (visited[i] == 0)
        {
            free(visited);
            return NOT_CONNECTED;
        }
    free(visited);
    return CONNECTED;
}

#define NOT_EULERIAN -1
int graph_list_is_eulerian(graph_list_t graph)
{
    size_t odd_nodes = 0;
    int odd_index = 0;
    for (size_t i = 0; i < graph.nodes; i++)
    {
        size_t ways = 0;
        for (size_t j = 0; j < graph.nodes; j++)
            ways += graph_list_value_by_pos(graph, i, j);
        if (ways % 2)
        {
            odd_nodes++;
            (odd_index > 0) ? (odd_index) : (odd_index = i);
        }
    }
    if (odd_nodes > 2)
        return NOT_EULERIAN;
    else
        return odd_index;
}

int graph_list_find_eulerian_path(graph_list_t src_graph)
{
    if (!graph_list_is_connected(src_graph, 0) || graph_list_is_eulerian(src_graph) == NOT_EULERIAN)
        return INCORRECT_CONTENT;
    graph_list_t tmp_graph;
    if (graph_list_create(&tmp_graph, src_graph.nodes))
        return UNSUCCESSFUL_MEMORY_ALLOCATION;
    if (graph_list_copy(src_graph, &tmp_graph))
    {
        graph_list_free(&tmp_graph);
        return UNSUCCESSFUL_MEMORY_ALLOCATION;
    }
    size_t start = graph_list_is_eulerian(src_graph);
    graph_list_print_eulerian_path(&tmp_graph, start);
    graph_list_free(&tmp_graph);
    return SUCCESS;
}

int graph_list_copy(graph_list_t src_graph, graph_list_t *dst_graph)
{
    dst_graph->nodes = src_graph.nodes;
    for (size_t i = 0; i < src_graph.nodes; i++)
        for (size_t j = 0; j < src_graph.nodes; j++)
            if (graph_list_value_by_pos(src_graph, i, j))
            {
                node_t *node = node_create(j);
                if (node == NULL)
                    return UNSUCCESSFUL_MEMORY_ALLOCATION;
                graph_list_push(dst_graph, i, node);
            }
    return SUCCESS;
}

int graph_list_check(graph_list_t graph)
{
    for (size_t i = 0; i < graph.nodes; i++)
        for (size_t j = i; j < graph.nodes; j++)
            if (graph_list_value_by_pos(graph, i, j) != graph_list_value_by_pos(graph, j, i))
                return 0;
    return 1;
}

void graph_list_print_eulerian_path(graph_list_t *graph, size_t node)
{
    for (size_t i = 0; i < graph->nodes; i++)
        if (graph_list_value_by_pos(*graph, node, i))
            if (!graph_list_is_bridge(*graph, i) || graph_list_edges(*graph) <= 1)
            {
                list_del(&graph->matrix[node], i);
                list_del(&graph->matrix[i], node);
                printf("%zu->%zu ", node + 1, i + 1);
                graph_list_print_eulerian_path(graph, i);
            }
}

int graph_list_is_bridge(graph_list_t graph, size_t j)
{
    int deg = 0;
    for (size_t k = 0; k < graph.nodes; k++)
        if (graph_list_value_by_pos(graph, j, k))
            deg++;
    if (deg > 1)
        return 0;
    return 1;
}

int graph_list_edges(graph_list_t graph)
{
    int edges = 0;
    for (size_t i = 0; i < graph.nodes; i++)
        for (size_t j = i; j < graph.nodes; j++)
            if (graph_list_value_by_pos(graph, i, j))
                edges++;
    return edges;
}

size_t graph_list_mem(graph_list_t graph)
{
    size_t mem = 0;
    for (size_t i = 0; i < graph.nodes; i++)
        if (graph.matrix[i])
            mem += list_len(graph.matrix[i]) * sizeof(node_t);
        else
            mem += sizeof(node_t);
    return mem;
}