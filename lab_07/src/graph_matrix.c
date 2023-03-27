#include "graph_matrix.h"

void graph_matrix_init(graph_matrix_t *graph)
{
    graph->matrix = NULL;
    graph->nodes = 0;
}

void graph_matrix_free(graph_matrix_t *graph)
{
    if (graph->matrix == NULL)
        return;
    for (size_t i = 0; i < graph->nodes; i++)
        free(graph->matrix[i]);
    free(graph->matrix);
    graph->matrix = NULL;
    graph->nodes = 0;
}

int graph_matrix_create(graph_matrix_t *graph, size_t nodes)
{
    graph->matrix = malloc(nodes * sizeof(size_t));
    if (graph->matrix == NULL)
        return UNSUCCESSFUL_MEMORY_ALLOCATION;
    for (size_t i = 0; i < nodes; i++)
    {
        graph->matrix[i] = malloc(nodes * sizeof(size_t));
        if (graph->matrix[i] == NULL)
        {
            for (size_t j = 0; j < i; j++)
                free(graph->matrix[j]);
            free(graph->matrix);
            return UNSUCCESSFUL_MEMORY_ALLOCATION;
        }
    }
    return SUCCESS;
}

int graph_matrix_fread(graph_matrix_t *graph, char *file_name)
{
    FILE *f = fopen(file_name, "r");
    if (f == NULL)
        return INCORRECT_FILE;
    if (fscanf(f, "%zu", &graph->nodes) != 1 || graph->nodes == 0)
        return INCORRECT_CONTENT;
    if (graph_matrix_create(graph, graph->nodes))
        return UNSUCCESSFUL_MEMORY_ALLOCATION;
    for (size_t i = 0; i < graph->nodes; i++)
        for (size_t j = 0; j < graph->nodes; j++)
            if (fscanf(f, "%zu", &graph->matrix[i][j]) != 1 || (graph->matrix[i][j] != 1 && graph->matrix[i][j] != 0) || (i == j && graph->matrix[i][j]))
                return INCORRECT_CONTENT;
    fclose(f);
    if (!graph_matrix_check(*graph))
        return INCORRECT_CONTENT;
    return SUCCESS;
}

int graph_matrix_fprint(graph_matrix_t graph, char *file_name)
{
    FILE *f = fopen(file_name, "w");
    if (f == NULL)
        return INCORRECT_FILE;
    fprintf(f, "graph G {\n");
    if (graph.nodes == 1)
        fprintf(f, "%zu -- %zu;\n", graph.nodes, graph.nodes);
    else
    {
        for (size_t i = 0; i < graph.nodes; i++)
            for (size_t j = i; j < graph.nodes; j++)
                if (graph.matrix[i][j] == 1)
                    fprintf(f, "%zu -- %zu;\n", i + 1, j + 1);
    }
    fprintf(f, "}");
    fclose(f);
    return SUCCESS;
}

void graph_matrix_dfs(graph_matrix_t graph, size_t node, size_t *visited)
{
    if (visited[node])
        return;
    visited[node] = 1;
    for (size_t i = 0; i < graph.nodes; i++)
        if (graph.matrix[node][i])
            graph_matrix_dfs(graph, i, visited);
}

#define NOT_CONNECTED 0
#define CONNECTED 1
int graph_matrix_is_connected(graph_matrix_t graph, size_t start)
{
    size_t *visited = calloc(graph.nodes, sizeof(size_t));
    if (visited == NULL)
        return UNSUCCESSFUL_MEMORY_ALLOCATION;
    graph_matrix_dfs(graph, start, visited);
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
int graph_matrix_is_eulerian(graph_matrix_t graph)
{
    size_t odd_nodes = 0;
    int odd_index = 0;
    for (size_t i = 0; i < graph.nodes; i++)
    {
        size_t ways = 0;
        for (size_t j = 0; j < graph.nodes; j++)
            ways += graph.matrix[i][j];
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

int graph_matrix_find_eulerian_path(graph_matrix_t src_graph)
{
    if (!graph_matrix_is_connected(src_graph, 0) || graph_matrix_is_eulerian(src_graph) == NOT_EULERIAN)
        return INCORRECT_CONTENT;
    graph_matrix_t tmp_graph;
    if (graph_matrix_create(&tmp_graph, src_graph.nodes))
        return UNSUCCESSFUL_MEMORY_ALLOCATION;
    graph_matrix_copy(src_graph, &tmp_graph);
    size_t start = graph_matrix_is_eulerian(src_graph);
    graph_matrix_print_eulerian_path(&tmp_graph, start);
    graph_matrix_fprint(tmp_graph, "tmp.txt");
    graph_matrix_free(&tmp_graph);
    return SUCCESS;
}

void graph_matrix_copy(graph_matrix_t src_graph, graph_matrix_t *dst_graph)
{
    dst_graph->nodes = src_graph.nodes;
    for (size_t i = 0; i < src_graph.nodes; i++)
        for (size_t j = 0; j < src_graph.nodes; j++)
            dst_graph->matrix[i][j] = src_graph.matrix[i][j];
}

int graph_matrix_check(graph_matrix_t graph)
{
    for (size_t i = 0; i < graph.nodes; i++)
        for (size_t j = i; j < graph.nodes; j++)
            if (graph.matrix[i][j] != graph.matrix[j][i])
                return 0;
    return 1;
}

void graph_matrix_print_eulerian_path(graph_matrix_t *graph, size_t node)
{
    for (size_t i = 0; i < graph->nodes; i++)
        if (graph->matrix[node][i])
            if (!graph_matrix_is_bridge(*graph, i) || graph_matrix_edges(*graph) <= 1)
            {
                graph->matrix[node][i] = 0;
                graph->matrix[i][node] = 0;
                printf("%zu->%zu ", node + 1, i + 1);
                graph_matrix_print_eulerian_path(graph, i);
            }
}

int graph_matrix_is_bridge(graph_matrix_t graph, size_t j)
{
    int deg = 0;
    for (size_t k = 0; k < graph.nodes; k++)
        if (graph.matrix[j][k])
            deg++;
    if (deg > 1)
        return 0;
    return 1;
}

int graph_matrix_edges(graph_matrix_t graph)
{
    int edges = 0;
    for (size_t i = 0; i < graph.nodes; i++)
        for (size_t j = i; j < graph.nodes; j++)
            if (graph.matrix[i][j])
                edges++;
    return edges;
}

size_t graph_matrix_mem(graph_matrix_t graph)
{
    return sizeof(size_t) * graph.nodes * graph.nodes;
}