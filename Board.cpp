#include "Board.h"

bool slide[5] = { 0, 1, 1, 1, 0 };
S8 vectors_len[5] = { 8, 8, 4, 4, 8 };
S8 move_vector[5][8] = {
    { SW, SOUTH, SE, WEST, EAST, NW, NORTH, NE },
    { SW, SOUTH, SE, WEST, EAST, NW, NORTH, NE },
    { SOUTH, WEST, EAST, NORTH                 },
    { SW, SE, NW, NE                           },
    { -33, -31, -18, -14, 14, 18, 31, 33       }
    };

Board::Board(){}

Board::Board(U8 new_pieces[], U8 new_colors[], U8 new_side, U8 new_my_king_location, U8 new_opp_king_location){
	for(int i=0; i<128; i++)
		pieces[i] = new_pieces[i];
	for(int i=0; i<128; i++)
		colors[i] = new_colors[i];
	side = new_side;
	my_king_location = new_my_king_location;
	opp_king_location = new_opp_king_location;
}

void Board::ClearBoard(){
	for(int i=0; i<128; i++)
		pieces[i] = EMPTY;
	for(int i=0; i<128; i++)
		colors[i] = TRANSPARENT;
}

void Board::StartingPosition(){
	pieces[0] = pieces[7] = ROOK;
	pieces[1] = pieces[6] = KNIGHT;
	pieces[2] = pieces[5] = BISHOP;
	pieces[3] = QUEEN;
	pieces[4] = KING;
	for(int i=0; i<8; i++)
		pieces[16+i] = PAWN;
	for(int i=0; i<8; i++)
		colors[i] = colors[i+16] = WHITE;

	for(int i=0; i<8; i++)
		pieces[112+i] = pieces[i];
	for(int i=0; i<8; i++)
		pieces[96+i] = PAWN;
	for(int i=0; i<8; i++)
		colors[96+i] = colors[112+i] = BLACK;

	side = 0;
	my_king_location = 4;
	opp_king_location = 116;

	Display();
}

void Board::Display(){
	char figures[] = {'K', 'Q', 'R', 'B', 'N', 'P', '.'};

	for(int i=7; i>=0; i--){
		for(int j=0; j<8; j++)
			cout<<(char)(figures[ pieces[16*i+j] ] + (colors[16*i+j] == BLACK)*('a'-'A'));
		cout<<"\n";
	}
	cout<<"\n\n";
}

void Board::GeneratePawnMoves(U8 sq, vector< pair<U8, U8> > &moves){
	//To do - en passant
	if(side == WHITE){
		//regular moves
		if(pieces[sq + NORTH] == EMPTY){
			moves.push_back(make_pair(sq, sq+NORTH));
			if((ROW(sq) == 1) && pieces[sq + NN] == EMPTY)
				moves.push_back(make_pair(sq, sq+NN));
		}
		//To do - promotions
		//captures
		if(IS_SQ(sq+NW) && colors[sq+NW] == (side^1)){
			moves.push_back(make_pair(sq, sq+NW));
		}
		if(IS_SQ(sq+NE) && colors[sq+NE] == (side^1)){
			moves.push_back(make_pair(sq, sq+NE));
		}
	}
	else{//side == BLACK
		//regular moves
		if(pieces[sq + SOUTH] == EMPTY){
			moves.push_back(make_pair(sq, sq+SOUTH));
			if((ROW(sq) == 6) && pieces[sq + SS] == EMPTY)
				moves.push_back(make_pair(sq, sq+SS));
		}
		//To do - promotions
		//captures
		if(IS_SQ(sq+SW) && colors[sq+SW] == (side^1)){
			moves.push_back(make_pair(sq, sq+SW));
		}
		if(IS_SQ(sq+SE) && colors[sq+SE] == (side^1)){
			moves.push_back(make_pair(sq, sq+SE));
		}
	}
}

void Board::GeneratePseudoLegal(vector< pair<U8, U8> > &moves){
	for(S8 i=0; i<8; i++)
		for(S8 j=0; j<8; j++){
			U8 sq = 16*i+j;
			if(colors[sq] == side){
				//To do - castle
				if(pieces[sq] == PAWN)
					GeneratePawnMoves(sq, moves);
				else{
					for(U8 dir=0; dir<vectors_len[ pieces[sq] ]; dir++){
						U8 pos = sq;
						while(true){
							pos = pos + move_vector[ pieces[sq] ][ dir ];
							if(! IS_SQ(pos)) break;
							if(pieces[pos] == EMPTY){
								moves.push_back(make_pair(sq, pos));
							}
							else if(colors[pos] != side){
								moves.push_back(make_pair(sq, pos));
								break;
							}
							else{
								break;
							}
							if(!slide[ pieces[sq] ]) break;
						}
					}
				}
			}
		}
}

void Board::MakeMove(U8 src, U8 dst){
	if(pieces[src] == KING)
		my_king_location = dst;
	pieces[dst] = pieces[src];
	pieces[src] = EMPTY;
	colors[dst] = colors[src];
	colors[src] = TRANSPARENT;
	side = (side^1);
	swap(my_king_location, opp_king_location);
}

bool Board::Attackers(U8 sq, U8 att_side, PieceType piece){
	for(U8 dir=0; dir<vectors_len[ piece ]; dir++){
		U8 pos = sq;
		while(true){
			pos = pos + move_vector[ piece ][ dir ];
			if(! IS_SQ(pos)) break;
			if(pieces[pos] != EMPTY){
				if((colors[pos] == att_side) && (pieces[pos] == piece || (pieces[pos] == QUEEN && (piece == ROOK || piece == BISHOP))))
					return true;
				else
					break;
			}
			if(!slide[ piece ]) break;
		}
	}

	return false;
}

bool Board::PawnAttackers(U8 sq, U8 att_side){
	if(att_side == BLACK){
		return (colors[sq+NW] == att_side && pieces[sq+NW] == PAWN) || (colors[sq+NE] == att_side && pieces[sq+NE] == PAWN);
	}
	else{
		return (colors[sq+SW] == att_side && pieces[sq+SW] == PAWN) || (colors[sq+SE] == att_side && pieces[sq+SE] == PAWN);
	}
}

bool Board::IsAttacked(U8 sq, U8 att_side){
	return Attackers(sq, att_side, KING) || Attackers(sq, att_side, ROOK) || Attackers(sq, att_side, BISHOP) || Attackers(sq, att_side, KNIGHT) || PawnAttackers(sq, att_side);
}
