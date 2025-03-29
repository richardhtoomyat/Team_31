#include <stdio.h>
#include <stdlib.h>
#include "snake.h"

void initializeSnake(Snake* snake) {
    // initial head segment
    snake->head = (SnakeSegment*)malloc(sizeof(SnakeSegment));
    if (snake->head == NULL) {
        exit(1);
    }
    
    snake->head->x = 15;
    snake->head->y = 7;
    snake->head->next = NULL;
    snake->direction = 'D';
    snake->length = 1;
}

void moveSnake(Snake* snake, char input) {
    int prevX = snake->head->x;
    int prevY = snake->head->y;
    
    if (input != 0) {
        switch (input) {
            case 'W':
            case 'w':
                if (snake->direction != 'S') snake->direction = 'W';
                break;
            case 'S':
            case 's':
                if (snake->direction != 'W') snake->direction = 'S';
                break;
            case 'A':
            case 'a':
                if (snake->direction != 'D') snake->direction = 'A';
                break;
            case 'D':
            case 'd':
                if (snake->direction != 'A') snake->direction = 'D';
                break;
        }
    }
    
    // Move head based on current direction
    switch (snake->direction) {
        case 'W': snake->head->y--; break;
        case 'S': snake->head->y++; break;
        case 'A': snake->head->x--; break;
        case 'D': snake->head->x++; break;
    }

    // Move the body segments
    SnakeSegment* current = snake->head->next;
    while (current != NULL) {
        int tempX = current->x;
        int tempY = current->y;
        current->x = prevX;
        current->y = prevY;
        prevX = tempX;
        prevY = tempY;
        current = current->next;
    }
}

void addSegment(Snake* snake) {
    SnakeSegment* newSegment = (SnakeSegment*)malloc(sizeof(SnakeSegment));
    if (newSegment == NULL) {
        return;
    }

    // Find last segment
    SnakeSegment* last = snake->head;
    while (last->next != NULL) {
        last = last->next;
    }

    int newX = last->x;
    int newY = last->y;

    switch (snake->direction) {
        case 'W': newY++; break;
        case 'S': newY--; break;
        case 'A': newX++; break;
        case 'D': newX--; break;
    }

    newSegment->x = newX;
    newSegment->y = newY;
    newSegment->next = NULL;
    last->next = newSegment;
    snake->length++;
}

//Recursion
void updateBoardWithSnakeRecursive(Cell gameBoard[HEIGHT][WIDTH], SnakeSegment* segment) {
    if (segment == NULL) return;
    if (segment->y >= 0 && segment->y < HEIGHT &&
        segment->x >= 0 && segment->x < WIDTH) {
        gameBoard[segment->y][segment->x].type = 'S';
    }
    updateBoardWithSnakeRecursive(gameBoard, segment->next);
}

void updateBoardWithSnake(Cell gameBoard[HEIGHT][WIDTH], Snake* snake) {
    // Clear previous snake positions
    for (int i = 1; i < HEIGHT-1; i++) {
        for (int j = 1; j < WIDTH-1; j++) {
            if (gameBoard[i][j].type == 'S') {
                gameBoard[i][j].type = ' ';
            }
        }
    }

    updateBoardWithSnakeRecursive(gameBoard, snake->head);
}

int checkCollisions(Snake* snake) {
    // Check wall collisions
    if (snake->head->x <= 0 || snake->head->x >= WIDTH-1 || 
        snake->head->y <= 0 || snake->head->y >= HEIGHT-1) {
        return 1;
    }

    // Check self-collision
    SnakeSegment* current = snake->head->next;
    while (current != NULL) {
        if (snake->head->x == current->x && snake->head->y == current->y) {
            return 1;
        }
        current = current->next;
    }

    return 0;

}

void freeSnake(Snake* snake) {
    SnakeSegment* current = snake->head;
    while (current != NULL) {
        SnakeSegment* next = current->next;
        free(current);
        current = next;
    }
    snake->head = NULL;
    snake->length = 0;
}