#include <corewar2.h>

void my_add(t_vm *machine, t_process *process, const cw_t *operation)
{
	printf("process %d: Add operation\n", process->id);
	int reg[3];
	char acb;
	int index = 0;
	acb = machine->battlefield[process->pc % MEM_SIZE];
	index += 1;
	for (int i = 0; i < 3; i++)
	{
		reg[i] = (machine->battlefield[(process->pc + index) % MEM_SIZE]);
		index += 1;
	};
	process->registers[reg[2]] = process->registers[reg[0]] + process->registers[reg[1]];
	process->pc = (process->pc + index % MEM_SIZE);
	process->carry = 0;

}
