#define __USE_MINGW_ANSI_STDIO
#include "repertuar_handling.h"

#define MAX_ITER 10000

int cmp_shows(const void *p, const void *q)
{
    return (strcmp(((show_t *)p)->title, ((show_t *)q)->title));
}

int cmp_keys(const void *p, const void *q)
{
    return (strcmp(((key_t *)p)->title, ((key_t *)q)->title));
}

void cmp_sorts(show_t rep[MAX_REP_RECS], size_t rep_size, key_t key_rep[MAX_REP_RECS])
{
    if (rep_size != 0)
    {
        show_t tmp_rep[MAX_REP_RECS];
        key_t tmp_key_rep[MAX_REP_RECS];

        int64_t time1 = 0, time2 = 0, time3 = 0, time4 = 0;
        struct timeval tv_start, tv_stop;

        for (int i = 0; i < MAX_ITER; i++)
        {
            for (size_t i = 0; i < rep_size; i++)
                tmp_key_rep[i] = key_rep[i];

            gettimeofday(&tv_start, NULL);
            sort_key(key_rep, rep_size);
            gettimeofday(&tv_stop, NULL);
            time1 += (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
        }
        for (int i = 0; i < MAX_ITER; i++)
        {
            for (size_t i = 0; i < rep_size; i++)
                tmp_rep[i] = rep[i];
            for (size_t i = 0; i < rep_size; i++)
                tmp_key_rep[i] = key_rep[i];

            gettimeofday(&tv_start, NULL);
            sort_rep(rep, rep_size, tmp_key_rep);
            gettimeofday(&tv_stop, NULL);
            time2 += (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
        }

        for (int i = 0; i < MAX_ITER; i++)
        {
            for (size_t i = 0; i < rep_size; i++)
                tmp_key_rep[i] = key_rep[i];

            gettimeofday(&tv_start, NULL);
            qsort(tmp_key_rep, rep_size, sizeof(key_t), &cmp_keys);
            gettimeofday(&tv_stop, NULL);
            time3 += (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
        }
        for (int i = 0; i < MAX_ITER; i++)
        {
            for (size_t i = 0; i < rep_size; i++)
                tmp_rep[i] = rep[i];

            gettimeofday(&tv_start, NULL);
            qsort(tmp_rep, rep_size, sizeof(show_t), &cmp_shows);
            gettimeofday(&tv_stop, NULL);
            time4 += (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
        }

        printf("\n        Сортировка пузырьком:");
        printf("\n        Таблица ключей %" PRId64 " µs", time1);
        printf("\n        Таблица репертуара %" PRId64 " µs\n", time2);
        printf("\n        Быстрая сортировка:");
        printf("\n        Таблица ключей %" PRId64 " µs", time3);
        printf("\n        Таблица репертуара %" PRId64 " µs", time4);
    }
    else
    {
        printf("\n        Таблица репертуара пустая.\n");
    }
}

int shows_for_kids(show_t rep[MAX_REP_RECS], size_t rep_size)
{
    if (rep_size == 0)
    {
        printf("\n        К сожалению, таблица репертуара пустая.\n");
        return SUCCESS;
    }
    int age, dur;
    printf("\n        Введите возраст, для поиска музыкальных спектаклей:");
    if (scanf("%d", &age) <= 0)
        return INCORRECT_SEARCH;
    printf("\n        Введите максимальную продолжительность:");
    if (scanf("%d", &dur) <= 0)
        return INCORRECT_SEARCH;
    printf("\n");
    int check = 0;
    for (size_t i = 0; i < rep_size; i++)
        if (rep[i].show_type == 3 && rep[i].type.music.duration < dur && rep[i].type.music.min_age <= age)
        {
            check = 1;
            print_show(rep[i]);
            printf("\n");
        }
    if (check == 0)
        printf("\n        Ничего не найдено.");
    return SUCCESS;
}

int fread_line(FILE *file, char *s, int str_len)
{
    int ch;
    int i = 0;
    while ((ch = fgetc(file)) != '\n' && ch != EOF && (i < str_len - 1))
        if (i < str_len - 1)
            s[i++] = ch;
    s[i] = '\0';
    if (ch != '\n' && ch != EOF && i > 0)
        return INCORRECT_CONTENT;
    return i;
}

int read_show(FILE *f, show_t *buf)
{
    int ec;
    if ((ec = fread_line(f, buf->theatre, MAX_STR_SIZE + 1)) == INCORRECT_CONTENT)
        return INCORRECT_CONTENT;
    if (ec == 0)
        return EOF;
    if (feof(f))
        return INCORRECT_CONTENT;
    if (fread_line(f, buf->title, MAX_STR_SIZE + 1) == INCORRECT_CONTENT)
        return INCORRECT_CONTENT;
    if (feof(f))
        return INCORRECT_CONTENT;
    if (fread_line(f, buf->director, MAX_STR_SIZE + 1) == INCORRECT_CONTENT)
        return INCORRECT_CONTENT;
    if (fscanf(f, "%d\n", &buf->min_price) == EOF || fscanf(f, "%d\n", &buf->max_price) == EOF || fscanf(f, "%d\n", &buf->show_type) == EOF)
        return INCORRECT_CONTENT;

    if (buf->show_type == 1)
    {
        if (fscanf(f, "%d\n", &buf->type.kids.min_age) == EOF || buf->type.kids.min_age < 0 || fscanf(f, "%d\n", &buf->type.kids.genre) == EOF || (buf->type.kids.genre != 1 && buf->type.kids.genre != 2))
            return INCORRECT_CONTENT;
    }
    else if (buf->show_type == 2)
    {
        if (fscanf(f, "%d\n", &buf->type.adults.genre) == EOF || (buf->type.adults.genre != 1 && buf->type.adults.genre != 2 && buf->type.adults.genre != 3))
            return INCORRECT_CONTENT;
    }
    else if (buf->show_type == 3)
    {
        if (fread_line(f, buf->type.music.compositor, MAX_STR_SIZE + 1) == INCORRECT_CONTENT)
            return INCORRECT_CONTENT;
        if (feof(f))
            return INCORRECT_CONTENT;
        if (fread_line(f, buf->type.music.country, MAX_STR_SIZE + 1) == INCORRECT_CONTENT)
            return INCORRECT_CONTENT;
        if (feof(f))
            return INCORRECT_CONTENT;
        if (fscanf(f, "%d\n", &buf->type.music.min_age) == EOF || buf->type.music.min_age < 0 || fscanf(f, "%d\n", &buf->type.music.duration) == EOF || buf->type.music.duration < 0)
            return INCORRECT_CONTENT;
    }
    else
    {
        return INCORRECT_CONTENT;
    }
    return SUCCESS;
}
void print_rep_key(key_t key_rep[MAX_REP_RECS], size_t rep_size)
{
    if (rep_size > 0)
        for (size_t i = 0; i < rep_size; i++)
        {
            printf("\n    Ключ %zu\n", (i + 1));
            printf("            Индекс таблицы репертуара: %d\n", key_rep[i].index);
            printf("            Название спектакля: %s\n\n", key_rep[i].title);
        }
    else
        printf("        Таблица репертуара пустая.");
}

void print_rep_no_key(show_t rep[MAX_REP_RECS], size_t rep_size)
{
    if (rep_size > 0)
        for (size_t i = 0; i < rep_size; i++)
        {
            printf("\n    Запись %zu\n", (i + 1));
            print_show(rep[i]);
        }
    else
        printf("        Таблица репертуара пустая.");
}

void print_rep_with_key(show_t rep[MAX_REP_RECS], size_t rep_size, key_t key_rep[MAX_REP_RECS])
{
    if (rep_size > 0)
        for (size_t i = 0; i < rep_size; i++)
        {
            printf("\n    Запись %zu\n", (i + 1));
            print_show(rep[key_rep[i].index]);
        }
    else
        printf("        Таблица репертуара пустая.");
}

void print_show(show_t show)
{
    printf("        Театр: %s\n", show.theatre);
    printf("        Спектакль: %s\n", show.title);
    printf("        Режиссер: %s\n", show.director);
    printf("        Диапазон цен на билет: %d-%d\n", show.min_price, show.max_price);
    if (show.show_type == 1)
    {
        printf("        Тип: Детский спектакль\n");
        printf("        Возраст: %d\n", show.type.kids.min_age);
        if (show.type.kids.genre == 1)
            printf("        Жанр: Пьесса\n");
        else
            printf("        Жанр: Сказка\n");
    }
    if (show.show_type == 3)
    {
        printf("        Тип: Музыкальный спектакль\n");
        printf("        Композитор: %s\n", show.type.music.compositor);
        printf("        Страна: %s\n", show.type.music.country);
        printf("        Минимальный возраст: %d\n", show.type.music.min_age);
        printf("        Продолжительность: %d мин\n", show.type.music.duration);
    }
    if (show.show_type == 2)
    {
        printf("        Тип: Взрослый спектакль\n");
        if (show.type.adults.genre == 1)
            printf("        Жанр: Пьесса\n");
        else if (show.type.adults.genre == 2)
            printf("        Жанр: Драма\n");
        else if (show.type.adults.genre == 3)
            printf("        Жанр: Комедия\n");
    }
}

void sort_rep(show_t rep[MAX_REP_RECS], size_t rep_size, key_t key_rep[MAX_REP_RECS])
{
    if (rep_size > 0)
    {
        show_t tmp;
        for (size_t i = 0; i < rep_size - 1; i++)
            for (size_t j = 0; j < rep_size - 1 - i; j++)
                if (strcmp(rep[j].title, rep[j + 1].title) > 0)
                {
                    tmp = rep[j];
                    rep[j] = rep[j + 1];
                    rep[j + 1] = tmp;
                }
        form_key(rep, rep_size, key_rep);
    }
    else
        printf("\n        Таблица репертуара пустая.\n");
}

void sort_key(key_t key_rep[MAX_REP_RECS], size_t rep_size)
{
    if (rep_size > 0)
    {
        key_t tmp;
        for (size_t i = 0; i < rep_size - 1; i++)
            for (size_t j = 0; j < rep_size - 1 - i; j++)
                if (strcmp(key_rep[j].title, key_rep[j + 1].title) > 0)
                {
                    tmp = key_rep[j];
                    key_rep[j] = key_rep[j + 1];
                    key_rep[j + 1] = tmp;
                }
    }
    else
        printf("\n        Таблица репертуара пустая.\n");
}

int repertuar_add_rec(show_t rep[MAX_REP_RECS], size_t *rep_size, key_t key_rep[MAX_REP_RECS])
{
    show_t buf;
    if (*rep_size == MAX_REP_RECS)
        printf("        Таблица репертуара полностью заполнена. Добавление невозможно.\n");
    else
    {
        printf("        Введите название театра: ");
        if (read_line(buf.theatre) <= 0)
            return ADD_REC_ERROR;
        printf("        Введите название спектакля: ");
        if (read_line(buf.title) <= 0)
            return ADD_REC_ERROR;
        printf("        Введите имя режиссера: ");
        if (read_line(buf.director) <= 0)
            return ADD_REC_ERROR;
        printf("        Введите нижнюю границу цены билета: ");
        if (scanf("%d", &buf.min_price) <= 0 || buf.min_price <= 0)
            return ADD_REC_ERROR;
        printf("        Введите верхнюю границу цены билета: ");
        if (scanf("%d", &buf.max_price) <= 0 || buf.max_price < buf.min_price)
            return ADD_REC_ERROR;
        printf("        Введите тип спектакля\n");
        printf("        (1 - детский)\n");
        printf("        (2 - взрослый)\n");
        printf("        (3 - музыкальный): ");
        if (scanf("%d", &buf.show_type) <= 0 || (buf.show_type != 1 && buf.show_type != 2 && buf.show_type != 3))
            return ADD_REC_ERROR;
        if (buf.show_type == 1)
        {
            printf("        Введите минимальный возраст: ");
            if (scanf("%d", &buf.type.kids.min_age) <= 0 || buf.type.kids.min_age < 0)
                return ADD_REC_ERROR;
            printf("        Введите жанр спектакля:\n");
            printf("        (1 - пьесса)\n");
            printf("        (2 - сказка): ");
            if (scanf("%d", &buf.type.kids.genre) <= 0 || (buf.type.kids.genre != 1 && buf.type.kids.genre != 2))
                return ADD_REC_ERROR;
        }
        if (buf.show_type == 2)
        {
            printf("        Введите жанр спектакля:\n");
            printf("        (1 - пьесса)\n");
            printf("        (2 - драма)\n");
            printf("        (3 - комедия):");
            if (scanf("%d", &buf.type.adults.genre) <= 0 || (buf.type.adults.genre != 1 && buf.type.adults.genre != 2 && buf.type.adults.genre != 3))
                return ADD_REC_ERROR;
        }
        if (buf.show_type == 3)
        {
            printf("        Введите имя композитора: ");
            if (read_line(buf.type.music.compositor) <= 0)
                return ADD_REC_ERROR;
            printf("        Введите страну производства: ");
            if (read_line(buf.type.music.country) <= 0)
                return ADD_REC_ERROR;
            printf("        Введите минимальный возраст: ");
            if (scanf("%d", &buf.type.music.min_age) <= 0 || buf.type.music.min_age <= 0)
                return ADD_REC_ERROR;
            printf("        Введите продолжительность в минутах: ");
            if (scanf("%d", &buf.type.music.duration) <= 0 || buf.type.music.duration <= 0)
                return ADD_REC_ERROR;
        }
        rep[*rep_size] = buf;
        key_rep[*rep_size].index = *rep_size;
        strcpy(key_rep[*rep_size].title, buf.title);
        *rep_size += 1;
    }
    printf("\n        Запись успешно добавлена\n");
    return SUCCESS;
}

int repertuar_del_rec(show_t rep[MAX_REP_RECS], size_t *rep_size, key_t key_rep[MAX_REP_RECS])
{
    int choice, num;
    char str[MAX_STR_SIZE];
    if (*rep_size == 0)
        printf("        Таблица репертуара пустая.\n");
    else
    {
        printf("        Выберите номер поля, по которому вы хотите удалить\n");
        printf("        (1  - название театра)\n");
        printf("        (2  - название спектакля)\n");
        printf("        (3  - имя режиссера)\n");
        printf("        (4  - минимальная цена)\n");
        printf("        (5  - максимальная цена)\n");
        printf("        (6  - тип спектакля)\n");
        printf("        (7  - для детского спектакля: возраст)\n");
        printf("        (8  - для детского спектакля: жанр)\n");
        printf("        (9  - для взрослого спектакля: жанр)\n");
        printf("        (10 - для музыкального спектакля: имя композитора)\n");
        printf("        (11 - для музыкального спектакля: страна производства)\n");
        printf("        (12 - для музыкального спектакля: возраст)\n");
        printf("        (13 - для музыкального спектакля: продолжительность):");
        if (scanf("%d", &choice) <= 0 || choice < 1 || choice > 13)
            return DEL_REC_ERROR;
        if (choice == 1)
        {
            printf("\n        Введите название театра: ");
            if (read_line(str) <= 0)
                return DEL_REC_ERROR;
            size_t i = 0;
            while (i < *rep_size)
            {
                if (strcmp(rep[i].theatre, str) == 0)
                {
                    for (size_t j = i; j < *rep_size - 1; j++)
                        rep[j] = rep[j + 1];
                    *rep_size -= 1;
                }
                else
                    i++;
            }
        }
        if (choice == 2)
        {
            printf("\n        Введите название спектакля: ");
            if (read_line(str) <= 0)
                return DEL_REC_ERROR;
            size_t i = 0;
            while (i < *rep_size)
            {
                if (strcmp(rep[i].title, str) == 0)
                {
                    for (size_t j = i; j < *rep_size - 1; j++)
                        rep[j] = rep[j + 1];
                    *rep_size -= 1;
                }
                else
                    i++;
            }
        }
        if (choice == 3)
        {
            printf("\n        Введите имя режиссера: ");
            if (read_line(str) <= 0)
                return DEL_REC_ERROR;
            size_t i = 0;
            while (i < *rep_size)
            {
                if (strcmp(rep[i].director, str) == 0)
                {
                    for (size_t j = i; j < *rep_size - 1; j++)
                        rep[j] = rep[j + 1];
                    *rep_size -= 1;
                }
                else
                    i++;
            }
        }
        if (choice == 4)
        {
            printf("\n        Введите минимальную цену: ");
            if (scanf("%d", &num) <= 0)
                return DEL_REC_ERROR;
            size_t i = 0;
            while (i < *rep_size)
            {
                if (rep[i].min_price == num)
                {
                    for (size_t j = i; j < *rep_size - 1; j++)
                        rep[j] = rep[j + 1];
                    *rep_size -= 1;
                }
                else
                    i++;
            }
        }
        if (choice == 5)
        {
            printf("\n        Введите максимальную цену: ");
            if (scanf("%d", &num) <= 0)
                return DEL_REC_ERROR;
            size_t i = 0;
            while (i < *rep_size)
            {
                if (rep[i].max_price == num)
                {
                    for (size_t j = i; j < *rep_size - 1; j++)
                        rep[j] = rep[j + 1];
                    *rep_size -= 1;
                }
                else
                    i++;
            }
        }
        if (choice == 6)
        {
            printf("\n        Введите тип спектакля\n");
            printf("        (1 - детский)\n");
            printf("        (2 - взрослый)\n");
            printf("        (3 - музыкальный): ");
            if (scanf("%d", &num) <= 0 || (num != 1 && num != 2 && num != 3))
                return DEL_REC_ERROR;
            size_t i = 0;
            while (i < *rep_size)
            {
                if (rep[i].show_type == num)
                {
                    for (size_t j = i; j < *rep_size - 1; j++)
                        rep[j] = rep[j + 1];
                    *rep_size -= 1;
                }
                else
                    i++;
            }
        }
        if (choice == 7)
        {
            printf("\n        Введите минимальный возраст: ");
            if (scanf("%d", &num) <= 0 || num < 0)
                return DEL_REC_ERROR;
            size_t i = 0;
            while (i < *rep_size)
            {
                if (rep[i].show_type == 1 && rep[i].type.kids.min_age == num)
                {
                    for (size_t j = i; j < *rep_size - 1; j++)
                        rep[j] = rep[j + 1];
                    *rep_size -= 1;
                }
                else
                    i++;
            }
        }
        if (choice == 8)
        {
            printf("\n        Введите жанр спектакля:");
            printf("        (1 - пьесса)\n");
            printf("        (2 - сказка): ");
            if (scanf("%d", &num) <= 0 || (num != 1 && num != 2))
                return DEL_REC_ERROR;
            size_t i = 0;
            while (i < *rep_size)
            {
                if (rep[i].show_type == 1 && rep[i].type.kids.genre == num)
                {
                    for (size_t j = i; j < *rep_size - 1; j++)
                        rep[j] = rep[j + 1];
                    *rep_size -= 1;
                }
                else
                    i++;
            }
        }
        if (choice == 9)
        {
            printf("\n        Введите жанр спектакля:");
            printf("        (1 - пьесса)\n");
            printf("        (2 - драма)\n");
            printf("        (3 - комедия):");
            if (scanf("%d", &num) <= 0 || (num != 1 && num != 2 && num != 3))
                return DEL_REC_ERROR;
            size_t i = 0;
            while (i < *rep_size)
            {
                if (rep[i].show_type == 2 && rep[i].type.adults.genre == num)
                {
                    for (size_t j = i; j < *rep_size - 1; j++)
                        rep[j] = rep[j + 1];
                    *rep_size -= 1;
                }
                else
                    i++;
            }
        }
        if (choice == 10)
        {
            printf("\n        Введите имя композитора: ");
            if (read_line(str) <= 0)
                return DEL_REC_ERROR;
            size_t i = 0;
            while (i < *rep_size)
            {
                if (rep[i].show_type == 3 && strcmp(rep[i].type.music.compositor, str) == 0)
                {
                    for (size_t j = i; j < *rep_size - 1; j++)
                        rep[j] = rep[j + 1];
                    *rep_size -= 1;
                }
                else
                    i++;
            }
        }
        if (choice == 11)
        {
            printf("\n        Введите страну производства: ");
            if (read_line(str) <= 0)
                return DEL_REC_ERROR;
            size_t i = 0;
            while (i < *rep_size)
            {
                if (rep[i].show_type == 3 && strcmp(rep[i].type.music.country, str) == 0)
                {
                    for (size_t j = i; j < *rep_size - 1; j++)
                        rep[j] = rep[j + 1];
                    *rep_size -= 1;
                }
                else
                    i++;
            }
        }
        if (choice == 12)
        {
            printf("\n        Введите возраст: ");
            if (scanf("%d", &num) <= 0)
                return DEL_REC_ERROR;
            size_t i = 0;
            while (i < *rep_size)
            {
                if (rep[i].show_type == 3 && rep[i].type.music.min_age == num)
                {
                    for (size_t j = i; j < *rep_size - 1; j++)
                        rep[j] = rep[j + 1];
                    *rep_size -= 1;
                }
                else
                    i++;
            }
        }
        if (choice == 13)
        {
            printf("\n        Введите продолжительность: ");
            if (scanf("%d", &num) <= 0)
                return DEL_REC_ERROR;
            size_t i = 0;
            while (i < *rep_size)
            {
                if (rep[i].show_type == 3 && rep[i].type.music.duration == num)
                {
                    for (size_t j = i; j < *rep_size - 1; j++)
                        rep[j] = rep[j + 1];
                    *rep_size -= 1;
                }
                else
                    i++;
            }
        }
        form_key(rep, *rep_size, key_rep);
    }
    printf("\n        Очистка по заданному полю завершена\n");
    return SUCCESS;
}
void form_key(show_t rep[MAX_REP_RECS], size_t rep_size, key_t key_rep[MAX_REP_RECS])
{
    for (size_t i = 0; i < rep_size; i++)
    {
        key_rep[i].index = i;
        strcpy(key_rep[i].title, rep[i].title);
    }
}

int fread_repertuar(FILE *f, show_t rep[MAX_REP_RECS], size_t *rep_size, key_t key_rep[MAX_REP_RECS])
{
    int e_c = SUCCESS;
    show_t buf;

    while (e_c == SUCCESS && *rep_size < MAX_REP_RECS)
    {
        e_c = read_show(f, &buf);
        if (e_c == SUCCESS)
        {
            rep[*rep_size] = buf;
            *rep_size += 1;
        }
        else if (e_c == EOF && *rep_size > 0)
        {
            form_key(rep, *rep_size, key_rep);
            fclose(f);
            printf("\n        Данные успешно прочитаны.\n");
            return SUCCESS;
        }
        else
        {
            fclose(f);
            return INCORRECT_CONTENT;
        }
    }
    return SUCCESS;
}

int read_line(char str[MAX_STR_SIZE + 1])
{

    char ch = '\0';
    int size = 0;
    ch = getchar();
    if (ch != '\n')
    {
        str[size] = ch;
        size += 1;
    }
    while ((ch = getchar()) != '\n' && size < MAX_STR_SIZE + 1)
        if (size == MAX_STR_SIZE)
        {
            printf("\n        Превышена максимальная длина строки\n");
            return INCORRECT_CONTENT;
        }
        else
        {
            str[size] = ch;
            size += 1;
        }
    str[size] = '\0';
    return size;
}

int save_curr_table(show_t rep[MAX_REP_RECS], size_t rep_size)
{
    FILE *f = fopen("out.txt", "w");
    for (size_t i = 0; i < rep_size; i++)
    {
        fprintf(f, "%s\n", rep[i].theatre);
        fprintf(f, "%s\n", rep[i].title);
        fprintf(f, "%s\n", rep[i].director);
        fprintf(f, "%d\n", rep[i].min_price);
        fprintf(f, "%d\n", rep[i].max_price);
        fprintf(f, "%d\n", rep[i].show_type);
        if (rep[i].show_type == 1)
        {
            fprintf(f, "%d\n", rep[i].type.kids.min_age);
            fprintf(f, "%d\n", rep[i].type.kids.genre);
        }
        if (rep[i].show_type == 2)
        {
            fprintf(f, "%d\n", rep[i].type.adults.genre);
        }
        if (rep[i].show_type == 3)
        {
            fprintf(f, "%s\n", rep[i].type.music.compositor);
            fprintf(f, "%s\n", rep[i].type.music.country);
            fprintf(f, "%d\n", rep[i].type.music.min_age);
            fprintf(f, "%d\n", rep[i].type.music.duration);
        }
    }
    fclose(f);
}