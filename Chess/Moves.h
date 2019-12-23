#pragma once

#include <vector>
#include "Piece.h"
#include "Board.h"

class Moves
{
public:
	void promote(std::vector<Piece*>& pieces, Piece*& pawn, int indx, Board& board);
	bool check(std::vector<Piece*> pieces, position, Board& board);
	bool checkMate(std::vector<Piece*> pieces, Piece* king, Board& board);
	void move(position from, position to, std::vector<Piece*>& p1, std::vector<Piece*>& p2, Board& board);
	void updateCheckFlag(bool& check, position& pos, std::vector<Piece*>& p1, std::vector<Piece*>& p2, Board& board);
	void updateCheckMateFlag(bool& checkMate, position& pos, std::vector<Piece*>& p1, std::vector<Piece*>& p2, Board& board);
};