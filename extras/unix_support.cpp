#include <stdio.h>
#include <sys/select.h>
#include <termios.h>
#include <stropts.h>
#include "helper.h"

void SetCursorPos(COORD coordsIn)
{
    printf("\033[%d;%dH", coordsIn.X + 1, coordsIn.Y + 1);
}

/**
 Linux (POSIX) implementation of kbhit().
 Morgan McGuire, morgan@cs.brown.edu
*/
int kbhit() {
    static const int STDIN = 0;
    static bool initialized = false;

    if (! initialized) {
        // Use termios to turn off line buffering
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }

    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}