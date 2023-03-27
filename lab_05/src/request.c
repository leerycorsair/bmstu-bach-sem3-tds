#include "request.h"

request_t *request_create(int type, double proc_time)
{
    request_t *request = malloc(sizeof(request_t));
    if (!request)
        return NULL;

    request->type = type;
    request->proc_time = proc_time;

    return request;
}

void request_free(request_t **request)
{
    if (!request || !*request)
        return;

    free(*request);
    *request = NULL;
}