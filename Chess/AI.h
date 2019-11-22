#pragma once

#include <vector>
#include "Piece.h"

class AI
{
public:
	AI()
	{
	}

	void move(std::vector<Piece*> pieces1, std::vector<Piece*> pieces2, Board &board);
	std::vector<int> randomMove(std::vector<Piece*> pieces1, std::vector<Piece*> pieces2, Board& board);
	std::vector<int> bestMove(std::vector<Piece*> pieces1, std::vector<Piece*> pieces2, Board& board);

	int minMax(int pos1, int pos2, int depth, bool maximizingPlayer, Piece*& piece, Board &board);
	int min(int a, int b);
	int max(int a, int b);

	bool ableToMove(Piece*& piece, Board &board);
};