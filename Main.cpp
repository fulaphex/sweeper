#include "Main.h"
#include "Board.h"
#include "Search.h"

Board board;

int main(){
	board.ClearBoard();
	board.test();

	Board x = board;

	board.Display();
	x.Display();
// 	board.StartingPosition();
	if(x.enpassant != board.enpassant){
		cout << (int)x.enpassant << " " << (int)board.enpassant << "\n";
		cout << "fucked up copy constructor";
	}
	if(x.castle_rights != board.castle_rights){
		cout << (int)x.castle_rights << " " << (int)board.castle_rights << "\n";
		cout << "fucked up copy constructor";
	}
	if(x.my_king_location != board.my_king_location){
		cout << (int)x.my_king_location << " " << (int)board.my_king_location << "\n";
		cout << "fucked up copy constructor";
	}
	if(x.opp_king_location != board.opp_king_location){
		cout << (int)x.opp_king_location << " " << (int)board.opp_king_location << "\n";
		cout << "fucked up copy constructor";
	}
	// Search(board, 1);
	cout<<curr<<" "<<captures<<" "<<checks<<"\n";

	return 0;
}
