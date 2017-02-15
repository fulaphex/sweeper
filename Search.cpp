#include "Main.h"
#include "Board.h"
#include "Search.h"

int curr = 0;
int captures = 0;
int checks = 0;
int mates = 0;
int enpassants = 0;

void Search(Board &state, S8 depth){
	if(depth == 0){
		curr++;
		// state.Display();
		return;
	}

	vector< MoveType > moves;
	state.GeneratePseudoLegal(moves);
	int cnt = 0;
	for(const auto &move : moves){
		Board new_state = state;
		new_state.MakeMove(move);
		//new_state.Display();
		//cout << cnt << "\n";
		//cout << (int)move.src << " " << (int)move.dst <<  "\n";
		//cnt ++;
		if(IsLegal(new_state)){
			cnt++;
			if(depth == 1 && (state.pieces[move.dst] != EMPTY || (state.pieces[move.src] == PAWN && move.dst == state.enpassant))){
				captures++;
				//cout<<captures<<"\n";
				//cout<<(int)move.src<<" "<<(int)move.dst<<" "<<(int)state.enpassant<<"\n";
				//new_state.Display();
			}
			if(depth == 1 && state.pieces[move.src] == PAWN && move.dst == state.enpassant){
				enpassants++;
			}
			if(depth == 1 && new_state.IsAttacked(new_state.my_king_location, (new_state.side^1))){
				checks++;
				// new_state.Display();
			}
			Search(new_state, depth-1);
		}
	}

	if(depth == 1 && cnt == 0)
		mates++;
}

bool IsLegal(Board &state){
	//return true;
	return !state.IsAttacked(state.opp_king_location, state.side);
}
