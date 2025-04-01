#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include "movement.h"

static struct termios orig_termios;

void changeTerminalSetting(void) {
    // Save original terminal settings
    tcgetattr(STDIN_FILENO, &orig_termios);
    
    // Set terminal to raw mode // IMPORTANT
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    
    // Set non-blocking input
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
}

void restoreTerminalSetting(void) {
    // Restore original terminal settings
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

char getInput() {
    char buf[3] = {0}; 

    // Helps to read a single input 
    if (read(STDIN_FILENO, &buf[0], 1) == 1) {
        if (buf[0] == '\x1b') {
            if (read(STDIN_FILENO, &buf[1], 1) == 1 &&
                read(STDIN_FILENO, &buf[2], 1) == 1) {

                if (buf[1] == '[') {
                    if (buf[2] == 'A') return 'W'; // W works as up arrow
                    else if (buf[2] == 'B') return 'S'; // S works as Down arrow
                    else if (buf[2] == 'C') return 'D'; // D works as Right arrow
                    else if (buf[2] == 'D') return 'A'; // A works as Left arrow
                }
            }
        }
        else {
            return buf[0];
        }
    }
    return 0;
}

