NAME = lib.a

SRC_LIB =	./my_printf/my_printf.c \
			./structs/linked_list.c \
			./structs/stack.c \
			./lib/my_strdup.c \
			./lib/my_strcmp.c \
			./lib/my_strcat.c \
			./lib/my_strncmp.c \
			./lib/my_path_cat.c \
			./lib/my_strcpy.c \
			./lib/itoa.c \
			./lib/my_strlen.c \
			./lib/my_bzero.c \
			./lib/my_strchr.c \
			./lib/my_strtok.c \
			./lib/concat.c \
			./lib/my_readline.c \
			./lib/my_atoi.c \
			./lib/my_strdel.c \
			./lib/my_strsplit.c \
			./lib/my_strsub.c \
			./lib/my_strip.c \
			./lib/my_strncpy.c \
			./lib/isnum.c \
			./lib/isspace.c \
			./lib/my_strndup.c \
			./lib/my_n_atoi.c \
			./lib/my_hex_to_dec.c \
			./lib/bytes_to_int.c \
			./lib/my_abs.c \
			./lib/my_memcmp.c \
			./lib/my_memcpy.c \
			./lib/my_memmove.c \
			./lib/my_memset.c \
			./lib/my_memdel.c \


INCLUDES = -I ./includes

OBJECT_LIB = $(SRC_LIB:.c=.o)

all: $(NAME)

$(NAME) : $(OBJECT_LIB)
		ar rc $(NAME) $(OBJECT_LIB)
		ranlib $(NAME)
%.o: %.c
		gcc -g -o $@ -c $< $(INCLUDES)
clean:
		rm -f $(OBJECT_LIB)

fclean: clean
		rm -f $(NAME)
re:		fclean all
