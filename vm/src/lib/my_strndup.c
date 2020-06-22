#include <my_lib.h>

char* my_strndup(char* a, int n)
{
    char* res;
    if (!n)
    {
        return NULL;
    }

    if (!(res = (char*)malloc(sizeof(char) * (n + 1))))
    {
        return NULL;
    }

    for (int i = 0; a[i] && i < n; i++)
    {
        res[i] = a[i];
    }
    res[n] = 0;
    return res;
}