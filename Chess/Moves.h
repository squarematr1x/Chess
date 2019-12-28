#pragma once

#include <vector>
#include "Piece.h"
#include "Board.h"

class Moves
{
public:
	void promote(std::vector<Piece*>& pieces, Piece*& pawn, int indx, Board& board);
	bool check(std::vector<Piece*> pieces, Position, Board& board);
	bool checkMate(std::vector<Piece*> pieces, Piece* king, Board& board);
	void move(Position from, Position to, std::vector<Piece*>& pieces1, std::vector<Piece*>& pieces2, Board& board);
	void updateCheckFlag(bool& check, Position& pos, std::vector<Piece*>& pieces1, std::vector<Piece*>& pieces2, Board& board);
	void updateCheckMateFlag(bool& checkMate, Position& pos, std::vector<Piece*>& pieces1, std::vector<Piece*>& pieces2, Board& board);
};
