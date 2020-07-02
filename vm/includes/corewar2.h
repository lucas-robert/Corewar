#ifndef _COREWAR_H_
# define _COREWAR_H_

#include <ncurses.h>
#include <my_lib.h>
#include <time.h>


# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN "\x1b[1;36m"
# define RESET "\x1b[0m"

# define MEM_SIZE                (4 * 1024)
# define IDX_MOD                 512
# define MAX_ARGS_NUMBER         4
# define MAX_PLAYERS_NUMBER      4
# define PROCESS_MAX_SIZE        (MEM_SIZE / 6)

# define COMMENT_CHAR            '#'
# define LABEL_CHAR              ':'
# define DIRECT_CHAR             '%'
# define SEPARATOR_CHAR          ','

# define LABEL_CHARS             "abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING         ".name"
# define COMMENT_CMD_STRING      ".comment"

/*
** regs
*/
# define REG_NUMBER              16

/*
**
*/
typedef unsigned char                    args_type_t;

# define T_REG                   1 << 0
# define T_DIR                   1 << 1
# define T_IND                   1 << 2
# define T_LAB                   1 << 3

typedef struct  cw_s
{
   char                         *mnemonique;
   char                         num_args;
   args_type_t                  type[MAX_ARGS_NUMBER];
   char                         code;
   int                          num_cycles;
   char                         *comment;
}cw_t ;

typedef struct op_s     op_t;

/*
** sizes
*/
# define IND_SIZE                1 << 1
# define REG_SIZE                1 << 2
# define DIR_SIZE                REG_SIZE

# define REGISTER				 1
# define ADDRESS				 2
# define NUMBER 				 4

/*
 * Encoding
 */
# define REG_CODE          1
# define DIR_CODE          2
# define IND_CODE          3

# define CYCLE_TO_DIE    1536
# define CYCLE_DELTA     50
# define NBR_LIVE        21
# define MAX_CHECKS      10

/*
** cw_tab
*/
// extern  cw_t    cw_tab[];

/*
** header
*/
# define PROG_NAME_LENGTH        128
# define COMMENT_LENGTH          2048
# define EXEC_MAGIC_LEN			 4
# define COREWAR_EXEC_MAGIC      0xea83f3
# define NULL_SEPARATOR_SIZE     4

extern const cw_t cw_tab[18];


typedef struct s_coords
{
	int y;
	int x;
} t_coords;

typedef struct header_s
{
   int  magic;
   char prog_name[PROG_NAME_LENGTH + 1];
   int  prog_size;
   char comment[COMMENT_LENGTH + 1];
} header_t;

typedef enum e_error
{
	NO_INPUT_FILE,
	TOO_MUCH_CHAMPIONS,
	NO_SUCH_CHAMPION,
	WRONG_N_NUMBER,
	ERR_ARG,
	SAME_N_NUMBER,
	NEGATIVE_DUMP_CYCLE,
	TOO_BIG_N_NUMBER,
	WRONG_MAGIC,
	WRONG_VERBOSE,
	TOO_LONG_CODE
} ERRORS;

typedef struct s_champion{
	int id;
	char *filename;
	char name[PROG_NAME_LENGTH + 1];
	char comment[COMMENT_LENGTH + 1];
	int exec_code_size;
	unsigned char code[PROCESS_MAX_SIZE + 1];
	int last_live;

}t_champion;

typedef struct s_champion_array
{
	int size;
	t_champion array[MAX_PLAYERS_NUMBER];
}t_champion_array;


typedef struct s_process
{
	int champion_id;
	int id;
	int registers[REG_NUMBER + 1]; //From r1 to rREG_NUMBER, leave the r0 unuse
	int carry;
	int pc;
	int last_live;
	int cycle_till_exec;
	int next_op;
} t_process;

/*
** live
*/

# define BYTES_PER_LINE  64
# define STARTING_CHAMPION_NUMBER 1

typedef struct s_gui
{
	t_coords core_c;
	WINDOW *core_w;
	t_coords legend_c;
	WINDOW *legend_w;
	t_coords header_c;
	WINDOW *header_w;
} t_gui;

typedef struct s_vm {
	int verbosity;
	int dump_cycle;
	int current_cycle;
	int cycle_to_die;
	int last_check;
	int nb_check;
	int nb_alive;
	unsigned char battlefield[MEM_SIZE + 1];
	t_champion *last_alive;
	t_champion_array champions;
	t_node *process_stack;
	int has_gui;
	t_gui *gui;
} t_vm;


