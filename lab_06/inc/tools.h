#ifndef __TOOLS_H__
#define __TOOLS_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <inttypes.h>
#include <sys/time.h>

uint64_t tick(void);

int is_prime(int num);
int next_prime(int n);

void empty_stream(FILE *stream);

#endif //__TOOLS_H__