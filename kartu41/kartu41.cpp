#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#else
#include <ncurses.h>
#endif

#include "kartu41.h"
#include "../extras/extra.h"

#define keyUp 72 // arrow keys
#define keyDown 80
#define keyLeft 75
#define keyRight 77
#define keyEnter 13

// A port of kisanak kartu41 in Python
// to C++ lang

void print_x_times(char ch, int x)
{
    for (int i = 0; i < x; i++)
    {
        printf("%c", ch);
    }
}

int determine_max_and_combine(int dataset[4])
{
    int n_pos = 0;
    int largest = dataset[0];
    int total_final = 0;
    for (int i = 0; i < 4; i++)
    {
        if (dataset[i] == -1)
        {
            dataset[i] == 0;
        }
        if (dataset[i] > largest)
        {
            largest = dataset[i];
            n_pos = i;
        }
    }
    for (int i = 0; i < 4; i++)
    {
        if (i == n_pos)
        {
            total_final += dataset[i];
        }
        else
        {
            total_final -= dataset[i];
        }
    }
    return total_final;
}

Kartu41::Kartu41(void)
{
    srand(time(NULL)); // seed RNGJesus
    this->gameover = false;
    this->winner = -1;

    for (int i = 0; i < 52; i++)
    {
        this->mainDeck[i] = 1;
        this->stackDeck[i] = -1;
    }

    for (int i = 0; i < 5; i++)
    {
        this->botDeck[i] = -1;
        this->playerDeck[i] = -1;
    }

    this->player_score = 0;
    this->bot_score = 0;

    this->latestCard = -1;
}

/*
    Implement Public function
*/
int Kartu41::draw_card()
{
    bool succeed = false;
    int card;
    while (!succeed)
    {
        card = rng_card();
        if (this->mainDeck[card] == 1)
        {
            this->mainDeck[card] = 0;
            succeed = true;
        }
    }
    return card;
}

int Kartu41::start_game()
{
#ifndef DEBUGGAME
    clearScreen();
    setCursorPosition(0, 0);
#endif
    printf("Membagikan kartu...\n");
    for (int i = 0; i < 4; i++)
    {
        this->playerDeck[i] = draw_card();
        this->botDeck[i] = draw_card();
    }
    printf("Memeriksa kartu awal...\n");
    check_card_stack();
    printf("Memulai game...\n");
    while (!gameover)
    {
#ifndef DEBUGGAME
        clearScreen();
        setCursorPosition(0, 0);
#endif
        player_turn();
        check_card_stack();
        if (gameover)
        {
            break;
        }
        for (int i = 0; i < 3; i++)
        {
            printf(".");
            Sleep(250);
        }
#ifndef DEBUGGAME
        clearScreen();
        setCursorPosition(0, 0);
#endif
        bot_turn();
        check_card_stack();
        if (gameover)
        {
            break;
        }
        for (int i = 0; i < 3; i++)
        {
            printf(".");
            Sleep(250);
        }
    }
    if (winner == 0)
    {
        printf("\nPemenangnya adalah: Player!\n");
        printf("Total nilai kartu pemain: %d\n", this->player_score);
        printf("Total nilai kartu bot: %d\n", this->bot_score);
    }
    else if (winner == 1)
    {
        printf("\nPemenangnya adalah: Bot!\n");
        printf("Total nilai kartu bot: %d\n", this->bot_score);
        printf("Total nilai kartu pemain: %d\n", this->player_score);
    }
    else if (winner == 2)
    {
        printf("\nPemenangnya adalah: Seri!\n");
        printf("Total nilai kartu pemain dan bot: %d dan %d\n", this->player_score, this->bot_score);
    }
    return 0;
}

void Kartu41::player_turn()
{
    print_stack();
    printf("\n");
    print_user_card();
    if (this->latestCard != -1)
    {
        int lock = 1;
        while (lock)
        {
            char ds_in;
            printf("Ambil dari (s)tack apa (d)eck? (s/d) -> ");
            scanf(" %c", &ds_in);
            getchar();
            to_lower(&ds_in);
            switch (ds_in)
            {
            case 's':
                card_controller(0, 0, this->latestCard);
                stack_controller(1);
                lock = 0;
                break;
            case 'd':
                card_controller(0, 0, draw_card());
                lock = 0;
                break;
            default:
                printf("Hah gimana?\n");
                break;
            }
        }
    }
    else
    {
        printf("\nMengambil dari deck...\n");
        card_controller(0, 0, draw_card());
    }
    stack_card_to_left(0);
    print_user_card();
    int lock2 = 1;
    while (lock2)
    {
        int card_trash = 0;
        printf("Keluarin kartu ke-");
        scanf("%[^\n]", &card_trash);
        getchar();
        if (card_trash != 0) {
            card_trash -= 48;
        }
#ifdef DEBUGGAME
        printf("\nUser input for card throwing: %d\n", card_trash);
#endif
        if (card_trash >= 1 && card_trash <= 5)
        {
            card_controller(0, 1, card_trash - 1);
            lock2 = 0;
        }
        else
        {
            printf("Yang bener boss... 1-5!\n");
        }
    }
    stack_card_to_left(0);
}

