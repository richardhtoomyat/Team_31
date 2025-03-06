#include <stdio.h>
#include <stdlib.h>
#include "snake.h"  
#include "grid.h"   

void init_snake(Snake* snake) {
    snake->x = WIDTH / 2;
    snake->y = HEIGHT / 2;
    snake->length = 1;
    snake->direction = 'D'; // Default direction (right)
    gameBoard[snake->y][snake->x].type = 'S';
}

void move_snake(Snake* snake) {
    // Clear previous position
    gameBoard[snake->y][snake->x].type = '.';

    // Move in the selected direction
    switch (snake->direction) {
        case 'W': snake->y--; break;
        case 'S': snake->y++; break;
        case 'A': snake->x--; break;
        case 'D': snake->x++; break;
    }

    // Set new position
    gameBoard[snake->y][snake->x].type = 'S';
}

int check_collision(Snake* snake) {
    return (snake->x <= 0 || snake->x >= WIDTH - 1 || snake->y <= 0 || snake->y >= HEIGHT - 1);
}
