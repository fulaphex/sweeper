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

enum CastleRight {
    CASTLE_WK = 1,
    CASTLE_WQ = 2,
    CASTLE_BK = 4,
    CASTLE_BQ = 8
};

class Board{
public:
	U8 pieces[128];
	U8 colors[128];
	U8 side; //0 - white, 1 - black
	U8 my_king_location;
	U8 opp_king_location;
	U8 castle_rights;
	U8 enpassant;
	
	Board();
	Board(U8 new_pieces[], U8 new_colors[], U8 new_side, U8 new_my_king_location, U8 new_opp_king_location);
	void ClearBoard();
	void StartingPosition();
	void GeneratePseudoLegal(vector< pair<U8, U8> > &moves);
	void MakeMove(U8 src, U8 dst);
	bool IsAttacked(U8 sq, U8 side);
	void Display();
	
private:
	void GeneratePawnMoves(U8 sq, vector< pair<U8, U8> > &moves);
	void GenerateCastles(vector< pair<U8, U8> > &moves);
	bool Attackers(U8 sq, U8 att_side, PieceType piece);
	bool PawnAttackers(U8 sq, U8 att_side);
};

#endif