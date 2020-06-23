#include <corewar2.h>

void my_ld(t_vm *machine, t_process *process, const cw_t *operation)
{
	int arg[operation->num_args];
	unsigned char type;
	int index = 0;
	char acb = machine->battlefield[(process->pc + index) % MEM_SIZE];
	index += 1;
	for (int i = 0; i < operation->num_args; i++)
	{
		type = (acb >> (2 * (3 - i)) & 3);
		if (!is_acb_valid(type, operation->type[i]))
		{
			return (operation_failed(process));
		}
		if (is_register(type))
		{
			arg[i] = get_reg_number(machine, process, &index, type);
			if (arg[i] > REG_NUMBER)
			{
				return (operation_failed(process));
			}
		}
		else
		{
			arg[i] = get_byte_value(machine, process, &index, type, MODULO);
		}
	}

	process->registers[arg[1]] = arg[0];
	process->carry = (arg[operation->num_args -1] = 0 ? 1 : 0);
	process->pc = (process->pc + index) % MEM_SIZE;
	printf("Process %d: ld operation\n", process->id);
}
