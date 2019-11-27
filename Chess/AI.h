#pragma once

#include <vector>
#include "Piece.h"

class AI
{
private:
	int m_wFrom1;
	int m_wFrom2;
	int m_wTo1;
	int m_wTo2;
	int m_bFrom1;
	int m_bFrom2;
	int m_bTo1;
	int m_bTo2;

	Board m_tempBoard;

public:
	AI(Board& board)
		: m_wFrom1(0), m_wFrom2(0), m_wTo1(0), m_wTo2(0), m_bFrom1(0), m_bFrom2(0), m_bTo1(0), m_bTo2(0)
	{
		m_tempBoard.copyBoard(board);
	}

	std::vector<int> move(std::vector<Piece*>& pieces1, std::vector<Piece*>& pieces2, Board &board);
	std::vector<int> randomMove(std::vector<Piece*>& pieces, Board& board);
	std::vector<int> bestMove(std::vector<Piece*>& pieces, Board& board);

	int minMax(int pos1, int pos2, int depth, bool maximizingPlayer, std::vector<Piece*>& pieces1, std::vector<Piece*>& pieces2, Board& board);
	int min(int a, int b);
	int max(int a, int b);

	int evaluate(int pos1, int pos2, std::vector<Piece*>& pieces, bool maximizing, Board& board);

	bool ableToMove(Piece*& piece, Board &board);
	Board& getBoard() { return m_tempBoard; }
};