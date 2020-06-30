#include <my_lib.h>

char *concat(char *s1, char *s2)
{
    char *res;
    int len = my_strlen(s1) + my_strlen(s2) + 1;
    if (!(res = (char *)malloc(sizeof(char) * len))) return NULL;

    int i = 0;
    int j = 0;
    if (s1)
    {
        while (s1[i])
        {
            res[i] = s1[i];
            i++;
        }
    }
    if (s2)
    {
        while (s2[j])
        {
            res[i] = s2[j];
            i++;
            j++;
        }
    }

    res[i] = '\0';
    free(s1);
    return res;
}