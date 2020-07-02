#include <corewar2.h>

int find_winner(t_vm *machine)
{
	if(machine->process_stack == NULL)
	{
		return 1;
	}

	int nb_process = 0;
	t_node *tmp = machine->process_stack;
	while (tmp)
	{
		nb_process++;
		tmp = tmp->next;
	}
	return (nb_process > 1 ? 0 : 1);
}

void check_alive_processes(t_vm *machine)
{
	t_node *check = machine->process_stack;

	while (check)
	{

		if (((t_process*)check->data)->last_live > machine->current_cycle - machine->cycle_to_die)
		{
			check = check->next;
		}
		else
		{
			t_node *tmp = check;
			check = check->next;
			delete_node(&machine->process_stack, tmp->data);
		}
	}

	machine->last_check = machine->current_cycle;
	if (machine->nb_alive >= NBR_LIVE || machine->nb_check >= MAX_CHECKS)
	{
		machine->cycle_to_die -= CYCLE_DELTA;
		machine->nb_check = 0;
	}
	else
	{
		machine->nb_check += 1;
	}
	machine->nb_alive = 0;
//	print_champions_last_live(machine);

}

int death_checker(t_vm *machine)
{
	if ((machine->current_cycle && (machine->current_cycle == machine->last_check + machine->cycle_to_die)) || machine->cycle_to_die < 0)
	{

		check_alive_processes(machine);
		if (find_winner(machine))
		{
			return 1;
		}
	}
	return 0;
}