void Kartu41::bot_turn()
{
    printf("Giliran bot!\n");
    int card = draw_card();
    card_controller(1, 0, card);
    int throw_card = (rand() % (5 - 1 + 1)) + 1;
    throw_card--;
#ifdef DEBUGGAME
    printf("Bot throwed card index %d, bot have %d %d %d %d %d on their hand\n", throw_card, this->botDeck[0], this->botDeck[1], this->botDeck[2], this->botDeck[3], this->botDeck[4]);
#endif
    int throwen_card = this->botDeck[throw_card];
    card_controller(1, 1, throw_card);
    stack_controller(0, throwen_card);
    stack_card_to_left(1);
#ifdef DEBUGGAME
    printf("After throwing that card, bot now have %d %d %d %d %d on their hand\n", this->botDeck[0], this->botDeck[1], this->botDeck[2], this->botDeck[3], this->botDeck[4]);
#endif
}

void Kartu41::print_stack()
{
    printf("\nStack:\n");
    if (this->latestCard != -1)
    {
        int n_deck = 0;
        char num = this->suites.pcDecks[this->latestCard][0];
        char suites = this->suites.pcDecks[this->latestCard][1];
        print_x_times('=', 11);
        printf("\n");
        printf("|	  |\n");
        printf("|	  |\n");
        if (num == ':') {
#ifdef FALLBACK_ASCII
            printf("    10%ls\n", this->suites.SUITES_SYMBOL[(int)suites - 42]);
#else
            printf("    10%s\n", this->suites.SUITES_SYMBOL[(int)suites - 42]);
#endif
        } else {
#ifdef FALLBACK_ASCII
            printf("    %c%ls\n", this->suites.SUITES_SYMBOL[(int)suites - 42]);
#else
            printf("    %c%s\n", num, this->suites.SUITES_SYMBOL[(int)suites - 42]);
#endif
        }
        printf("|	  |\n");
        printf("|	  |\n");
        print_x_times('=', 11);
        printf("\n");
    }
    else
    {
        printf("Tidak ada stack yang bisa diambil.\n");
    }
}
void Kartu41::print_user_card()
{
    int amount_to_print = 0;
    for (int i = 0; i < 5; i++)
    {
        if (this->playerDeck[i] != -1)
        {
            amount_to_print++;
        }
    }
#ifdef DEBUGGAME
    printf("Total to print: %d\nKartu ditangan: %d %d %d %d %d\n", amount_to_print, this->playerDeck[0], this->playerDeck[1], this->playerDeck[2], this->playerDeck[3], this->playerDeck[4]);
#endif
    printf("Kartu Tangan:\n");
    for (int i = 0; i < amount_to_print; i++)
    {
        print_x_times('=', 11);
        printf(" ");
    }
    printf("\n");
    if (amount_to_print == 4)
    {
        for (int i = 0; i < 2; i++)
        {
            printf("|	  | ");
            printf("|	      | ");
        }
        printf("\n");
        for (int i = 0; i < 2; i++)
        {
            printf("|	  | ");
            printf("|	      | ");
        }
    }
    else
    {
        for (int i = 0; i < 2; i++)
        {
            printf("|	  | ");
            printf("|	      | ");
        }
        printf("|	  | ");
        printf("\n");
        for (int i = 0; i < 2; i++)
        {
            printf("|	  | ");
            printf("|	      | ");
        }
        printf("|	  | ");
    }
    printf("\n");
    char num1 = this->suites.pcDecks[this->playerDeck[0]][0];
    char suites1 = this->suites.pcDecks[this->playerDeck[0]][1];
    if (num1 == ':') {
#ifdef FALLBACK_ASCII
        printf("    10%ls  ", this->suites.SUITES_SYMBOL[(int)suites - 42]);
#else
        printf("    10%s  ", this->suites.SUITES_SYMBOL[(int)suites1 - 42]);
#endif
    } else {
#ifdef FALLBACK_ASCII
        printf("    %c%ls  ", this->suites.SUITES_SYMBOL[(int)suites - 42]);
#else
        printf("    %c%s  ", num1, this->suites.SUITES_SYMBOL[(int)suites1 - 42]);
#endif
    }
    for (int i = 1; i < amount_to_print; i++)
    {
        char num = this->suites.pcDecks[this->playerDeck[i]][0];
        char suites = this->suites.pcDecks[this->playerDeck[i]][1];
        if (num == ':') {
#ifdef FALLBACK_ASCII
            printf("        10%ls  ", this->suites.SUITES_SYMBOL[(int)suites - 42]);
#else
            printf("        10%s  ", this->suites.SUITES_SYMBOL[(int)suites - 42]);
#endif
        } else {
#ifdef FALLBACK_ASCII
            printf("        %c%ls  ", this->suites.SUITES_SYMBOL[(int)suites - 42]);
#else
            printf("        %c%s  ", num, this->suites.SUITES_SYMBOL[(int)suites - 42]);
#endif
        }
    }
    printf("\n");
    if (amount_to_print == 4)
    {
        for (int i = 0; i < 2; i++)
        {
            printf("|	  | ");
            printf("|	      | ");
        }
        printf("\n");
        for (int i = 0; i < 2; i++)
        {
            printf("|	  | ");
            printf("|	      | ");
        }
    }
    else
    {
        for (int i = 0; i < 2; i++)
        {
            printf("|	  | ");
            printf("|	      | ");
        }
        printf("|	  | ");
        printf("\n");
        for (int i = 0; i < 2; i++)
        {
            printf("|	  | ");
            printf("|	      | ");
        }
        printf("|	  | ");
    }
    printf("\n");
    for (int i = 0; i < amount_to_print; i++)
    {
        print_x_times('=', 11);
        printf(" ");
    }
    printf("\n");
    for (int i = 0; i < amount_to_print; i++)
    {
        printf("    (%d)     ", i + 1);
    }
    printf("\n");
}

