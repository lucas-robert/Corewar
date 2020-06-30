#include <corewar1.h>

char get_acb(TOKEN t)
{
    if (t == DIRECT_LABEL || t == DIRECT_NUMBER)
    {
        return 0b10;
    }
    if (t == INDIRECT_LABEL || t == NUMBER)
    {
        return 0b11;
    }
    if (t == REGISTER)
    {
        return 0b01;
    }
    return (0b0);
}

int is_dir(TOKEN t)
{
    if (t == DIRECT_LABEL || t == DIRECT_REGISTER || t == DIRECT_NUMBER)
    {
        return (1);
    }
    return (0);
}

int is_ind(TOKEN t)
{
    if (t == INDIRECT_LABEL || t == NUMBER)
    {
        return (1);
    }
    return (0);
}

int is_reg(TOKEN t)
{
    if (t == REGISTER)
    {
        return (1);
    }
    return (0);
}

int has_acb(int code)
{
    if (code == 1 || code == 9 || code == 12 || code == 15)
    {
        return (0);
    }
    return (1);
}

int is_number(TOKEN t)
{
    if (t == NUMBER || t == DIRECT_NUMBER)
    {
        return (1);
    }
    return (0);
}

// T_REG = 01
// T_DIR = 10
// T_IND = 11
int type_value(TOKEN t)
{
    if (t == REGISTER)
    {
        return (1);
    }
    if (t == DIRECT_LABEL || t == DIRECT_NUMBER)
    {
        return (2);
    }
    if (t == INDIRECT_LABEL || t == NUMBER)
    {
        return (3);
    }
    return (0);
}

int t_dir_size(int code)
{
    if (code == 9 || code == 10 || code == 11 || code == 12 || code == 14 ||
        code == 15)
    {
        return (2);
    }

    return (4);
}
// 11 01 00 00
// 10 01 00 00
// 11 01 00 00

// 11 01 00 00 |
// 10 01 00 00 &
// 01 00 00 00 ^
//

// T_REG = 01 1
// T_DIR = 10 2
// T_IND = 11 3
#define REG 1
#define DIR 2
#define IND 3

int validate_argument1(int c, TOKEN t)
{
    if ((c == 1 && !is_dir(t)) || (c == 2 && !is_dir(t) && !is_ind(t)) ||
        (c == 3 && !is_reg(t)) || (c == 4 && !is_reg(t)) ||
        (c == 5 && !is_reg(t)) ||
        (c == 6 && !is_reg(t) && !is_dir(t) && !is_ind(t)) ||
        (c == 7 && !is_reg(t) && !is_dir(t) && !is_ind(t)) ||
        (c == 8 && !is_reg(t) && !is_dir(t) && !is_ind(t)) ||
        (c == 9 && !is_dir(t)) ||
        (c == 10 && !is_reg(t) && !is_dir(t) && !is_ind(t)) ||
        (c == 11 && !is_reg(t)) || (c == 12 && !is_dir(t)) ||
        (c == 13 && !is_dir(t) && !is_ind(t)) ||
        (c == 14 && !is_reg(t) && !is_dir(t) && !is_ind(t)) ||
        (c == 15 && !is_dir(t)) || (c == 16 && !is_reg(t)))
    {
        return (0);
    }
    return (1);
}

int validate_argument2(int c, TOKEN t)
{
    if ((c == 2 && !is_reg(t)) || (c == 3 && !is_reg(t) && !is_ind(t)) ||
        (c == 4 && !is_reg(t)) || (c == 5 && !is_reg(t)) ||
        (c == 6 && !is_reg(t) && !is_dir(t) && !is_ind(t)) ||
        (c == 7 && !is_reg(t) && !is_dir(t) && !is_ind(t)) ||
        (c == 8 && !is_reg(t) && !is_dir(t) && !is_ind(t)) ||
        (c == 10 && !is_reg(t) && !is_dir(t)) ||
        (c == 11 && !is_reg(t) && !is_dir(t) && !is_ind(t)) ||
        (c == 13 && !is_reg(t)) || (c == 14 && !is_reg(t) && !is_dir(t)))

    {
        return (0);
    }
    return (1);
}

int validate_argument3(int c, TOKEN t)
{
    if ((c == 4 && !is_reg(t)) || (c == 5 && !is_reg(t)) ||
        (c == 6 && !is_reg(t)) || (c == 7 && !is_reg(t)) ||
        (c == 8 && !is_reg(t)) || (c == 10 && !is_reg(t)) ||
        (c == 11 && !is_reg(t) && !is_dir(t)) || (c == 14 && !is_reg(t)))
    {
        return (0);
    }
    return (1);
}

int arg_validation_dispatcher(int c, TOKEN t, int arg_nb)
{
    if (arg_nb == 0)
    {
        return validate_argument1(c, t);
    }
    else if (arg_nb == 1)
    {
        return validate_argument2(c, t);
    }

    else
    {
        return validate_argument3(c, t);
    }
}

// will return 1 if acb is valid
// it should accept
// int is_valid_acb(int code, char acb, cw_t cw)
// {
//     if (code == 1 && (acb ^ (DIR << 6)) == 0)
//         return (1);
//     if (code == 2 &&
//         (acb &))

// }
