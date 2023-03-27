#include "config.h"

void default_config_init(config_t *config)
{
    config->first_in_min = 0;
    config->first_in_max = 5;
    config->first_proc_min = 0;
    config->first_proc_max = 4;
    config->second_proc_min = 0;
    config->second_proc_max = 4;
}
void print_config(config_t config)
{
    printf(ANSI_COLOR_MAGENTA "Текущие параметры генерации\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW "Время прихода заявки 1 типа:%.3lf..%.3lf\n" ANSI_COLOR_RESET, config.first_in_min, config.first_in_max);
    printf(ANSI_COLOR_YELLOW "Время обработки заявки 1 типа:%.3lf..%.3lf\n" ANSI_COLOR_RESET, config.first_proc_min, config.first_proc_max);
    printf(ANSI_COLOR_YELLOW "Время обработки заявки 2 типа:%.3lf..%.3lf\n" ANSI_COLOR_RESET, config.second_proc_min, config.second_proc_max);
}
void read_config(config_t *config)
{
    printf("\n");
    printf(ANSI_COLOR_GREEN "Введите минимальное время прихода первой заявки:" ANSI_COLOR_RESET);
    if (!scanf("%lf", &config->first_in_min) || config->first_in_min < 0)
    {
        printf(ANSI_COLOR_RED "Вы совершили ошибку, повторите попытку." ANSI_COLOR_RESET);
        return;
    }
    printf(ANSI_COLOR_GREEN "Введите максимальное время прихода первой заявки:" ANSI_COLOR_RESET);
    if (!scanf("%lf", &config->first_in_max) || config->first_in_max < 0 || config->first_in_max <= config->first_in_min)
    {
        printf(ANSI_COLOR_RED "Вы совершили ошибку, повторите попытку." ANSI_COLOR_RESET);
        return;
    }
    printf("\n");
    printf(ANSI_COLOR_GREEN "Введите минимальное время обработки первой заявки:" ANSI_COLOR_RESET);
    if (!scanf("%lf", &config->first_proc_min) || config->first_proc_min < 0)
    {
        printf(ANSI_COLOR_RED "Вы совершили ошибку, повторите попытку." ANSI_COLOR_RESET);
        return;
    }
    printf(ANSI_COLOR_GREEN "Введите максимальное время обработки первой заявки:" ANSI_COLOR_RESET);
    if (!scanf("%lf", &config->first_proc_max) || config->first_proc_max < 0 || config->first_proc_max <= config->first_proc_min)
    {
        printf(ANSI_COLOR_RED "Вы совершили ошибку, повторите попытку." ANSI_COLOR_RESET);
        return;
    }
    printf("\n");
    printf(ANSI_COLOR_GREEN "Введите минимальное время обработки второй заявки:" ANSI_COLOR_RESET);
    if (!scanf("%lf", &config->second_proc_min) || config->second_proc_min < 0)
    {
        printf(ANSI_COLOR_RED "Вы совершили ошибку, повторите попытку." ANSI_COLOR_RESET);
        return;
    }
    printf(ANSI_COLOR_GREEN "Введите максимальное время обработки второй заявки:" ANSI_COLOR_RESET);
    if (!scanf("%lf", &config->second_proc_max) || config->second_proc_max < 0 || config->second_proc_max <= config->second_proc_min)
    {
        printf(ANSI_COLOR_RED "Вы совершили ошибку, повторите попытку." ANSI_COLOR_RESET);
        return;
    }
}