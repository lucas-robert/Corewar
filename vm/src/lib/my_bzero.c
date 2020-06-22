#include <my_lib.h>

void my_bzero(char *s, int n)
{
    int i;

    i = 0;
    while (i < n)
    {
        ((char *)s)[i] = '\0';
        i++;
    }
    return;
}