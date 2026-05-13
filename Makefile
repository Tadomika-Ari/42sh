##
## EPITECH PROJECT, 2025
## minishell
## File description:
## Makefile
##

SRC = 	src/main.c							            \
		src/built_in/cd.c					            \
		src/built_in/env.c					            \
		src/built_in/exit.c					            \
		src/built_in/setenv.c				            \
		src/built_in/unsetenv.c				            \
		src/error/error_message.c			            \
		src/loop_tcsh/loop.c				            \
		src/loop_tcsh/command.c				            \
		src/redirection/in_simple.c			            \
		src/redirection/out_simple.c		            \
		src/redirection/tools.c				            \
		src/free/free_all.c					            \
		src/tools/file.c					            \
		src/free/my_free.c					            \
		src/loop_tcsh/child.c				            \
		src/loop_tcsh/error_handling_pipe.c	            \
		src/history/history.c                           \
		src/tools/parser.c                              \
		src/initialisation/fill_rc.c                    \
		src/tools/correct_tab.c                         \
		src/tools/array_to_node.c                       \
		src/tools/check_str.c                           \
		src/tools/sweeper.c                             \
		src/tools/translate.c                           \
		src/user/my_getline.c           	            \
		src/user/check_history_up.c 		            \
		src/user/check_history_down.c 		            \
		src/user/left_key.c  				            \
		src/user/right_key.c				            \
		src/user/all_for_len.c      		            \
		src/user/cursor_move.c     			            \
		src/built_in/fg.c					            \
        src/built_in/bg.c					            \
        src/jobs/add_job.c					            \
        src/jobs/find_job.c					            \
        src/jobs/remove_job.c				            \
        src/jobs/free_job.c					            \
        src/jobs/continue_job.c                         \
		src/jobs/printing.c                             \
		src/jobs/job_control.c				            \
		src/jobs/job_control_exec.c			            \
		src/jobs/job_control_empty_case.c	            \
		src/var_interpreters/var_interpreter.c			\
		src/var_interpreters/var_manipulator.c			\
		src/built_in/which.c							\
		src/built_in/where.c							\
		src/built_in/foreach.c							\
		src/built_in/foreach_tools.c					\
		src/alias/add_alias.c                           \
		src/alias/check_alias.c                         \
		src/loop_tcsh/search_binary.c                   \
		src/repeat/check_repeat.c                       \
		src/repeat/error_repeat.c                       \
		src/built_in/set.c                              \
	    src/tools/if_tools.c                            \
		src/built_in/if.c                               \
		src/tools/parsing_tool.c                        \
		src/initialisation/create_node.c                \
		src/tools/glob.c                                \
		src/repeat/len_base.c                           \
		src/repeat/cut_len.c                            \
		src/tools/fill_buff.c                           \
		src/tools/my_strip_newline.c                    \
		src/alias/tools_alias.c                         \
		src/tools/check_parenthesis.c                   \
		src/tools/check_back.c                          \
		src/autocompletation/autocompletation.c	        \
		src/command_utilities/backsticks.c              \
		src/built_in/else.c								\
		src/built_in/is_scripting.c						\
		src/autocompletation/see_tab.c   				\

OBJ = 	$(SRC:.c=.o)

TEST_NAME = unit_tests

