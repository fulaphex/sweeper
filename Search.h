#ifndef SEARCH_H
#define SEARCH_H

extern int curr;
void Perft(Board &state, S8 depth);
int Search(Board &state, S8 depth);
MoveType BestMove(Board &state, S8 depth);
MoveType FindBestMove(Board &state, S8 depth);

#endif