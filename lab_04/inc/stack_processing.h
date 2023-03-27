#ifndef __STACK_PROCESSING_H__
#define __STACK_PROCESSING_H__

#include <inttypes.h>
#include <sys/time.h>
#include "err_codes.h"
#include "io_lib.h"



int vector_stack_push(vector_stack_t *vector_stack, int value);
int vector_stack_pop(vector_stack_t *vector_stack);

int list_stack_push(list_stack_t *list_stack, int value);
int list_stack_pop(list_stack_t *list_stack);

int gen_stack(list_stack_t *list_stack, vector_stack_t *vector_stack, int size);

int sort_vector_stacks(vector_stack_t vector_stack_1, vector_stack_t vector_stack_2, vector_stack_t *vector_stack_3);
int merge_vector_stacks(vector_stack_t vector_stack_1, vector_stack_t vector_stack_2, vector_stack_t *vector_stack_3);
int sort_vector_stack(vector_stack_t *vector_stack);

int sort_list_stacks(list_stack_t list_stack_1, list_stack_t list_stack_2, list_stack_t *list_stack_3);
int merge_list_stacks(list_stack_t list_stack_1, list_stack_t list_stack_2, list_stack_t *list_stack_3);
int sort_list_stack(list_stack_t *list_stack);

// uint64_t tick(void);

#endif