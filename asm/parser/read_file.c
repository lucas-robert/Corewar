#include <corewar1.h>

int get_number_of_lines(int fd)
{
    int nb_lines = 0;
    char *str = NULL;

    while ((str = my_readline(fd)))
    {
        free(str);
        nb_lines += 1;
    }

    lseek(fd, 0, SEEK_SET);
    return nb_lines;
}

// will validate file for *.s on fail exits
void validate_filename(char *s1)
{
    int len = my_strlen(s1);
    if (len <= 2 || my_strcmp(&s1[len - 2], ".s") != 0)
        my_error(VALIDATION_FAILED, NULL);
}

void strip_extra_spaces(char *str)
{
    int i, x;
    for (i = x = 0; str[i]; ++i)
        if (!isspace(str[i]) || (i > 0 && !isspace(str[i - 1])))
            str[x++] = str[i];
    str[x] = '\0';
}

// trims line
char *prepare_line(char *s)
{
    char *new;

    if (!s || !*s)
    {
        return s;
    }

    new = NULL;
    new = my_strip(s);
    strip_extra_spaces(new);
    // my_printf("%s\n", new);
    free(s);

    return new;
}

// will read file on fail clear t_base->file
void read_file(char *filename, t_base *base)
{
    char *s = NULL;
    int i = 0;
    int number_of_lines = 0;

    int fd = open(filename, O_RDONLY);

    if (fd < 0)
    {
        my_error(OPEN_ERROR, base);
    }

    number_of_lines = get_number_of_lines(fd);

    base->code = (char **)malloc(sizeof(char *) * number_of_lines);
    while ((s = my_readline(fd)) != NULL)
    {
        base->code[i] = prepare_line(s);
		// printf("Line %i : [%s]\n", i, base->code[i]);
        base->lines++;
        s = NULL;
        i++;
    }
}
