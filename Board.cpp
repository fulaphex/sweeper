#include<bits/stdc++.h>
#include "0x88_math.h"
using namespace std;

#define U64 unsigned long long int
#define U32 unsigned int
#define U16 unsigned short int
#define U8 unsigned char
#define S64 long long int
#define S32 int
#define S16 short int
#define S8 char

enum PieceType{ //blacky = 8
	EMPTY,
	PAWN,
	KNIGHT,
	BISHOP,
	ROOK,
	QUEEN,
	KING,
};

bool slide[5] = { 0, 1, 1, 1, 0 };
S8 vectors[5] = { 8, 8, 4, 4, 8 };
S8 vector[5][8] = {
    { SW, SOUTH, SE, WEST, EAST, NW, NORTH, NE },
    { SW, SOUTH, SE, WEST, EAST, NW, NORTH, NE },
    { SOUTH, WEST, EAST, NORTH                 },
    { SW, SE, NW, NE                           },
    { -33, -31, -18, -14, 14, 18, 31, 33       }
    };


enum PieceColor{
	WHITE = 0,
	BLACK = 1
};

struct Board{
	U8 pieces[128];
	U8 colors[128];
	S8 attackedSquares[2][128];
	U8 side; //0 - white, 1 - black
	U8 myKingLocation;
	U8 oppKingLocation;
	//bool lastWasCastle;
	//bool lastWasEnpassant;
};

Board board;

void clearBoard(){
	for(int i=0; i<128; i++)
		board.pieces[i] = EMPTY;
	//To do - attacked squares
}

int main(){
	
	return 0;
}