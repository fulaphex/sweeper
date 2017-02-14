#ifndef BOARD_H
#define BOARD_H

#include "Main.h"
#include "Math_0x88.h"

enum PieceType{
	KING,
    QUEEN,
    ROOK,
    BISHOP,
    KNIGHT,
    PAWN,
    EMPTY
};

enum PieceColor{
	WHITE = 0,
	BLACK = 1,
	TRANSPARENT = 2
};

class Board{
public:
	U8 pieces[128];
	U8 colors[128];
	//S8 attackedSquares[2][128];
	U8 side; //0 - white, 1 - black
	U8 my_king_location;
	U8 opp_king_location;
	//bool lastWasCastle;
	//bool lastWasEnpassant;
	
	void ClearBoard();
	void StartingPosition();
	void GeneratePawnMoves(U8 sq, vector< pair<U8, U8> > &moves);
	void GeneratePseudoLegal(vector< pair<U8, U8> > &moves);
	void MakeMove(U8 src, U8 dst);
};

#endif