#include <corewar2.h>

t_champion* get_champion_by_id(t_vm *machine, int champion_id)
{
	int i = 0;
	while (i < machine->champions->size)
	{
		if (machine->champions->array[i].id == -champion_id)
		{
			return &machine->champions->array[i];
		}
		else
			i++;
	}
	return NULL;
}

void my_live(t_vm *machine, t_process *process, const cw_t *operation)
{
	// printf("Live operation\n");

	(void)operation;
	int champion_number = read_bytes(4, machine->battlefield, ring(process->pc + 1));
	process->last_live = machine->current_cycle;
	// printf("Champion number of live op %d\n", champion_number);
	t_champion *last_alive = get_champion_by_id(machine, champion_number);
	if (last_alive)
	{
		machine->last_alive = last_alive;
		machine->last_alive->last_live = machine->current_cycle;
		if (machine->verbosity == 1)
			printf("Player %d (%s) has been reported alive!\n", machine->last_alive->id, machine->last_alive->name);
	}


	process->pc = ring(process->pc + (4) + 1);
	machine->nb_alive += 1;
	if (machine->verbosity == 4)
		printf("Process %d | %s %d\n", process->id, operation->mnemonique, champion_number);
}
