#include <corewar2.h>

void my_and(t_vm *machine, t_process *process, const cw_t *operation)
{
	//T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG
	int index = 0;
	int arg[3];
	char acb = machine->battlefield[process->pc + index];
	index += 1;
	args_type_t type = acb << 6;
	for (int i = 0; i < 3; i++)
	{
		arg[i] = get_byte_value(machine, process, &index, type);
		type = type >> 2;
	}
	process->registers[arg[2]] = arg[0] & arg[1];
	process->pc += index;
	printf("Process %d: And operation\n", process->id);
}
