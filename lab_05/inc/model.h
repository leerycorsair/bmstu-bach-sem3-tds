#ifndef __MODEL_H__
#define __MODEL_H__

#include <stdlib.h>
#include "queue.h"
#include "config.h"
#include "log.h"


#define MAX_REQUESTS 1000
#define STEP 100

typedef struct
{
    config_t config;
    queue_t queue;
    double total_time;
    double idle_time;
    size_t first_in;
    size_t first_out;
    size_t second_proced;
} model_t;


int model_create(model_t* model);
void model_del(model_t *model);
void model_launch(model_t *model, log_t*log);


#endif //__MODEL_H__