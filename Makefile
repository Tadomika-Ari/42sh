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
		src/error/error_term.c			    \
		src/history/history.c               \
		src/tools/parser.c                  \
		src/initialisation/fill_rc.c        \
		src/tools/correct_tab.c             \
		src/error/put_err.c			        \
		src/tools/array_to_node.c           \
		src/tools/check_str.c               \
		src/tools/sweeper.c                 \
		src/tools/translate.c               \
		src/user/my_getline.c           	\
		src/user/check_history_up.c 		\
		src/user/check_history_down.c 		\
		src/user/left_key.c  				\
		src/user/right_key.c				\
		src/user/all_for_len.c      		\
		src/user/cursor_move.c     			\
		src/built_in/fg.c					\
        src/built_in/bg.c					\
        src/jobs/add_job.c					\
        src/jobs/find_job.c					\
        src/jobs/remove_job.c				\
        src/jobs/free_job.c					\
        src/jobs/continue_job.c             \
		src/jobs/printing.c                 \
		src/special_variable/sepecial_variable.c\
		src/alias/add_alias.c\
		src/alias/check_alias.c             \
		src/loop_tcsh/search_binary.c       \
		src/error/put_error_ptr.c \
		src/built_in/set.c					\
		src/built_in/if.c					\

OBJ = 	$(SRC:.c=.o)

TEST_NAME = unit_tests

TEST_SRC = tests/test_42sh.c \
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
		src/error/error_term.c			    \
		src/history/history.c               \
		src/tools/parser.c                  \
		src/initialisation/fill_rc.c        \
		src/tools/correct_tab.c             \
		src/error/put_err.c			        \
		src/tools/array_to_node.c           \
		src/tools/check_str.c               \
		src/tools/sweeper.c                 \
		src/tools/translate.c               \
		src/user/my_getline.c           	\
		src/user/check_history_up.c 		\
		src/user/check_history_down.c 		\
		src/user/left_key.c  				\
		src/user/right_key.c				\
		src/user/all_for_len.c    			\
		src/user/cursor_move.c     			\
		src/built_in/fg.c					\
        src/built_in/bg.c					\
        src/jobs/add_job.c					\
        src/jobs/find_job.c					\
        src/jobs/remove_job.c				\
        src/jobs/free_job.c					\
        src/jobs/continue_job.c             \
		src/jobs/printing.c                 \
		src/special_variable/sepecial_variable.c \
		src/alias/add_alias.c\
		src/alias/check_alias.c             \
		src/loop_tcsh/search_binary.c       \
		src/error/put_error_ptr.c \
		src/built_in/set.c					\
		src/built_in/if.c					\


NAME =	42sh

all:	$(NAME)

$(NAME): do_lib $(OBJ)
	epiclang -o $(NAME) $(SRC) -lmy -Llib/my

do_lib:
	make -C lib/my/

make_debug:	$(OBJ)
	epiclang -o $(NAME) $(SRC) -g3
	valgrind --leak-check=full ./42sh 2> val.txt

unit_tests:	all
	@epiclang -o $(TEST_NAME) $(TEST_SRC) --coverage -lcriterion -lmy -Llib/my

tests_run: unit_tests
	@./$(TEST_NAME)
	@gcovr --gcov-executable "llvm-cov-20 gcov" --exclude tests/

cover: tests_run
	gcovr --gcov-executable "llvm-cov-20 gcov" --exclude tests/ --branches

clean:
	@rm -f $(OBJ)
	@rm -f *.gcno
	@rm -f *.gcda

fclean: clean
	make fclean -C lib/my/
	@rm -f $(NAME)
	@rm -f $(TEST_NAME)

re:	fclean all
