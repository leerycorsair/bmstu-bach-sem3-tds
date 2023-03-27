#ifndef REAL_NUMS_IO_H
#define REAL_NUMS_IO_H
#ifndef __USE_MINGW_ANSI_STDIO
#define __USE_MINGW_ANSI_STDIO
#endif

#include "my_real.h"
#include "err_codes.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


#define MAXSTRSIZE 256
int print_my_real(my_real_t num);
int read_line(char *str);
int check_str_to_real(char *str);
my_real_t str_to_real(char*str);
int is_zero(char *str);

#endif