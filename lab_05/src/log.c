#include "log.h"

int log_create(log_t *log)
{
    if (vector_init(&log->allocated))
        return UNSUCCESSFUL_MEMORY_ALLOCATION;
    if (vector_init(&log->freed))
    {
        vector_free(&log->allocated);
        return UNSUCCESSFUL_MEMORY_ALLOCATION;
    }
    log->allocated_unique = 0;
    log->freed_unique = 0;
    return SUCCESS;
}

void log_wipe(log_t *log)
{
    vector_free(&log->allocated);
    vector_free(&log->freed);
    log->freed_unique = 0;
    log->allocated_unique = 0;
}

int log_add(log_t *log, int mode, void *elem)
{
    if (mode == 1)
        return vector_add(&log->allocated, elem);
    else if (mode == 2)
        return vector_add(&log->freed, elem);
    else
        return -1;
}

void print_log(log_t log)
{
    if (log.allocated.curr_len == 0 && log.freed.curr_len == 0)
    {
        printf(ANSI_COLOR_YELLOW "Журнал пуст.\n" ANSI_COLOR_RESET);
        return;
    }
    else
    {
        printf("%40s%43s\n", "Выделенные", "Освобожденные");
        for (size_t i = 0; i < log.allocated.curr_len || i < log.freed.curr_len; i++)
        {

#ifdef MAX_LOGS
            if (i >= MAX_LOGS)
            {
                printf(".....\n");
                break;
            }
#endif
            if (i < log.allocated.curr_len)
                printf("%30p", log.allocated.data[i]);
            else
                printf("%30s", "");
            if (i < log.freed.curr_len)
                printf("%30p", log.freed.data[i]);
            printf("\n");
        }
    }
}

void print_log_unique(log_t log)
{
    double reusage = 100 * (1 - check_unique(log.allocated));
    printf(ANSI_COLOR_GREEN "Повторное использованной памяти:%g\n" ANSI_COLOR_RESET, reusage);
}