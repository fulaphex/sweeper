#include <cstdio>
#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>
using namespace std;

char board[8][8];

void print_board(){
    for(int i = 0; i < 8; i++){
        cout << "# ";
        for(int j = 0; j < 8; j++){
            cout << board[i][j];
        }
        cout << '\n';
    }
}

string make_move(){
    usleep(rand()%300000 + 700000);
    string move = "....";
    cout << "# CALCULATING A MOVE HERE\n";
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 8; j++){
            if(board[i][j] == 'P' && board[i-1][j] == '.'){
                move[0] = j + 'a';
                move[1] = i + '1';
                move[2] = j + 'a';
                move[3] = i-1 + '1';
                board[i-1][j] = board[i][j];
                board[i][j] = '.';
                return move;
            }
        }
    }
    return move;
}

void init_board(){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            board[i][j] = '.';
        }
    }
    for(int i = 0; i < 8; i++){
        board[1][i] = 'p';
        board[6][i] = 'P';
    }
    board[0][0] = 'r';
    board[0][7] = 'r';
    board[7][0] = 'R';
    board[7][7] = 'R';
    board[0][1] = 'n';
    board[0][6] = 'n';
    board[7][1] = 'N';
    board[7][6] = 'N';
    board[0][2] = 'b';
    board[0][5] = 'b';
    board[7][2] = 'B';
    board[7][5] = 'B';
    board[0][3] = 'k';
    board[0][4] = 'q';
    board[7][3] = 'K';
    board[7][4] = 'Q';
}

int main(){
    ios::sync_with_stdio(false);
    cout.setf(ios::unitbuf);
    int time_left, opponent_time_left;
    init_board();
    string comm, move;
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
        else if(comm.substr(0,4) == "time"){
            time_left = stoi(comm.substr(5));
            cout << "#       my time remaining: " << time_left/100 << "seconds\n";
        }
        else if(comm.substr(0,4) == "otim"){
            opponent_time_left = stoi(comm.substr(5));
            cout << "# opponent time remaining: " << opponent_time_left/100 << "seconds\n";
        }
        else if(comm.length() == 4){
            int x = int(comm[1]-'1'), y = int(comm[0]-'a'), nx = int(comm[3]-'1'), ny = int(comm[2]-'a');
            // cout  << "# " << x << y << nx << ny << "\n";
            if(0 <= min(min(x, nx), min(y, ny)) && 8 > max(max(x, nx), max(y, ny))){
                // cout << "# parsing a move: " << comm << "\n";
                // print_board();
                board[nx][ny] = board[x][y];
                board[x][y] = '.';
                // print_board();
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
            move = make_move();
            if(move[0] != '.'){
                cout << "move " << move << "\n";
            }
            else{
                cout << "resign\n";
                return 0;
            }
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
