#ifndef __IO_LIB_H__
#define __IO_LIB_H__

#include <stdio.h>
#include "err_codes.h"

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_RESET "\x1b[0m"

void print_menu(void);
void print_welcome(void);

// int read_line(FILE *file, char **s);

#endif //__IO_LIB_H__