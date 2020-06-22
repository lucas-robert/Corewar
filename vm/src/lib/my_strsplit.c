#include <my_lib.h>

static int countwords(char const *s, char c)
{
    int cwords;
    int j;

    j = 0;
    cwords = 0;
    while (s[j])
    {
        while (s[j] == c && s[j]) j++;
        if (s[j] != c && s[j])
        {
            cwords++;
            while (s[j] != c && s[j]) j++;
        }
    }
    return (cwords);
}

static char **freeallarr(char ***arr)
{
    int i;

    i = 0;
    while ((*arr)[i]) my_strdel(&(*arr)[i++]);
    free(**arr);
    **arr = 0;
    return (0);
}

char **my_strsplit(char const *s, char c)
{
    char **wordarr;
    int start;
    int i;
    int cword;

    if (!s && !*s) return (0);
    if (!(wordarr = (char **)malloc(sizeof(char *) * (countwords(s, c) + 1))))
        return (0);
    i = 0;
    cword = 0;
    while (s[i] != '\0')
    {
        while (s[i] == c && s[i]) i++;
        if (!s[i]) continue;
        start = i;
        while (s[i] != c && s[i]) i++;
        if (!(wordarr[cword++] = my_strsub(s, start, i - start)))
            return ((char **)freeallarr(&wordarr));
    }
    wordarr[cword] = 0;
    return (wordarr);
}