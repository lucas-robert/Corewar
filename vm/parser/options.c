#include <corewar2.h>

int get_next_n(char **av, int *index)
{
	if (av[*index + 1])
	{
		(*index)++;
		return (my_atoi(av[*index]));
	}
	else
	{
		return -1;
	}
}

int get_dump_cycle(char **av, int *index)
{
	if (av[*index + 1])
	{
		(*index)++;
		return (my_atoi(av[*index]));
	}
	else
	{
		return -1;
	}

}

int get_verbosity(char **av, int *index)
{
	if (av[*index + 1])
	{
		(*index)++;
		return (my_atoi(av[*index]));
	}
	else
	{
		return -1;
	}
}

int handle_option(char **av, t_vm *machine, int *index, int *next_n)
{
	if (my_strcmp(av[*index], "-dump") == 0 || my_strcmp(av[*index], "-d") == 0)
	{
		machine->dump_cycle = get_dump_cycle(av, index);
		if (machine->dump_cycle < 0)
		{
			return (my_error(NEGATIVE_DUMP_CYCLE, NULL));
		}
	}
	else if (my_strcmp(av[*index], "-n") == 0)
	{
		*next_n = get_next_n(av, index);
		if (*next_n < 0 || *next_n > MAX_PLAYERS_NUMBER)
		{
			return my_error(WRONG_N_NUMBER, NULL);
		}
	}
	else if (my_strcmp(av[*index], "-v") == 0)
	{
		if (!machine->gui)
		{
			machine->verbosity = get_verbosity(av, index);
		}
		if (machine->verbosity < 0)
		{
			return my_error(WRONG_VERBOSE, NULL);
		}
	}
	else if (my_strcmp(av[*index], "-g") == 0)
	{
		init_gui(machine);
		machine->verbosity = 0;
	}
	else
	{
		return (my_error(ERR_ARG, av[*index]));
	}
	return EXIT_SUCCESS;
}
