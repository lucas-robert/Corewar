#include <corewar2.h>

void print_results(t_vm *machine)
{
	printf("Constestant %d %s won the match after %d cycles!",machine->last_alive->id + 1, machine->last_alive->name, machine->current_cycle);
	// (void)machine;
	// printf("Results printing");
	return ;
}