//Verbose modes
# define VERBOSE_LIVE 1
# define VERBOSE_CYCLE 2
# define VERBOSE_OP 4

/*
**  Parser
*/

// validate_args.c
int parse_champions(t_vm *machine, char **av);

//options.c
int handle_option(char **av, t_vm *machine, int *index, int *next_n);

/*
**  Initializer
*/

// champ_init.c
void init_champs_id(t_champion_array *champions);
int read_champions(t_champion_array *champions);

// machine_init.c
void place_champions(t_vm *machine);
void init_vm(t_vm *machine);
t_champion *set_last_alive(t_vm *machine);

/*
**  CPU
*/

//death_checker.c
int find_winner(t_vm *machine);
int death_checker(t_vm *machine);

//game_helpers.c
t_champion *get_champion_by_process(t_vm *machine, t_process *process);
void print_champions_last_live(t_vm *machine);
void print_list(t_node **head);

// game.c
int play(t_vm *machine);

//process_execution.c
int is_op_valid(int c);
void execute_process(t_vm *machine, t_process *current_process);
void set_next_op(t_vm *machine, t_process *process);


// memory_reader.c
# define MODULO 1
# define NO_MODULO 0

int read_bytes(int size, unsigned char *battlefield, int pc);
int get_byte_value(t_vm *machine, t_process *process, int *index, args_type_t type, char modulo);
int get_reg_number(t_vm *machine, t_process *process, int *index, args_type_t type);

/*
**  Errors
*/
// errors.c
int my_error(ERRORS err_code, char *str);
void delete_vm(t_vm *machine);

/*
**  GUI
*/
# define ADDRESS_INDICATOR 10
# define MIN_ROW 210
# define MIN_LINE 70
# define CORE_SIZE (BYTES_PER_LINE * 3) + ADDRESS_INDICATOR + 2
# define HEADER_SIZE 8
# define SLEEP_TIME 10000000000 //nanoseconds

// print_memory.c
void print_memory(t_vm *machine);

// results.c
void print_results(t_vm *machine);

// ncurses_init.c
void init_gui(t_vm *machine);
void init_ncurses_battlefield(t_vm *machine);
void ncurses_place_champion(t_vm *machine, int position, int id);

// ncurses_helpers.c
void get_position(int pc, t_coords *location);
int get_op_size(t_vm *machine, int pc);
int get_dir_size(int opcode);
int has_acb(int opcode);

//ncurses_update_core.c
void update_storage_gui(t_vm *machine, int address, int champion_id);
void update_core_gui(t_vm *machine, int pc, int champion_id);
void unset_core_gui(t_vm *machine, int pc, int champion_id);
void unset_core_gui_continue(t_vm *machine, int pc, int champion_id);
void gui_unseter(t_vm *machine, t_process *process);

//ncurses_legend.c
void gui_legend(t_vm *machine);

/*
**  Operations
*/

#define CONTINUE -2 //Increment the pc without operating anything

void my_live(t_vm *machine, t_process *process, const cw_t *operation);
void my_ld(t_vm *machine, t_process *process, const cw_t *operation);
void my_st(t_vm *machine, t_process *process, const cw_t *operation);
void my_add(t_vm *machine, t_process *process, const cw_t *operation);
void my_sub(t_vm *machine, t_process *process, const cw_t *operation);
void my_and(t_vm *machine, t_process *process, const cw_t *operation);
void my_or(t_vm *machine, t_process *process, const cw_t *operation);
void my_xor(t_vm *machine, t_process *process, const cw_t *operation);
void my_zjmp(t_vm *machine, t_process *process, const cw_t *operation);
void my_ldi(t_vm *machine, t_process *process, const cw_t *operation);
void my_sti(t_vm *machine, t_process *process, const cw_t *operation);
void my_fork(t_vm *machine, t_process *process, const cw_t *operation);
void my_lld(t_vm *machine, t_process *process, const cw_t *operation);
void my_lldi(t_vm *machine, t_process *process, const cw_t *operation);
void my_lfork(t_vm *machine, t_process *process, const cw_t *operation);
void my_aff(t_vm *machine, t_process *process, const cw_t *operation);

//Operations helpers
int is_acb_valid(args_type_t acb, args_type_t op);
int is_register(args_type_t type);
int is_direct(args_type_t type);
int is_indirect(args_type_t type);
t_process *copy_process(t_vm *machine, t_process *root, int address);
void operation_failed(t_process *process);
void debug(int pc, unsigned char *battlefield);
void copy_bytes(t_vm *machine, int address, int storage);
int ring(int pc);
#endif
