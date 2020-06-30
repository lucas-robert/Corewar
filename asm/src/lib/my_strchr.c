#include <my_lib.h>

char *my_strchr(char *s, int c)
{
    int i;
    char *res = NULL;

    if (s && s[0] == c)
        i = 1;
    else
        i = 0;
    if (s)
    {
        while (s[i])
        {
            if (s[i] == c)
            {
                while (s[i] == c)
                {
                    i++;
                }
                res = my_strdup(&s[i]);
                free(s);
                return (res);
            }
            else
                i++;
        }
    }

    if (c == '\0') return ((char *)&s[i]);
    return NULL;
}