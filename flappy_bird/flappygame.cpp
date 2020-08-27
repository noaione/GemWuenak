#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

#include "flappygame.h"
#include "../extras/extra.h"

FlappyTheBird::FlappyTheBird(void) {
    this->score = 0;

    this->high;
    this->width;

    this->bird_x;
    this->bird_y;
    this->bar_y;

    this->bar_xDown;
    this->bar_xTop;
}

void FlappyTheBird::startup_bird() // Data initialization
{
    this->high = 18; // Initialization boundary
    this->width = 26;

    this->bird_x = this->high / 2; // Initializes the bird coordinates
    this->bird_y = this->width / 2;

    this->bar_y = this->width; // Baffle coordinates

    this->bar_xTop = this->high / 2; // Baffle opening
    this->bar_xDown = this->bar_xTop + 4;

    this->score = 0; // score

    hideCursor(); // Hide the cursor
}

void FlappyTheBird::show_bird() // display
{
    int i, j;
    setCursorPosition(0, 0);
    for (i = 0; i <= this->high + 1; i++)
    {
        for (j = 0; j <= this->width; j++)
        {
            if ((i == this->bird_x) && (j == this->bird_y))
            {
                printf(">");
            } // Output the bird
            else if (i == this->high + 1)
            {
                printf("_");
            } // Output lower boundary
            else if ((j == this->bar_y) && ((i <= this->bar_xTop) || (i >= this->bar_xDown)))
            {
                printf("||");
            } // Output damper
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("Score: %d\n", this->score);
}

int FlappyTheBird::updateWithoutInput() // Game logic/rule
{
    if (this->bird_y == this->bar_y - 1)
    {
        if ((this->bird_x > this->bar_xTop) && (this->bird_x < this->bar_xDown))
        {
            this->score++;
        } // Birds score points by opening the baffle
        else
        {
            printf(" RIP \n"); // The bird hit the wall
            return 1;          // 1 == dead
        }
    }

    if (this->bar_y > 0)
    {
        this->bar_y--;
    }
    else
    {
        this->bar_y = this->width;
        this->bar_xTop = rand() % (this->high - 4);
        this->bar_xDown = this->bar_xTop + 4;
    }

    if (this->bird_x < this->high + 1)
    {
        this->bird_x++;
    }
    else
    {
        printf(" RIP \n");
        return 1; // 1 = dead
    }
    Sleep(125); // Speed game(<75 == godly)
    return 0;
}

void FlappyTheBird::updateWithInput() // Updates related to user input
{
    char input;
    if (kbhit())
    {
        input = getch();
        if ((input == ' ') && (this->bird_x > 0) && (this->bird_x <= this->high))
        {
            // Bird jumps up
            this->bird_x = this->bird_x - 2;
        }
    }
}