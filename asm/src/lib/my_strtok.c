#include <my_lib.h>

char *my_strtok(char *str, char sep)
{
    char *res;
    int i = 0;
    if (str)
    {
        while (str[i] == sep) i++;
        while (str[i] && str[i] != sep) i++;
    }
    if (!str) return NULL;

    if (!(res = (char *)malloc(sizeof(char) * (i + 1)))) return NULL;

    for (int j = 0; j < i; j++)
    {
        res[j] = str[j];
    }
    res[i] = '\0';
    return res;
}