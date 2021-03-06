#include <corewar2.h>

void my_st(t_vm *machine, t_process *process, const cw_t *operation)
{
	//T_REG, T_REG | T_IND
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
			arg[i] = get_reg_number(machine, process, &index, type);
			if (arg[i] > REG_NUMBER)
			{
				return (operation_failed(process));
			}
		}
		else if (i == 1 && is_register(type))
		{
			arg[i] = get_reg_number(machine, process, &index, type);
			if (arg[1] > REG_NUMBER)
			{
				return (operation_failed(process));
			}
			process->registers[arg[1]] = process->registers[arg[0]];
			if (machine->verbosity & VERBOSE_OP)
			{
				printf("Process %d | %s r%d %d\n", process->id, operation->mnemonique, arg[0], arg[1]);
			}
		}
		else if (i == 1 && !is_register(type))
		{
			int address = read_bytes(ADDRESS, machine->battlefield, ring(process->pc + index));
			arg[i] = ring(process->pc + (address % IDX_MOD));
			copy_bytes(machine, arg[1], process->registers[arg[0]]);
			index += ADDRESS;
			if (machine->verbosity & VERBOSE_OP)
			{
				printf("Process %d | %s r%d %d\n", process->id, operation->mnemonique, arg[0], address);
			}
			if (machine->gui)
			{
				update_storage_gui(machine, arg[i], process->champion_id);
			}
		}
	}
	process->pc = ring(process->pc + index);

}
