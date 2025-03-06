#ifndef SNAKE_H
#define SNAKE_H

typedef struct Snake {
    int x, y;
    int length;
    char direction; // 'W', 'A', 'S', 'D'
} Snake;

void init_snake(Snake* snake);
void move_snake(Snake* snake);
int check_collision(Snake* snake);

#endif
