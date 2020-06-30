#include "my_lib.h"

char *my_strcat(char *dest, const char *app)
{
    char *d;

    d = dest;
    while (*d) d++;
    while (*app)
    {
        *d = *app;
        app++;
        d++;
    }
    *d = '\0';
    return (dest);
}