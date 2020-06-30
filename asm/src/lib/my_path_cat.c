#include <my_lib.h>

void my_path_cat(char *buff, char *s1, char *s2)
{
    int z;

    z = 0;
    for (int i = 0; i < my_strlen(s1); i++, z++) buff[z] = s1[i];
    buff[z++] = '/';
    for (int i = 0; i < my_strlen(s2); i++, z++) buff[z] = s2[i];
    buff[z] = '\0';
}