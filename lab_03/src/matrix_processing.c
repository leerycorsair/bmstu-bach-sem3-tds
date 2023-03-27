#define __USE_MINGW_ANSI_STDIO
#include "matrix_processing.h"

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

int *nmatrix_create(n_matrix_t m)
{
    return (malloc(m.columns * m.rows * sizeof(int)));
}

void nmatrix_del(n_matrix_t *m)
{
    if (m->matrix != NULL)
    {
        free(m->matrix);
        m->matrix = NULL;
    }
    m->matrix = NULL;
    m->rows = 0;
    m->rows = 0;
}

void smatrix_del(s_matrix_t *m)
{
    if (m->nnz_values != NULL)
        free(m->nnz_values);
    if (m->row_indeces != NULL)
        free(m->row_indeces);
    if (m->column_indeces != NULL)
        free(m->column_indeces);
    m->nnz_values = NULL;
    m->column_indeces = NULL;
    m->row_indeces = NULL;
    m->elems = 0;
    m->columns = 0;
    m->rows = 0;
}

void memory_wipe(n_matrix_t *m1, n_matrix_t *m2, s_matrix_t *m3, s_matrix_t *m4, n_matrix_t *m5, s_matrix_t *m6)
{
    nmatrix_del(m1);
    nmatrix_del(m2);
    smatrix_del(m3);
    smatrix_del(m4);
    nmatrix_del(m5);
    smatrix_del(m6);
}

int n_multi(n_matrix_t m1, n_matrix_t m2, n_matrix_t *res, uint64_t *time)
{
    uint64_t start = tick();
    if (m1.matrix == NULL || m2.matrix == NULL)
    {
        printf(ANSI_COLOR_YELLOW "\nМатрица или вектор пустая(ой).\n" ANSI_COLOR_RESET);
        return SUCCESS;
    }
    if (res->matrix != NULL)
        nmatrix_del(res);
    if (m1.columns != m2.rows)
    {
        printf(ANSI_COLOR_RED "\nНекорректный размер матриц.\n" ANSI_COLOR_RESET);
        return N_MULTI_ERROR;
    }
    res->matrix = calloc(m1.rows * m2.columns, sizeof(int));
    res->rows = m1.rows;
    res->columns = m2.columns;
    if (res->matrix == NULL)
    {
        printf(ANSI_COLOR_RED "\nНевозможно выделить память.\n" ANSI_COLOR_RESET);
        return UNSUCCESSFUL_MEMORY_ALLOCATION;
    }

    for (int i = 0; i < m1.rows; i++)
        for (int j = 0; j < m2.columns; j++)
            for (int k = 0; k < m1.columns; k++)
                res->matrix[i * m2.columns + j] += m1.matrix[i * m1.columns + k] * m2.matrix[k * m2.columns + j];
    uint64_t end = tick();
    *time += end - start;
    return SUCCESS;
}

int generator(n_matrix_t *nm, s_matrix_t *sm, n_matrix_t *nv, s_matrix_t *sv, int rows, int columns, int sparce_rate)
{
    nm->rows = rows;
    nm->columns = columns;
    nv->columns = 1;
    nv->rows = nm->columns;

    srand(time(NULL));
    int *index_arr = malloc(nm->rows * nm->columns * sizeof(int));
    nm->matrix = calloc(nm->rows * nm->columns, sizeof(int));
    if (index_arr == NULL || nm->matrix == NULL)
    {
        free(index_arr);
        printf(ANSI_COLOR_RED "\nОшибка выделения памяти. Программма завершена.\n" ANSI_COLOR_RESET);
        return UNSUCCESSFUL_MEMORY_ALLOCATION;
    }
    for (int i = 0; i < nm->rows * nm->columns; i++)
        index_arr[i] = i;
    for (int curr_nums = 0; (double)curr_nums / (nm->rows * nm->columns) < (double)sparce_rate / 100; curr_nums++)
    {
        int curr_rand = rand() % (nm->rows * nm->columns - curr_nums);
        int curr_i = index_arr[curr_rand];
        index_arr[curr_rand] = index_arr[nm->rows * nm->columns - curr_nums - 1];
        nm->matrix[curr_i] = rand() % 100;
    }
    free(index_arr);

    srand(time(NULL));
    index_arr = malloc(nv->rows * nv->columns * sizeof(int));
    nv->matrix = calloc(nv->rows * nv->columns, sizeof(int));
    if (index_arr == NULL || nv->matrix == NULL)
    {
        free(index_arr);
        printf(ANSI_COLOR_RED "\nОшибка выделения памяти. Программма завершена.\n" ANSI_COLOR_RESET);
        return UNSUCCESSFUL_MEMORY_ALLOCATION;
    }
    for (int i = 0; i < nv->rows * nv->columns; i++)
        index_arr[i] = i;
    for (int curr_nums = 0; (double)curr_nums / (nv->rows * nv->columns) < (double)sparce_rate / 100; curr_nums++)
    {
        int curr_rand = rand() % (nv->rows * nv->columns - curr_nums);
        int curr_i = index_arr[curr_rand];
        index_arr[curr_rand] = index_arr[nv->rows * nv->columns - curr_nums - 1];
        nv->matrix[curr_i] = rand() % 100;
    }
    free(index_arr);

    if (form_sparce(*nm, sm) || form_sparce(*nv, sv))
        return UNSUCCESSFUL_MEMORY_ALLOCATION;
    return SUCCESS;
}

