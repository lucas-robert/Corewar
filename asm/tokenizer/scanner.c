#include <corewar1.h>

// will return if will find register number till del
int matches_register(char *s)
{
    int i = 0;
    int found = 0;

    if (!s || !*s)
    {
        return 0;
    }
    while (s[i] != '\0' && s[i] != ' ' && s[i] != SEPARATOR_CHAR &&
           s[i] != '\t')
    {
        int z = my_atoi(&s[i]);
        if (z >= 1 && z <= REG_NUMBER && found == 0)
            found = 1;
        else
            found = 2;
        i++;
    }
    return found == 1 ? 1 : 0;
}

void _scan_comment(t_tokens_stream *stream, char *line, int *curr_line)
{
    stream->tokens[stream->i].value = my_strdup(line);
    stream->tokens[stream->i].type = COMMENT;
    stream->tokens[stream->i].line = *curr_line + 1;
    stream->i++;
}

void _scan_register(t_tokens_stream *stream, char *line, int direct,
                    int *curr_line)
{
    int q = 1;
    int i = 0;

    if (!line || !*line) return;
    stream->tokens[stream->i].value = (char *)malloc(sizeof(char) * 3 + 1);
    stream->tokens[stream->i].line = *curr_line + 1;
    if (direct == 1)
        stream->tokens[stream->i].type = DIRECT_REGISTER;
    else
        stream->tokens[stream->i].type = REGISTER;
    stream->tokens[stream->i].value[0] = 'r';
    while (line[i] >= 49 && line[i] <= 57)
    {
        stream->tokens[stream->i].value[q] = line[i];
        i++;
        q++;
    }
    stream->tokens[stream->i].value[q] = '\0';
    stream->i++;
}

int matches_label_name(char s)
{
    for (int i = 0; i < my_strlen(LABEL_CHARS); i++)
    {
        if (LABEL_CHARS[i] == s)
        {
            return 1;
        }
    }
    return 0;
}

void _scan_indirect(t_tokens_stream *stream, char *line, int direct,
                    int *curr_line)
{
    if (!line || !*line) return;

    int i = 0;
    int z = 0;
    stream->tokens[stream->i].value = (char *)malloc(sizeof(char) * 256 + 1);
    stream->tokens[stream->i].line = *curr_line + 1;
    if (direct == 1)
        stream->tokens[stream->i].type = DIRECT_LABEL;
    else
        stream->tokens[stream->i].type = INDIRECT_LABEL;
    while ((line[i] != '\0' && line[i] != SEPARATOR_CHAR))
    {
        if (!matches_label_name(line[i]))
        {
            set_null_token(stream, curr_line);
            return;
        }
        else if (z < 256)
        {
            stream->tokens[stream->i].value[z] = line[i];
            z++;
        }
        else
        {
            my_printf("Error, increased value len\n");
            return;
        }
        i++;
    }
    stream->tokens[stream->i].value[z] = '\0';
    stream->i++;
}

void _scan_number(t_tokens_stream *stream, char *line, int direct,
                  int *curr_line)
{
    if (!line || !*line) return;

    int i = 0;
    int neg = 0;
    stream->tokens[stream->i].value = (char *)malloc(sizeof(char) * 256 + 1);
    stream->tokens[stream->i].line = *curr_line + 1;
    if (direct == 1)
        stream->tokens[stream->i].type = DIRECT_NUMBER;
    else
        stream->tokens[stream->i].type = NUMBER;
    int z = 0;
    while (line[i] != '\0' && !isspace(line[i]) && line[i] != SEPARATOR_CHAR)
    {
        if (line[i] == '-' && !neg)
        {
            stream->tokens[stream->i].value[z] = line[i];
            z++;
            neg++;
        }
        else if (isnum(line[i]))
        {
            stream->tokens[stream->i].value[z] = line[i];
            z++;
        }
        else if (z >= 255)
        {
            my_printf("Error, increased value len");
            return;
        }
        else
        {
            set_null_token(stream, curr_line);
            return;
        }
        i++;
    }
    stream->tokens[stream->i].value[z] = '\0';
    stream->i++;
}

void _scan_direct(t_tokens_stream *stream, char *line, int *curr_line)
{
    int i = 0;

    if (!line && !*line) return;
    if (line[i] == LABEL_CHAR)
        _scan_indirect(stream, &line[i + 1], 1, curr_line);
    else if (line[i] == 'r' && matches_register(&line[i + 1]))
        _scan_register(stream, &line[i + 1], 1, curr_line);
    else
        _scan_number(stream, &line[i], 1, curr_line);
}

// will parse %value %:label :label, r[1-16], value
void _scan_argument(t_tokens_stream *stream, char *line, int *curr_line)
{
    if (!line || !*line) return;  // error empty param

    int i = 0;

    while (isspace(line[i]) || line[i] == SEPARATOR_CHAR)
    {
        i++;
    }
    // till next separator
    while (line[i] && !isspace(line[i]) && line[i] != SEPARATOR_CHAR)
    {
        if (line[i] == DIRECT_CHAR || line[i] == LABEL_CHAR || line[i] == 'r' ||
            (isnum(line[i]) || line[i] == '-'))
        {
            if (line[i] == DIRECT_CHAR)
                _scan_direct(stream, &line[i + 1], curr_line);
            else if (line[i] == LABEL_CHAR)
                _scan_indirect(stream, &line[i + 1], 0, curr_line);
            else if (line[i] == 'r')
                _scan_register(stream, &line[i + 1], 0, curr_line);
            else if (isnum(line[i]) || line[i] == '-')
                _scan_number(stream, &line[i], 0, curr_line);
            break;
        }
        else
        {
            return;
        }
        i++;
    }
}

// will parse label
void _scan_label(t_tokens_stream *stream, char *line, int max, int *curr_line)
{
    stream->tokens[stream->i].value = (char *)malloc(sizeof(char) * 256);
    stream->tokens[stream->i].type = LABEL;
    stream->tokens[stream->i].line = *curr_line + 1;
    int z = 0;
    for (int i = 0; i < max; i++)
    {
        if (matches_label_name(line[i]))
        {
            stream->tokens[stream->i].value[z] = line[i];
            z++;
        }
        else
        {
            set_null_token(stream, curr_line);
            return;
        }
    }
    stream->tokens[stream->i].value[z] = '\0';
    stream->i++;
}

int string_match_labels_char(char *s, int max)
{
    for (int i = 0; i < max; i++)
    {
        if (!matches_label_name(s[i]))
        {
            return (0);
        }
    }
    return (1);
}
