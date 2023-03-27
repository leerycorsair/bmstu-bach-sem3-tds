#ifndef __MATRIX_PROCESSING_H__
#define __MATRIX_PROCESSING_H__

#include <stdlib.h>
#include <inttypes.h>
#include <sys/time.h>
#include "io_lib.h"
#include "err_codes.h"
#include "sparce_normal_types.h"

int *nmatrix_create(n_matrix_t m);

int form_sparce(n_matrix_t src, s_matrix_t *dst);
int form_normal(s_matrix_t src, n_matrix_t *dst);
int generator(n_matrix_t *nm, s_matrix_t *sm, n_matrix_t *nv, s_matrix_t *sv, int rows, int columns, int sparce_rate);

void nmatrix_del(n_matrix_t *m);
void smatrix_del(s_matrix_t *m);
void memory_wipe(n_matrix_t *m1, n_matrix_t *m2, s_matrix_t *m3, s_matrix_t *m4, n_matrix_t *m5, s_matrix_t *m6);
int n_multi(n_matrix_t m1, n_matrix_t m2, n_matrix_t *res, uint64_t *time);
int s_multi(s_matrix_t m1, s_matrix_t m2, s_matrix_t *res, uint64_t *time);

uint64_t tick(void);

#endif