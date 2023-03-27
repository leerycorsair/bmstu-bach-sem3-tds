#include <stdio.h>

#include "io_lib.h"
#include "err_codes.h"
#include "model.h"
#include "log.h"

void go_modeling(model_t *model, log_t *log)
{
    log_wipe(log);
    log_create(log);
    model_launch(model, log);
    config_t tmp = model->config;
    model_del(model);
    model_create(model);

    model->config = tmp;
}

void go_exit(model_t *model, log_t *log)
{
    printf(ANSI_COLOR_GREEN "\nПрограмма завершена.\n" ANSI_COLOR_RESET);
    log_wipe(log);
    model_del(model);
}

void go_author()
{
    print_author();
}

void go_config(model_t *model)
{
    print_config(model->config);
    read_config(&model->config);
}

void go_log(log_t log)
{
    print_log(log);
    print_log_unique(log);
}

void option_perform(int option, model_t *model, log_t *log)
{
    switch (option)
    {
    case 0:
        go_exit(model, log);
        break;
    case 1:
        go_modeling(model, log);
        break;
    case 2:
        go_config(model);
        break;
    case 3:
        go_log(*log);
        break;
    case 4:
        go_author();
        break;
    default:
        printf(ANSI_COLOR_RED "Некорректная опция меню.\n" ANSI_COLOR_RESET);
        break;
    }
}

int main(void)
{
    setbuf(stdout, NULL);
    srand(time(NULL));

    print_welcome();

    log_t log;
    if (log_create(&log))
    {
        printf(ANSI_COLOR_RED "Не удалось выделить память под журнал." ANSI_COLOR_RESET);
        return UNSUCCESSFUL_MEMORY_ALLOCATION;
    }

    model_t model;
    if (model_create(&model))
    {
        printf(ANSI_COLOR_RED "Не удалось выделить память под очередь." ANSI_COLOR_RESET);
        log_wipe(&log);
        return UNSUCCESSFUL_MEMORY_ALLOCATION;
    }

    int option = -1;
    while (option)
    {
        option = -1;
        print_menu();
        printf(ANSI_COLOR_MAGENTA "Выберите опцию меню:" ANSI_COLOR_RESET);
        if (!scanf("%d", &option) || option < 0 || option > 4)
        {
            printf(ANSI_COLOR_RED "Некорректная опция меню.\n" ANSI_COLOR_RESET);
            return INCORRECT_OPTION;
        }
        else
            option_perform(option, &model, &log);
    }
    return SUCCESS;
}