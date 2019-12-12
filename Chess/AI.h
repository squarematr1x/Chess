#pragma once

#include <vector>
#include "Piece.h"
#include "Board.h"

class AI
{
private:
	int m_from1;
	int m_from2;
	int m_to1;
	int m_to2;

	Board m_tempBoard;

public:
	AI(Board& board)
		: m_from1(0), m_from2(0), m_to1(0), m_to2(0)
	{
		m_tempBoard.copyBoard(board);
	}

	std::vector<int> move(std::vector<Piece*>& pieces1, std::vector<Piece*>& pieces2, Board &board);
	std::vector<int> randomMove(std::vector<Piece*>& pieces, Board& board);
	std::vector<int> bestMove(std::vector<Piece*>& pieces, Board& board);

	int minMax(int depth, int alpha, int beta, bool maximizingPlayer, std::vector<Piece*>& pieces1, std::vector<Piece*>& pieces2, Board& board);
	int min(int a, int b);
	int max(int a, int b);

	int evaluate(std::vector<Piece*>& pieces, bool maximizing, Board& board);
	void updatePos(int from1, int from2, int to1, int to2);

	bool ableToMove(Piece*& piece, Board &board);
	Board& getBoard() { return m_tempBoard; }
};