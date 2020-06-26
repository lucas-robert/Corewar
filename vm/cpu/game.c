#include <corewar2.h>

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
			printf("Cycle to die: %d\n", machine->cycle_to_die);
			print_list(&machine->process_stack);
			print_memory(machine, 1);
			delete_list(&machine->process_stack);
			return 1;
		}
		if (find_winner(machine))
		{
			printf("Found a winner!\n");
			print_memory(machine, 0);
			return 0;
		}

		if (death_checker(machine))
			return 0;
		machine->current_cycle += 1;
	}
}
