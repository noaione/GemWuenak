#ifndef KARTU41_SUITES_H
#define KARTU41_SUITES_H

typedef struct CardSuites
{
    char fullDecks[52][10] = {
        "A♣",
        "2♣",
        "3♣",
        "4♣",
        "5♣",
        "6♣",
        "7♣",
        "8♣",
        "9♣",
        "10♣",
        "J♣",
        "Q♣",
        "K♣",
        "A♦",
        "2♦",
        "3♦",
        "4♦",
        "5♦",
        "6♦",
        "7♦",
        "8♦",
        "9♦",
        "10♦",
        "J♦",
        "Q♦",
        "K♦",
        "A♥",
        "2♥",
        "3♥",
        "4♥",
        "5♥",
        "6♥",
        "7♥",
        "8♥",
        "9♥",
        "10♥",
        "J♥",
        "Q♥",
        "K♥",
        "A♠",
        "2♠",
        "3♠",
        "4♠",
        "5♠",
        "6♠",
        "7♠",
        "8♠",
        "9♠",
        "10♠",
        "J♠",
        "Q♠",
        "K♠"
    };
};

// Game utama
int kartu41_game();

#endif /* KARTU41_SUITES_H */