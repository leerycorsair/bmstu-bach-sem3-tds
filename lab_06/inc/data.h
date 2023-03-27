#ifndef __DATA_H__
#define __DATA_H__

#include "vector.h"
#include "io_lib.h"

typedef vector_t data_t;

void data_init(data_t *data);
void data_wipe(data_t *data);
void print_data(data_t *data);

int data_read(data_t *data);


#endif //__DATA_H__