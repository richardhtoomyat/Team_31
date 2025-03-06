#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GRID_COL 32
#define GRID_ROW 17

typedef struct Cell {
   char type; // 'S' for snake, 'F' for food, ' ' for empty
} Cell;

Cell grid [GRID_ROW][GRID_COL]; // row x column

    void init_grid() {
        for (int i = 0; i < GRID_ROW; i++) {

            for (int j = 0; j < GRID_COL; j++) 
            {   
                if (i == 0 || j == 0 || i == GRID_ROW - 1 || j == GRID_COL - 1)
                grid[i][j].type = '=';

                else
                grid[i][j].type = '.';
            }
        }
    }

    void print_grid() {
        for (int i = 0; i < GRID_ROW; i++) {
            for (int j = 0; j < GRID_COL; j++) {
                printf("%c ", grid[i][j].type);
            }
            printf("\n");
        }
    }

    int main(){    
        init_grid();
        print_grid();
        return 0;
    }

