#ifndef SNAKE_H
#define SNAKE_H

#include "game_board.h"

// Snake segment structure (linked list node)
typedef struct SnakeSegment {
    int x, y;
    struct SnakeSegment* next;
} SnakeSegment;

// Snake structure with head pointer and direction
typedef struct Snake {
    SnakeSegment* head;
    char direction;  // 'W', 'A', 'S', 'D'
    int length;     // Current length of snake
} Snake;

// Function declarations
void initializeSnake(Snake* snake);
void moveSnake(Snake* snake, char input);
void addSegment(Snake* snake);
void updateBoardWithSnake(Cell gameBoard[HEIGHT][WIDTH], Snake* snake);
int checkCollisions(Snake* snake);


#endif // SNAKE_H 
