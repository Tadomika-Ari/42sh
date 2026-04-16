##
## EPITECH PROJECT, 2025
## minishell
## File description:
## Makefile
##

SRC = 	src/main.c							\
		src/initialisation/init.c			\
		src/built_in/cd.c					\
		src/built_in/env.c					\
		src/built_in/exit.c					\
		src/built_in/setenv.c				\
		src/built_in/unsetenv.c				\
		src/error/error_message.c			\
		src/loop_tcsh/argument.c			\
		src/loop_tcsh/loop.c				\
		src/loop_tcsh/command.c				\
		src/redirection/in_simple.c			\
		src/redirection/out_simple.c		\
		src/redirection/tools.c				\
		src/free/free_all.c					\
		src/error/other_error_message.c		\
		src/tools/file.c					\
		src/free/my_free.c					\
		src/loop_tcsh/child.c				\
		src/loop_tcsh/error_handling_pipe.c	\
		src/error/error_term.c			\
		src/history/history.c\
		src/tools/parser.c\

OBJ = 	$(SRC:.c=.o)

TEST_NAME = unit_tests

NAME =	42sh

all:	$(NAME)

$(NAME): do_lib $(OBJ)
	epiclang -o $(NAME) $(SRC) -lmy -Llib/my

do_lib:
	make -C lib/my/

make_debug:	$(OBJ)
	epiclang -o $(NAME) $(SRC) -g3
	valgrind --leak-check=full ./mysh 2> val.txt

unit_tests:	all
	@epiclang -o $(TEST_NAME) $(TEST_SRC) --coverage -lcriterion -lgcov -lmy -Llib/my

tests_run: unit_tests
	@./$(TEST_NAME)
	@gcovr --gcov-executable "llvm-cov-20 gcov" --exclude tests/

clean:
	@rm -f $(OBJ)

fclean: clean
	make fclean -C lib/my/
	@rm -f $(NAME)
	@rm -f $(TEST_NAME)

re:	fclean all
