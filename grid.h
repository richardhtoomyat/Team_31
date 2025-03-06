#ifndef GRID_H
#define GRID_H

#define WIDTH 32
#define HEIGHT 17

typedef struct Cell {
    char type;
} Cell;

extern Cell gameBoard[HEIGHT][WIDTH];

void init_grid();
void print_grid();

#endif
