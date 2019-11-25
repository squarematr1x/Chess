#pragma once

#include <vector>
#include "Piece.h"

class AI
{
private:
	int bestPos1;
	int bestPos2;

public:
	AI() : bestPos1(0), bestPos2(0)
	{
	}

	void move(std::vector<Piece*> pieces1, std::vector<Piece*> pieces2, Board &board);
	std::vector<int> randomMove(std::vector<Piece*> pieces, Board& board);
	std::vector<int> bestMove(std::vector<Piece*> pieces, Board& board);

	int minMax(int pos1, int pos2, int depth, bool maximizingPlayer, std::vector<Piece*> pieces1, std::vector<Piece*> pieces2, Board& board);
	int min(int a, int b);
	int max(int a, int b);

	int evaluate(int pos1, int pos2, bool maximizing, Board& board);

	bool ableToMove(Piece*& piece, Board &board);
};