#include <corewar2.h>

void my_sti(t_vm *machine, t_process *process, const cw_t *operation)
{
	// T_DIR SIZE = 2;
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
			printf("Invalid acb \n");
			process->cycle_till_exec = -1;
			return ;
		}
		if (i == 0)
		{
			arg[i] = get_reg_number(machine, process, &index, type);
			printf("%d \n" ,arg[i]);
		}
		else if (is_direct(type))
		{
			arg[i] = read_bytes(2, machine->battlefield, process->pc + index);
			index += 2;
		}
		else
		{
			arg[i] = get_byte_value(machine, process, &index, type, MODULO);
		}
	}
	printf("reg %d => %d   + %d  \n",arg[0], arg[1], arg[2]);
	machine->battlefield[((arg[1] + arg[2]) % IDX_MOD) % MEM_SIZE] = process->registers[arg[0]];
	process->pc = (process->pc + index) % MEM_SIZE;
	printf("Process %d: sti operation\n", process->id);
}
