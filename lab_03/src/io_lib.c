
#include "io_lib.h"

void print_menu(void)
{
    printf(ANSI_COLOR_GREEN "\nМеню:\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "1.Ввод матрицы и вектора в стандартном виде.\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "2.Ввод матрицы и вектора в разряженном виде.\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "3.Сгенерировать матрицу и вектор автоматически.\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "4.Умножить матрицу и вектор, используя стандартный вид.\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "5.Умножить матрицу и вектор, используя разреженный вид.\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "6.Печать исходных данных и результирующей матрицы в стандартном виде.\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "7.Печать исходных данных и результирующей матрицы в разреженном виде.\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "8.Сравнение времени умножения при разном представлении матриц.\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "9.Справка.\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "0.Завершить работу.\n" ANSI_COLOR_RESET);
}

void print_help(void)
{
    printf(ANSI_COLOR_YELLOW "\nДанная программа предназначена для умножения матрицы на вектор\nв стандартом и разреженном виде с замером времени.\n\nПри хранении разреженных матриц в случае отсутствия строки\nиспользуется -1, чтобы обозначить это.\n\nВремя выполнения операций указывается в тиках процессора.\n" ANSI_COLOR_RESET);
}

void print_n(n_matrix_t m)
{
    if (m.matrix == NULL)
        printf(ANSI_COLOR_YELLOW "Данные отсутствуют.\n" ANSI_COLOR_RESET);
    else
    {
        for (int i = 0; i < m.rows; i++)
        {
            for (int j = 0; j < m.columns; j++)
                printf("%7d", m.matrix[i * m.columns + j]);
            printf("\n");
        }
    }
}

void print_s(s_matrix_t m)
{
    if (m.nnz_values == NULL)
        printf(ANSI_COLOR_YELLOW "Данные отсутствуют.\n" ANSI_COLOR_RESET);
    else
    {
        printf(ANSI_COLOR_GREEN "Ненулевые значения:\n" ANSI_COLOR_RESET);
        for (int i = 0; i < m.elems; i++)
            printf("%7d", m.nnz_values[i]);
        printf(ANSI_COLOR_GREEN "\nИндексы столбцов:\n" ANSI_COLOR_RESET);
        for (int i = 0; i < m.elems; i++)
            printf("%7d", m.column_indeces[i]);
        printf(ANSI_COLOR_GREEN "\nИндексы строк:\n" ANSI_COLOR_RESET);
        for (int i = 0; i < m.rows; i++)
            printf("%7d", m.row_indeces[i]);
    }
}

int read_nmatrix(n_matrix_t *m, s_matrix_t *sm)
{
    printf(ANSI_COLOR_YELLOW "Чтение матрицы.\n" ANSI_COLOR_RESET);
    nmatrix_del(m);
    printf(ANSI_COLOR_MAGENTA "Введите количество строк:" ANSI_COLOR_RESET);
    if (scanf("%d", &m->rows) <= 0 || m->rows <= 0)
        return INCORRECT_INPUT;
    printf(ANSI_COLOR_MAGENTA "Введите количество столбцов:" ANSI_COLOR_RESET);
    if (scanf("%d", &m->columns) <= 0 || m->columns <= 0)
        return INCORRECT_INPUT;
    m->matrix = nmatrix_create(*m);
    if (m->matrix == NULL)
    {
        printf(ANSI_COLOR_RED "Невозможно выделить память.\n" ANSI_COLOR_RESET);
        return UNSUCCESSFUL_MEMORY_ALLOCATION;
    }
    for (int i = 0; i < m->rows; i++)
    {
        printf("Введите %d строку, разделяя элементы пробелами:", i);
        for (int j = 0; j < m->columns; j++)
            if (scanf("%d", &m->matrix[i * m->columns + j]) <= 0)
                return INCORRECT_INPUT;
    }
    if (form_sparce(*m, sm))
        return UNSUCCESSFUL_MEMORY_ALLOCATION;
    printf(ANSI_COLOR_YELLOW "\nДанные успешно прочитаны.\n" ANSI_COLOR_RESET);

    return SUCCESS;
}

int read_nvector(n_matrix_t *v, s_matrix_t *sv)
{
    printf(ANSI_COLOR_YELLOW "\nЧтение вектора-столбца.\n" ANSI_COLOR_RESET);
    nmatrix_del(v);
    v->columns = 1;
    printf(ANSI_COLOR_MAGENTA "Введите количество элементов:" ANSI_COLOR_RESET);
    if (scanf("%d", &v->rows) <= 0 || v->rows <= 0)
        return INCORRECT_INPUT;
    v->matrix = nmatrix_create(*v);
    if (v->matrix == NULL)
    {
        printf(ANSI_COLOR_RED "Невозможно выделить память." ANSI_COLOR_RESET);
        return UNSUCCESSFUL_MEMORY_ALLOCATION;
    }
    printf("Введите данные, разделяя элементы пробелами:");
    for (int j = 0; j < v->rows; j++)
        if (scanf("%d", &v->matrix[j]) <= 0)
            return INCORRECT_INPUT;
    if (form_sparce(*v, sv))
        return UNSUCCESSFUL_MEMORY_ALLOCATION;
    printf(ANSI_COLOR_YELLOW "\nДанные успешно прочитаны.\n" ANSI_COLOR_RESET);
    return SUCCESS;
}

