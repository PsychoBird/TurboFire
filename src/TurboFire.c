#include "Deck.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    deck_init();
    printf("Testing: Card 0 is ");
    print_card(*deck->cards[0]);
    shuffle_deck();
    print_deck();
    deck_free();
    return 0;
}

