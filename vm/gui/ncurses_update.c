#include <corewar2.h>

// Reset gui at last position
void unset_core_gui(t_vm *machine, int pc, int champion_id)
{
	t_coords location;
	int size = get_op_size(machine, ring(pc));
	chtype byte;
	attron(COLOR_PAIR((champion_id)));
	for (int i = 0; i < size + 1; i++)
	{
		get_position(ring(pc), &location);
		for (int y = 0; y < 3; y++)
		{
			byte = mvinch(location.y, location.x);
			if (((byte & A_COLOR) == COLOR_PAIR(champion_id * 10)) || ((byte & A_COLOR) == COLOR_PAIR(champion_id * 10 + 1)))
			{
				mvaddch(location.y, location.x, byte & A_CHARTEXT);
			}
			location.x++;
		}
		pc++;
	}
	attroff(COLOR_PAIR((champion_id)));
	// refresh();
}

void unset_core_gui_continue(t_vm *machine, int pc, int champion_id)
{
	//Don't set the attribute
	t_coords location;
	int size = get_op_size(machine, ring(pc));
	chtype byte;

	attron(A_NORMAL);
	for (int i = 0; i < size + 1; i++)
	{
		get_position(ring(pc), &location);
		for (int y = 0; y < 3; y++)
		{
			byte = mvinch(location.y, location.x);
			if (((byte & A_COLOR) == COLOR_PAIR(champion_id * 10)) || ((byte & A_COLOR) == COLOR_PAIR(champion_id * 10 + 1)))
			{
				mvaddch(location.y, location.x, byte & A_CHARTEXT);
			}
			location.x++;
		}
		pc++;
	}
	attroff(A_NORMAL);
	// refresh();
}

void update_core_gui(t_vm *machine, int pc, int champion_id)
{
	t_coords location;
	char byte[4];
	int size = get_op_size(machine, pc);

	// Print pc
	attron(COLOR_PAIR(champion_id * 10));
	sprintf(byte, "%.2x ", machine->battlefield[pc]);
	get_position(pc, &location);
	// mvwaddstr(machine->core, location.y, location.x, byte);
	mvaddstr(location.y, location.x, byte);
	attroff(COLOR_PAIR((champion_id * 10)));
	pc++;

	//print next code to exec;
	attron(COLOR_PAIR(champion_id * 10 + 1));
	for (int i = 0; i < size; i++)
	{
		get_position(ring(pc), &location);
		sprintf(byte, "%.2x ", machine->battlefield[ring(pc)]);
		// mvwaddstr(machine->core, location.y, location.x, byte);
		mvaddstr(location.y, location.x, byte);
		pc++;
	}
	attroff(COLOR_PAIR(champion_id * 10 + 1));
	// wrefresh(machine->core);
	refresh();
}

void handle_gui(t_vm *machine, t_process *process)
{
	if (machine->gui)
	{
		if (process->next_op == CONTINUE)
		{
			unset_core_gui_continue(machine, ring(process->pc - 1), process->champion_id);
		}
		else
		{
			unset_core_gui(machine, process->pc, process->champion_id);
		}
	}
	return;
}
