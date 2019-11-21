#pragma once

#include <vector>
#include "Piece.h"

class AI
{
private:
	int m_blackScore;
	int m_whiteScore;

public:
	AI() : m_blackScore(-1290), m_whiteScore(1290)
	{
	}

	void move(std::vector<Piece*> pieces1, std::vector<Piece*> pieces2, Board &board);
	std::vector<int> testMove(std::vector<Piece*> pieces1, std::vector<Piece*> pieces2, Board& board);
	std::vector<int> bestMove(std::vector<Piece*> pieces1, std::vector<Piece*> pieces2, Board& board);

	int minMax(int pos1, int pos2, int depth, bool maximizingPlayer, Piece*& piece, Board &board);
	int min(int a, int b);
	int max(int a, int b);

	bool ableToMove(Piece*& piece, Board &board);
};