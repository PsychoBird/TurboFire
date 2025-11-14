#include "Game.h"
#include "Deck.h"

#include <stdlib.h>

int players;
Hand** hands;

void game_init(int _players) {
    int i;

    players = _players;
    hands = (Hand**) malloc(players * sizeof(Hand*));
    for (i = 0; i < players; i++) {
        hands[i] = (Hand*) malloc(sizeof(Hand));
    }

    deck_init();
    shuffle_deck();
    for (i = 0; i < players; i++) {
        deal_hand(i);
    }
}

void game_free() {
    int i;
    for (i = 0; i < players; i++) {
        free(hands[i]);
    }
    free(hands);
}

void deal_hand(int player) {
    hands[player]->cards[0] = draw_card();
    hands[player]->cards[1] = draw_card();
}

