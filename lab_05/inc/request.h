#ifndef __REQUEST_H__
#define __REQUEST_H__

#include <stdlib.h>

typedef struct
{
    int type;
    double proc_time;
} request_t;

request_t *request_create(int type, double proc_time);
void request_free(request_t **request);

#endif //__REQUEST_H__