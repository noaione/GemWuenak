#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>

#include "kartu41.h"

// A port of kisanak kartu41 in Python
// to C++ lang

void print_x_times(char ch, int x)
{
    for (int i = 0; i < x; i++)
    {
        printf("%c", ch);
    }
}

class Kartu41
{
public:
    bool gameover;
    int winner, turn;
    int player_score, bot_score, latestStack;
    int mainDeck[52] = {1}, stackDeck[52] = {0}, playerDeck[5] = {-1}, botDeck[5] = {-1};
    CardSuites suites;

    Kartu41(void)
    {
        srand(time(NULL)); // seed RNGJesus
        this->gameover = false;
        this->winner = -1;

        this->turn = 0;

        this->playerDeck;
        this->botDeck;

        this->player_score = 0;
        this->bot_score = 0;

        this->mainDeck;
        this->stackDeck;
        this->latestStack = -1;
    }
    int rng_card()
    {
        // https://www.geeksforgeeks.org/generating-random-number-range-c/
        int num = (rand() % (51 - 0 + 1)) + 0;
        return num;
    }
    int draw_card(int whomst, int card_pos = 0)
    {
        bool succeed = false;
        int card;
        while (!succeed)
        {
            card = rng_card();
            if (this->mainDeck[card] == 1)
            {
                if (whomst == 0)
                {
                    this->playerDeck[card_pos] = card;
                }
                else if (whomst == 1)
                {
                    this->botDeck[card_pos] = card;
                }
                this->mainDeck[card] = 0;
                succeed = true;
            }
        }
        return card;
    }
    void start_game()
    {
        for (int i = 0; i < 4; i++)
        {
            draw_card(0, i);
            draw_card(1, i);
        }
        int firstStack = draw_card(2);
        this->latestStack = firstStack;
        this->stackDeck[firstStack] = 1;
        print_stack();
        while (!gameover) {
            player_turn();
            for (int i = 0; i < 3; i++) {
                printf(".");
                Sleep(250);
            }
            bot_turn();
        }
        if (winner == 0) {
            printf("\nPemenangnya adalah: Player!");
        } else if (winner == 1) {
            printf("\nPemenangnya adalah: Bot!");
        }
    }
    void print_stack()
    {
        printf("\nStack:\n");
        print_x_times('=', 11);
        printf("\n");
        printf("|	  |\n");
        printf("|	  |\n");
        printf("|	  |\n");
        printf("    %s\n", this->suites.fullDecks[this->latestStack]);
        printf("|	  |\n");
        printf("|	  |\n");
        printf("|	  |\n");
        print_x_times('=', 11);
    }
    void player_turn() {}
    void bot_turn() {}
    void check_card_stack() {}
};


// N4O: Untested.
int kartu41_game() {
    Kartu41 game;
    game.start_game();
    return 0;
}