#ifndef __IO_LIB_H__
#define __IO_LIB_H__

#include <stdio.h>
#include <stdlib.h>
#include "err_codes.h"
#include "sparce_normal_types.h"
#include "matrix_processing.h"

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_RESET "\x1b[0m"


void print_menu(void);
void print_help(void);

void print_n(n_matrix_t m);
void print_s(s_matrix_t m);

int read_nmatrix(n_matrix_t *m, s_matrix_t *sm);
int read_nvector(n_matrix_t *v, s_matrix_t *sv);

int read_smatrix(s_matrix_t *sm, n_matrix_t *nm);
int read_svector(s_matrix_t *sv, n_matrix_t *nv);

#endif