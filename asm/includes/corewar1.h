/*
**
*/
#ifndef _COREWAR_H_
#define _COREWAR_H_

#define MEM_SIZE (6 * 1024)  // size of vm
#define IDX_MOD 512          // used to % to prevent big step
#define MAX_ARGS_NUMBER 4    // max players

#define COMMENT_CHAR '#'    // comment
#define LABEL_CHAR ':'      // label
#define DIRECT_CHAR '%'     // direct
#define SEPARATOR_CHAR ','  // separate

#define LABEL_CHARS "abcdefghijklmnopqrstuvwxyz_0123456789"

#define NAME_CMD_STRING ".name"
#define COMMENT_CMD_STRING ".comment"

/*
** regs
*/
#define REG_NUMBER 16  // r1 - r16 0x01 - 0x0f

/*
**
*/
typedef char args_type_t;

// arguments coding byte
#define T_REG 1 << 0  // 01
#define T_DIR 1 << 1  // 10
#define T_IND 1 << 2  // 11
#define T_LAB 1 << 3

typedef struct cw_s
{
    char *mnemonique;
    char num_args;
    args_type_t type[MAX_ARGS_NUMBER];
    char code;
    int num_cycles;
    char *comment;
} cw_t;

typedef struct op_s op_t;

/*
** size
*/
#define IND_SIZE 1 << 1    // 2
#define REG_SIZE 1 << 2    // 4
#define DIR_SIZE REG_SIZE  // 4 or 2

/*
** cw_tab
*/
// extern  cw_t    cw_tab[];

/*
** header
*/
#define PROG_NAME_LENGTH 128
#define COMMENT_LENGTH 2048
#define COREWAR_EXEC_MAGIC 0xea83f3

struct header_s
{
    int magic;
    char prog_name[PROG_NAME_LENGTH + 1];
    int prog_size;
    char comment[COMMENT_LENGTH + 1];
};

typedef struct header_s header_t;

/*
** live
*/
#define CYCLE_TO_DIE 1536
#define CYCLE_DELTA 5
#define NBR_LIVE 40

#include <my_lib.h>

typedef enum PARSE_ERRORS
{
    UNDEFINED_TOKEN,
    TOO_MUCH_ARGUMENTS,
    DOUBLE_LABEL,
    DOUBLE_INST,
    NOT_ENOUGH_ARGUMENTS,
} PARSE_ERRORS;

typedef enum ERRORS
{
    OPEN_ERROR,
    VALIDATION_FAILED,
    METADATA_DOES_NOT_EXIST,
    NAME_DOES_NOT_EXIST,
    COMMENT_DOES_NOT_EXIST,
    COMMENT_SIZE_ERROR,
    NAME_SIZE_ERROR,
    EMPTY_FILE,
    NO_FILE
} ERRORS;

// used by clear function
typedef enum BASE_FREE
{
    ALL,
    ONLY_FILE,
    FILE_AND_TOKENS,
} BASE_FREE;

// used for tokenizer
typedef enum TOKEN
{
    UNDEFINED,  // default

    NAME_TAG,              // NAME_CMD_STRING ex: .name
    NAME,                  // PROG_NAME_LENGTH ex: "name"
    CHAMPION_COMMENT_TAG,  // COMMENT_CMD_STRING ex: .comment
    CHAMPION_COMMENT,      // "comment" COMMENT_LENGTH

    LABEL,  // [LABEL_CHARS]LABEL_CHAR ex: hello:

    INSTRUCTION,  // one of 16 instruction

    REGISTER,  // one of REG_NUMBER, starts with r1

    INDIRECT_LABEL,  // (label, register, int)
    NUMBER,

    DIRECT_LABEL,  // DIRECT_CHAR value (label, register, int)
    DIRECT_NUMBER,

    DIRECT_REGISTER,
    SEPARATOR,  // SEPARATOR_CHAR ,
    COMMENT     // COMMENT #sdsd\n
} TOKEN;

typedef struct s_token
{
    TOKEN type;
    char *value;
    int line;
} t_token;

typedef enum
{
    false = 0,
    true = !false
} BOOL;

typedef enum
{
    ZERO_ARGUMENTS,
    ONE_ARGUMENT,
    TWO_ARGUMENTS,
    THREE_ARGUMENTS
} ARGUMENTS_LEN;

typedef union arg
{
    int integer;
    unsigned char byte[4];
} argument_value;

typedef struct s_argument
{
    BOOL set;
    TOKEN type;
    char name[256];
    argument_value value;
    int label;
} t_argument;

typedef struct s_label
{
    char name[256];
    argument_value address;
} t_label;

typedef struct s_instruction
{
    BOOL label_exist;
    BOOL operation_exist;
    int arguments_number;
    int line_number;
    int op_code;
    int arg_iterator;
    unsigned char acb;
    t_label label;
    t_argument *arguments;

} t_instruction;

typedef struct s_tokens_stream
{
    t_token *tokens;
    int i;
} t_tokens_stream;

typedef struct s_base
{
    // whole file to read
    char **code;
    int lines;
    t_instruction *instructions;
    cw_t cw_tab[18];
    int EOM_number;
    int instructions_len;
    t_tokens_stream *stream;
    int instructions_cap;
} t_base;

void my_error(ERRORS err, t_base *base);

void validate_filename(char *s1);
char *prepare_line(char *s);
void read_file(char *filename, t_base *base);

void find_metadata(t_base *base, header_t *metadata);
void parse_tokens(t_base *base);
void my_parse_error(PARSE_ERRORS err, int line, t_base *base);

args_type_t *get_types_by_name(char *op, t_base *base);
int get_code_by_name(char *op, t_base *base);
int get_args_by_name(char *op, t_base *base);
void tokenize(t_base *base);
void set_null_token(t_tokens_stream *stream, int *curr_line);

void preprocess(t_base *base);
void compile(t_base *base, char *filename, header_t *metadata);
int is_ind(TOKEN t);
int is_reg(TOKEN t);
int is_dir(TOKEN t);
int has_acb(int code);
int arg_validation_dispatcher(int c, TOKEN t, int arg_nb);
char get_acb(TOKEN t);
int is_number(TOKEN t);
int t_dir_size(int code);

void delete_base_struct(t_base *base);

void write_metadata(header_t *, int);

int search_comment(char *line, t_base *base, int *curr_line);
void _scan_argument(t_tokens_stream *stream, char *line, int *curr_line);
void _scan_comment(t_tokens_stream *stream, char *line, int *curr_line);
int string_match_labels_char(char *s, int max);

#endif
