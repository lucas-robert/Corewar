#ifndef MY_LIB_H
#define MY_LIB_H

#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define READLINE_READ_SIZE 512

typedef struct s_readline_node
{
    int fd;
    char *current_line;
    struct s_readline_node *next;
} t_readline_node;

char re_val(long long num);
int my_strlen(char *s);
int is_flag(char c);
int parse_flag(char *fmt, char *flag);
int format(char *flag, va_list args);
int my_printf(char *format, ...);
char *lltob(char *res, int base, long long inputNum);
void strev(char *str);
char *my_strdup(char *src);
int my_strcmp(const char *s1, const char *s2);
char *my_strcat(char *dest, const char *app);
int my_strncmp(const char *s1, const char *s2, int n);
void my_path_cat(char *buff, char *s1, char *s2);
char *my_strcpy(char *dest, const char *src);
char *itoa(int nb);
void my_bzero(char *s, int n);
int my_strlen(char *str);
char *my_strchr(char *s, int c);
char *my_strtok(char *str, char sep);
char *concat(char *s1, char *s2);
char *my_readline(int fd);
int my_atoi(char *a);
void my_strdel(char **as);
char **my_strsplit(char const *s, char c);
char *my_strsub(char const *s, unsigned int start, size_t len);
char *my_strip(char *a);
char *lltob(char *res, int base, long long inputNum);
char *my_strncpy(char *, char *, int);
int isspace(int a);
int isnum(char a);
char *my_strndup(char *a, int n);

#endif