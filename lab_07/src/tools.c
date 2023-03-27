#include "tools.h"
#include "graph_matrix.h"

uint64_t tick(void)
{
    uint32_t high, low;
    __asm__ __volatile__(
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r"(high), "=r"(low)::"%rax", "%rbx", "%rcx", "%rdx");

    uint64_t ticks = ((uint64_t)high << 32) | low;

    return ticks;
}

void empty_stream(FILE *stream)
{
    int c = getc(stream);

    while (c != '\n' && c != EOF)
        c = getc(stream);
}

void file_matrix_gen(size_t matrix_size, char *filename)
{
    srand(time(NULL));
    FILE *f = fopen(filename, "w");
    fprintf(f, "%zu\n", matrix_size);
    graph_matrix_t tmp_graph;
    graph_matrix_init(&tmp_graph);
    graph_matrix_create(&tmp_graph, matrix_size);
    for (size_t i = 0; i < matrix_size; i++)
        for (size_t j = i; j < matrix_size; j++)
            if (j == i)
                tmp_graph.matrix[i][j] = 0;
            else
            {
                tmp_graph.matrix[i][j] = rand() % 2;
                tmp_graph.matrix[j][i] = tmp_graph.matrix[i][j];
            }
    for (size_t i = 0; i < matrix_size; i++)
    {
        for (size_t j = 0; j < matrix_size; j++)
            fprintf(f, "%zu ", tmp_graph.matrix[i][j]);
        free(tmp_graph.matrix[i]);
        fprintf(f, "\n");
    }
    free(tmp_graph.matrix);
    fclose(f);
}