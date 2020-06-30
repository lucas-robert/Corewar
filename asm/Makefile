NAME = asm

SRC =	main.c \
		errors/errors.c \
		parser/read_file.c \
		parser/metadata.c \
		tokenizer/tokenizer.c \
		tokenizer/parse_tokens.c \
		tokenizer/scanner.c \
		compiler/operations_table_helper.c \
		compiler/compile_helpers.c \
		compiler/compile.c \
		compiler/delete_struct.c \
		compiler/write.c \


OBJECT_MY_ASM = $(SRC:.c=.o)
INCLUDES_MY_ASM = -I ./includes/
INCLUDES_LIB = -I ./src/includes
LIB = ./src/lib.a
SANITIZE = -g3 -fsanitize=address -Wall -Wextra -Werror
CLAFGS = -Wall -Wextra -Werror


all: $(NAME)

$(NAME) : $(OBJECT_MY_ASM)
	make -C ./src
	@echo "\033[0;32m[LIB COMPILED]\033[0;0m"
	@gcc -o $(NAME) $(SANITIZE) $(CFLAGS) $(OBJECT_MY_ASM) $(LIB)
	# @gcc -o $(NAME) $(OBJECT_MY_ASM) $(LIB)
	@echo "\033[0;32m[MY_LS COMPILED]\033[0;0m"

%.o: %.c includes/*.h
	gcc -g -o $@ -c $< $(INCLUDES_MY_ASM) $(SANITIZE) $(INCLUDES_LIB)

clean:
	make -C ./src clean
	rm -f $(OBJECT_MY_ASM)
	rm -f TAGS

fclean: clean
	rm -f ./src/lib.a
	rm -f $(NAME)

re: fclean all
