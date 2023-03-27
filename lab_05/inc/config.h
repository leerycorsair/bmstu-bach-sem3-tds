#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "io_lib.h"

typedef struct
{
    double first_in_min;
    double first_in_max;
    double first_proc_min;
    double first_proc_max;
    double second_proc_min;
    double second_proc_max;
} config_t;

void default_config_init(config_t *config);
void print_config(config_t config);
void read_config(config_t *config);

#endif