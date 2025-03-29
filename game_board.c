#include <stdio.h>
#include <stdlib.h>
#include "game_board.h"

void initializeBoard(Cell gameBoard[HEIGHT][WIDTH]) {
    
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == 0 || i == HEIGHT-1) {
                gameBoard[i][j].type = (j == 0 || j == WIDTH-1) ? '+' : '-';
            } else if (j == 0 || j == WIDTH-1) {
                gameBoard[i][j].type = '|';
            } else {
                gameBoard[i][j].type = ' ';
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

