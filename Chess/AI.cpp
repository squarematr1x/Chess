#include <climits>  
#include <time.h>
#include "AI.h"

std::vector<Position> AI::move(std::vector<Piece*>& pieces1, std::vector<Piece*>& pieces2, Board& board)
{
	int alpha = INT_MIN;
	int beta = INT_MAX;

	int depth = 2;
	minMax(depth, alpha, beta, MinMaxPlayer::MINIMIZING, pieces1, pieces2, board);

	std::vector<Position> positions;
	positions.resize(2);

	positions[0] = m_from;
	positions[1] = m_to;

	return positions;
}

std::vector<Position> AI::randomMove(std::vector<Piece*>& pieces, Board& board)
{
	std::vector<Position> positions;
	positions.resize(2);

	int rdm;
	int boardSize = 8;
	bool found = false;

	while (1)
	{
		srand((unsigned int) time(nullptr));
		rdm = rand() % pieces.size();
		if (ableToMove(pieces[rdm], board))
			break;
	}

	for (int i = 0; i < boardSize; i++)
	{
		if (!found)
		{
			for (int j = 0; j < boardSize; j++)
			{

				if (pieces[rdm]->canMove(Position{ i, j }, board))
				{
					positions[0] = pieces[rdm]->getPos();
					positions[1] = Position{ i, j };
					found = true;
					break;
				}
			}
		}
		else
			break;
	}
	return positions;
}

bool AI::ableToMove(Piece*& piece, Board& board)
{
	int boardSize = 8;

	for (int i = 0; i < boardSize; i++)
	{
		for (int j = 0; j < boardSize; j++)
		{
			if (piece->canMove(Position{ i, j }, board))
				return true;
		}
	}
	return false;
}

int AI::minMax(int depth, int alpha, int beta, MinMaxPlayer player, std::vector<Piece*>& pieces1, std::vector<Piece*>& pieces2, Board& board)
{
	if (depth == 0)
		return evaluate(pieces1, player, board);

	int boardSize = 8;

	if (player == MinMaxPlayer::MAXIMIZING)
	{
		int maxEval = INT_MIN;

		// Checking each piece
		for (auto p1 : pieces1)
		{
			// Checking each possible position 
			for (int i = 0; i < boardSize; i++)
			{
				for (int j = 0; j < boardSize; j++)
				{
					Position newPos{ i, j };
					if (p1->canMove(newPos, board) && board.ColorAt(p1->getPos()) == p1->color())
					{
						Board tempB;
						tempB.copyBoard(board);
						tempB.updateBoard(p1->getPos(), newPos, p1->name(), p1->color());

						Position oldPos = p1->getPos();

						// Updating position for recursive function calls
						p1->updatePos(newPos);

						int eval = minMax(depth - 1, alpha, beta, MinMaxPlayer::MINIMIZING, pieces2, pieces1, tempB);

						// Resetting position
						p1->updatePos(oldPos);
						maxEval = max(eval, maxEval);
						
						alpha = max(alpha, eval);
						if (beta <= alpha)
							exitLoop(i, j, boardSize);
					}
				}
			}
		}
		return maxEval;
	}
	else
	{
		int minEval = INT_MAX;
		for (auto p1 : pieces1)
		{
			for (int i = 0; i < boardSize; i++)
			{
				for (int j = 0; j < boardSize; j++)
				{
					Position newPos{ i, j };
					if (p1->canMove(newPos, board) && board.ColorAt(p1->getPos()) == p1->color())
					{
						Board tempB;
						tempB.copyBoard(board);
						tempB.updateBoard(p1->getPos(), newPos, p1->name(), p1->color());

						Position oldPos = p1->getPos();
						p1->updatePos(newPos);

						int eval = minMax(depth - 1, alpha, beta, MinMaxPlayer::MAXIMIZING, pieces2, pieces1, tempB);

						p1->updatePos(oldPos);

						if (eval < minEval)
							updatePos(p1->getPos(), newPos);
						else if (eval == minEval)
							swapBestPos(p1->getPos(), newPos);

						minEval = min(eval, minEval);

						beta = min(beta, eval);
						if (beta <= alpha)
							exitLoop(i, j, boardSize);
					}
				}
			}
		}
		return minEval;
	}
}

int AI::evaluate(std::vector<Piece*>& pieces, MinMaxPlayer player, Board& board)
{
	int eval;

	if (player == MinMaxPlayer::MAXIMIZING)
		eval = INT_MIN;
	else
		eval = INT_MAX;

	int boardSize = 8;

	for (auto p : pieces)
	{
		for (int i = 0; i < boardSize; i++)
		{
			for (int j = 0; j < boardSize; j++)
			{
				Position pos{ i , j };
				if (p->canMove(pos, board) && board.ColorAt(p->getPos()) == p->color())
				{
					Board tempB;
					tempB.copyBoard(board);
					tempB.updateBoard(p->getPos(), pos, p->name(), p->color());

					if (player == MinMaxPlayer::MAXIMIZING)
					{
						int newValue = tempB.BoardValue();
						if (newValue > eval)
							eval = newValue;
					}
					else
					{
						int newValue = tempB.BoardValue();
						if (newValue < eval)
							eval = newValue;
					}
				}
			}
		}
	}
	return eval;
}

int AI::min(int a, int b)
{
	if (a <= b)
		return a;
	else
		return b;
}

int AI::max(int a, int b)
{
	if (a >= b)
		return a;
	else
		return b;
}

void AI::updatePos(Position from, Position to)
{
	m_from = from;
	m_to = to;
}

// If equally good position is found, it can replace previously found position
void AI::swapBestPos(Position from, Position to)
{
	int percent = 10;
	bool swap = (rand() % 100) < percent;

	if (swap)
		updatePos(from, to);
}

void AI::exitLoop(int& i, int& j, int boardSize)
{
	i = boardSize;
	j = boardSize;
}
