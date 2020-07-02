#include <corewar2.h>

// Reset gui at last position
static const int STORAGE_SIZE = 12; //(2 char + space) * 4 bytes

void update_storage_gui(t_vm *machine, int address, int champion_id)
{

	t_coords location;
	char byte[4];

	//Set stored value in color
	wattron(machine->gui->core_w, COLOR_PAIR(champion_id));
	for (int i = 0; i < STORAGE_SIZE; i++)
	{
		get_position(ring(address), &location);
		sprintf(byte, "%.2x ", machine->battlefield[ring(address)]);
		mvwaddstr(machine->gui->core_w, location.y, location.x, byte);
		address++;
	}
	wattron(machine->gui->core_w, COLOR_PAIR(champion_id * 10));
	wrefresh(machine->gui->core_w);
}

void unset_core_gui(t_vm *machine, int pc, int champion_id)
{
	t_coords location;
	int size = get_op_size(machine, ring(pc));
	chtype byte;

	if (machine->battlefield[pc] != 0)
		wattron(machine->gui->core_w, COLOR_PAIR((champion_id)));
	for (int i = 0; i < size + 1; i++)
	{
		get_position(ring(pc), &location);
		for (int y = 0; y < 3; y++)
		{
			byte = mvwinch(machine->gui->core_w, location.y, location.x);
			if (((byte & A_COLOR) == COLOR_PAIR(champion_id * 10)) || ((byte & A_COLOR) == COLOR_PAIR(champion_id * 10 + 1)))
			{
				mvwaddch(machine->gui->core_w, location.y, location.x, byte & A_CHARTEXT);
			}
			location.x++;
		}
		pc++;
	}

	wattroff(machine->gui->core_w, COLOR_PAIR((champion_id)));
}

//Don't set the attribute
void unset_pc(t_vm *machine, int pc, int champion_id)
{
	t_coords location;
	// int size = get_op_size(machine, ring(pc));
	chtype byte;
	(void)machine;
	(void) champion_id;
	// wattron(machine->gui->core_w,A_NORMAL);
	// for (int i = 0; i < size + 2; i++)
	// {
	get_position(ring(pc), &location);
	for (int y = 0; y < 3; y++)
	{
		byte = mvinch(location.y, location.x);
		if (((byte & A_ATTRIBUTES) == A_STANDOUT))
		{
			mvwaddch(machine->gui->core_w, location.y, location.x, byte & A_CHARTEXT);
		}
		location.x++;
	}
		// pc++;
	// }
	// wattroff(machine->gui->core_w, A_NORMAL);
}

void update_core_gui(t_vm *machine, int pc, int champion_id)
{
	t_coords location;
	char byte[4];
	int size = get_op_size(machine, pc);

	// Print pc
	// wattron(machine->gui->core_w, COLOR_PAIR(champion_id * 10));
	// sprintf(byte, "%.2x ", machine->battlefield[pc]);
	get_position(pc, &location);
 	mvwchgat(machine->gui->core_w, location.y, location.x, 3, A_STANDOUT, 0, NULL);
	// mvwaddstr(machine->gui->core_w, location.y, location.x, byte);
	// wattroff(machine->gui->core_w, COLOR_PAIR((champion_id * 10)));
	pc++;

	//print next code to exec;
	wattron(machine->gui->core_w, COLOR_PAIR(champion_id * 10 + 1));
	for (int i = 0; i < size; i++)
	{
		get_position(ring(pc), &location);
		sprintf(byte, "%.2x ", machine->battlefield[ring(pc)]);
		mvwaddstr(machine->gui->core_w, location.y, location.x, byte);
		pc++;
	}
	wattron(machine->gui->core_w, COLOR_PAIR(champion_id * 10 + 1));
	wrefresh(machine->gui->core_w);
}

void gui_unseter(t_vm *machine, t_process *process)
{
	if (machine->gui)
	{
		if (process->next_op == CONTINUE)
		{
			debug(process->pc - 1, machine->battlefield);
			unset_pc(machine, ring(process->pc - 1), process->champion_id);
		}
		else
		{
			unset_core_gui(machine, process->pc, process->champion_id);
		}
	}
	return;
}
