#include <stdint.h>
#include <string.h>

#include "ranks.h"

uint16_t flush_map[0x2000];
uint16_t rank_map[0x10000];

uint16_t get_rank_map_index(uint64_t hand) {
	uint32_t folded;
	uint16_t id;

	folded = (uint32_t)(hand >> 32) ^ (uint32_t)hand;
	id     = (folded * OMPEVAL_MAGIC) >> 16;

	return id;
}

uint16_t get_flush_map_index(uint64_t hand) {
	uint16_t fc, fd, fh, fs;

	//create 13bit hand signature 
	fc = (hand >> 48) & 0x1FFF ;
	fd = (hand >> 32) & 0x1FFF ;
	fh = (hand >> 16) & 0x1FFF ;
	fs =  hand        & 0x1fff ;

	//__builtin_popcount() is a quick gcc func for counting bits 
	if (__builtin_popcount(fc) >= 5) return fc;
	if (__builtin_popcount(fd) >= 5) return fd;
	if (__builtin_popcount(fh) >= 5) return fh;
	if (__builtin_popcount(fs) >= 5) return fs;

	return 0;
}

uint64_t combine_hand_board(uint64_t hand, uint64_t board) {
	return hand | board;
}

int evaluate(uint64_t hand, uint64_t board) {
	uint32_t id;
	uint64_t combined;

	combined = combine_hand_board(hand, board); 
	
	id = get_flush_map_index(combined);
	if (id)
		return flush_map[id];	
	
	id = get_rank_map_index(combined);
	return rank_map[id];
}

uint16_t calculate_flush_strength_from_hand(uint16_t generated, int *normal_flush_counter) {
	int i;
	uint16_t rank;

	//wheel straight flush
	if ((generated & 0b1000000001111) == 0b1000000001111)
		return STRAIGHT_FLUSH_FLOOR;
	
	// check all other straight flushes
	// we're going to shift the straight flush all the way up to royal
	for (i = 8; i >= 0; i--)
		if (((generated >> i) & 0b11111) == 0b11111) 
			return STRAIGHT_FLUSH_FLOOR + (i + 1);
	
	//all others, we're now counting up
	rank = FLUSH_FLOOR + *normal_flush_counter;

	(*normal_flush_counter)++;

	return rank;
}

uint16_t calculate_rank_strength(int *ranks) {
	return 0;
}

void generate_ranks_recursive(int depth, int start_rank, uint64_t current_hand, int *current_ranks) {
	uint32_t rank_id;
	int rank, count, k;
	uint64_t new_card;

	//base case 7 cards
	if (depth == 7) {
		rank_id = get_rank_map_index(current_hand);

		//check if already populated
		if (rank_map[rank_id])
			return;

		rank_map[rank_id] = calculate_rank_strength(current_ranks);
	}

	for (rank = start_rank; rank <= 12; r++) {
		count = 0;

		for (k = 0; k < depth; k++)
			if (current_ranks[k] == rank)
				count++;

		// we cant have five of a kind
		if (count >= 4)
			continue; 

		current_ranks[depth] = rank;

		new_card = (1ULL << (rank + (16 * (depth % 4))));

		generate_ranks_recursive(depth + 1, rank, current_hand | new_card, current_ranks);
	}
}

void init_rank_map() {
	int rank_storage[7];

	//no zero sets in recurse, safety
	memset(rank_map, 0, sizeof(rank_map));

	generate_ranks_recursive(0, 0, 0, rank_storage);
}

void init_flush_map() {
	int count, normal_flush_counter, i;

	normal_flush_counter = 0;
	for (i = 0; i < 0x2000; i++) {
		count = __builtin_popcount(i);
		if (count == 5) 
			flush_map[i] = calculate_flush_strength_from_hand(i, &normal_flush_counter);
		else if (count > 5)
			// a fun hack to set 6/7 card hand to its 5 card hand value
			// ex: B:AdQdJdTd3s H:Kd3d will be hashed to diff indeces with but same result as AdKdQdJdTd 
			flush_map[i] = flush_map[i & (i - 1)]; 
		else
			flush_map[i] = 0; // non flush
	}
}



 
