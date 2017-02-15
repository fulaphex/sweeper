#include "Main.h"
#include "Board.h"
#include "Search.h"
#include "Parser.h"

Board board;

int SEARCH_DEPTH = 3;

int main(){
    ios::sync_with_stdio(false);
    cout.setf(ios::unitbuf);
    int time_left, opponent_time_left;
	board.ClearBoard();
	board.StartingPosition();
    string comm, out;
	MoveType move;
    cout << "feature reuse=0\n";
    getline(cin, comm);
    cout << "feature sigint=0\n";
    getline(cin, comm);
    cout << "feature name=sweeper\n";
    getline(cin, comm);
    cout << "feature variants=\"crazyhouse\"\n";
    getline(cin, comm);
    cout << "feature debug=1\n";
    getline(cin, comm);
    cout << "feature done=1\n";
    getline(cin, comm);
    bool move_parsed = false;
    while(true){
        // cout << "# insinde game loop\n";
        getline(cin, comm);
        if(comm == "quit")
            return 0;
        else if(comm == "draw"){
            cout << "offer draw";
        }
        else if(comm.substr(0,5) == "level"){
            // Todo parse level command and time
            continue;
        }
        else if(comm == "post"){
            // Todo parse level command and time
            continue;
        }
        else if(comm.substr(0,4) == "time"){
            time_left = stoi(comm.substr(5));
            cout << "#       my time remaining: " << time_left/100 << "seconds\n";
        }
        else if(comm.substr(0,4) == "otim"){
            opponent_time_left = stoi(comm.substr(5));
            cout << "# opponent time remaining: " << opponent_time_left/100 << "seconds\n";
        }
        else if(comm.length() == 4 || comm.length() == 5){
            int x = int(comm[1]-'1'), y = int(comm[0]-'a'), nx = int(comm[3]-'1'), ny = int(comm[2]-'a');
            // cout  << "# " << x << y << nx << ny << "\n";
			cout << "# comm = '" << comm << "' " << comm.length();
			move = StringToMove(comm);
			cout << move.drop << " " << move.src << " " << move.dst << " " << move.promotion << "\n";
            // if(0 <= min(min(x, nx), min(y, ny)) && 8 > max(max(x, nx), max(y, ny))){
			if(move.dst != 255){
                // cout << "# parsing a move: " << comm << "\n";
				board.MakeMove(move);
                move_parsed = true;
            }
        }
        else{
            // cout << "# nothing to do: \'" << comm << "\' " << comm.length() << " " << move_parsed << "\n";
            continue;
        }
        if(move_parsed){
            // cout << "# making a move\n";
            // print_board();

            move = FindBestMove(board, SEARCH_DEPTH);
			board.MakeMove(move);
			out = MoveToString(move);
            cout << "move " << out << "\n";

            // if(move[0] != '.'){
            // }
            // else{
            //     cout << "resign\n";
            //     return 0;
            // }
            // print_board();
            move_parsed = false;
        }


        // print_board();

        // p = int(comm);
        // while(p--){
        //     cout << p << "\n";
        // }
    }
    return 0;
}

// int main(){
// 	//board.TestCastles();
// 	board.ClearBoard();
// 	board.StartingPosition();
// 	//board.TestBoard3();
// 	board.MakeMove(MoveType(E2, E4));
// 	board.MakeMove(MoveType(E7, E5));
// 	board.MakeMove(MoveType(G1, F3));
// 	board.MakeMove(MoveType(B8, C6));
// 	board.MakeMove(MoveType(F1, C4));
// 	board.MakeMove(MoveType(F8, C5));
// 	board.MakeMove(MoveType(C4, F7));
// 	board.MakeMove(MoveType(E8, F7));
// 	board.Display();
// 	//cout<<(int)board.enpassant<<"\n";
// 	Perft(board, 1);
// 	cout<<curr<<" "<<captures<<" "<<checks<<" "<<mates<<" "<<enpassants<<" "<<promotions<<" "<<castles<<"\n";
//
// 	MoveType x = StringToMove("P@d6");
// 	cout << x.drop << " " << x.src << " " << x.dst << " " << x.promotion << "\n";
//
// 	x = StringToMove("e2e4");
// 	cout << x.drop << " " << x.src << " " << x.dst << " " << x.promotion << "\n";
//
// 	x = StringToMove("e7e8Q");
// 	cout << x.drop << " " << x.src << " " << x.dst << " " << x.promotion << "\n";
//
// 	cout << MoveToString(MoveType(PAWN, 255, E4, EMPTY)) << "\n";
//
// 	cout << MoveToString(MoveType(E2, E4)) << "\n";
//
// 	cout << MoveToString(MoveType(E7, E8, QUEEN)) << "\n";
//
// 	// MoveType best = FindBestMove(board, 1);
// 	// cout<<best.src<<" "<<best.dst<<" "<<best.drop<<" "<<best.promotion<<"\n";
// 	return 0;
// }
