#include <corewar1.h>

void delete_base_struct(t_base *base)
{
    if (base)
    {
        for (int i = 0; i < base->lines; i++)
        {
            if (base->code[i])
            {
                free(base->code[i]);
            }
        }
        if (base->code)
        {
            free(base->code);
        }

        if (base->instructions)
        {
            for (int i = 0; i < base->instructions_len + 1; i++)
            {
                free(base->instructions[i].arguments);
            }
            free(base->instructions);
        }

        if (base->stream)
        {
            for (int i = 0; i < base->stream->i; i++)
            {
                free(base->stream->tokens[i].value);
            }
            free(base->stream->tokens);
            free(base->stream);
        }
    }

    return;
}