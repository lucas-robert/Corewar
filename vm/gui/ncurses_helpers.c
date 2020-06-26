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

int size_without_acb(int opcode)
{
	switch (opcode)
	{
		case 1: //live
			return 4;
		case 9: //zjmp
			return 2;
		case 12: //fork
			return 2;
		case 15: //lfork
			return 2;
		case CONTINUE: //no_operation
		case -1:
		default:
			return 1;
	}
}

int get_op_size(t_vm *machine, int pc)
{
	int res = 0; // PC + ACB
	int opcode = machine->battlefield[pc];
	if (!has_acb(opcode))
	{
		return (size_without_acb(opcode));
	}
	else
	{
		unsigned char acb = machine->battlefield[ring(pc + 1)];
		for (int i = 0; i < 3; i++)
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
	location->x = (pc % BYTES_PER_LINE) * 3 + ADDRESS_INDICATOR - 1;
	location->y = (pc / BYTES_PER_LINE);
}
