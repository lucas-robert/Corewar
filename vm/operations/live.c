#include <corewar2.h>

void my_live(t_vm *machine, t_process *process, const cw_t *operation)
{
	printf("Live operation\n");

	int champion_number = bytes_to_int(&machine->battlefield[((process->pc + sizeof(operation->code)) % MEM_SIZE)], sizeof(int));
	if (champion_number < machine->champions->size)
	{
		machine->last_alive = &machine->champions->array[champion_number];
		my_printf("%s has been reported alive!\n", machine->last_alive->name);
		process->last_live = machine->current_cycle;
	}

	return ;
}
