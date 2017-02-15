#include "Eval.h"

int piece_val[] = {0, 900, 500, 300, 300, 100};

int Eval(Board &state){
	vector< MoveType > moves;
	state.GeneratePseudoLegal(moves);
	vector< MoveType > legal;
	for(auto &move : moves){
		Board new_state = state;
		new_state.MakeMove(move);
		if(new_state.IsLegal())
			legal.push_back(move);
	}
	
	if(legal.size() == 0){
		return (state.IsAttacked(state.my_king_location, state.side^1) ? -INF : 0);
	}
	
	int score = 0;
	for(int p = QUEEN; p!=EMPTY; p++)
		score += (state.piece_count[state.side][p])*(piece_val[p]);
// 	for(int p = QUEEN; p!=EMPTY; p++)
// 		score += state.stash[state.side][p]*pieces_values[p];
	
	for(int p = QUEEN; p!=EMPTY; p++)
		score -= (state.piece_count[state.side^1][p])*(piece_val[p]);
// 	for(int p = QUEEN; p!=EMPTY; p++)
// 		score -= state.stash[state.side][p^1]*pieces_values[p];
	
	return score;
}