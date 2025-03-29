CC = gcc
CFLAGS = -Wall -Wextra -std=c11

SRC = main.c food.c game_board.c movement.c snake.c
game: $(SRC)
	$(CC) $(CFLAGS) -o snake_game $(SRC)

TEST_SRC = tests.c game_board.c food.c snake.c
test:
	$(CC) $(CFLAGS) -o tests $(TEST_SRC)
	./tests

clean:
	rm -f snake_game tests
