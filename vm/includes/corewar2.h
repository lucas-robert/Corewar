#ifndef _COREWAR_H_
# define _COREWAR_H_

#include <my_lib.h>

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
typedef char                    args_type_t;

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

/*
 * Encoding
 */
# define REG_CODE          1
# define DIR_CODE          2
# define IND_CODE          3

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

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"


extern const cw_t cw_tab[18];

typedef struct header_s
{
   int  magic;
   char prog_name[PROG_NAME_LENGTH + 1];
   int  prog_size;
   char comment[COMMENT_LENGTH + 1];
} header_t;

# define HEX_BASE 16
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
	WRONG_MAGIC
} ERRORS;

typedef struct s_champion{
	int id;
	char *filename;
	const char *color;
	char name[PROG_NAME_LENGTH + 1];
	char comment[COMMENT_LENGTH + 1];
	int exec_code_size;
	char code[PROCESS_MAX_SIZE + 1];

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
	int registers[REG_NUMBER];
	int carry;
	int pc;
	int last_live;
	int cycle_till_exec;
	int next_op;
} t_process;

/*
** live
*/
# define CYCLE_TO_DIE    1536
# define CYCLE_DELTA     50
# define NBR_LIVE        40
# define MAX_CHECKS      10
# define BYTES_PER_LINE  16
# define PRINT_STEP      512

typedef struct s_vm {
	int dump_cycle;
	int current_cycle;
	int cycle_to_die;
	int cycle_delta;
	int nb_check;
	char battlefield[MEM_SIZE + 1];
	t_champion *last_alive;
	t_champion_array *champions;
	t_node *process_stack;

} t_vm;


int my_error(ERRORS err_code);
void init_vm(t_vm *machine, t_champion_array *champions, int dump_cycle);
void print_memory(char *battlefield);
int parse_champions(t_champion_array *champions, int ac, char **av);
void play(t_vm *machine);
void print_results(t_vm *machine);
int get_byte_value(t_vm *machine, t_process *process, int *index, args_type_t type);

// Operations

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

#endif
