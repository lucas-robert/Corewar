#include <corewar2.h>

void my_or(t_vm *machine, t_process *process, const cw_t *operation)
{
	//T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG
	int arg[operation->num_args];
	unsigned char type;
	int index = 0;
	unsigned char acb = machine->battlefield[(process->pc + index) % MEM_SIZE];
	index += 1;
	for (int i = 0; i < operation->num_args; i++)
	{
		type = (acb >> (2 * (3 - i)) & 3);
		if (!is_acb_valid(type, operation->type[i]))
		{
			return (operation_failed(process));
		}
		arg[i] = get_reg_number(machine, process, &index, type);
		if (arg[i] > REG_NUMBER)
		{
			return (operation_failed(process));
		}
	}

	process->carry = (process->registers[arg[2]] = 0 ? 1 : 0);
	process->registers[arg[2]] = process->registers[arg[0]] | process->registers[arg[1]];
	process->pc = (process->pc + index) % MEM_SIZE;
	printf("Process %d: or operation\n", process->id);
}
