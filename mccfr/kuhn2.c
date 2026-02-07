#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
	float regret_sum[2];
	float strategy_sum[2];
} Node;

Node node_map[12];

#define GAME_ROOT 0
#define P1_PASS   1
#define P1_BET    2
#define P2_BET    3

#define PASS      0
#define BET       1

#define P1        0
#define P2        1

int get_action(float* strategy) {
	float r;
	
	r = (float)rand() / (float)RAND_MAX;

	if (r < strategy[0])
		return PASS;
	return BET;
}

void get_strategy(float* regret, float* out_strategy) {
	int i;

	float normalize_sum;

	//normalize
	for ( i = 0 ; i < 2; i++ )
		out_strategy[i] = regret[i] <= 0 ? 0 : regret[i];

	normalize_sum = out_strategy[PASS] + out_strategy[BET];

	if ( normalize_sum > 0 ) //there's some regret
		for ( i = 0 ; i < 2; i++)
			out_strategy[i] = out_strategy[i] / normalize_sum;
	else //we want equal strat if we have no fomo!
		for ( i = 0 ; i < 2 ; i++)
			out_strategy[i] = 1.0 / 2.0;
}

int get_node_key(int card, int history) {
	return (card * 4) + history; //4 histroies, 3 cards
}

float mccfr(int history, int p1_card, int p2_card, int traverser) {
	int action_player;
	int action_player_card;
	int is_traverser_turn;
	int node_key;

	Node* current_node;

	float strategy[2] = {0, 0};

	if (history == GAME_ROOT || history == P2_BET) {
		action_player      = P1;
		action_player_card = p1_card;
	}
	else {
		action_player      = P2;
		action_player_card = p2_card;
	}

	is_traverser_turn  = (traverser == action_player);
	
	node_key = get_node_key(action_player_card, history);
	current_node = &node_map[node_key];

	get_strategy(current_node->regret_sum, strategy);
	if (is_traverser_turn) {
		
	}
	else {

	}

	return -1337; //we shouldnt get here lol
}

void main() {

}
