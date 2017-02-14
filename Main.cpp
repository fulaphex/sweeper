#include "Main.h"
#include "Board.h"

Board board;

int main(){
	board.ClearBoard();
	board.StartingPosition();
	vector< pair<U8, U8> > M;
	board.GeneratePseudoLegal(M);
	cout<<M.size()<<"\n";
	for(auto v : M){
		cout<<(int)v.first<<" "<<(int)v.second<<"\n";
	}
	
	return 0;
}