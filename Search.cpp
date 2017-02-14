#include "Main.h"
#include "Board.h"
#include "Search.h"

int curr = 0;
int captures = 0;
int checks = 0;

void Search(Board &state, S8 depth){
	if(depth == 0){
		curr++;
		return;
	}

	vector< pair<U8, U8> > moves;
	state.GeneratePseudoLegal(moves);
	for(const auto &move : moves){
		Board new_state(state.pieces, state.colors, state.side, state.my_king_location, state.opp_king_location);
		new_state.MakeMove(move.first, move.second);
		if(IsLegal(new_state)){
			captures += (depth == 1 && state.pieces[move.second] != EMPTY);
			if(depth == 1 && new_state.IsAttacked(new_state.my_king_location, (new_state.side^1))){
				checks++;
				//new_state.Display();
			}
			Search(new_state, depth-1);
		}
	}
}

bool IsLegal(Board &state){
	//return true;
	return !state.IsAttacked(state.opp_king_location, state.side);
}
