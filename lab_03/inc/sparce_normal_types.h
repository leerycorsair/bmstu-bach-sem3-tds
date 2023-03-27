#ifndef __SPARCE_NORMAL_TYPES_H__
#define __SPARCE_NORMAL_TYPES_H__

typedef struct
{
    int *matrix;
    int rows;
    int columns;
} n_matrix_t;

typedef struct
{
    int *nnz_values;
    int *column_indeces;
    int *row_indeces;
    int elems;
    int rows;
    int columns;
} s_matrix_t;

#endif
