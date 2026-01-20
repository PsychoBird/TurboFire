#ifndef RANKS_H
#define RANKS_H

#include <stdint.h>

const uint64_t OMPEVAL_MAGIC        = 0xE91AAA35U;

const uint16_t HIGH_CARD_FLOOR      = 1;    // + 1277 | (13 choose 5) - 10 straights
const uint16_t ONE_PAIR_FLOOR       = 1278; // + 2860 | (12 choose 3) * 13
const uint16_t TWO_PAIR_FLOOR       = 4138; // + 858  | (13 choose 2) * 11
const uint16_t TRIPS_FLOOR          = 4996; // + 858  | (12 choose 2) * 13
const uint16_t STRAIGHT_FLOOR       = 5864; // + 10   | (wheel straight -> broadway straight)
const uint16_t FLUSH_FLOOR          = 5864; // + 1277 | (13 choose 5) - 10 straight flushes
const uint16_t FULL_HOUSE_FLOOR     = 7174; // + 156  | 13 * 12 full house combos
const uint16_t QUADS_FLOOR          = 7297; // + 156  | 13 * 12 quads combos
const uint16_t STRAIGHT_FLUSH_FLOOR = 7453; // + 10   | (wheel straight flush -> royal)
const uint16_t ROYAL_FLUSH          = 7463; // CEILING 

extern uint16_t flush_map[0x2000];
extern uint16_t rank_map[0x10000];

int      evaluate(uint64_t hand, uint64_t board);
void     init_flush__map();
void     init_rank_map();

#endif
