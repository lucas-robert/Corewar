#include <corewar2.h>

void reduce_speed()
{

	const struct timespec sleeper = {0, SLEEP_TIME};
	nanosleep(&sleeper, NULL);
}

int play(t_vm *machine)
{
	while(1)
	{
		if (machine->verbosity & VERBOSE_CYCLE)
			printf("Cycle %d / %d\n", machine->current_cycle, machine->dump_cycle);
		t_node *runner = machine->process_stack;
		while (runner)
		{
			t_node *to_process = runner;
			runner = runner->next;
			execute_process(machine, to_process->data);
		}
		if (machine->current_cycle == machine->dump_cycle)
		{
			if (!machine->gui)
				print_memory(machine);
			delete_list(&machine->process_stack);
			return 1;
		}
		if (find_winner(machine))
		{
			return 0;
		}
		if (death_checker(machine))
			return 0;

		if (machine->gui)
		{
			gui_legend(machine);
			reduce_speed();
		}
		machine->current_cycle += 1;
	}
}
