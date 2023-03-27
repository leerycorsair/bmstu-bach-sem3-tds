#include "file.h"

#include <string.h>

int search_file(char *to_find, FILE *f)
{
    rewind(f);
    int i = 0;
    char buffer[MAX_STR_LEN];
    while (fscanf(f, "%s\n", buffer) > 0 && feof(f) != EOF)
    {
        i++;
        if (buffer[strlen(buffer)] == '\n')
            buffer[strlen(buffer)] = '\0';

        if (strcmp(to_find, buffer) == 0)
        {
            return i;
        }
    }
    rewind(f);
    return 0;
}