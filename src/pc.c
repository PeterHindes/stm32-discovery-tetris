#include "pc.h"
#include "game.h"

// Function to enable non-canonical input mode
void enableRawMode() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

// Function to restore terminal settings
void disableRawMode() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= (ICANON | ECHO); // Re-enable canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

struct timeval tv;
fd_set readfds;
char command;
void setup(){
    enableRawMode();
}

void winddown(){
    disableRawMode();
}

bool handleInputAndTimeout(Board *board, Piece *piece){
    // Set up the timeout for non-blocking input
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);

    // Wait for input or timeout
    int result = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &tv);

    // Read the user input if available
    if (result > 0 && FD_ISSET(STDIN_FILENO, &readfds)) {
        command = getchar(); 
        if (command == 'q') {
            printf("Game Over! Exiting...\n");
            return false;
        }
        handleInput(board, piece, command);
    }
    return true;
}