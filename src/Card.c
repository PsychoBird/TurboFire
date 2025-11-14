#include "Card.h"

static const char* rank_names[] = {
    "A", "2", "3", "4", "5", "6", "7",
    "8", "9", "T", "J", "Q", "K"
};

static const char* suit_names[] = {
    "♣", "♦", "♥", "♠"
};

void print_card(Card card) {
    printf("%s%s\n", rank_names[card.rank], suit_names[card.suit]);
}

