#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   // ✅ Required for `usleep()`
#include <termios.h>  // ✅ Required for `tcgetattr()` and `tcsetattr()`
#include <fcntl.h>    // ✅ Required for `fcntl()`
#include "grid.h"
#include "snake.h"


// Function to handle non-blocking input
int kbhit(void) {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}


char getInput() {
    if (kbhit()) {
        return getchar();
    }
    return 0;
}

int main() {
    Snake snake;
    int gameOver = 0;

    init_grid();
    init_snake(&snake);

    while (!gameOver) {
        print_grid();

        char input = getInput();
        if (input) {
            if ((input == 'W' || input == 'w') && snake.direction != 'S') snake.direction = 'W';
            if ((input == 'S' || input == 's') && snake.direction != 'W') snake.direction = 'S';
            if ((input == 'A' || input == 'a') && snake.direction != 'D') snake.direction = 'A';
            if ((input == 'D' || input == 'd') && snake.direction != 'A') snake.direction = 'D';
        }

        move_snake(&snake);
        gameOver = check_collision(&snake);

        usleep(200000);
        system("clear");
    }

    printf("Game Over!\n");
    return 0;
}
