#include "Game.h"
#include "Deck.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    game_init(2);
    monte_carlo_from_position(2);

    game_free();
    deck_free();
    return 0;
}

