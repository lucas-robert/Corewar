NAME = lib.a

SRC_PRINTF =	./my_printf/my_printf.c \
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

INCLUDES = -I ./includes

OBJECT_PRINTF = $(SRC_PRINTF:.c=.o)

all: $(NAME)

$(NAME) : $(OBJECT_PRINTF)
		ar rc $(NAME) $(OBJECT_PRINTF)
		ranlib $(NAME)
%.o: %.c
		gcc -g -o $@ -c $< $(INCLUDES)
clean:
		rm -f $(OBJECT_PRINTF)

fclean: clean
		rm -f $(NAME)
re:		fclean all

tags:
		rm -f TAGS
		etags -e -R *.c *.h
