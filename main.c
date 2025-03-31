#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "game_board.h"
#include "snake.h"
#include "movement.h"
#include "food.h"

int loadHighScore(const char* filename) {
    FILE* file = fopen(filename, "r");
    int highScore = 0;
    if (file != NULL) {
        fscanf(file, "%d", &highScore); 
        fclose(file);
    }
    return highScore;
}

void saveHighScore(const char* filename, int score) {
    FILE* file = fopen(filename, "w");
    if (file != NULL) {
        time_t now = time(NULL);
        struct tm* t = localtime(&now);

        fprintf(file, "%d -> %02d-%02d-%04d %02d:%02d:%02d\n",
                score,
                t->tm_mday, t->tm_mon + 1, t->tm_year + 1900,
                t->tm_hour, t->tm_min, t->tm_sec);

        fclose(file);
    }
}


int main() {
    srand(time(NULL));
    Cell gameBoard[HEIGHT][WIDTH];
    Snake snake;
    int gameOver = 0;
    int score = 0;
    int highScore = loadHighScore("highscore.txt");

    initializeBoard(gameBoard);
    initializeSnake(&snake);
    generateFood(gameBoard, &snake);
    changeTerminalSetting();

    while (!gameOver) {
        system("clear");
        printf("Score: %d  |  High Score: %d\n", score, highScore);
        printBoard(gameBoard);
        char lastInput = 0; // keep track of last input
        char input = getInput();
        if (input != 0 && input != lastInput) {
            moveSnake(&snake, input);
            lastInput = input;
        } else {
            moveSnake(&snake, 0); // ignor if the same key is pressed again
        }

        if (isFood(gameBoard, snake.head->x, snake.head->y)) {
            addSegment(&snake);
            score++;
            gameBoard[snake.head->y][snake.head->x].type = ' ';
            generateFood(gameBoard, &snake);
        }

        updateBoardWithSnake(gameBoard, &snake);
        gameOver = checkCollisions(&snake);
        usleep(100000); // speed of the snake
    }

    restoreTerminalSetting();
    printf("\nGame Over!\n");

    if (score > highScore) {
        printf("New High Score!\n");
        saveHighScore("highscore.txt", score);
        printf("Leaderboard: %d\n", score);
    } else {
        printf("Leaderboard: %d\n", highScore);
    }

    void freeSnake(Snake* snake);
    freeSnake(&snake);
    return 0;
}
