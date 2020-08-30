#ifndef KARTU41_SUITES_H
#define KARTU41_SUITES_H

#include <stdlib.h>

typedef struct CardSuites
{
    // Code friendly-version.
    // : is 10
    // ASCII code friendly.
    char pcDecks[52][3] = {
        "A+", // ♣
        "2+",
        "3+",
        "4+",
        "5+",
        "6+",
        "7+",
        "8+",
        "9+",
        ":+", // 10
        "J+",
        "Q+",
        "K+",
        "A,", // ♦
        "2,",
        "3,",
        "4,",
        "5,",
        "6,",
        "7,",
        "8,",
        "9,",
        ":,", // 10
        "J,",
        "Q,",
        "K,",
        "A-", // ♥
        "2-",
        "3-",
        "4-",
        "5-",
        "6-",
        "7-",
        "8-",
        "9-",
        ":-", // 10
        "J-",
        "Q-",
        "K-",
        "A*", // ♠
        "2*",
        "3*",
        "4*",
        "5*",
        "6*",
        "7*",
        "8*",
        "9*",
        ":*", // 10
        "J*",
        "Q*",
        "K*"};

#ifdef FALLBACKASCII
    // club, diamonnd, heart, spade, 
    wchar_t SUITES_SYMBOL[4][10] = {L"\u2663", L"\u2666", L"\u2665", L"\u2660"};
#else
    char SUITES_SYMBOL[4][10] = {"♣", "♦", "♥", "♠"};
#endif
} CardSuites;

class Kartu41
{
private:
    CardSuites suites;
    int mainDeck[52], stackDeck[52];
    int player_score, bot_score, latestCard;

    int rng_card()
    {
        // https://www.geeksforgeeks.org/generating-random-number-range-c/
        int num = (rand() % (52 - 1 + 1)) + 1;
        return num - 1;
    }

    void stack_controller(int mode, int card = 0)
    {
        switch (mode)
        {
        case 0:
            for (int i = 0; i < 52; i++)
            {
                if (this->stackDeck[i] == -1)
                {
                    this->stackDeck[i] = card;
                    this->latestCard = card;
                    break;
                }
            }
            break;
        case 1:
            // Get latest and remove.
            int card_n = -1;
            for (int i = 51; i >= 0; i--)
            {
                if (this->stackDeck[i] != -1)
                {
                    card_n = this->stackDeck[i];
                    this->stackDeck[i] = -1;
                    if (i - 1 < 0)
                    {
                        this->latestCard = -1;
                    }
                    else
                    {
                        this->latestCard = this->stackDeck[i - 1];
                    }
                    break;
                }
            }
            break;
        }
    }
    void card_controller(int player, int mode, int card = 0)
    {
        switch (mode)
        {
        case 0:
            for (int i = 0; i < 5; i++)
            {
                if (player == 0)
                {
                    if (this->playerDeck[i] == -1)
                    {
                        this->playerDeck[i] = card;
                    }
                }
                else if (player == 1)
                {
                    if (this->botDeck[i] == -1)
                    {
                        this->botDeck[i] = card;
                    }
                }
            }
            break;
        case 1:
            if (player == 0)
            {
                this->playerDeck[card] = -1;
            }
            else if (player == 1)
            {
                this->botDeck[card] = -1;
            }
            break;
        }
    }
    void stack_card_to_left(int player)
    {
        switch (player)
        {
        case 0:
        {
#ifdef DEBUGGAME
            printf("Stack player deck to left (before): %d %d %d %d %d\n", this->playerDeck[0], this->playerDeck[1], this->playerDeck[2], this->playerDeck[3], this->playerDeck[4]);
#endif
            int player_data[5] = {-1, -1, -1, -1, -1};
            int player_count = 0;
            for (int i = 0; i < 5; i++)
            {
                if (this->playerDeck[i] != -1)
                {
                    player_data[player_count++] = this->playerDeck[i];
                }
            }
            for (int i = 0; i < 5; i++)
            {
                this->playerDeck[i] = player_data[i];
            }
#ifdef DEBUGGAME
            printf("Stack player deck to left (after): %d %d %d %d %d\n", this->playerDeck[0], this->playerDeck[1], this->playerDeck[2], this->playerDeck[3], this->playerDeck[4]);
#endif
            break;
        }
        case 1:
        {
#ifdef DEBUGGAME
            printf("Stack bot deck to left (before): %d %d %d %d %d\n", this->botDeck[0], this->botDeck[1], this->botDeck[2], this->botDeck[3], this->botDeck[4]);
#endif
            int bot_data[5] = {-1, -1, -1, -1, -1};
            int bot_count = 0;
            for (int j = 0; j < 5; j++)
            {
                if (this->botDeck[j] != -1)
                {
                    bot_data[bot_count++] = this->botDeck[j];
                }
            }
            for (int j = 0; j < 5; j++)
            {
                this->botDeck[j] = bot_data[j];
            }
#ifdef DEBUGGAME
            printf("Stack bot deck to left (after): %d %d %d %d %d\n", this->botDeck[0], this->botDeck[1], this->botDeck[2], this->botDeck[3], this->botDeck[4]);
#endif
            break;
        }
        }
    }

public:
    bool gameover;
    int winner;
    int playerDeck[5], botDeck[5];

    Kartu41(void);

    int draw_card();
    int start_game();

    void player_turn();
    void bot_turn();

    void check_card_stack();
    void print_stack();
    void print_user_card();
};

#endif /* KARTU41_SUITES_H */