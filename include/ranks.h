#ifndef RANKS_H
#define RANKS_H

#include <stdint.h>

const uint64_t OMPEVAL_MAGIC        = 0xE91AAA35U;

const uint16_t STRAIGHT_FLUSH_FLOOR = 7453;
const uint16_t FLUSH_FLOOR          = 5864;

extern uint16_t flush_map[0x2000];
extern uint16_t rank_map[0x10000];

int      evaluate(uint64_t hand, uint64_t board);
void     init_flush__map();

#endif
