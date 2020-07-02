#include <corewar2.h>

void delete_vm(t_vm *machine)
{
	// sleep(10);

	if (machine->gui)
	{
		delwin(machine->gui->core_w);
		delwin(machine->gui->legend_w);
		endwin();
		free(machine->gui);
	}
	machine = NULL;
	return;
}
