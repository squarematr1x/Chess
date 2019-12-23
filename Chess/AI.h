#pragma once

#include <vector>
#include "Piece.h"
#include "Board.h"

class AI
{
private:
	position m_from{ 0, 0 };
	position m_to{ 0, 0 };

	Board m_tempBoard;

public:
	AI(Board& board)
	{
		m_tempBoard.copyBoard(board);
	}

	std::vector<position> move(std::vector<Piece*>& pieces1, std::vector<Piece*>& pieces2, Board &board);
	std::vector<position> randomMove(std::vector<Piece*>& pieces, Board& board);

	int minMax(int depth, int alpha, int beta, bool maximizingPlayer, std::vector<Piece*>& pieces1, std::vector<Piece*>& pieces2, Board& board);
	int min(int a, int b);
	int max(int a, int b);
	int evaluate(std::vector<Piece*>& pieces, bool maximizing, Board& board);

	void updatePos(position from, position to);

	bool ableToMove(Piece*& piece, Board &board);

	Board& getBoard() { return m_tempBoard; }
};