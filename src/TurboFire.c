#include "Game.h"
#include "Deck.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    int i, players = 2;
    Hand** my_hands = (Hand**) malloc(players * sizeof(Hand*));
    for (i = 0; i < players; i++) {
        my_hands[i] = (Hand*) malloc(sizeof(Hand));
    }
    
    //player 0 pocket aces
    my_hands[0]->cards[0].rank = ACE;
    my_hands[0]->cards[0].suit = CLUBS;
    my_hands[0]->cards[1].rank = KING;
    my_hands[0]->cards[1].suit = SPADES;
    
    //pocket kings p1
    my_hands[1]->cards[0].rank = NINE;
    my_hands[1]->cards[0].suit = HEARTS;
    my_hands[1]->cards[1].rank = NINE;
    my_hands[1]->cards[1].suit = DIAMONDS;
    
    game_init_with_hands(my_hands, players);
    print_hand(0);
    print_hand(1);
    monte_carlo_from_position(2);

    game_free();
    deck_free();
    return 0;
}