int form_sparce(n_matrix_t src, s_matrix_t *dst)
{
    dst->columns = src.columns;
    dst->elems = 0;
    dst->rows = src.rows;
    for (int i = 0; i < src.columns * src.rows; i++)
        if (src.matrix[i] != 0)
            dst->elems += 1;
    dst->nnz_values = malloc(dst->elems * sizeof(int));
    dst->column_indeces = malloc(dst->elems * sizeof(int));
    dst->row_indeces = malloc(dst->rows * sizeof(int));
    if (dst->nnz_values == NULL || dst->column_indeces == NULL || dst->row_indeces == NULL)
        return UNSUCCESSFUL_MEMORY_ALLOCATION;
    for (int i = 0; i < src.rows; i++)
        dst->row_indeces[i] = -1;
    dst->elems = 0;
    for (int i = 0; i < src.rows; i++)
        for (int j = 0; j < src.columns; j++)
            if (src.matrix[i * src.columns + j] != 0)
            {
                dst->nnz_values[dst->elems] = src.matrix[i * src.columns + j];
                dst->column_indeces[dst->elems] = j;
                if (dst->row_indeces[i] == -1)
                    dst->row_indeces[i] = dst->elems;
                dst->elems += 1;
            }
    return SUCCESS;
}

int form_normal(s_matrix_t src, n_matrix_t *dst)
{
    dst->columns = src.columns;
    dst->rows = src.rows;
    dst->matrix = calloc(dst->columns * dst->rows, sizeof(int));
    if (dst->matrix == NULL)
        return UNSUCCESSFUL_MEMORY_ALLOCATION;
    for (int i = 0; i < dst->rows; i++)
    {
        if (src.row_indeces[i] != -1)
        {
            int n_i = i + 1;
            while (n_i < src.rows && src.row_indeces[n_i] == -1)
                n_i++;
            if (n_i == src.rows)
                n_i = src.elems;
            else
                n_i = src.row_indeces[n_i];
            for (int j = src.row_indeces[i]; j < n_i; j++)
                if (dst->matrix[i * dst->columns + src.column_indeces[j]] == 0)
                    dst->matrix[i * dst->columns + src.column_indeces[j]] = src.nnz_values[j];
                else
                    return INCORRECT_INPUT;
        }
    }
    return SUCCESS;
}

int s_multi(s_matrix_t m1, s_matrix_t m2, s_matrix_t *res, uint64_t *time)
{
    uint64_t start = tick();
    if (m1.nnz_values == NULL || m2.nnz_values == NULL)
    {
        printf(ANSI_COLOR_YELLOW "\nМатрица или вектор пустая(ой).\n" ANSI_COLOR_RESET);
        return SUCCESS;
    }
    if (res->nnz_values != NULL)
        smatrix_del(res);
    if (m1.columns != m2.rows)
    {
        printf(ANSI_COLOR_RED "\nНекорректный размер матриц.\n" ANSI_COLOR_RESET);
        return N_MULTI_ERROR;
    }
    res->nnz_values = calloc(m1.rows, sizeof(int));
    res->column_indeces = calloc(m1.rows, sizeof(int));
    res->row_indeces = malloc(m1.rows * sizeof(int));
    for (int i = 0; i < m1.rows; i++)
        res->row_indeces[i] = -1;
    if (res->nnz_values == NULL || res->column_indeces == NULL || res->row_indeces == NULL)
        return UNSUCCESSFUL_MEMORY_ALLOCATION;
    int nnz_counter = 0;
    for (int i = 0; i < m1.rows; i++)
    {
        if (m1.row_indeces[i] != -1)
        {
            int check = 0;
            int n_i = i + 1;
            while (n_i < m1.rows && m1.row_indeces[n_i] == -1)
                n_i++;
            if (n_i == m1.rows)
                n_i = m1.elems;
            else
                n_i = m1.row_indeces[n_i];
            for (int j = m1.row_indeces[i]; j < n_i; j++)
            {
                if (m2.row_indeces[m1.column_indeces[j]] != -1)
                {
                    check = 1;
                    res->nnz_values[nnz_counter] += m1.nnz_values[j] * m2.nnz_values[m2.row_indeces[m1.column_indeces[j]]];
                }
            }
            if (check == 1)
            {
                res->row_indeces[i] = nnz_counter;
                nnz_counter += 1;
            }
        }
    }
    res->nnz_values = realloc(res->nnz_values, nnz_counter * sizeof(int));
    res->column_indeces = realloc(res->column_indeces, nnz_counter * sizeof(int));
    res->elems = nnz_counter;
    res->rows = m1.rows;
    res->columns = m1.columns;
    uint64_t end = tick();
    *time += end - start;
    return SUCCESS;
}