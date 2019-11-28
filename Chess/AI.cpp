#include <climits>  
#include <time.h>
#include "AI.h"
#include "Board.h"
#include "Moves.h"

std::vector<int> AI::move(std::vector<Piece*>& pieces1, std::vector<Piece*>& pieces2, Board& board)
{
	int depth = 1;
	minMax(depth, false, pieces1, pieces2, board);

	std::vector<int> positions;
	positions.resize(4);
	positions[0] = m_bFrom1;
	positions[1] = m_bFrom2;
	positions[2] = m_bTo1;
	positions[3] = m_bTo2;

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
					if (board.getOwner(i, j) != piece->getColor())
					{
						if (board.getCharAt(i, j) == 'P')
							newMove = 10;
						else if (board.getCharAt(i, j) == 'R')
							newMove = 50;
						else if (board.getCharAt(i, j) == 'n')
							newMove = 30;
						else if (board.getCharAt(i, j) == 'B')
							newMove = 30;
						else if (board.getCharAt(i, j) == 'Q')
							newMove = 90;
						else if (board.getCharAt(i, j) == 'K')
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
		std::cout << "The best move: " << bestMove << "\n";
		std::vector<int> positions;
		positions.resize(4);
		positions[0] = fromPos1;
		positions[1] = fromPos2;
		positions[2] = bestPos1;
		positions[3] = bestPos2;

		std::cout << "pos size in bestPos: " << positions.size() << "\n";

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

int AI::minMax(int depth, bool maximizingPlayer, std::vector<Piece*>& pieces1, std::vector<Piece*>& pieces2, Board& board)
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
					if (p1->canMove(i, j, board))
					{
						Board tempB;
						tempB.copyBoard(board);
						tempB.updateBoard(p1->getPos1(), p1->getPos2(), i, j, p1->getName(), p1->getColor());

						std::cout << "TempBoard in after white move\n";
						m_tempBoard.printBoard();

						int eval = minMax(depth - 1, false, pieces2, pieces1, tempB);

						if (eval > maxEval)
						{
							m_wFrom1 = p1->getPos1();
							m_wFrom2 = p1->getPos2();
							m_wTo1 = i;
							m_wTo2 = j;
						}
						maxEval = max(eval, maxEval);
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
					if (p1->canMove(i, j, board))
					{
						Board tempB;
						tempB.copyBoard(board);
						tempB.updateBoard(p1->getPos1(), p1->getPos2(), i, j, p1->getName(), p1->getColor());

						std::cout << "TempBoard in after black move\n";
						tempB.printBoard();

						int eval = minMax(depth - 1, true, pieces2, pieces1, tempB);
						// tempB.copyBoard(board); // Set board back after minMax
						if (eval < minEval)
						{
							m_bFrom1 = p1->getPos1();
							m_bFrom2 = p1->getPos2();
							m_bTo1 = i;
							m_bTo2 = j;
						}

						minEval = min(eval, minEval);
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

// calculate board value here instead
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
				if (p->canMove(i, j, board))
				{
					Board tempB;
					tempB.copyBoard(board);
					tempB.updateBoard(p->getPos1(), p->getPos1(), i, j, p->getName(), p->getColor());

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
		std::cout << "Board value: " << eval << "\n";
	}
	return eval;
}