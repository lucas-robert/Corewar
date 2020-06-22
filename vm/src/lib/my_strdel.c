#include <my_lib.h>

void my_strdel(char **as)
{
    if (as != NULL)
    {
        free(*as);
        *as = NULL;
    }
}