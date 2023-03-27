#include "tools.h"

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

void empty_stream(FILE *stream)
{
    int c = getc(stream);

    while (c != '\n' && c != EOF)
        c = getc(stream);
}

int is_prime(int num)
{
    if (num <= 1)
        return 0;
    if (num % 2 == 0 && num > 2)
        return 0;
    for (int i = 3; i < floor(sqrt(num)); i += 2)
        if (num % i == 0)
            return 0;
    return 1;
}

int next_prime(int n)
{
    int prime = n + 1;
    while (!is_prime(prime))
        prime++;
    return prime;
}
