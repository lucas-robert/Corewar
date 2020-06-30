#include <corewar1.h>

/*
operation arg
operation arg1,arg2,arg3
operation arg1,arg2
*/

// int curr_line = 0;

void print_stream(t_base *base)
{
    for (int i = 0; i < base->stream->i; i++)
    {
        if (base->stream->tokens[i].type == UNDEFINED)
            my_printf("[UNDEFINED]");
        else if (base->stream->tokens[i].type == LABEL)
            my_printf("[LABEL]");
        else if (base->stream->tokens[i].type == INSTRUCTION)
            my_printf("[INSTRUCTION]");
        else if (base->stream->tokens[i].type == REGISTER)
            my_printf("[REGISTER]");
        else if (base->stream->tokens[i].type == DIRECT_LABEL)
            my_printf("[DIRECT_LABEL]");
        else if (base->stream->tokens[i].type == INDIRECT_LABEL)
            my_printf("[INDIRECT_LABEL]");
        else if (base->stream->tokens[i].type == DIRECT_REGISTER)
            my_printf("[DIRECT_REGISTER]");
        else if (base->stream->tokens[i].type == DIRECT_NUMBER)
            my_printf("[DIRECT_NUMBER]");
        else if (base->stream->tokens[i].type == NUMBER)
            my_printf("[NUMBER]");
        else if (base->stream->tokens[i].type == COMMENT)
            my_printf("[COMMENT]");
        my_printf("[%s][line %d]\n", base->stream->tokens[i].value,
                  base->stream->tokens[i].line);
    }
    return;
}

void add_instruction(t_base *base, char *line, int *curr_line, int *index,
                     int comment_offset)
{
	int y = 0;

	base->stream->tokens[base->stream->i].value =
        (char *)malloc(sizeof(char) * 10);
    base->stream->tokens[base->stream->i].type = INSTRUCTION;
    base->stream->tokens[base->stream->i].line = *curr_line + 1;

    while (*index < comment_offset && !isspace(line[*index]))
    {
        base->stream->tokens[base->stream->i].value[y] = line[*index];
        (*index)++;
        y++;
    }

    base->stream->tokens[base->stream->i].value[y] = '\0';
    base->stream->i++;
	// while (line[*index] && isspace(line[*index]))
	// {
	// 	(*index)++;
	// }
}

void add_label(t_base *base, char *line, int *curr_line, int index)
{
    base->stream->tokens[base->stream->i].value = my_strndup(line, index);
    base->stream->tokens[base->stream->i].type = LABEL;
    base->stream->tokens[base->stream->i].line = *curr_line + 1;
    base->stream->i++;
}

void set_null_token(t_tokens_stream *stream, int *curr_line)
{
    free(stream->tokens[stream->i].value);
    stream->tokens[stream->i].value = NULL;
    stream->tokens[stream->i].type = UNDEFINED;
    stream->tokens[stream->i].line = *curr_line + 1;
    stream->i++;
}

int search_label(t_base *base, char *line, int comment_offset, int *curr_line)
{
    int index = 0;
    while (index < comment_offset)
    {
        if (isspace(line[index]) || line[index] == SEPARATOR_CHAR)
		{
			break;
		}
        if (line[index] == LABEL_CHAR && string_match_labels_char(line, index))
        {
            // add new label
            add_label(base, line, curr_line, index);
            return index;
        }
        // todo: label:operation
        // else if (line[i] == ' ');
        index++;
    }
    return 0;
}


int search_comment(char *line, t_base *base, int *curr_line)
{
    int comment_offset = 0;
	int len = my_strlen(line);
    for (int i = 0; i < len; i++)
    {
        if (line[i] == COMMENT_CHAR)
        {
            _scan_comment(base->stream, &line[i], curr_line);
            break;
        }
        comment_offset++;
    }
    return comment_offset;
}

int is_empty(char *line)
{
    if (!line || my_strcmp(line, "\n") == 0 || my_strlen(line) == 0)
	 	return (1);
    return (0);
}
int find_operation(char *op, t_base *base)
{
    int len = 0;
    for (int i = 0; i < 18; i++)
    {
        len = my_strlen(base->cw_tab[i].mnemonique);
        // my_printf("len %d %s %s\n", len, base->cw_tab[i].mnemonique,
                  // &op[len + 1]);
        if (my_strncmp(op, base->cw_tab[i].mnemonique, len) == 0 &&
            (op[len] == ' ' || op[len] == '\t'))
            return (1);
    }
    return (0);
}

// will create list of tokens
// on fail will exit
void tokenize(t_base *base)
{
    int curr_line = base->EOM_number;
    base->stream = (t_tokens_stream *)malloc(sizeof(t_tokens_stream) * 1);
    base->stream->tokens = (t_token *)malloc(sizeof(t_token) * 1024);
    base->stream->i = 0;

    while (curr_line < base->lines)
    {
        char *line = base->code[curr_line];

        if (*line && (*line == COMMENT_CHAR || is_empty(line)))
        {
            curr_line++;
            continue;
        }

        int comment_offset = search_comment(line, base, &curr_line);

        if (comment_offset == 0)
        {
			curr_line++;
            continue;
        }

        int runner = search_label(base, line, comment_offset, &curr_line);

        while (runner < comment_offset &&
               (isspace(line[runner]) || line[runner] == LABEL_CHAR))
        {
            runner++;
        }

        if (line[runner] != '\0' && find_operation(&line[runner], base))
        {
            add_instruction(base, line, &curr_line, &runner, comment_offset);
        }
        else if (line[runner])
        {
            set_null_token(base->stream, &curr_line);
        }


        for (int i = comment_offset - 1; i >= runner; i--)
        {
            if (line[i] == SEPARATOR_CHAR || (isspace(line[i]) && i - 1 >= 0 &&
                                              line[i - 1] != SEPARATOR_CHAR))
            {
                _scan_argument(base->stream, &line[i + 1], &curr_line);
            }
        }
        curr_line++;
    }

    // print_stream(base);
    return;
}
