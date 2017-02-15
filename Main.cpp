#include "Main.h"
#include "Board.h"
#include "Search.h"

Board board;

int main(){
	//board.TestCastles();
	board.ClearBoard();
	board.StartingPosition();
	//board.TestBoard3();
	//board.MakeMove(E2, E4);
	board.Display();
	//cout<<(int)board.enpassant<<"\n";
	Search(board, 5);
	cout<<curr<<" "<<captures<<" "<<checks<<" "<<mates<<" "<<enpassants<<"\n";
	return 0;
}
