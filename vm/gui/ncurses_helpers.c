#include <corewar2.h>

int has_acb(int opcode)
{
    if (opcode == 1 || opcode == 9 || opcode == 12 || opcode == 15 || opcode == CONTINUE || opcode == -1)
    {
        return 0;
    }
    return 1;
}

int get_dir_size(int opcode)
{
    if (opcode == 9 || opcode == 10 || opcode == 11 || opcode == 12 || opcode == 14 ||
        opcode == 15)
    {
        return 2;
    }
    return 4;
}

int get_op_size(t_vm *machine, int pc, int opcode)
{
	int res = 1;
	if (!has_acb(opcode))
	{
		return 1;
	}
	else
	{
		unsigned char acb = machine->battlefield[pc];
		for (int i = 0; i < cw_tab[opcode].num_args; i++)
		{
			unsigned char type = (acb >> (2 * (3 - i)) & 3);
			if (type == REG_CODE)
			{
				res += REGISTER;
			}
			else if (type == IND_CODE)
			{
				res += ADDRESS;
			}
			else if (type == DIR_CODE)
			{
				res += get_dir_size(opcode);
			}
		}
	}
	return res;
}

void get_position(int pc, t_coords *location)
{
	location->y = (pc / BYTES_PER_LINE) + ADDRESS_INDICATOR;
	location->x = pc % BYTES_PER_LINE;
}
