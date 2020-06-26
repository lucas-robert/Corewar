#include <corewar2.h>

// Champion 1 code
// Champion 2 code
// Champion 3 code
// Champion 4 code

// Champion 1 pc
// Champion 2 pc
// Champion 3 pc
// Champion 4 pc

// Champion 1 code_exec
// Champion 2 code_exec
// Champion 3 code_exec
// Champion 4 code_exec

void init_ncurses_battlefield(t_vm *machine)
{
	for (int line = 0; line < MEM_SIZE / BYTES_PER_LINE; line++)
	{
		char address[ADDRESS_INDICATOR];
		sprintf(address, "0x%.4x : ", line * BYTES_PER_LINE);
		addstr(address);
		for (int row = 0; row < BYTES_PER_LINE; row ++)
		{
			char bytes[3];
			sprintf(bytes, "%.2x ", machine->battlefield[line * BYTES_PER_LINE + row]);
			addstr(bytes);
		}
		addstr("\n");
	}
	refresh();
	return;
}


void init_color_pairs()
{
	//CHAMP 1
	init_pair(1, COLOR_RED, COLOR_BLACK); // CODE
	init_pair(10, COLOR_CYAN, COLOR_RED); // PC
	init_pair(11, COLOR_WHITE, COLOR_RED); // NEXT_CODE_TO_EXEC

	//CHAMP 2
	init_pair(2, COLOR_BLUE, COLOR_BLACK); // CODE
	init_pair(20, COLOR_CYAN, COLOR_BLUE); // PC
	init_pair(21, COLOR_WHITE, COLOR_BLUE); // NEXT_CODE_TO_EXEC

	//CHAMP 3
	init_pair(3, COLOR_GREEN, COLOR_BLACK); // CODE
	init_pair(30, COLOR_CYAN, COLOR_GREEN); // PC
	init_pair(31, COLOR_WHITE, COLOR_GREEN); // NEXT_CODE_TO_EXEC

	// CHAMP 4
	init_pair(4, COLOR_MAGENTA, COLOR_BLACK); // CODE
	init_pair(40, COLOR_CYAN, COLOR_MAGENTA); // PC
	init_pair(41, COLOR_WHITE, COLOR_MAGENTA); // NEXT_CODE_TO_EXEC
}

void init_gui(t_vm *machine)
{
	initscr();
	if (has_colors() == FALSE)
	{
    	endwin();
    	printf("Your terminal does not support color\n");
		return;
	}

	machine->gui = 1;
	noecho();
	box(stdscr, '|', '-');
	start_color();
	init_color_pairs();
	init_ncurses_battlefield(machine);
}

void ncurses_place_champion(unsigned char *champion_code, int pc, int champion_number)
{
	// Set attribute
	t_coords location;

	attron(COLOR_PAIR(champion_number)); // Set the code in the defined color
	for (int i = 0; champion_code[i]; i++)
	{
		get_position(pc, &location);
		char bytes[3];
		sprintf(bytes, "%.2x ", champion_code[i]);
		mvaddstr(location.y, location.x, bytes);
		pc++;
	}
	attroff(COLOR_PAIR(champion_number));
	refresh();
}
