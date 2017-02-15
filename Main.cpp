#include "Main.h"
#include "Board.h"
#include "Search.h"

Board board;

int main(){
	//board.TestCastles();
	board.ClearBoard();
	board.StartingPosition();
	//board.TestBoard3();
	// board.MakeMove(E2, E4);
	// board.MakeMove(E7, E5);
	// board.MakeMove(G1, F3);
	// board.MakeMove(B8, C6);
	// board.MakeMove(F1, C4);
	// board.MakeMove(F8, C5);
	// board.MakeMove(C4, F7);
	// board.MakeMove(E8, F7);
	board.MakeMove(MoveType(E2, E4));
	board.MakeMove(MoveType(E7, E5));
	board.MakeMove(MoveType(G1, F3));
	board.MakeMove(MoveType(B8, C6));
	board.MakeMove(MoveType(F1, C4));
	board.MakeMove(MoveType(F8, C5));
	board.MakeMove(MoveType(C4, F7));
	board.MakeMove(MoveType(E8, F7));
	board.Display();
	//cout<<(int)board.enpassant<<"\n";
	Search(board, 1);
	cout<<curr<<" "<<captures<<" "<<checks<<" "<<mates<<" "<<enpassants<<" "<<promotions<<" "<<castles<<"\n";
	return 0;
}
