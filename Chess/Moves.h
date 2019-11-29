#pragma once

#include <vector>
#include "Piece.h"
#include "Board.h"

class Moves
{
public:
	void promote(std::vector<Piece*>& pieces, Piece*& pawn, int indx, Board& board);
	bool check(std::vector<Piece*> pieces, int row, int col, Board& board);
	bool checkMate(std::vector<Piece*> pieces, Piece* king, Board& board);
	void selectAndMove(int row1, int col1, int row2, int col2, std::vector<Piece*>& p1, std::vector<Piece*>& p2, Board& board);
	void updateCheckFlag(bool& check, int& row, int& col, std::vector<Piece*>& pieces1, std::vector<Piece*>& pieces2, Board& board);
	void updateCheckMateFlag(bool& checkMate, int& row, int& col, std::vector<Piece*>& pieces1, std::vector<Piece*>& pieces2, Board& board);
};