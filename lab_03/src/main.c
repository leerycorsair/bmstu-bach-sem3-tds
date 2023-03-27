#define __USE_MINGW_ANSI_STDIO

#include <stdio.h>
#include "err_codes.h"
#include "io_lib.h"
#include "sparce_normal_types.h"

#define MAX_SIZE 400
#define MAX_ITER 1000
#define MAX_SPARCE 100

int main(void)
{
    setbuf(stdout, NULL);
    uint64_t time, time1, time2;
    int choice;
    n_matrix_t n_matrix = {.matrix = NULL, .rows = 0, .columns = 0};
    n_matrix_t n_vector = {.matrix = NULL, .rows = 0, .columns = 0};
    n_matrix_t n_res = {.matrix = NULL, .rows = 0, .columns = 0};
    s_matrix_t s_matrix = {.nnz_values = NULL, .column_indeces = NULL, .row_indeces = NULL, .elems = 0, .columns = 0, .rows = 0};
    s_matrix_t s_res = {.nnz_values = NULL, .column_indeces = NULL, .row_indeces = NULL, .elems = 0, .columns = 0, .rows = 0};
    s_matrix_t s_vector = {.nnz_values = NULL, .column_indeces = NULL, .row_indeces = NULL, .elems = 0, .columns = 0, .rows = 0};
    while (1)
    {
        print_menu();
        printf(ANSI_COLOR_MAGENTA "\nВыберите опцию меню: " ANSI_COLOR_RESET);
        if (scanf("%d", &choice) <= 0 || choice < 0 || choice > 9)
        {
            memory_wipe(&n_matrix, &n_vector, &s_matrix, &s_vector, &n_res, &s_res);
            printf(ANSI_COLOR_RED "\n\nНекорректный ввод.Программа завершена.\n\n" ANSI_COLOR_RESET);
            return INCORRECT_MENU_OPTION;
        }
        if (choice == 0)
        {
            memory_wipe(&n_matrix, &n_vector, &s_matrix, &s_vector, &n_res, &s_res);
            printf(ANSI_COLOR_GREEN "\n\nПрограмма успешно завершена.\n\n" ANSI_COLOR_RESET);
            return SUCCESS;
        }
        if (choice == 1)
        {
            printf("\n");
            memory_wipe(&n_matrix, &n_vector, &s_matrix, &s_vector, &n_res, &s_res);
            if (read_nmatrix(&n_matrix, &s_matrix) || read_nvector(&n_vector, &s_vector))
            {
                memory_wipe(&n_matrix, &n_vector, &s_matrix, &s_vector, &n_res, &s_res);
                printf(ANSI_COLOR_RED "\n\nОшибка чтения.Программа завершена.\n\n" ANSI_COLOR_RESET);
                return INCORRECT_INPUT;
            }
        }
        if (choice == 2)
        {
            memory_wipe(&n_matrix, &n_vector, &s_matrix, &s_vector, &n_res, &s_res);
            if (read_smatrix(&s_matrix, &n_matrix) || read_svector(&s_vector, &n_vector))
            {
                memory_wipe(&n_matrix, &n_vector, &s_matrix, &s_vector, &n_res, &s_res);
                printf(ANSI_COLOR_RED "\n\nОшибка чтения.Программа завершена.\n\n" ANSI_COLOR_RESET);
                return INCORRECT_INPUT;
            }
        }
        if (choice == 3)
        {
            int columns, rows, sparce_rate;
            memory_wipe(&n_matrix, &n_vector, &s_matrix, &s_vector, &n_res, &s_res);
            printf(ANSI_COLOR_MAGENTA "Введите количество строк:" ANSI_COLOR_RESET);
            if (scanf("%d", &rows) <= 0 || rows <= 0)
            {
                memory_wipe(&n_matrix, &n_vector, &s_matrix, &s_vector, &n_res, &s_res);
                printf(ANSI_COLOR_RED "\n\nНекорректный ввод.Программа завершена.\n\n" ANSI_COLOR_RESET);
                return INCORRECT_INPUT;
            }
            printf(ANSI_COLOR_MAGENTA "Введите количество столбцов:" ANSI_COLOR_RESET);
            if (scanf("%d", &columns) <= 0 || columns <= 0)
            {
                memory_wipe(&n_matrix, &n_vector, &s_matrix, &s_vector, &n_res, &s_res);
                printf(ANSI_COLOR_RED "\n\nНекорректный ввод.Программа завершена.\n\n" ANSI_COLOR_RESET);
                return INCORRECT_INPUT;
            }
            printf(ANSI_COLOR_MAGENTA "Введите степень разряженности (1..100):" ANSI_COLOR_RESET);
            if (scanf("%d", &sparce_rate) <= 0 || sparce_rate <= 0 || sparce_rate > 100)
            {
                memory_wipe(&n_matrix, &n_vector, &s_matrix, &s_vector, &n_res, &s_res);
                printf(ANSI_COLOR_RED "\n\nНекорректный ввод.Программа завершена.\n\n" ANSI_COLOR_RESET);
                return INCORRECT_INPUT;
            }
            if (generator(&n_matrix, &s_matrix, &n_vector, &s_vector, rows, columns, sparce_rate))
            {
                memory_wipe(&n_matrix, &n_vector, &s_matrix, &s_vector, &n_res, &s_res);
                printf(ANSI_COLOR_RED "\n\nНекорректный ввод.Программа завершена.\n\n" ANSI_COLOR_RESET);
                return GEN_ERROR;
            }
            printf(ANSI_COLOR_YELLOW "\nДанные успешно сгенерированы.\n" ANSI_COLOR_RESET);
        }
        if (choice == 4)
        {
            time = 0;
            if (n_multi(n_matrix, n_vector, &n_res, &time))
            {
                memory_wipe(&n_matrix, &n_vector, &s_matrix, &s_vector, &n_res, &s_res);
                printf(ANSI_COLOR_RED "\n\nОшибка умножения.Программа завершена.\n\n" ANSI_COLOR_RESET);
                return N_MULTI_ERROR;
            }
            printf(ANSI_COLOR_YELLOW "\nКоличество тиков процессора для умножения\nв стандартном представлении:%zu\n\n" ANSI_COLOR_RESET, time);
        }
        if (choice == 5)
        {
            time = 0;
            if (s_multi(s_matrix, s_vector, &s_res, &time))
            {
                memory_wipe(&n_matrix, &n_vector, &s_matrix, &s_vector, &n_res, &s_res);
                printf(ANSI_COLOR_RED "\n\nОшибка умножения.Программа завершена.\n\n" ANSI_COLOR_RESET);
                return S_MULTI_ERROR;
            }
            printf(ANSI_COLOR_YELLOW "\nКоличество тиков процессора для умножения\nв разреженном представлении:%zu\n\n" ANSI_COLOR_RESET, time);
        }
        if (choice == 6)
        {
            printf(ANSI_COLOR_MAGENTA "\nМатрица в стандартном виде:\n" ANSI_COLOR_RESET);
            print_n(n_matrix);
            printf(ANSI_COLOR_MAGENTA "\nВектор в стандартном виде:\n" ANSI_COLOR_RESET);
            print_n(n_vector);
            printf(ANSI_COLOR_MAGENTA "\nРезультат умножения в стандартном виде:\n" ANSI_COLOR_RESET);
            print_n(n_res);
        }
        if (choice == 7)
        {
            printf(ANSI_COLOR_MAGENTA "\nМатрица в разреженном виде:\n" ANSI_COLOR_RESET);
            print_s(s_matrix);
            printf(ANSI_COLOR_MAGENTA "\n\nВектор в разреженном виде:\n" ANSI_COLOR_RESET);
            print_s(s_vector);
            printf(ANSI_COLOR_MAGENTA "\n\nРезультат умножения в разреженном виде:\n" ANSI_COLOR_RESET);
            print_s(s_res);
        }
        if (choice == 8)
        {
            printf("\n___________________________________________________________________");
            printf("\n|    SIZE   |     FULL_RATE     |     NORMAL     |     SPARCE     |");
            for (int i = 100; i <= MAX_SIZE; i *= 2)
                for (int j = 10; j <= MAX_SPARCE; j += 10)
                {

                    memory_wipe(&n_matrix, &n_vector, &s_matrix, &s_vector, &n_res, &s_res);
                    if (generator(&n_matrix, &s_matrix, &n_vector, &s_vector, i, i, j))
                    {
                        memory_wipe(&n_matrix, &n_vector, &s_matrix, &s_vector, &n_res, &s_res);
                        printf(ANSI_COLOR_RED "\n\nОшибка выделения памяти.Программа завершена.\n\n" ANSI_COLOR_RESET);
                        return GEN_ERROR;
                    }
                    time1 = 0;
                    for (int i = 0; i < MAX_ITER; i++)
                        if (n_multi(n_matrix, n_vector, &n_res, &time1))
                        {
                            memory_wipe(&n_matrix, &n_vector, &s_matrix, &s_vector, &n_res, &s_res);
                            printf(ANSI_COLOR_RED "\n\nОшибка умножения.Программа завершена.\n\n" ANSI_COLOR_RESET);
                            return N_MULTI_ERROR;
                        }

                    time2 = 0;
                    for (int i = 0; i < MAX_ITER; i++)
                        if (s_multi(s_matrix, s_vector, &s_res, &time2))
                        {
                            memory_wipe(&n_matrix, &n_vector, &s_matrix, &s_vector, &n_res, &s_res);
                            printf(ANSI_COLOR_RED "\n\nОшибка умножения.Программа завершена.\n\n" ANSI_COLOR_RESET);
                            return S_MULTI_ERROR;
                        }
                    printf("\n___________________________________________________________________");
                    printf("\n|%5dx%-5d|%10d         |    %8zu    |    %8zu    |", i, i, j, time1 / MAX_ITER, time2 / MAX_ITER);
                }
            printf("\n___________________________________________________________________");
        }
        if (choice == 9)
        {
            print_help();
        }
    }
    return SUCCESS;
}