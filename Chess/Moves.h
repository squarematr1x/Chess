#pragma once

#include <vector>
#include "Piece.h"
#include "Board.h"

class Moves
{
public:
	static void promote(std::vector<Piece*>& pieces, Piece*& pawn, int indx, Board& board);
	static void move(Position from, Position to, std::vector<Piece*>& pieces1, std::vector<Piece*>& pieces2, Board& board, bool& gameOver);
	static void updateCheckFlag(bool& check, Position& pos, std::vector<Piece*>& pieces1, std::vector<Piece*>& pieces2, Board& board);
	static void updateCheckMateFlag(bool& checkMate, std::vector<Piece*>& pieces1, std::vector<Piece*>& pieces2, Board& board);

	static bool check(std::vector<Piece*> pieces, Position pos, Board& board);
	static bool checkMate(std::vector<Piece*> pieces1, std::vector<Piece*> pieces2, Piece* king, Board& board);

	static bool canKingMove(std::vector<Piece*> pieces, Piece* king, Board& board);
	static bool saveKing(std::vector<Piece*> pieces1, std::vector<Piece*> pieces2, Piece* king, Board& board);
	static bool killAttacker(std::vector<Piece*> pieces1, std::vector<Piece*> pieces2, Piece* king, Board& board);
};
