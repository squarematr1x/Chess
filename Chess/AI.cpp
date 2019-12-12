#include <climits>  
#include <time.h>
#include "AI.h"

std::vector<int> AI::move(std::vector<Piece*>& pieces1, std::vector<Piece*>& pieces2, Board& board)
{
	int alpha = INT_MIN;	// Worst for white
	int beta = INT_MAX;		// Worst for black

	int depth = 2;
	minMax(depth, alpha, beta, false, pieces1, pieces2, board);

	std::vector<int> positions;
	positions.resize(4);
	positions[0] = m_from1;
	positions[1] = m_from2;
	positions[2] = m_to1;
	positions[3] = m_to2;

	return positions;
}

std::vector<int> AI::randomMove(std::vector<Piece*>& pieces, Board& board)
{
	std::vector<int> positions;
	positions.resize(4);

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

				if (pieces[rdm]->canMove(i, j, board)) 
				{
					positions[0] = pieces[rdm]->getPos1();
					positions[1] = pieces[rdm]->getPos2();
					positions[2] = i;
					positions[3] = j;
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

std::vector<int> AI::bestMove(std::vector<Piece*>& pieces, Board& board)
{
	int bestMove = INT_MIN;
	int newMove = 0;
	int fromPos1 = 0, fromPos2 = 0;
	int bestPos1 = 0, bestPos2 = 0;
	int boardSize = 8;

	for (auto piece : pieces)
	{
		for (int i = 0; i < boardSize; i++)
		{
			for (int j = 0; j < boardSize; j++)
			{
				if (piece->canMove(i, j, board))
				{
					if (board.getColorAt(i, j) != piece->getColor())
					{
						if (board.getPieceAt(i, j) == 'P')
							newMove = 10;
						else if (board.getPieceAt(i, j) == 'R')
							newMove = 50;
						else if (board.getPieceAt(i, j) == 'n')
							newMove = 30;
						else if (board.getPieceAt(i, j) == 'B')
							newMove = 30;
						else if (board.getPieceAt(i, j) == 'Q')
							newMove = 90;
						else if (board.getPieceAt(i, j) == 'K')
							newMove = 900;
						else
							newMove = 0;
					}
					if (newMove > bestMove)
					{
						bestMove = newMove;
						bestPos1 = i;
						bestPos2 = j;
						fromPos1 = piece->getPos1();
						fromPos2 = piece->getPos2();
					}
				}

			}
		}
	}

	if (bestMove > 0)
	{
		std::vector<int> positions;
		positions.resize(4);
		positions[0] = fromPos1;
		positions[1] = fromPos2;
		positions[2] = bestPos1;
		positions[3] = bestPos2;

		return positions;
	}
	else
	{
		std::vector<int> randomPositions;
		randomPositions.resize(4);
		randomPositions = randomMove(pieces, board);
		return randomPositions;
	}
}

bool AI::ableToMove(Piece*& piece, Board& board)
{
	int boardSize = 8;

	for (int i = 0; i < boardSize; i++)
	{
		for (int j = 0; j < boardSize; j++)
		{
			if (piece->canMove(i, j, board)) {
				return true;
			}
		}
	}
	return false;
}

int AI::minMax(int depth, int alpha, int beta, bool maximizingPlayer, std::vector<Piece*>& pieces1, std::vector<Piece*>& pieces2, Board& board)
{
	if (depth == 0)
	{
		return evaluate(pieces1, maximizingPlayer, board);
	}

	int boardSize = 8;

	if (maximizingPlayer)
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
					if (p1->canMove(i, j, board) && board.getColorAt(p1->getPos1(), p1->getPos2()) == p1->getColor())
					{
						Board tempB;
						tempB.copyBoard(board);
						tempB.updateBoard(p1->getPos1(), p1->getPos2(), i, j, p1->getName(), p1->getColor());

						int oldPos1 = p1->getPos1();
						int oldPos2 = p1->getPos2();

						// Updating position for recursive function calls
						p1->updatePos(i, j);

						int eval = minMax(depth - 1, alpha, beta, false, pieces2, pieces1, tempB);

						// Resetting position
						p1->updatePos(oldPos1, oldPos2);
						maxEval = max(eval, maxEval);
						
						alpha = max(alpha, eval);
						if (beta <= alpha)
						{
							i = boardSize;
							j = boardSize;
						}
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
					if (p1->canMove(i, j, board) && board.getColorAt(p1->getPos1(), p1->getPos2()) == p1->getColor())
					{
						Board tempB;
						tempB.copyBoard(board);
						tempB.updateBoard(p1->getPos1(), p1->getPos2(), i, j, p1->getName(), p1->getColor());

						int oldPos1 = p1->getPos1();
						int oldPos2 = p1->getPos2();
						p1->updatePos(i, j);

						int eval = minMax(depth - 1, alpha, beta, true, pieces2, pieces1, tempB);

						p1->updatePos(oldPos1, oldPos2);

						if (eval < minEval)
						{
							m_from1 = p1->getPos1();
							m_from2 = p1->getPos2();
							m_to1 = i;
							m_to2 = j;
						}
						minEval = min(eval, minEval);

						beta = min(beta, eval);
						if (beta <= alpha)
						{
							i = boardSize;
							j = boardSize;
						}
					}

				}
			}
		}
		return minEval;
	}
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

int AI::evaluate(std::vector<Piece*>& pieces, bool maximizing, Board& board)
{
	int eval;

	if (maximizing)
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
				if (p->canMove(i, j, board) && board.getColorAt(p->getPos1(), p->getPos2()) == p->getColor())
				{
					Board tempB;
					tempB.copyBoard(board);
					tempB.updateBoard(p->getPos1(), p->getPos2(), i, j, p->getName(), p->getColor());

					if (maximizing)
					{
						int newValue = tempB.getBoardValue();
						if (newValue > eval)
							eval = newValue;
					}
					else
					{
						int newValue = tempB.getBoardValue();
						if (newValue < eval)
							eval = newValue;
					}
				}
			}
		}
	}
	return eval;
}