#include "Main.h"
#include "Board.h"
#include "Search.h"

Board board;

int main(){
	board.ClearBoard();
	board.test();
// 	board.StartingPosition();
	board.Display();
	Search(board, 1);
	cout<<curr<<" "<<captures<<" "<<checks<<"\n";

	return 0;
}
