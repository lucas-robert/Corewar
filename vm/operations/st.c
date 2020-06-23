#include <corewar2.h>

void my_st(t_vm *machine, t_process *process, const cw_t *operation)
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
			process->cycle_till_exec = -1;
			return ;
			printf("Invalid acb for player %s\n", (get_champion_by_id(machine, process))->name);
		}
		if (i == 0)
		{
			arg[i] = get_reg_number(machine, process, &index, type);
		}
		if (i == 1 && is_register(type))
		{
			arg[i] = get_reg_number(machine, process, &index, type);
			process->registers[arg[1]] = process->registers[arg[0]];
		}
		else if (i == 1 && is_indirect(type))
		{
			arg[i] = read_bytes(T_IND, machine->battlefield, process->pc);
			arg[1] = (process->pc + (arg[i] % IDX_MOD)) % MEM_SIZE;
			machine->battlefield[arg[1]] = arg[0];
			index += T_IND;
		}
	}
	process->pc = (process->pc + index) % MEM_SIZE;
	printf("Process %d: st operation\n", process->id);
}
