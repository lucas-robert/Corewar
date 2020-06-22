#include <corewar2.h>

int my_error(ERRORS err_code)
{
	if (err_code == NO_INPUT_FILE)
	{
		my_printf("USAGE: ./corewar [-dump nbr_cycles][[-n number] champion1.cor] \n");
	}
	else if (err_code == ERR_ARG)
	{
		my_printf("Error parsing arguments");
	}
	else if (err_code == TOO_MUCH_CHAMPIONS)
	{
		my_printf("Error! Max %d champions are allowed\n", MAX_PLAYERS_NUMBER);
	}
	else if (err_code == NO_SUCH_CHAMPION)
	{
		my_printf("Error opening champion file\n");
	}
	else if (err_code == TOO_BIG_N_NUMBER)
	{
		my_printf("N number must be in range {0..%d} and can't exceed the number of players\n", MAX_PLAYERS_NUMBER);
	}
	else if (err_code == SAME_N_NUMBER)
	{
		my_printf("N number must be unique\n");
	}
	else if (err_code == NEGATIVE_DUMP_CYCLE)
	{
		my_printf("Dump cycle cannot be negative\n");
	}
	else if (err_code == WRONG_N_NUMBER)
	{
		my_printf("N number must be in range {0..%d} and can't exceed the number of players\n", MAX_PLAYERS_NUMBER);
	}
	else if (err_code == WRONG_MAGIC)
	{
		my_printf("invalid header\n");
	}
	else
		my_printf("Undefined error\n");

	return 1;
}
