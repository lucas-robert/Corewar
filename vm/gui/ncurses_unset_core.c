#include <corewar2.h>

void unset_pc(t_vm *machine, int pc)
{
	t_coords location;
	chtype byte;

	get_position(ring(pc), &location);
	byte = mvwinch(machine->gui->core_w, location.y, location.x);
	mvwchgat(machine->gui->core_w, location.y, location.x, 3, 0, PAIR_NUMBER(byte & A_COLOR), NULL);
}

// Reset gui at last position
void unset_core_gui(t_vm *machine, int pc, int champion_id)
{
	t_coords location;
	int size = get_op_size(machine, ring(pc));
	chtype byte;
	unset_pc(machine, pc);
	pc++;

	wattron(machine->gui->core_w, COLOR_PAIR((champion_id)));
	for (int i = 0; i < size; i++)
	{
		get_position(ring(pc), &location);
		for (int y = 0; y < 3; y++)
		{
			byte = mvwinch(machine->gui->core_w, location.y, location.x);
			if (((byte & A_COLOR) == COLOR_PAIR(champion_id * 10 + 1)))
			{
				mvwaddch(machine->gui->core_w, location.y, location.x, byte & A_CHARTEXT);
			}
			location.x++;
		}
		pc++;
	}
	wattroff(machine->gui->core_w, COLOR_PAIR((champion_id)));
}

void gui_unseter(t_vm *machine, t_process *process)
{
	if (machine->gui)
	{
		if (process->next_op == CONTINUE)
		{
			unset_pc(machine, ring(process->pc - 1));
		}
		else if (is_op_valid(process->next_op))
		{
			unset_core_gui(machine, process->pc, process->champion_id);
		}

		wrefresh(machine->gui->core_w);
	}
	return;
}
