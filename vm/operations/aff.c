#include <corewar2.h>

void my_aff(t_vm *machine, t_process *process, const cw_t *operation)
{
	printf("Aff operation\n");
	(void)operation;
	int reg = bytes_to_int(&machine->battlefield[process->pc % MEM_SIZE], REG_SIZE);
	process->pc += 1;
	printf("Process %d says: \"%c\"\n",process->id, (reg % 256));
	return ;
}
