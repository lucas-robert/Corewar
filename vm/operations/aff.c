#include <corewar2.h>

void my_aff(t_vm *machine, t_process *process, const cw_t *operation)
{
	printf("Aff operation\n");
	(void)operation;
	int reg = read_bytes(T_REG, machine->battlefield, process->pc);
	process->pc = (process->pc + (T_REG)) % MEM_SIZE;
	printf("Process %d says: \"%c\"\n",process->id, (reg % 256));
	return ;
}
