#include <my_lib.h>

int isspace(int a)
{
    if (a == ' ' || a == '\t' || a == '\r' || a == '\v' || a == '\f')
        return (1);
    return (0);
}
