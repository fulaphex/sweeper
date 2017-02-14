#include "Main.h"
#include "Board.h"
#include "Search.h"

int curr = 0;
int captures = 0;
int checks = 0;

void Search(Board &state, S8 depth){
	if(depth == 0){
		curr++;
		// state.Display();
		return;
	}

	vector< pair<U8, U8> > moves;
	state.GeneratePseudoLegal(moves);
	int cnt = 0;
	for(const auto &move : moves){
		Board new_state(state.pieces, state.colors, state.side, state.my_king_location, state.opp_king_location, state.castle_rights, state.enpassant);
		new_state.MakeMove(move.first, move.second);
		new_state.Display();
		cout << cnt << "\n";
		cout << (int)move.first << " " << (int)move.second <<  "\n";
		cnt ++;
		if(IsLegal(new_state)){
			if(depth == 1 && (state.pieces[move.second] != EMPTY || (state.pieces[move.first] == PAWN && move.second == state.enpassant))){
				captures++;
				//cout<<captures<<"\n";
				//cout<<(int)move.first<<" "<<(int)move.second<<" "<<(int)state.enpassant<<"\n";
				//new_state.Display();
			}
			if(depth == 1 && new_state.IsAttacked(new_state.my_king_location, (new_state.side^1))){
				checks++;
				// new_state.Display();
			}
			Search(new_state, depth-1);
		}
	}
}

bool IsLegal(Board &state){
	//return true;
	return !state.IsAttacked(state.opp_king_location, state.side);
}
