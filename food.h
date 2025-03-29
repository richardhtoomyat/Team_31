#ifndef FOOD_H
#define FOOD_H

#include "game_board.h"
#include "snake.h"

void generateFood(Cell gameBoard[HEIGHT][WIDTH], Snake* snake);
int isFood(Cell gameBoard[HEIGHT][WIDTH], int x, int y);
int isValidFoodPosition(Cell gameBoard[HEIGHT][WIDTH], Snake* snake, int x, int y);

#endif // FOOD_H 