int read_smatrix(s_matrix_t *sm, n_matrix_t *nm)
{
    nmatrix_del(nm);
    smatrix_del(sm);
    printf(ANSI_COLOR_YELLOW "\nЧтение матрицы в разреженном виде.\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MAGENTA "Введите количество строк:" ANSI_COLOR_RESET);
    if (scanf("%d", &nm->rows) <= 0 || nm->rows <= 0)
        return INCORRECT_INPUT;
    printf(ANSI_COLOR_MAGENTA "Введите количество столбцов:" ANSI_COLOR_RESET);
    if (scanf("%d", &nm->columns) <= 0 || nm->columns <= 0)
        return INCORRECT_INPUT;
    int tmp_elems;
    printf(ANSI_COLOR_MAGENTA "Введите количество ненулевых элементов:" ANSI_COLOR_RESET);
    if (scanf("%d", &tmp_elems) <= 0 || tmp_elems <= 0)
        return INCORRECT_INPUT;
    nm->matrix = calloc(nm->rows * nm->columns, sizeof(int));
    if (nm->matrix == NULL)
    {
        printf(ANSI_COLOR_RED "Невозможно выделить память." ANSI_COLOR_RESET);
        return UNSUCCESSFUL_MEMORY_ALLOCATION;
    }
    for (int i = 0; i < tmp_elems; i++)
    {
        printf("\n");
        int value, i_value, j_value;
        printf(ANSI_COLOR_YELLOW "Введите значение %d элемента:" ANSI_COLOR_RESET, i);
        if (scanf("%d", &value) <= 0)
            return INCORRECT_INPUT;
        printf(ANSI_COLOR_YELLOW "Введите индекс строки %d элемента(0..%d):" ANSI_COLOR_RESET, i, nm->rows - 1);
        if (scanf("%d", &i_value) <= 0 || i_value >= nm->rows || i_value < 0)
            return INCORRECT_INPUT;
        printf(ANSI_COLOR_YELLOW "Введите индекс столбца %d элемента(0..%d):" ANSI_COLOR_RESET, i, nm->columns - 1);
        if (scanf("%d", &j_value) <= 0 || j_value >= nm->columns || j_value < 0)
            return INCORRECT_INPUT;
        if (nm->matrix[i_value * nm->columns + j_value] == 0)
            nm->matrix[i_value * nm->columns + j_value] = value;
        else
            return INCORRECT_INPUT;
        printf("\n");
    }
    if (form_sparce(*nm, sm))
        return UNSUCCESSFUL_MEMORY_ALLOCATION;
    printf(ANSI_COLOR_YELLOW "\nДанные успешно прочитаны.\n" ANSI_COLOR_RESET);
    return SUCCESS;
}

int read_svector(s_matrix_t *sv, n_matrix_t *nv)
{
    nmatrix_del(nv);
    smatrix_del(sv);
    printf(ANSI_COLOR_YELLOW "\nЧтение вектора в разреженном виде.\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MAGENTA "Введите количество строк:" ANSI_COLOR_RESET);
    if (scanf("%d", &nv->rows) <= 0 || nv->rows <= 0)
        return INCORRECT_INPUT;
    nv->columns = 1;
    int tmp_elems;
    printf(ANSI_COLOR_MAGENTA "Введите количество ненулевых элементов:" ANSI_COLOR_RESET);
    if (scanf("%d", &tmp_elems) <= 0 || tmp_elems <= 0)
        return INCORRECT_INPUT;
    nv->matrix = calloc(nv->rows * nv->columns, sizeof(int));
    if (nv->matrix == NULL)
    {
        printf(ANSI_COLOR_RED "Невозможно выделить память." ANSI_COLOR_RESET);
        return UNSUCCESSFUL_MEMORY_ALLOCATION;
    }
    for (int i = 0; i < tmp_elems; i++)
    {
        printf("\n");
        int value, i_value, j_value;
        printf(ANSI_COLOR_YELLOW "Введите значение %d элемента:" ANSI_COLOR_RESET, i);
        if (scanf("%d", &value) <= 0)
            return INCORRECT_INPUT;
        printf(ANSI_COLOR_YELLOW "Введите индекс строки %d элемента(0..%d):" ANSI_COLOR_RESET, i, nv->rows - 1);
        if (scanf("%d", &i_value) <= 0 || i_value >= nv->rows || i_value < 0)
            return INCORRECT_INPUT;
        j_value = 1;
        if (nv->matrix[i_value * nv->columns + j_value] == 0)
            nv->matrix[i_value * nv->columns + j_value] = value;
        else
            return INCORRECT_INPUT;
        printf("\n");
    }
    if (form_sparce(*nv, sv))
        return UNSUCCESSFUL_MEMORY_ALLOCATION;
    printf(ANSI_COLOR_YELLOW "\nДанные успешно прочитаны.\n" ANSI_COLOR_RESET);
    return SUCCESS;
}