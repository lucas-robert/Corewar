#include <corewar2.h>

int my_error(ERRORS err_code, char *str)
{
	if (err_code == NO_INPUT_FILE)
	{
		fprintf(stderr,"USAGE: ./corewar [-dump nbr_cycles][-v verbosity [1 || 2 || 4]][[-n number] champion1.cor] \n");
	}
	else if (err_code == ERR_ARG)
	{
		fprintf(stderr,"Error parsing argument %s\n", str);
	}
	else if (err_code == TOO_MUCH_CHAMPIONS)
	{
		fprintf(stderr,"Error! Max %d champions are allowed\n", MAX_PLAYERS_NUMBER);
	}
	else if (err_code == NO_SUCH_CHAMPION)
	{
		fprintf(stderr,"Error opening champion file %s\n", str);
	}
	else if (err_code == TOO_BIG_N_NUMBER)
	{
		fprintf(stderr,"N number must be in range {1..%d} and can't exceed the number of players inputed\n", MAX_PLAYERS_NUMBER);
	}
	else if (err_code == SAME_N_NUMBER)
	{
		fprintf(stderr,"N number must be unique\n");
	}
	else if (err_code == NEGATIVE_DUMP_CYCLE)
	{
		fprintf(stderr,"Dump cycle cannot be negative\n");
	}
	else if (err_code == WRONG_N_NUMBER)
	{
		fprintf(stderr,"N number must be in range {1..%d} and can't exceed the number of players inputed\n", MAX_PLAYERS_NUMBER);
	}
	else if (err_code == WRONG_MAGIC)
	{
		fprintf(stderr,"Error: %s has an unvalid header\n", str);
	}
	else if (err_code == WRONG_VERBOSE)
	{
		fprintf(stderr,"Usage: -v 1: Show lives\n-v 2 show cycles\n -v 4 show operations \n");
	}
	else if (err_code == TOO_LONG_CODE)
	{
		fprintf(stderr,"Error: %s has an invalid code (too long). Max code size is %d\n", str, PROCESS_MAX_SIZE);
	}
	else
	{
		fprintf(stderr,"Undefined error\n");
	}
		
	return 1;
}
