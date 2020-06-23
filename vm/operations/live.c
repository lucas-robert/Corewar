#include <corewar2.h>

void my_live(t_vm *machine, t_process *process, const cw_t *operation)
{
	printf("Live operation\n");
	(void)operation;
	int champion_number = read_bytes(DIR_SIZE, machine->battlefield, process->pc) % 256;
	process->last_live = machine->current_cycle;
	printf("Champion number of live op %d\n", champion_number);
	if (champion_number < machine->champions->size)
	{
		machine->last_alive = &machine->champions->array[champion_number];
		my_printf("%s has been reported alive!\n", machine->last_alive->name);
	}
	process->pc += DIR_SIZE;

	return ;
}
