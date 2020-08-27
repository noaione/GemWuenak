#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

#include "flappygame.h"
#include "../extras/extra.h"

int high, width;         // The border
int bird_x, bird_y;      // The bird coordinates
int bar_y;               // Baffle coordinates
int bar_xTop, bar_xDown; // Upper and lower coordinates of the baffle opening
int score;               // score
int check;

void WingUp()
{
    puts("\\");
    puts("<\\=Q");
}

void WingDown()
{
    puts("<//=Q");
    puts("//");
}

void replay()
{
	
}

void startup_bird() // Data initialization
{
    high = 18; // Initialization boundary
    width = 26;

    bird_x = high / 2; // Initializes the bird coordinates
    bird_y = width / 2;

    bar_y = width; // Baffle coordinates

    bar_xTop = high / 2; // Baffle opening
    bar_xDown = bar_xTop + 4;

    score = 0; // score

    hideCursor(); // Hide the cursor
}

void show_bird() // display
{
    int i, j;
    setCursorPosition(0, 0);
    for (i = 0; i <= high + 1; i++)
    {
        for (j = 0; j <= width; j++)
        {
            if ((i == bird_x) && (j == bird_y))
            {
                printf(">");
            } // Output the bird
            else if (i == high + 1)
            {
                printf("_");
            } // Output lower boundary
            else if ((j == bar_y) && ((i <= bar_xTop) || (i >= bar_xDown)))
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
    printf("Score: %d\n", score);
}

int updateWithoutInput() // Game logic/rule
{
    if (bird_y == bar_y - 1)
    {
        if ((bird_x > bar_xTop) && (bird_x < bar_xDown))
        {
            score++;
        } // Birds score points by opening the baffle
        else
        {
            printf(" RIP \n"); // The bird hit the wall
            return 1;          // 1 == dead
        }
    }

    if (bar_y > 0)
    {
        bar_y--;
    }
    else
    {
        bar_y = width;
        bar_xTop = rand() % (high - 4);
        bar_xDown = bar_xTop + 4;
    }

    if (bird_x < high + 1)
    {
        bird_x++;
    }
    else
    {
        printf(" RIP \n");
        return 1; // 1 = dead
    }
    Sleep(125); // Speed game(<75 == godly)
    return 0;
}

void updateWithInput() // Updates related to user input
{
    char input;
    if (kbhit())
    {
        input = getch();
        if ((input == ' ') && (bird_x > 0) && (bird_x <= high))
        {
            // Bird jumps up
            bird_x = bird_x - 2;
        }
    }
}