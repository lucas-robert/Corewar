#include <corewar2.h>

void gui_legend(t_vm *machine)
{
	int len;

	wattron(machine->gui->legend_w, A_UNDERLINE);
	len = snprintf(NULL, 0 , "Current cycle: %d\n", machine->current_cycle);
	char cycle[len + 1];
	sprintf(cycle, "Current cycle: %d\n", machine->current_cycle);
	mvwaddstr(machine->gui->legend_w, 10, 2, cycle);

	len = snprintf(NULL, 0 , "Cycle to die: %d\n", machine->cycle_to_die);
	char cycletd[len + 1];
	sprintf(cycletd, "Cycle to die: %d\n", machine->cycle_to_die);
	mvwaddstr(machine->gui->legend_w, 12, 2, cycletd);

	wattroff(machine->gui->legend_w, A_UNDERLINE);

	for (int i = 0; i < machine->champions.size; i++)
	{
		wattron(machine->gui->legend_w, COLOR_PAIR(i + 1));
		len = snprintf(NULL, 0, "Player %d\n", machine->champions.array[i].id);
		char player_id[len + 1];
		sprintf(player_id, "Player %d\n", machine->champions.array[i].id);
		mvwaddstr(machine->gui->legend_w, (i + 1) * 14, 2, player_id);
		wattroff(machine->gui->legend_w, COLOR_PAIR(i + 1));

		len = snprintf(NULL, 0, "%s\n", machine->champions.array[i].name);
		char player_name[len + 1];
		sprintf(player_name, "%s\n", machine->champions.array[i].name);
		mvwaddstr(machine->gui->legend_w, (i + 1) * 14 + 1, 2, player_name);

		len = snprintf(NULL, 0, "Last live :%d\n", machine->champions.array[i].last_live);
		char last_live[len + 1];
		sprintf(last_live, "Last live :%d\n", machine->champions.array[i].last_live);
		mvwaddstr(machine->gui->legend_w, (i + 1) * 14 + 2, 2, last_live);
	}
	wrefresh(machine->gui->legend_w);
}
