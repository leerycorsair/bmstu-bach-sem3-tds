#include "numbers.h"

void avg_add(avg_t *avg, double num)
{
    avg->sum += num;
    avg->points++;
}

double avg_get(avg_t avg)
{
    if (avg.points == 0)
        return 0;
    return (avg.sum / avg.points);
}

void avg_wipe(avg_t *avg)
{
    avg->sum = 0;
    avg->points = 0;
}

double rand_num(double min, double max)
{
    return (min + (max - min) * (rand() / (double)RAND_MAX));
}

uint64_t tick(void)
{
    uint32_t high, low;
    __asm__ __volatile__(
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r"(high), "=r"(low)::"%rax", "%rbx", "%rcx", "%rdx");

    uint64_t ticks = ((uint64_t)high << 32) | low;

    return ticks;
}