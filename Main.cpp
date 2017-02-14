#include "Main.h"
#include "Board.h"
#include "Search.h"

Board board;

int main(){
	board.ClearBoard();
	board.StartingPosition();
	Search(board, 5);
	cout<<curr<<" "<<captures<<" "<<checks<<"\n";
	
	return 0;
}