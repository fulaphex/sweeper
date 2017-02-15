#include "Main.h"
#include "Board.h"
#include "Search.h"

Board board;

int main(){
	//board.TestCastles();
	board.ClearBoard();
	board.StartingPosition();
	//board.TestBoard3();
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
	Perft(board, 1);
	cout<<curr<<" "<<captures<<" "<<checks<<" "<<mates<<" "<<enpassants<<" "<<promotions<<" "<<castles<<"\n";
	
	MoveType best = FindBestMove(board, 1);
	cout<<best.src<<" "<<best.dst<<" "<<best.drop<<" "<<best.promotion<<"\n";
	return 0;
}
