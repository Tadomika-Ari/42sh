##
## EPITECH PROJECT, 2026
## Pain_Au_Chocolat
## File description:
## Makefile
##

NAME = test
SRC = main.c

TEST_BIN = unit_tests
TEST_SRC = ./tests/test_sample.c

CC = epiclang
CFLAGS =

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	rm -f *.o
	rm -f *.gcno *.gcda

fclean: clean
	rm -f $(NAME)
	rm -f $(TEST_BIN)

re: fclean all

unit_tests: all
	clang --coverage -o $(TEST_BIN) $(TEST_SRC) -lcriterion -lgcov -lm

tests_run: unit_tests
	./$(TEST_BIN)