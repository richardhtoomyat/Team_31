#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#define HEIGHT 27
#define WIDTH 43

typedef struct Cell {
    char type;  // 'S' for snake, 'F' for food, ' ' for empty
} Cell;

// Function declarations
void initializeBoard(Cell gameBoard[HEIGHT][WIDTH]);
void printBoard(Cell gameBoard[HEIGHT][WIDTH]);
void clearBoard(Cell gameBoard[HEIGHT][WIDTH]);

#endif // GAME_BOARD_H 
