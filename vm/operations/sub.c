#include <corewar2.h>

void my_sub(t_vm *machine, t_process *process, const cw_t *operation)
{
	int reg[operation->num_args];
	unsigned char type;
	int index = 1;
	unsigned char acb  = machine->battlefield[ring(process->pc + index)];
	index += 1;

	for (int i = 0; i < operation->num_args; i++)
	{
		type = (acb >> (2 * (3 - i)) & 3);
		if (i == 2)
		{
			reg[i] = get_reg_number(machine, process, &index, type);
			if (reg[i] > REG_NUMBER)
			{
				return (operation_failed(process));
			}
		}
		else
		{
			reg[i] = get_byte_value(machine, process, &index, type, MODULO);
		}

	};
	process->registers[reg[2]] = reg[0] - reg[1];
	process->pc = (ring(process->pc + index));
	process->carry = (process->registers[reg[2]] ? 0 : 1);

	if (machine->verbosity & VERBOSE_OP)
	{
		printf("Process %d | %s %d %d r%d\n", process->id, operation->mnemonique, reg[0], reg[1], reg[2]);
	}
}
