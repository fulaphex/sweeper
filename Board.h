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

enum CastleRight{
    CASTLE_WK = 1,
    CASTLE_WQ = 2,
    CASTLE_BK = 4,
    CASTLE_BQ = 8
};

enum SquareCoor{
    A1=0  , B1, C1, D1, E1, F1, G1, H1,
    A2=16 , B2, C2, D2, E2, F2, G2, H2,
    A3=32 , B3, C3, D3, E3, F3, G3, H3,
    A4=48 , B4, C4, D4, E4, F4, G4, H4,
    A5=64 , B5, C5, D5, E5, F5, G5, H5,
    A6=80 , B6, C6, D6, E6, F6, G6, H6,
    A7=96 , B7, C7, D7, E7, F7, G7, H7,
    A8=112, B8, C8, D8, E8, F8, G8, H8
};

struct MoveType{
	PieceType drop;
	U8 src;
	U8 dst;
	PieceType promotion;

	MoveType(U8 x, U8 y){
		drop = EMPTY;
		src = x;
		dst = y;
		promotion = EMPTY;
	}

	MoveType(U8 x, U8 y, PieceType piece){
		drop = EMPTY;
		src = x;
		dst = y;
		promotion = piece;
	}

	MoveType(PieceType d, U8 x, U8 y, PieceType piece){
		// cout << d;
		drop = d;
		src = x;
		dst = y;
		promotion = piece;
	}
};

class Board{
public:
	U8 pieces[128];
	U8 colors[128];
	U8 primal[128];
	U8 white_stash[6];
	U8 black_stash[6];
	U8 piece_count[2][6];
	U8 side; //0 - white, 1 - black
	U8 my_king_location;
	U8 opp_king_location;
	U8 castle_rights;
	U8 enpassant;

	Board();
	Board(Board &b);
	void ClearBoard();
	void StartingPosition();
	void GeneratePseudoLegal(vector< MoveType > &moves);
	void MakeMove(MoveType move);
	bool IsAttacked(U8 sq, U8 side);
	bool IsLegal();
	void Display();
	void test();
	void TestCastles();
	void TestBoard3();
	void TestBoard4();

private:
	void setpos(SquareCoor a, PieceType x, PieceColor y);
	void GenerateDrops(U8 sq, vector<MoveType> &moves);
	void GeneratePawnMoves(U8 sq, vector< MoveType > &moves);
	void GenerateCastles(vector< MoveType > &moves);
	bool Attackers(U8 sq, U8 att_side, PieceType piece);
	bool PawnAttackers(U8 sq, U8 att_side);
	void inline SwapSquares(U8 src, U8 dst);
};

#endif
