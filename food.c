
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "food.h"

int isValidFoodPosition(Cell gameBoard[HEIGHT][WIDTH], Snake* snake, int x, int y) {
    // Check if position is on border
    if (x <= 0 || x >= WIDTH-1 || y <= 0 || y >= HEIGHT-1) {
        return 0;
    }
    
    // Check if position is on snake
    SnakeSegment* current = snake->head;
    while (current != NULL) {
        if (x == current->x && y == current->y) {
            return 0;
        }
        current = current->next;
    }
    
    return 1;
}

void generateFood(Cell gameBoard[HEIGHT][WIDTH], Snake* snake) {
   

    int x, y;
    int attempts = 0;
    const int MAX_ATTEMPTS = 100; 
    
    do {
        x = rand() % (WIDTH - 2) + 1;
        y = rand() % (HEIGHT - 2) + 1;
        attempts++;
    } while (!isValidFoodPosition(gameBoard, snake, x, y) && attempts < MAX_ATTEMPTS);
    
    if (attempts < MAX_ATTEMPTS) {
        gameBoard[y][x].type = 'F';
    }
}

int isFood(Cell gameBoard[HEIGHT][WIDTH], int x, int y) {
    return gameBoard[y][x].type == 'F';
} 
