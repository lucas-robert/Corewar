#include <my_lib.h>

char* my_strdup(char* a)
{
    char* res;
    int i = 0;
    int len = my_strlen(a);
    if (len == 0) return NULL;

    if (!(res = (char*)malloc(sizeof(char) * (len + 1)))) return NULL;

    for (; a[i]; i++)
    {
        res[i] = a[i];
    }
    res[i] = 0;
    return res;
}