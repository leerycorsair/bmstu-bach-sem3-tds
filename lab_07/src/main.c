#include <stdio.h>

#include "io_lib.h"
#include "err_codes.h"
#include "graph_matrix.h"
#include "graph_list.h"
#include "tools.h"

void go_exit(graph_matrix_t *graph_matrix, graph_list_t *graph_list)
{
    graph_matrix_free(graph_matrix);
    graph_list_free(graph_list);
    printf(ANSI_COLOR_GREEN "\nПрограмма успешно завершена.\n" ANSI_COLOR_RESET);
}

void go_read_graph(graph_matrix_t *graph_matrix, graph_list_t *graph_list)
{
    printf(ANSI_COLOR_MAGENTA "Введите имя файла:\n" ANSI_COLOR_RESET);
    char file_name[50];
    if (scanf("%s", file_name) <= 0)
    {
        printf(ANSI_COLOR_RED "Не удалось прочесть имя.\n" ANSI_COLOR_RESET);
        return;
    }
    graph_matrix_free(graph_matrix);
    graph_list_free(graph_list);
    if (graph_matrix_fread(graph_matrix, file_name))
    {
        graph_matrix_free(graph_matrix);
        printf(ANSI_COLOR_RED "Некорректный файл.\n" ANSI_COLOR_RESET);
        return;
    }
    if (graph_list_fread(graph_list, file_name))
        graph_list_free(graph_list);
}

void go_print_graph(graph_matrix_t graph_matrix)
{
    if (graph_matrix.matrix == NULL)
    {
        printf(ANSI_COLOR_RED "Данные отсутствуют.\n" ANSI_COLOR_RESET);
        return;
    }
    if (graph_matrix_fprint(graph_matrix, "tmp_file"))
    {
        printf(ANSI_COLOR_RED "Не удалось создать файл.\n" ANSI_COLOR_RESET);
        return;
    }
    system("dot -Tpng tmp_file -o graph.png");
    system("rm tmp_file");
}

void go_find_euler(graph_matrix_t graph_matrix, graph_list_t graph_list)
{
    if (graph_matrix.matrix == NULL)
    {
        printf(ANSI_COLOR_RED "Данные отсутствуют.\n" ANSI_COLOR_RESET);
        return;
    }
    if (graph_matrix.nodes == 1)
    {
        printf(ANSI_COLOR_RED "Граф состоит из одной вершины.\n" ANSI_COLOR_RESET);
        return;
    }
    printf(ANSI_COLOR_MAGENTA "Результат поиска пути в графе на основе матрицы смежности:\n" ANSI_COLOR_RESET);
    uint64_t matrix_t = tick();
    if (graph_matrix_find_eulerian_path(graph_matrix))
        printf(ANSI_COLOR_RED "Путь не найден" ANSI_COLOR_RESET);
    matrix_t = tick() - matrix_t;
    size_t matrix_mem = graph_matrix_mem(graph_matrix);

    printf(ANSI_COLOR_MAGENTA "\nРезультат поиска пути в графе на основе списка смежности:\n" ANSI_COLOR_RESET);
    uint64_t list_t = tick();
    if (graph_list_find_eulerian_path(graph_list))
        printf(ANSI_COLOR_RED "Путь не найден" ANSI_COLOR_RESET);
    list_t = tick() - list_t;
    size_t list_mem = graph_list_mem(graph_list);

    printf("\n----------------------------------------------------\n");
    printf("|                   |    Время   |      Память     |\n");
    printf("----------------------------------------------------\n");
    printf("| Матрица смежности |%12zu|%12zu байт|\n", matrix_t, matrix_mem);
    printf("----------------------------------------------------\n");
    printf("| Список смежности  |%12zu|%12zu байт|\n", list_t, list_mem);
    printf("----------------------------------------------------\n");
}

#define MAX_SIZE 256
#define MAX_ITER 10
void go_cmp_structs()
{

    graph_matrix_t graph_matrix;
    graph_matrix_init(&graph_matrix);
    graph_list_t graph_list;
    graph_list_init(&graph_list);
    printf(ANSI_COLOR_RED "\n--------------------------------------------------------------------------\n" ANSI_COLOR_RESET);
    printf("|                                         |    Время   |      Память     |\n");
    for (size_t i = 16; i <= MAX_SIZE; i = i * 2)
    {
        size_t matrix_t = 0, list_t = 0;
        size_t matrix_mem = 0, list_mem = 0;
        for (size_t j = 0; j < MAX_ITER; j++)
        {
            file_matrix_gen(i, "tmp_file.txt");
            graph_matrix_init(&graph_matrix);
            graph_list_init(&graph_list);
            graph_matrix_fread(&graph_matrix, "tmp_file.txt");
            graph_list_fread(&graph_list, "tmp_file.txt");

            uint64_t tmp_t = tick();
            graph_matrix_find_eulerian_path(graph_matrix);
            printf("\r\33[2K");
            matrix_t += tick() - tmp_t;
            matrix_mem += graph_matrix_mem(graph_matrix);

            tmp_t = tick();
            graph_list_find_eulerian_path(graph_list);
            printf("\r\33[2K");
            list_t += tick() - tmp_t;
            list_mem += graph_list_mem(graph_list);
            graph_matrix_free(&graph_matrix);
            graph_list_free(&graph_list);
        }

        printf(ANSI_COLOR_RED "--------------------------------------------------------------------------\n" ANSI_COLOR_RESET);
        printf("| Матрица смежности %10zux%-10zu |%12zu|%12zu байт|\n", i, i, matrix_t / MAX_ITER, matrix_mem / MAX_ITER);
        printf("--------------------------------------------------------------------------\n");
        printf("| Список смежности  %10zux%-10zu |%12zu|%12zu байт|\n", i, i, list_t / MAX_ITER, list_mem / MAX_ITER);
    }
    printf(ANSI_COLOR_RED "--------------------------------------------------------------------------\n" ANSI_COLOR_RESET);
}

void option_perform(int *option, graph_matrix_t *graph_matrix, graph_list_t *graph_list)
{
    switch (*option)
    {
    case 0:
        go_exit(graph_matrix, graph_list);
        break;
    case 1:
        go_read_graph(graph_matrix, graph_list);
        break;
    case 2:
        go_print_graph(*graph_matrix);
        break;
    case 3:
        go_find_euler(*graph_matrix, *graph_list);
        break;
    case 4:
        go_cmp_structs();
        break;
    default:
        printf(ANSI_COLOR_RED "Некорректная опция меню.\n" ANSI_COLOR_RESET);
        break;
    }
}

int main(void)
{
    setbuf(stdout, NULL);
    print_welcome();

    graph_matrix_t graph_matrix;
    graph_matrix_init(&graph_matrix);
    graph_list_t graph_list;
    graph_list_init(&graph_list);

    int option = -1;
    while (option)
    {
        option = -1;
        print_menu();
        printf(ANSI_COLOR_MAGENTA "Выберите опцию меню:" ANSI_COLOR_RESET);
        scanf("%d", &option);
        option_perform(&option, &graph_matrix, &graph_list);
        empty_stream(stdin);
    }
    return SUCCESS;
}