void Kartu41::check_card_stack()
{
    int playerSuitesSet[4] = {0, 0, 0, 0};
    for (int i = 0; i < 5; i++)
    {
        char fletter = this->suites.pcDecks[this->playerDeck[i]][0];
        char suites = this->suites.pcDecks[this->playerDeck[i]][1];
        switch (fletter)
        {
        case 'J':
            playerSuitesSet[(int)suites - 42] += 10;
            break;
        case 'Q':
            playerSuitesSet[(int)suites - 42] += 10;
            break;
        case 'K':
            playerSuitesSet[(int)suites - 42] += 10;
            break;
        case 'A':
            playerSuitesSet[(int)suites - 42] += 11;
            break;
        default:
            playerSuitesSet[(int)suites - 42] += ((int)fletter - 48);
            break;
        }
    }
#ifdef DEBUGGAME
    printf("Player Score: %d %d %d %d\n", playerSuitesSet[0], playerSuitesSet[1], playerSuitesSet[2], playerSuitesSet[3]);
#endif
    this->player_score = determine_max_and_combine(playerSuitesSet);
    if (this->player_score >= 41)
    {
        this->winner = 0;
        this->gameover = true;
        return;
    }
    int botSuitesSet[4] = {0, 0, 0, 0};
    for (int i = 0; i < 5; i++)
    {
        char fletter = this->suites.pcDecks[this->botDeck[i]][0];
        char suites = this->suites.pcDecks[this->botDeck[i]][1];
        switch (fletter)
        {
        case 'J':
            botSuitesSet[(int)suites - 42] += 10;
            break;
        case 'Q':
            botSuitesSet[(int)suites - 42] += 10;
            break;
        case 'K':
            botSuitesSet[(int)suites - 42] += 10;
            break;
        case 'A':
            botSuitesSet[(int)suites - 42] += 11;
            break;
        default:
            botSuitesSet[(int)suites - 42] += ((int)fletter - 48);
            break;
        }
    }
#ifdef DEBUGGAME
    printf("Bot Score: %d %d %d %d\n", botSuitesSet[0], botSuitesSet[1], botSuitesSet[2], botSuitesSet[3]);
#endif
    this->bot_score = determine_max_and_combine(botSuitesSet);
    if (this->bot_score >= 41)
    {
        this->winner = 1;
        this->gameover = true;
        return;
    }
    int card_in_deck = 0;
    for (int i = 0; i < 52; i++)
    {
        if (this->mainDeck[i] == 1)
        {
            card_in_deck++;
        }
    }
    if (card_in_deck == 0)
    {
        this->gameover = true;
        // check who have the highest score.
        if (this->player_score == this->bot_score)
        {
            this->winner = 2;
        }
        else if (this->player_score > this->bot_score)
        {
            this->winner = 0;
        }
        else if (this->player_score < this->bot_score)
        {
            this->winner = 1;
        }
    }
}
