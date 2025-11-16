#ifndef CARD_H
#define CARD_H

#include <stdio.h>
#include <time.h>

#define CARD_COUNT 13
#define SUIT_COUNT 4

typedef enum {
    ACE = 0,
    TWO = 1,
    THREE = 2,
    FOUR = 3,
    FIVE = 4,
    SIX = 5,
    SEVEN = 6,
    EIGHT = 7,
    NINE = 8,
    TEN = 9,
    JACK = 10,
    QUEEN = 11,
    KING = 12,
} Rank;

typedef enum {
    CLUBS = 0,
    DIAMONDS = 1,
    HEARTS = 2,
    SPADES = 3,
} Suit;

typedef struct Card {
    Rank rank;
    Suit suit;
} Card;

extern const char* rank_names[];
extern const char* suit_names[];

void print_card(Card card);

#endif /* CARD_H */

