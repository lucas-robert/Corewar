#include <corewar2.h>

void my_lld(t_vm *machine, t_process *process, const cw_t *operation)
{
	int arg[operation->num_args];
	unsigned char type;
	int index = 1;
	unsigned char acb = machine->battlefield[ring(process->pc + index)];
	index += 1;
	for (int i = 0; i < operation->num_args; i++)
	{
		type = (acb >> (2 * (3 - i)) & 3);
		if (i == 0)
		{
		arg[i] = get_byte_value(machine, process, &index, type, NO_MODULO);
		}
		else if (i == 1)
		{
			arg[i] = get_reg_number(machine, process, &index, type);
			if (arg[i] > REG_NUMBER)
			{
				return (operation_failed(process));
			}
		}
	}
	process->registers[arg[1]] = arg[0];
	process->carry = (arg[0] == 0 ? 1 : 0);
	process->pc = ring(process->pc + index);
	if (machine->verbosity & VERBOSE_OP)
	{
		printf("Process %d | %s %d r%d\n", process->id, operation->mnemonique, process->registers[arg[1]], arg[1]);
	}
}
