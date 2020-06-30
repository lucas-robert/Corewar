#include <corewar1.h>

void create_instruction(t_base *base, int i)
{
    base->instructions[i].label_exist = false;
    base->instructions[i].operation_exist = false;
    base->instructions[i].arguments_number = 0;
    base->instructions[i].line_number = 0;
    base->instructions[i].op_code = 0;
    base->instructions[i].arg_iterator = 0;
    base->instructions[i].acb = 0;
    base->instructions[i].arguments = NULL;
    base->instructions[i].label.address.integer = 0;
}

int is_argument(TOKEN type)
{
    if (type == REGISTER || type == DIRECT_LABEL || type == DIRECT_REGISTER ||
        type == DIRECT_NUMBER || type == INDIRECT_LABEL || type == NUMBER ||
        type == REGISTER)
        return (1);
    return (0);
}

int not_enough_arguments(t_instruction *ins)
{
    int res = 0;
    if (ins->arguments)
    {
        for (int i = 0; i < ins->arguments_number; i++)
        {
            if (ins->arguments[i].set == true)
            {
                res++;
            }
        }
    }
    if (res != ins->arguments_number)
    {
        return (1);
    }
    return (0);
}

t_argument *init_arg_array()
{
    t_argument *argument_array = malloc(sizeof(t_argument) * 3);
    for (int i = 0; i < 3; i++)
    {
        argument_array[i].type = UNDEFINED;
        argument_array[i].value.integer = 0;
        argument_array[i].label = 0;
        argument_array[i].set = false;
    }
    return argument_array;
}

void increase_capacity(t_base *base)
{
    base->instructions_cap *= 2;
    base->instructions = (t_instruction *)realloc(
        base->instructions, sizeof(t_instruction) * base->instructions_cap);
}

// it should start reading each token and validate it by adding it to instrution
// array it uses c_tab structure as protocol label live? add to instruction
// arguments number on errror it throw it and clears all data

void parse_argument(t_base *base, t_token *token)
{
    base->instructions[base->instructions_len].arg_iterator++;

    int index = base->instructions[base->instructions_len].arg_iterator;

    if (index > base->instructions[base->instructions_len].arguments_number)
    {
        my_parse_error(TOO_MUCH_ARGUMENTS, token->line, base);
    }

    int arg_len = base->instructions[base->instructions_len].arguments_number;

    if (base->instructions[base->instructions_len].arguments == NULL)
    {
        base->instructions[base->instructions_len].arguments = init_arg_array();
    }

    my_strcpy(base->instructions[base->instructions_len]
                  .arguments[arg_len - index]
                  .name,
              token->value);
    base->instructions[base->instructions_len].arguments[arg_len - index].type =
        token->type;
    base->instructions[base->instructions_len].arguments[arg_len - index].set =
        true;
}

void parse_instruction(t_base *base, t_token *token)
{
    if (base->instructions[base->instructions_len].operation_exist == true)
    {
        // operation already exist
        my_parse_error(DOUBLE_INST, token->line, base);
    }

    base->instructions[base->instructions_len].operation_exist = true;
    base->instructions[base->instructions_len].op_code =
        get_code_by_name(token->value, base);
    base->instructions[base->instructions_len].arguments_number =
        get_args_by_name(token->value, base);
}

void parse_label(t_base *base, t_token *token)
{
    if (base->instructions[base->instructions_len].label_exist == true)
    {
        // parse error
        my_parse_error(DOUBLE_LABEL, token->line, base);
    }

    base->instructions[base->instructions_len].label_exist = true;
    my_strcpy(base->instructions[base->instructions_len].label.name,
              token->value);
}

void init_instruction(t_base *base, t_token *token, int *current_line_index)
{
    if (*current_line_index != token->line)
    {
        if (base->instructions_len != -1 &&
            not_enough_arguments(&base->instructions[base->instructions_len]))
        {
			// printf("Error parsing ")
            my_parse_error(NOT_ENOUGH_ARGUMENTS, *current_line_index, base);
        }
        *current_line_index = token->line;
        if (base->instructions_len == -1 ||
            base->instructions[base->instructions_len].operation_exist == true)
        {
            base->instructions_len++;
            if (base->instructions_len >= base->instructions_cap)
            {
                increase_capacity(base);
            }
            create_instruction(base, base->instructions_len);
        }
    }
}

void parse_tokens(t_base *base)
{
    int current_line_index;
    base->instructions =
        (t_instruction *)malloc(sizeof(t_instruction) * base->instructions_cap);

    current_line_index = -1;

    for (int i = 0; i < base->stream->i; i++)
    {
        t_token token = base->stream->tokens[i];
        init_instruction(base, &token, &current_line_index);

        if (token.type == UNDEFINED)
        {
            my_parse_error(UNDEFINED_TOKEN, token.line, base);
        }
        else if (token.type == LABEL)
        {
            parse_label(base, &token);
        }
        else if (token.type == INSTRUCTION)
        {
            parse_instruction(base, &token);
        }
        else if (is_argument(token.type))
        {
            parse_argument(base, &token);
        }
    }
}
