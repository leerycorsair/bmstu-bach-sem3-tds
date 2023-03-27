#define __USE_MINGW_ANSI_STDIO
#include "model.h"

int model_create(model_t *model)
{
    default_config_init(&model->config);
    if (queue_create(&model->queue))
        return UNSUCCESSFUL_MEMORY_ALLOCATION;
    model->first_in = 0;
    model->first_out = 0;
    model->second_proced = 0;
    model->total_time = 0;
    model->idle_time = 0;
    return SUCCESS;
}

void model_del(model_t *model)
{
    queue_del(&model->queue);
}

void model_launch(model_t *model, log_t *log)
{
    size_t last_print = 0;
    double first_in = 0;
    double time_proc = rand_num(model->config.second_proc_min, model->config.second_proc_max);

    request_t *last = NULL;
    double next_event = 0;

    queue_f_insert(&model->queue, request_create(2, 0));
    time_proc = 0;

    printf("---------------------------------------------------------\n");
    printf("|Заявок типа 1|Пришло заявок|Текущая длина|Средняя длина|\n");
    printf("|  обработано |    1 типа   |   очереди   |   очереди   |\n");

    while (model->first_out < MAX_REQUESTS)
    {
        if (CMP_NUMS(first_in, next_event))
        {
            request_t *request = NULL;
            request = request_create(1, first_in);
            queue_f_insert(&model->queue, request);
            log_add(log, 1, request);
            model->first_in++;
            first_in += rand_num(model->config.first_in_min, model->config.first_in_max);
        }
        if (CMP_NUMS(time_proc, next_event))
        {
            if (model->queue.curr_len != 0)
            {
                last = list_queue_del_elem(&model->queue.list_queue);
                array_queue_del_elem(&model->queue.array_queue);
                model->queue.curr_len--;
                if (last->type == 1)
                {
                    model->first_out++;
                    log_add(log, 2, last);
                    request_free(&last);
                    time_proc += rand_num(model->config.first_proc_min, model->config.first_proc_max);
                }
                else
                {
                    model->second_proced++;
                    last->proc_time = rand_num(model->config.second_proc_min, model->config.second_proc_max);
                    queue_s_insert(&model->queue, last);
                    time_proc += rand_num(model->config.second_proc_min, model->config.second_proc_max);
                }
            }
            else
                model->idle_time += first_in - time_proc;
        }
        next_event = fmin(first_in, time_proc);

        if (model->first_out % STEP == 0 && model->first_out != last_print)
        {
            printf("---------------------------------------------------------\n");
            printf("|%13zu|%13zu|%13zu|%13.3lf|\n", model->first_out, model->first_in, model->queue.curr_len, avg_get(model->queue.avg_len));
            last_print = model->first_out;
        }
    }
    model->total_time = first_in;
    printf("---------------------------------------------------------\n");
    printf(ANSI_COLOR_MAGENTA "\nРезультаты моделирования\n" ANSI_COLOR_RESET);

    double avg_s_proc = model->config.second_proc_min + (model->config.second_proc_max - model->config.second_proc_min) / 2.0;
    double avg_f_in = model->config.first_in_min + (model->config.first_in_max - model->config.first_in_min) / 2.0;
    double avg_f_proc = model->config.first_proc_min + (model->config.first_proc_max - model->config.first_proc_min) / 2.0;
    double expected_time;
    if (avg_f_in >= avg_f_proc)
    {
        avg_s_proc = (avg_s_proc - (avg_f_in - avg_f_proc)) * 0.25;
        expected_time = avg_f_in * MAX_REQUESTS + avg_s_proc * model->second_proced;
    }
    else
        expected_time = avg_f_proc * MAX_REQUESTS + avg_s_proc * model->second_proced;

    printf(ANSI_COLOR_YELLOW "Ожидаемое время: %g е.в.\n" ANSI_COLOR_RESET, expected_time);
    printf(ANSI_COLOR_YELLOW "Фактическое время: %g е.в.\n" ANSI_COLOR_RESET, model->total_time);
    printf(ANSI_COLOR_YELLOW "Время простоя: %g е.в.\n" ANSI_COLOR_RESET, model->idle_time);
    printf(ANSI_COLOR_YELLOW "Погрешность: %g %%\n" ANSI_COLOR_RESET, 100*fabs(model->total_time - expected_time)/expected_time);
    printf("\n");
    printf(ANSI_COLOR_YELLOW "Количество вошедших заявок первого типа: %zu\n" ANSI_COLOR_RESET, model->first_in);
    printf(ANSI_COLOR_YELLOW "Количество вышедших заявок первого типа: %zu\n" ANSI_COLOR_RESET, model->first_out);
    printf(ANSI_COLOR_YELLOW "Количество обращений заявок второго типа: %zu\n" ANSI_COLOR_RESET, model->second_proced);
    printf("\n");
    printf(ANSI_COLOR_YELLOW "Время работы очереди на массиве: %5.3lf мс\n" ANSI_COLOR_RESET, model->queue.array_time / 1000000.0);
    printf(ANSI_COLOR_YELLOW "Время работы очереди на списке: %5.3lf мс\n" ANSI_COLOR_RESET, model->queue.list_time / 1000000.0);
    printf("\n");
    printf(ANSI_COLOR_YELLOW "Среднее время обработки заявки первого типа: %5.3lf мс\n" ANSI_COLOR_RESET, model->total_time / model->first_out);
    printf(ANSI_COLOR_YELLOW "Среднее время обработки заявки второго типа: %5.3lf мс\n" ANSI_COLOR_RESET, model->total_time / model->second_proced);
    printf("\n");
    printf(ANSI_COLOR_YELLOW "Память очереди на массиве: %zu\n" ANSI_COLOR_RESET, model->queue.array_mem);
    printf(ANSI_COLOR_YELLOW "Память очереди на списке: %zu\n" ANSI_COLOR_RESET, model->queue.list_mem);
    printf("\n");
}
