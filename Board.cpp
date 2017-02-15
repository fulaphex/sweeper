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

Board::Board(Board &b){
    copy(b.pieces, b.pieces+128, pieces);
    copy(b.colors, b.colors+128, colors);
    copy(b.primal, b.primal+128, primal);
    copy(b.white_stash, b.white_stash+6 , white_stash);
    copy(b.black_stash, b.black_stash+6 , black_stash);
    side = b.side;
    my_king_location = b.my_king_location;
    opp_king_location = b.opp_king_location;
    enpassant = b.enpassant;
    castle_rights = b.castle_rights;
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

	for(int i=0; i<8; i++)
		primal[i] = 1;
	for(int i=112; i<120; i++)
		primal[i] = 1;

    for(int i = 0; i < 6; i++)
        white_stash[i] = black_stash[i] = 0;

	side = 0;

	my_king_location = 4;
	opp_king_location = 116;

	castle_rights = 15;//2^4-1
	enpassant = -1;
	// Display();
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

void Board::GeneratePawnMoves(U8 sq, vector< MoveType > &moves){
	if(side == WHITE){
		//regular moves
		if(pieces[sq + NORTH] == EMPTY){
			if(ROW(sq) == 6){
				for(int p = QUEEN; p!=PAWN; p++)
					moves.push_back(MoveType(sq, sq+NORTH, (PieceType)p));
			}
			else
				moves.push_back(MoveType(sq, sq+NORTH));
			if((ROW(sq) == 1) && pieces[sq + NN] == EMPTY)
				moves.push_back(MoveType(sq, sq+NN));
		}
		//captures
		if(IS_SQ(sq+NW) && (colors[sq+NW] == (side^1) || enpassant == sq+NW)){
			if(ROW(sq) == 6){
				for(int p = QUEEN; p!=PAWN; p++)
					moves.push_back(MoveType(sq, sq+NW, (PieceType)p));
			}
			else
				moves.push_back(MoveType(sq, sq+NW));
		}
		if(IS_SQ(sq+NE) && (colors[sq+NE] == (side^1) || enpassant == sq+NE)){
			if(ROW(sq) == 6){
				for(int p = QUEEN; p!=PAWN; p++)
					moves.push_back(MoveType(sq, sq+NE, (PieceType)p));
			}
			else
				moves.push_back(MoveType(sq, sq+NE));
		}
	}
	else{//side == BLACK
		//regular moves
		if(pieces[sq + SOUTH] == EMPTY){
			if(ROW(sq) == 1){
				for(int p = QUEEN; p!=PAWN; p++)
					moves.push_back(MoveType(sq, sq+SOUTH, (PieceType)p));
			}
			else
				moves.push_back(MoveType(sq, sq+SOUTH));
			if((ROW(sq) == 6) && pieces[sq + SS] == EMPTY)
				moves.push_back(MoveType(sq, sq+SS));
		}
		//captures
		if(IS_SQ(sq+SW) && (colors[sq+SW] == (side^1) || enpassant == sq+SW)){
			if(ROW(sq) == 1){
				for(int p = QUEEN; p!=PAWN; p++)
					moves.push_back(MoveType(sq, sq+SW, (PieceType)p));
			}
			else
				moves.push_back(MoveType(sq, sq+SW));
		}
		if(IS_SQ(sq+SE) && (colors[sq+SE] == (side^1) || enpassant == sq+SE)){
			if(ROW(sq) == 1){
				for(int p = QUEEN; p!=PAWN; p++)
					moves.push_back(MoveType(sq, sq+SE, (PieceType)p));
			}
			else
				moves.push_back(MoveType(sq, sq+SE));
		}
	}
}

void Board::GenerateCastles(vector< MoveType > &moves){
	if(side == WHITE){
		if(castle_rights & CASTLE_WK){
			if(pieces[F1] == EMPTY && pieces[G1] == EMPTY && !IsAttacked(E1, (side^1)) && !IsAttacked(F1, (side^1))) //&& !IsAttacked(G1, (side^1)) - I will check that anyway
				moves.push_back(MoveType(E1, G1));
		}
		if(castle_rights & CASTLE_WQ){
			if(pieces[B1] == EMPTY && pieces[C1] == EMPTY && pieces[D1] == EMPTY && !IsAttacked(E1, (side^1)) && !IsAttacked(D1, (side^1)))//&& !IsAttacked(C1, (side^1)) - I will check that anyway
				moves.push_back(MoveType(E1, C1));
		}
	}
	else{
		if(castle_rights & CASTLE_BK){
			if(pieces[F8] == EMPTY && pieces[G8] == EMPTY && !IsAttacked(E8, (side^1)) && !IsAttacked(F8, (side^1))) //&& !IsAttacked(G8, (side^1)) - I will check that anyway
				moves.push_back(MoveType(E8, G8));
		}
		if(castle_rights & CASTLE_BQ){
			if(pieces[B8] == EMPTY && pieces[C8] == EMPTY && pieces[D8] == EMPTY && !IsAttacked(E8, (side^1)) && !IsAttacked(D8, (side^1)))//&& !IsAttacked(C8, (side^1)) - I will check that anyway
				moves.push_back(MoveType(E8, C8));
		}
	}
}

void Board::GeneratePseudoLegal(vector< MoveType > &moves){
	GenerateCastles(moves);
	for(S8 i=0; i<8; i++)
		for(S8 j=0; j<8; j++){
			U8 sq = (U8)(16*i+j);
			if(colors[sq] == side){
				if(pieces[sq] == PAWN)
					GeneratePawnMoves(sq, moves);
				else{
					for(U8 dir=0; dir<vectors_len[ pieces[sq] ]; dir++){
						U8 pos = sq;
						while(true){
							pos = pos + (U8)move_vector[ pieces[sq] ][ dir ];
							if(! IS_SQ(pos)) break;
							if(pieces[pos] == EMPTY){
								moves.push_back(MoveType(sq, pos));
							}
							else if(colors[pos] != side){
								moves.push_back(MoveType(sq, pos));
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

void inline Board::SwapSquares(U8 src, U8 dst){
	pieces[dst] = pieces[src];
	pieces[src] = EMPTY;
	colors[dst] = colors[src];
	colors[src] = TRANSPARENT;
    primal[dst] = primal[src];
    primal[src] = 0;
}

void Board::TestCastles(){
	ClearBoard();
	castle_rights = 15;
	side = BLACK;
	pieces[E8] = KING;
	colors[E8] = BLACK;
	pieces[A8] = ROOK;
	colors[A8] = BLACK;
	pieces[H8] = ROOK;
	colors[H8] = BLACK;

	pieces[D6] = BISHOP;
	colors[D6] = WHITE;

	vector< MoveType > M;
	Display();
	GenerateCastles(M);
	cout<<M.size()<<"\n";
}

void Board::MakeMove(MoveType move){
	//cout<<"MakeMove: "<<(int)src<<" "<<(int)dst<<"\n";
	U8 src = move.src, dst = move.dst, promotion = move.promotion;
	if(pieces[src] == KING){
		my_king_location = dst;

		if(colors[src] == WHITE)
			castle_rights &= (U8)(~(CASTLE_WK&CASTLE_WQ));
		else
			castle_rights &= (U8)(~(CASTLE_BK&CASTLE_BQ));

		if(dst - src == 2){//short castle
			SwapSquares(dst+1, dst-1);
		}
		else if(src - dst == 2){//long castle
			SwapSquares(dst-2, dst+1);
		}
	}

	//Castle rights if rook moves
	if(src == H1 && pieces[H1] == ROOK && colors[H1] == WHITE)
		castle_rights &= (U8)(~CASTLE_WK);
	if(src == A1 && pieces[A1] == ROOK && colors[A1] == WHITE)
		castle_rights &= (U8)(~CASTLE_WQ);
	if(src == H8 && pieces[H8] == ROOK && colors[H8] == BLACK)
		castle_rights &= (U8)(~CASTLE_BK);
	if(src == A8 && pieces[A8] == ROOK && colors[A8] == BLACK)
		castle_rights &= (U8)(~CASTLE_BQ);
	//cout<<(pieces[src] == PAWN)<<" "<<(int)dst<<" "<<(int)enpassant<<"\n";
	if(pieces[src] == PAWN){
		//Make en passant
		if(dst == enpassant){
            if(side == WHITE)
                white_stash[PAWN]++;
            else
                black_stash[PAWN]++;
			pieces[dst+(side==WHITE ? SOUTH : NORTH)] = EMPTY;
			//cout<<"jolo\n";
		}

		//En passant rights
		enpassant = -1;
		//cout<<(int)dst<<" "<<(int)src<<"\n";
		if((S8)dst-(S8)src == NN)
			enpassant = src+NORTH;
		if((S8)dst-(S8)src == SS)
			enpassant = src+SOUTH;
		//cout<<(int)enpassant<<"\n";

		//Promotion
		if((ROW(dst) == 0) || (ROW(dst) == 7))
			pieces[src] = promotion;
	}
	else
		enpassant = -1;
    if(pieces[dst] != EMPTY){
        if(side == WHITE){
            if(primal[dst])
                white_stash[pieces[dst]]++;
            else
                white_stash[PAWN]++;
        }
        else{
            if(primal[dst])
                black_stash[pieces[dst]]++;
            else
                black_stash[PAWN]++;
        }
    }
	SwapSquares(src, dst);

	side = (side^1);
	swap(my_king_location, opp_king_location);
}

bool Board::Attackers(U8 sq, U8 att_side, PieceType piece){
	for(U8 dir=0; dir<vectors_len[ piece ]; dir++){
		U8 pos = sq;
		while(true){
			pos = pos + (U8)move_vector[ piece ][ dir ];
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
		return (IS_SQ(sq+NW) && colors[sq+NW] == att_side && pieces[sq+NW] == PAWN) || (IS_SQ(sq+NE) && colors[sq+NE] == att_side && pieces[sq+NE] == PAWN);
	}
	else{
		return (IS_SQ(sq+SW) && colors[sq+SW] == att_side && pieces[sq+SW] == PAWN) || (IS_SQ(sq+SE) && colors[sq+SE] == att_side && pieces[sq+SE] == PAWN);
	}
}

bool Board::IsAttacked(U8 sq, U8 att_side){
	return Attackers(sq, att_side, KING) || Attackers(sq, att_side, ROOK) || Attackers(sq, att_side, BISHOP) || Attackers(sq, att_side, KNIGHT) || PawnAttackers(sq, att_side);
}

void Board::TestBoard3(){
	ClearBoard();
	castle_rights = 0;
	side = WHITE;
	my_king_location = A5;
	opp_king_location = H4;
	enpassant = -1;

	pieces[A5] = KING;
	pieces[B5] = PAWN;
	pieces[B4] = ROOK;
	pieces[E2] = PAWN;
	pieces[G2] = PAWN;

	colors[A5] = WHITE;
	colors[B5] = WHITE;
	colors[B4] = WHITE;
	colors[E2] = WHITE;
	colors[G2] = WHITE;

	pieces[C7] = PAWN;
	pieces[D6] = PAWN;
	pieces[F4] = PAWN;
	pieces[H5] = ROOK;
	pieces[H4] = KING;

	colors[C7] = BLACK;
	colors[D6] = BLACK;
	colors[F4] = BLACK;
	colors[H5] = BLACK;
	colors[H4] = BLACK;

	//Display();
}

void Board::setpos(SquareCoor a, PieceType x, PieceColor y){
    pieces[a] = x;
    colors[a] = y;
}

void Board::TestBoard4(){
	ClearBoard();
	castle_rights = 12;
	side = WHITE;
    pieces[A1] = ROOK;
    colors[A1] = WHITE;
    pieces[D1] = QUEEN;
    colors[D1] = WHITE;
    pieces[F1] = ROOK;
    colors[F1] = WHITE;
    pieces[G1] = KING;
    colors[G1] = WHITE;
    pieces[A2] = PAWN;
    colors[A2] = WHITE;
    pieces[D2] = PAWN;
    colors[D2] = WHITE;
    pieces[G2] = PAWN;
    colors[G2] = WHITE;
    pieces[H2] = PAWN;
    colors[H2] = WHITE;
    setpos(F3, KNIGHT, WHITE);

    pieces[A4] = BISHOP;
    colors[A4] = WHITE;
    pieces[B4] = BISHOP;
    colors[B4] = WHITE;
    pieces[C4] = PAWN;
    colors[C4] = WHITE;
    pieces[E4] = PAWN;
    colors[E4] = WHITE;
    pieces[B5] = PAWN;
    colors[B5] = WHITE;
    pieces[H6] = KNIGHT;
    colors[H6] = WHITE;
    pieces[A7] = PAWN;
    colors[A7] = WHITE;

    setpos(B2, PAWN, BLACK);

    setpos(A3, QUEEN, BLACK);
    setpos(A5, KNIGHT, BLACK);
    setpos(B6, BISHOP, BLACK);
    setpos(F6, KNIGHT, BLACK);
    setpos(G6, BISHOP, BLACK);

    setpos(B7, PAWN, BLACK);
    setpos(C7, PAWN, BLACK);
    setpos(D7, PAWN, BLACK);
    setpos(F7, PAWN, BLACK);
    setpos(G7, PAWN, BLACK);
    setpos(H7, PAWN, BLACK);

    setpos(A8, ROOK, BLACK);
    setpos(E8, KING, BLACK);
    setpos(H8, ROOK, BLACK);

    my_king_location = G1;
    opp_king_location = E8;
    enpassant = -1;
}
