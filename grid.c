#include <stdio.h>

#define WIDTH 32
#define HEIGHT 17

// Define the Cell structure for the game board
typedef struct Cell {
    char type; // 'S' for snake, 'F' for food, '.' for empty
} Cell;

// Define the game board as a global 2D array
Cell gameBoard[HEIGHT][WIDTH];

// Function to initialize the grid
void init_grid() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == 0 || j == 0 || i == HEIGHT - 1 || j == WIDTH - 1)
                gameBoard[i][j].type = '=';  // Walls
            else
                gameBoard[i][j].type = '.';  // Empty space
        }
    }
}

// Function to print the grid
void print_grid() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c ", gameBoard[i][j].type);
        }
        printf("\n");
    }
}
