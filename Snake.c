#include <stdio.h>
#include <stdlib.h>

typedef struct Snake {
    int x, y; // Position
    int length;
    char direction; // 'W', 'A', 'S', 'D'
} Snake;

