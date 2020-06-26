#include <corewar2.h>

void print_list(t_node **head)
{
	t_node *tmp = *head;
	int index = 0;
	while (tmp)
	{
		index++;
		printf("[%d] ->", ((t_process*)tmp->data)->id);
		tmp = tmp->next;
	}
	printf("\n");
}

void print_champions_last_live(t_vm *machine)
{
	for (int i = 0; i < machine->champions.size; i++)
	{
		printf("Champion [%s] (%d): last_alive: %d\n", machine->champions.array[i].name, machine->champions.array[i].id, machine->champions.array[i].last_live);
	}
}

t_champion *get_champion_by_process(t_vm *machine, t_process *process)
{
	if (process)
	{
		return (&machine->champions.array[process->champion_id]);
	}
	return NULL;
}
