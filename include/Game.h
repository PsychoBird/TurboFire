#ifndef GAME_H
#define GAME_H

#include "Card.h"

typedef struct Hand {
    Card cards[2];
} Hand;

typedef struct Board {
    Card flop[3];
    Card turn;
    Card river;
} Board;

extern Hand** hands;
extern int players;

void game_init(int);
void deal_hand(int);

#endif /* GAME_H */

