NAME = corewar

SRC =	main.c \
		errors.c \
		validate_args.c \
		init.c \
		print_memory.c \
		results.c \
		game.c \
		op.c \
		operations/add.c \
		operations/aff.c \
		operations/and.c \
		operations/fork.c \
		operations/ld.c \
		operations/ldi.c \
		operations/lfork.c \
		operations/live.c \
		operations/lld.c \
		operations/lldi.c \
		operations/or.c \
		operations/st.c \
		operations/sti.c \
		operations/sub.c \
		operations/xor.c \
		operations/zjmp.c \
		operations/op_helpers.c \
		memory_reader.c \


OBJECT_MY_VM = $(SRC:.c=.o)
INCLUDES_MY_VM = -I ./includes/
INCLUDES_LIB = -I ./src/includes
LIB = ./src/lib.a
SANITIZE = -g3 -fsanitize=address -Wall -Wextra -Werror
CLAFGS = -Wall -Wextra -Werror


all: $(NAME)

$(NAME) : $(OBJECT_MY_VM)
	make -C ./src
	@echo "\033[0;32m[LIB COMPILED]\033[0;0m"
	@gcc -o $(NAME) $(SANITIZE) $(CFLAGS) $(OBJECT_MY_VM) $(LIB)
	# @gcc -o $(NAME) $(OBJECT_MY_VM) $(LIB)
	@echo "\033[0;32m[COREWAR COMPILED]\033[0;0m"

%.o: %.c includes/*.h
	gcc -g -o $@ -c $< $(INCLUDES_MY_VM) $(SANITIZE) $(INCLUDES_LIB)

clean:
	make -C ./src clean
	rm -f $(OBJECT_MY_VM)
	rm -f TAGS

fclean: clean
	rm -f ./src/lib.a
	rm -f $(NAME)

re: fclean all
