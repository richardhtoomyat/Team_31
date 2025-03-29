CC = gcc
CFLAGS = -Wall -Wextra -std=c11

SRC = main.c food.c game_board.c movement.c snake.c
game: $(SRC)
	$(CC) $(CFLAGS) -o snake_game $(SRC)

TEST_SRC = tests.c game_board.c food.c snake.c
test:
	$(CC) $(CFLAGS) -o tests $(TEST_SRC)
	./tests

run: game
	./snake_game

clean:
	rm -f snake_game tests

# make : compile
# make test : to test
# make run : to run the program
# make clean : to clean
