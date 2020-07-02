#include <corewar2.h>

int parse_champions(t_vm *machine, char **av)
{
	int index = 1;
	int next_n = 0;
	int champion_id = 0;
	init_vm(machine);
	init_champs_id(&machine->champions);

	while(av[index])
	{
		if (av[index][0] == '-')
		{
			if (handle_option(av, machine, &index, &next_n) > 0)
			{
				return EXIT_FAILURE;
			}
		}
		else
		{
			if (champion_id > MAX_PLAYERS_NUMBER)
			{
				return (my_error(TOO_MUCH_CHAMPIONS, NULL));
			}
			machine->champions.array[champion_id].filename = av[index];
			machine->champions.array[champion_id].id = next_n - 1;
			next_n = 0;
			champion_id++;
		}
		index++;
	}
	machine->champions.size = champion_id;

	if (read_champions(&machine->champions) > 0)
	{
		// delete_vm(machine);
		return EXIT_FAILURE;
	}

	place_champions(machine);
	machine->last_alive = set_last_alive(machine);
	return EXIT_SUCCESS;
}
