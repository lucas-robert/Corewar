#include <corewar2.h>

int parse_champions(t_vm *machine, t_champion_array *champions, char **av)
{
	int index = 1;
	int next_n = 0;
	int champion_id = 0;

	machine->dump_cycle = -1;
	machine->verbosity = 0;

	while(av[index])
	{
		if (av[index][0] == '-')
		{
			if (handle_option(av, machine, &index, &next_n) > 0)
				return EXIT_FAILURE;
		}
		else
		{
			if (champion_id > MAX_PLAYERS_NUMBER)
			{
				return (my_error(TOO_MUCH_CHAMPIONS, NULL));
			}
			champions->array[champion_id].filename = av[index];
			champions->array[champion_id].id = next_n - 1;
			next_n = 0;
			champion_id++;
		}
		index++;
	}
	champions->size = champion_id;
	if (read_champions(champions) > 0)
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}
