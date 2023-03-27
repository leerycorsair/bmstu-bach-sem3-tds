#ifndef __NUMBERS_H__
#define __NUMBERS_H__

#include <stdlib.h>
#include <math.h>

#include <inttypes.h>
#include <sys/time.h>

#define EPS 1e-6
#define CMP_NUMS(num1, num2) (fabs((num1) - (num2)) <= EPS)

typedef struct
{
    double sum;
    size_t points;
} avg_t;

double avg_get(avg_t avg);
void avg_add(avg_t *avg, double num);
void avg_wipe(avg_t *avg);
double rand_num(double min, double max);
uint64_t tick(void);

#endif //__NUMBERS_H__