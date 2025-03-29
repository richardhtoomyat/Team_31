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

    if (read(STDIN_FILENO, &buf[0], 1) == 1) {
        if (buf[0] == '\x1b') {
            // Possible escape sequence
            if (read(STDIN_FILENO, &buf[1], 1) == 1 && read(STDIN_FILENO, &buf[2], 1) == 1) {
                if (buf[1] == '[') {
                    switch (buf[2]) {
                        case 'A': return 'W';  // Up 
                        case 'B': return 'S';  // Down 
                        case 'C': return 'D';  // Right 
                        case 'D': return 'A';  // Left
                    }
                }
            }
        } else {
            // Handle keys like 'q' to quit
            return buf[0];
        }
    }

    return 0; 
} 
