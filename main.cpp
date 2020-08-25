#include <stdio.h>
#include "extras/extra.h"

// Import pong.
#include "pong/ponggame.cpp"
// Import flappy bird.
// Note: Doesn't supppot Linux completely.
// someone please reimplement getch()
#include "flappy_bird/flappy_menu.cpp"

// N4O: someone please make the main menu, kthx.
// extra.h contain some function like
// hideCursor(), clearScreen(), setCursorPosition(x, y)
// please use that since it's UNIX/Windows compliant.
int main() {
    // flappy_bird();
    return 0;
}