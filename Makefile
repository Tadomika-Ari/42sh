##
## EPITECH PROJECT, 2025
## minishell
## File description:
## Makefile
##

SRC = 	main.c							\
		initialisation/init.c			\
		built_in/cd.c					\
		built_in/env.c					\
		built_in/exit.c					\
		built_in/setenv.c				\
		built_in/unsetenv.c				\
		error/error_message.c			\
		loop_tcsh/argument.c			\
		loop_tcsh/loop.c				\
		loop_tcsh/command.c				\
		redirection/in_simple.c			\
		redirection/out_simple.c		\
		redirection/tools.c				\
		free/free_all.c					\
		error/other_error_message.c		\
		tools/file.c					\
		free/my_free.c					\
		loop_tcsh/child.c				\
		loop_tcsh/error_handling_pipe.c	\
		error/error_term.c			\
		history/history.c\
		user/my_getline.c           \

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