TEST_SRC = tests/test_42sh.c                            \
		src/built_in/cd.c                               \
		src/built_in/env.c                              \
		src/built_in/exit.c					            \
		src/built_in/setenv.c				            \
		src/built_in/unsetenv.c				            \
		src/error/error_message.c			            \
		src/loop_tcsh/loop.c				            \
		src/loop_tcsh/command.c				            \
		src/redirection/in_simple.c			            \
		src/redirection/out_simple.c		            \
		src/redirection/tools.c				            \
		src/free/free_all.c					            \
		src/tools/file.c					            \
		src/free/my_free.c					            \
		src/loop_tcsh/child.c				            \
		src/loop_tcsh/error_handling_pipe.c	            \
		src/history/history.c                           \
		src/tools/parser.c                              \
		src/initialisation/fill_rc.c                    \
		src/tools/correct_tab.c                         \
		src/tools/array_to_node.c                       \
		src/tools/check_str.c                           \
		src/tools/sweeper.c                             \
		src/tools/translate.c                           \
		src/user/my_getline.c           	            \
		src/user/check_history_up.c 		            \
		src/user/check_history_down.c 		            \
		src/user/left_key.c  				            \
		src/user/right_key.c				            \
		src/user/all_for_len.c    			            \
		src/user/cursor_move.c     			            \
		src/built_in/fg.c					            \
        src/built_in/bg.c					            \
        src/jobs/add_job.c					            \
        src/jobs/find_job.c					            \
        src/jobs/remove_job.c				            \
        src/jobs/free_job.c					            \
        src/jobs/continue_job.c                         \
		src/jobs/printing.c                             \
		src/jobs/job_control.c				            \
		src/jobs/job_control_exec.c			            \
		src/jobs/job_control_empty_case.c	            \
		src/var_interpreters/var_interpreter.c			\
		src/built_in/foreach.c							\
		src/built_in/foreach_tools.c					\
        src/var_interpreters/var_manipulator.c			\
        src/tools/if_tools.c							\
        src/built_in/which.c							\
        src/built_in/where.c							\
		src/alias/add_alias.c                           \
		src/alias/check_alias.c                         \
		src/loop_tcsh/search_binary.c                   \
		src/command_utilities/backsticks.c              \
		src/repeat/check_repeat.c			            \
		src/repeat/error_repeat.c    		            \
		src/built_in/set.c					            \
		src/built_in/if.c					            \
		src/tools/parsing_tool.c                        \
		src/initialisation/create_node.c                \
		src/tools/glob.c                                \
		src/tools/fill_buff.c                           \
		src/tools/my_strip_newline.c                    \
		src/repeat/len_base.c 				            \
		src/repeat/cut_len.c 				            \
		src/alias/tools_alias.c                         \
		src/tools/check_parenthesis.c                   \
		src/tools/check_back.c                          \
		src/autocompletation/autocompletation.c         \
        src/built_in/else.c								\
        src/built_in/is_scripting.c						\
		src/autocompletation/see_tab.c   				\

TEST_OBJ = $(TEST_SRC:.c=.o)

BONUS_SRC = src/bonus/pelophylax.c                      \
		src/bonus/cprintf.c                             \
		src/bonus/fill_bonus.c                          \
		src/bonus/hangman.c                             \
		src/bonus/fill_buff_bonus.c                     \
		src/bonus/steps_hangman.c                       \
		src/bonus/print_letter_hangman.c                \
		src/bonus/flipcoin.c                            \
		src/bonus/throwdice.c                           \
		src/bonus/guessnumber.c                         \
		src/bonus/author.c                              \
		src/bonus/play_sound.c                          \
		src/bonus/mambo.c                               \
		src/bonus/yippee.c                              \
		src/bonus/rickroll.c                            \
		src/bonus/tic_tac_toe.c                         \
		src/bonus/jobs.c                                \
		src/bonus/velkoz.c \
    	src/built_in/banana.c				\

BONUS_OBJ = 	$(BONUS_SRC:.c=.o)

SRC2 = src/initialisation/init.c                        \
		src/loop_tcsh/argument.c			            \
		src/error/put_error.c\

OBJ2 = 	$(SRC2:.c=.o)

BONUS_SRC2 = src/bonus/init.c                           \
		src/bonus/argument_bonus.c                      \
		src/bonus/put_err_bonus.c			            \

BONUS_OBJ2 = 	$(BONUS_SRC2:.c=.o)

NAME =	42sh

all:	$(NAME)

$(NAME): do_lib
	epiclang -o $(NAME) $(SRC) $(SRC2) -lmy -Llib/my

debug: CC = epiclang
debug: do_lib $(OBJ) $(OBJ2)
	epiclang -o $(NAME) $(SRC) $(SRC2) -lmy -Llib/my

bonus: do_lib $(OBJ) $(BONUS_OBJ) $(BONUS_OBJ2)
	epiclang -o $(NAME) $(SRC) $(BONUS_SRC) $(BONUS_SRC2) -lmy -Llib/my

do_lib:
	make -C lib/my/

make_debug:	$(OBJ)
	epiclang -o $(NAME) $(OBJ) -g3
	valgrind --leak-check=full ./42sh 2> val.txt

unit_tests:	do_lib $(TEST_OBJ) $(OBJ2)
	@epiclang -o $(TEST_NAME) $(TEST_SRC) $(SRC2) --coverage -lcriterion -lmy -Llib/my

tests_run: unit_tests
	@./$(TEST_NAME)
	@gcovr --gcov-executable "llvm-cov-20 gcov" --exclude tests/

cover: tests_run
	gcovr --gcov-executable "llvm-cov-20 gcov" --exclude tests/ --branches

clean:
	@rm -f $(OBJ)
	@rm -f $(OBJ2)
	@rm -f $(BONUS_OBJ)
	@rm -f $(BONUS_OBJ2)
	@rm -f *.gcno
	@rm -f *.gcda

fclean: clean
	make fclean -C lib/my/
	@rm -f $(NAME)
	@rm -f $(TEST_NAME)

re:	fclean all
