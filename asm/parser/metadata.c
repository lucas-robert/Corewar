#include <corewar1.h>

// will add name from " to "
void set_name(char *line, header_t *metadata, t_base *base)
{
    int i;
	my_memset(metadata->prog_name, 0, PROG_NAME_LENGTH);

    i = 0;
    while (*line && *line != '"')
    {
        line++;
    }
    if (*line == 0)
    {
        my_error(NAME_DOES_NOT_EXIST, base);
    }
    line++;
    while (*line && *line != '"' && i < PROG_NAME_LENGTH)
    {
        metadata->prog_name[i] = *line;
        line++;
        i++;
    }
    metadata->prog_name[i] = '\0';
    if (*line == 0)
    {
        my_error(NAME_DOES_NOT_EXIST, base);
    }
    if (i == PROG_NAME_LENGTH)
    {
        my_error(NAME_SIZE_ERROR, base);
    }
}

// will add comment from " to "
void set_comment(char *line, header_t *metadata, t_base *base)
{
    int i;
	my_memset(metadata->comment, 0, COMMENT_LENGTH);

    i = 0;
    while (*line && *line != '"')
    {
        line++;
    }
    if (*line == 0)
    {
        my_error(COMMENT_DOES_NOT_EXIST, base);
    }
    line++;
    while (*line && *line != '"' && i < COMMENT_LENGTH)
    {
        metadata->comment[i] = *line;
        line++;
        i++;
    }
    metadata->comment[i] = '\0';
    if (*line == 0)
    {
        my_error(COMMENT_DOES_NOT_EXIST, base);
    }
    if (i == COMMENT_LENGTH)
    {
        my_error(COMMENT_SIZE_ERROR, base);
    }
}

// checks only first lines till not find .name
// or .comment, skips # or  \n
void find_metadata(t_base *base, header_t *metadata)
{
    char *line;
    int name_found;
    int comment_found;

    name_found = 0;
    comment_found = 0;
    line = NULL;
    if (base->lines == 0) my_error(EMPTY_FILE, base);
    for (int i = 0; i < base->lines; i++)
    {
        line = base->code[i];
        if (line[0] != 0 && (line[0] == COMMENT_CHAR || line[0] == '\n'))
            continue;
        else if (my_strncmp(line, COMMENT_CMD_STRING,
                            my_strlen(COMMENT_CMD_STRING)) == 0 &&
                 !comment_found)
        {
            set_comment(line, metadata, base);
            comment_found = 1;
        }
        else if (my_strncmp(line, NAME_CMD_STRING,
                            my_strlen(NAME_CMD_STRING)) == 0 &&
                 !name_found)
        {
            set_name(line, metadata, base);
            name_found = 1;
        }
        else if (!name_found || !comment_found)
        {
            if (!name_found && !comment_found)
                my_error(METADATA_DOES_NOT_EXIST, base);
            else if (!name_found)
                my_error(NAME_DOES_NOT_EXIST, base);
            else
                my_error(COMMENT_DOES_NOT_EXIST, base);
        }
        else
        {
            base->EOM_number = i;
            return;
        }
    }
}
