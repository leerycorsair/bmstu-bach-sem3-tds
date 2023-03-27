#ifndef __LOG_H__
#define __LOG_H__

#include "vector.h"
#include "io_lib.h"

#define MAX_LOGS 50

typedef struct
{
    vector_t allocated;
    size_t allocated_unique;
    vector_t freed;
    size_t freed_unique;
} log_t;

int log_create(log_t *log);
void log_wipe(log_t *log);

int log_add(log_t *log, int mode, void *elem);

void print_log(log_t log);
void print_log_unique(log_t log);

#endif //__LOG_H__