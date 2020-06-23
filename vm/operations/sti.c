#include <corewar2.h>

void my_sti(t_vm *machine, t_process *process, const cw_t *operation)
{
	int arg[operation->num_args];
	unsigned char type;
	int index = 0;
	char acb = machine->battlefield[(process->pc + index) % MEM_SIZE];
	index += 1;
	for (int i = 0; i < operation->num_args; i++)
	{
		type = (acb >> (2 * (4 - i)) & 3);
		if ((type & operation->type[i]) != type)
		{
			printf("Invalid acb \n");
			process->cycle_till_exec = -1;
			return ;
		}
		if (i == 0)
		{
			arg[i] = get_reg_number(machine, process, &index, type);
		}
		else
		{
			arg[i] = get_byte_value(machine, process, &index, type, MODULO);
		}
	}

	machine->battlefield[((arg[1] + arg[2]) % IDX_MOD) % MEM_SIZE] = process->registers[arg[0]];
	process->pc = (process->pc + index) % MEM_SIZE;
	printf("Process %d: sti operation\n", process->id);
}
