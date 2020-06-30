#include <corewar1.h>

int get_args_by_name(char *op, t_base *base)
{
    for (int i = 0; i < 18; i++)
    {
        if (my_strcmp(op, base->cw_tab[i].mnemonique) == 0)
        {
            return (base->cw_tab[i].num_args);
        }
    }
    return (0);
}

int get_code_by_name(char *op, t_base *base)
{
    for (int i = 0; i < 18; i++)
    {
        if (my_strcmp(op, base->cw_tab[i].mnemonique) == 0)
        {
            return (base->cw_tab[i].code);
        }
    }
    return (0);
}

args_type_t *get_types_by_name(char *op, t_base *base)
{
    for (int i = 0; i < 18; i++)
    {
        if (my_strcmp(op, base->cw_tab[i].mnemonique) == 0)
        {
            return (base->cw_tab[i].type);
        }
    }
    return NULL;
}