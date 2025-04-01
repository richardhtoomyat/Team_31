#include <stdio.h>
#include <stdlib.h>
#include "game_board.h"

void initializeBoard(Cell gameBoard[HEIGHT][WIDTH]) {
    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            
            // Looks through corners and sets +
            if ((row == 0 || row == HEIGHT - 1) && (col == 0 || col == WIDTH - 1)) {
                gameBoard[row][col].type = '+';
            }
                
            // Looks through top and bottom edges and sets -
            else if (row == 0 || row == HEIGHT - 1) {
                gameBoard[row][col].type = '-';
            }
                
            // Looks through left and right edges and sets |
            else if (col == 0 || col == WIDTH - 1) {
                gameBoard[row][col].type = '|';
            }

            // if none then gives a empty space
            else {
                gameBoard[row][col].type = ' ';
            }
        }
    }
}


void printBoard(Cell gameBoard[HEIGHT][WIDTH]) {
     
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", gameBoard[i][j].type);
        }
        printf("\n");
    }
}

