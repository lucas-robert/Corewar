#include "../includes/gui.h"
#include <ncurses.h>


#include <stdio.h>
#include <signal.h>
#include <string.h>

//  void resizeHandler(int sig)
//  {
// 	  int nh, nw;
//
// 	  getmaxyx(stdscr, nh, nw);  /* get the new screen size */
// 	  	addstr("I am highlighted!\n");
// 	// return NULL;
// }
// void set_gui()
// {
// 	initscr();
// 	noecho();
// 	cbreak();
// 	keypad(stdscr, TRUE);
//
// 	unsigned char arena[10] = {10, 15, 255, 60, 90, 100, 7, 10, 9, 234};
//
// 	// WINDOW *window = newwin(NB_LINES, 100, 0 , 0 );
// 	int ch;
// 	nodelay(stdscr, TRUE);
// 	// int mvwprintw(WINDOW *win, int y, int x, char *fmt [, arg] ...);
// 	attron(A_STANDOUT);
// 	signal(SIGWINCH, resizeHandler);
// 	addstr("I am highlighted!\n");
// 	// mvwprintw(stdscr, 0, 0, "%.2x ", 255);
//
// 	while (1) {
// 	 if ((ch = getch()) == ERR) {
// 		 /* user hasn't responded
// 		  ...
// 		 */
// 	 }
// 	 else {
// 		 printf("%d\n", ch);
// 		 /* user has pressed a key ch
// 		  ...
// 		 */
// 	 }
// 	}
//
// 	endwin();
// }




//
// int main()
// {
// 	set_gui();
// }
// void print_memory(WINDOW* stdscr, unsigned char *arena)
// {
//
// 	for (int line = 0; line < 1000 / 50; line++)
// 	{
// 		printw(stdscr, "0x%.4x : ", line * 50);
// 		for (int row = 0; row < 50; row ++)
// 		{
// 			printw(stdscr, "%.2x ", arena[line * BYTES_PER_LINE + row]);
// 		}
// 		// printw("\n");
// 	}
// 	return;
// }
//
// int main(void)
// {
// 	initscr();
// 	unsigned char arena[1000];
// 	memset(arena, 0, 1000);
// 	// print_memory(stdscr, arena);
//
// 	addstr((const char *)arena);
// 	refresh();
// 	getch();
// 	attrset(A_BOLD | A_UNDERLINE | A_STANDOUT);
// 	// int vwprintw(WINDOW *win, const char *fmt, va_list varglist);
// 	vwprintw(stdscr, "%.2x ", 255);
// 	attroff(A_BOLD | A_UNDERLINE | A_STANDOUT);
// 	refresh();
//  	// print_memory(stdscr, arena);
//  	// getch();
//
//   	endwin();
//   	return 0;
// }

void test()
{

}

#include <ncurses.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
	int parent_x;
	int parent_y;
	int legend_size = 40;
	initscr();
	noecho();
	curs_set(FALSE);
	// get our maximum window dimensions
	// getmaxyx(stdscr, parent_y, parent_x);
	// set up initial windows
	// WINDOW *arena = newwin(parent_y, parent_x - legend_size, 0, 0);
	// WINDOW *legend = newwin(parent_y, legend_size,0,  parent_x - legend_size);
	// // draw to our windows
	// mvwprintw(arena, 0, 0, "Arena");
	// mvwprintw(legend, 0, 0, "legend");
	// box(arena, '|', '-' );
	// box(legend, '|', '-' );
	addstr("8457913284759827345982734985 Salut les copains\n");
	refresh();
	sleep(3);
	attron(A_BOLD | A_UNDERLINE | A_STANDOUT);
	char prout[100];
	sprintf(prout, "%2.x ", 155);
	mvaddstr(0, 2, prout);
	attroff(A_BOLD | A_UNDERLINE | A_STANDOUT);
	refresh();
	sleep(5);
	// // refresh each window
	// wrefresh(arena);
	// wrefresh(legend);
	// sleep(5);
	// clean up
	// delwin(arena);
	// delwin(legend);
	endwin();
	return 0;
}

// void update_ncurse(t_vm *machine, int pc, int value, int size)
// {
// 	char update[size * 2];
//
//
//
// }
