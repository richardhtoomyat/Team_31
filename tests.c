#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "game_board.h"
#include "snake.h"
#include "food.h"

void test_isFood() { // unit test
    Cell board[HEIGHT][WIDTH];
    initializeBoard(board);
    board[5][5].type = 'F';
    assert(isFood(board, 5, 5) == 1);
    assert(isFood(board, 7, 4) == 0); //random spot check
    printf("test_isFood passed!!\n");
}

void test_addSegment() {
    Snake snake;
    initializeSnake(&snake);
    int before = snake.length;
    addSegment(&snake);
    assert(snake.length == before + 1);
    printf("test_addSegment passed!!\n");
}

void test_foodNotOnSnake() { // edge case 1 for proper food spawning
    Cell board[HEIGHT][WIDTH];
    initializeBoard(board);

    Snake snake;
    initializeSnake(&snake);

    // Fill nearly the whole board with snake
    SnakeSegment* current = snake.head;
    for (int i = 1; i < HEIGHT-2; ++i) {
        SnakeSegment* newSegment = (SnakeSegment*)malloc(sizeof(SnakeSegment));
        newSegment->x = 1;
        newSegment->y = i;
        newSegment->next = current;
        current = newSegment;
    }
    snake.head = current;
    snake.length = HEIGHT-3;

    generateFood(board, &snake); // create food at rmaining empty space

    // to make sure food is not on snake
    int x, y, collide = 0;
    for (y = 0; y < HEIGHT; ++y) {
        for (x = 0; x < WIDTH; ++x) {
            if (isFood(board, x, y)) { // check if food is on snale
                SnakeSegment* cur = snake.head;
                while (cur) {
                    if (cur->x == x && cur->y == y)
                        collide = 1; // if food is on snake
                    cur = cur->next;
                }
            }
        }
    }
    assert(collide == 0);
    printf("test_foodNotOnSnake passed!!\n");
}

void test_snakeWallCollision() { // edge case 2 for proper collision check
    Snake snake; 
    initializeSnake(&snake);
    snake.head->x = 1; // Move snake close to left wall
    snake.head->y = 1;
    snake.direction = 'A'; // move left into the wall 
    moveSnake(&snake, 'A');

    int collision = checkCollisions(&snake);
    assert(collision == 1); // it Should collide
    printf("test_snakeWallCollision passed!!\n");
}

void test_snakeLength() { // edge case 3 for proper snake growth and length check
    Snake snake;
    initializeSnake(&snake);
    int maxSegments = (HEIGHT - 2) * (WIDTH - 2) - 1; // exclude borders and count possible length of snake

    for (int i = 0; i < maxSegments - 1; ++i) { // create snake upto the limit
        addSegment(&snake);
    }

    assert(snake.length == maxSegments);
    printf("test_snakeLength passed!!\n");
}

void test_foodNotOnBorder() { // edge case 4 for food on border check
    Cell board[HEIGHT][WIDTH];
    initializeBoard(board);

    Snake snake;
    initializeSnake(&snake);
    generateFood(board, &snake); // creates food at random empty space

    int temp = 0;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (isFood(board, j, i)) {
                if (i == 0 || i == HEIGHT-1 || j == 0 || j == WIDTH-1)
                    temp = 1; // if food is on snake
            }
        }
    }

    assert(temp == 0);
    printf("test_foodNotOnBorder passed!!\n");
}


int main() {
    test_isFood();
    test_addSegment();
    test_foodNotOnSnake();
    test_snakeWallCollision();
    test_snakeLength();
    test_foodNotOnBorder();
    printf("All tests passed!!\n");
    return 0;
}
