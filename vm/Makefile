NAME = corewar

SRC =	main.c \
		cpu/game.c \
		cpu/memory_reader.c \
		cpu/op.c \
		errors/errors.c \
		gui/print_memory.c \
		gui/results.c \
		initializer/champ_init.c \
		initializer/machine_init.c \
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
		parser/options.c \
		parser/validate_args.c

OBJECT_MY_VM = $(SRC:.c=.o)
INCLUDES_MY_VM = -I ./includes/
INCLUDES_LIB = -I ./src/includes
LIB = ./src/lib.a
SANITIZE = -fsanitize=address -Wall -Wextra -Werror
CLAFGS = -Wall -Wextra -Werror


all: $(NAME)

$(NAME) : $(OBJECT_MY_VM)
	make -C ./src
	@echo "\033[0;32m[LIB COMPILED]\033[0;0m"
	@gcc -o $(NAME) $(SANITIZE) $(CFLAGS) $(OBJECT_MY_VM) $(LIB)
	# @gcc -o $(NAME) $(OBJECT_MY_VM) $(LIB)
	@echo "\033[0;32m[COREWAR COMPILED]\033[0;0m"

%.o: %.c includes/*.h
	gcc -g -o $@ -c $< $(INCLUDES_MY_VM) $(SANITIZE) $(CFLAGS) $(INCLUDES_LIB)

clean:
	make -C ./src clean
	rm -f $(OBJECT_MY_VM)

fclean: clean
	rm -f ./src/lib.a
	rm -f $(NAME)

re: fclean all
