CC = gcc
CFLAGS = -g -Wall -Wshadow

all: snake_game

snake_game: main.o grid.o snake.o
	$(CC) $(CFLAGS) main.o grid.o snake.o -o snake_game

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

grid.o: grid.c
	$(CC) $(CFLAGS) -c grid.c

snake.o: snake.c
	$(CC) $(CFLAGS) -c snake.c

clean:
	rm -f *.o snake_game
