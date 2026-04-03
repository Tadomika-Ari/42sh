##
## EPITECH PROJECT, 2026
## chocolatine
## File description:
## Makefile
##

NAME	= 	choco

NAMEunitest = unit_tests

SRC = ./main.c

CC = epiclang

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ)

all: $(NAME)

clean:
	rm -rf $(OBJ)
	rm -rf *.gcno
	rm -rf *.gcda

fclean: clean
	rm -rf $(NAME)
	rm -rf $(NAMEunitest)

unit_tests:
	clang -o $(NAMEunitest) $(SRC) tests/*.c --coverage -lcriterion -lgcov

tests_run: unit_tests
	./$(NAMEunitest)
	gcovr --gcov-executable "llvm-cov-20 gcov" --exclude tests/

cover: tests_run
	gcovr --gcov-executable "llvm-cov-20 gcov" --exclude tests/ --branches

re: fclean all