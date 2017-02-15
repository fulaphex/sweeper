#include "Parser.h"

MoveType StringToMove(string s){
    // cout << s << "\n";
    if(s.length() == 4){
        if(s[1] == '@'){ // drop move
            // cout << "dropmove '" << s[0] << "'\n";
            U8 nc = s[2] - 'a', nr = s[3] - '1';
            PieceType drop;
            switch(s[0]){
                case 'P':{
                    drop = PAWN;
                    break;
                }
                case 'N':{
                    drop = KNIGHT;
                }
                case 'B':{
                    drop = BISHOP;
                    break;
                }
                case 'R':{
                    drop = ROOK;
                    break;
                }
                case 'Q':{
                    drop = QUEEN;
                    break;
                }
                default:{
                    assert(1 == 0);
                    break;
                }
            }
            return MoveType(drop, (SquareCoor)255, (SquareCoor)SET_SQ(nr, nc), EMPTY);
        }
        else{ // normal move
            U8 c = s[0] - 'a', r = s[1] - '1', nc = s[2] - 'a', nr = s[3] - '1';
            // cout << r << " " << c << " " << nr << " " << nc << "\n";
            return MoveType((SquareCoor)SET_SQ(r, c), (SquareCoor)SET_SQ(nr, nc));
        }
    }
    if(s.length() == 5){
        U8 c = s[0] - 'a', r = s[1] - '1', nc = s[2] - 'a', nr = s[3] - '1';
        PieceType promotion;
        switch(s[4]){
            case 'P':{
                promotion = PAWN;
                break;
            }
            case 'N':{
                promotion = KNIGHT;
                break;
            }
            case 'B':{
                promotion = BISHOP;
                break;
            }
            case 'R':{
                promotion = ROOK;
                break;
            }
            case 'Q':{
                promotion = QUEEN;
                break;
            }
            default:{
                assert(1 == 0);
                break;
            }
        }
        return MoveType((SquareCoor)SET_SQ(r, c), (SquareCoor)SET_SQ(nr, nc), promotion);
    }
}

char piece[6] = {'K', 'Q', 'R', 'B', 'N', 'P'};

string MoveToString(MoveType m){
    string s;
    if(m.drop != EMPTY){
        // drop move
        s = ".@..";
        s[0] = piece[m.drop];
        s[2] = COL(m.dst) + 'a';
        s[3] = ROW(m.dst) + '1';
    }
    else if(m.promotion != EMPTY){
        // promotion move
        s = ".....";
        s[0] = COL(m.src) + 'a';
        s[1] = ROW(m.src) + '1';
        s[2] = COL(m.dst) + 'a';
        s[3] = ROW(m.dst) + '1';
        s[4] = piece[m.promotion];
    }
    else{
        // normal move
        s = "....";
        s[0] = COL(m.src) + 'a';
        s[1] = ROW(m.src) + '1';
        s[2] = COL(m.dst) + 'a';
        s[3] = ROW(m.dst) + '1';
    }
    return s;
}
