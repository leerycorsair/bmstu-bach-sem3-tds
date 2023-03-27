#ifndef __TOOLS_H__
#define __TOOLS_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <inttypes.h>
#include <sys/time.h>
#include <time.h>

uint64_t tick(void);

void empty_stream(FILE *stream);
void file_matrix_gen(size_t matrix_size, char *filename);
// size_t **gen_sparse_matrix(size_t **matrix, size_t size, size_t rate);

#endif //__TOOLS_H__