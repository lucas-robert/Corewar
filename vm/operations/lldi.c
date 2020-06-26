#include <corewar2.h>

void my_lldi(t_vm *machine, t_process *process, const cw_t *operation)
{
	int arg[operation->num_args];
	unsigned char type;
	int index = 1;
	unsigned char acb  = machine->battlefield[ring(process->pc + index)];
	index += 1;
	for (int i = 0; i < operation->num_args; i++)
	{
		type = (acb >> (2 * (3 - i)) & 3);
		if (i == 2)
		{
			arg[i] = get_reg_number(machine, process, &index, type);
			if (arg[i] > REG_NUMBER)
			{
				return (operation_failed(process));
			}
		}
		else
		{
			arg[i] = get_byte_value(machine, process, &index, type, NO_MODULO);
		}
	}

	process->registers[arg[2]] = read_bytes(sizeof(int), machine->battlefield, (arg[0] + arg[1]) % MEM_SIZE);
	process->pc = ring(process->pc + index);
	if (machine->verbosity & VERBOSE_CYCLE)
	{
		printf("Process %d | %s %d %d %d\n", process->id, operation->mnemonique, arg[0], arg[1], arg[2]);
	}
}
