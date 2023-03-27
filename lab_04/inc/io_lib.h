#ifndef __IO_LIB_H__
#define __IO_LIB_H__

#include <stdio.h>
#include "structs.h"
#include "err_codes.h"
#include "mem_manager.h"
#include "stack_processing.h"

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_RESET "\x1b[0m"

void print_menu(void);
void print_welcome(void);

int read_stack(list_stack_t *list_stack, vector_stack_t *vector_stack);
int form_ls_by_vs(list_stack_t *list_stack, vector_stack_t vector_stack);

void print_vector_stack(vector_stack_t vector_stack);
void print_list_stack(list_stack_t list_stack);
void print_free_mem_pointers(node_t **free_mem_pointers, size_t size);

#endif