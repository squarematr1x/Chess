#include "AI.h"
#include "Board.h"
#include <climits>  
#include <time.h>
#include "Moves.h"

void AI::move(std::vector<Piece*> pieces1, std::vector<Piece*> pieces2, Board& board)
{
}

std::vector<int> AI::testMove(std::vector<Piece*> pieces1, std::vector<Piece*> pieces2, Board& board)
{
	std::vector<int> positions;
	positions.resize(4);

	int rdm;
	while (1)
	{
		srand((unsigned int) time(nullptr));
		rdm = rand() % pieces1.size();
		std::cout << "rdm was this time: " << rdm << "\n";
		if (ableToMove(pieces1[rdm], board))
			break;
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (pieces1[rdm]->canMove(i, j, board)) {
				positions[0] = pieces1[rdm]->getPos1();
				positions[1] = pieces1[rdm]->getPos2();
				positions[2] = i;
				positions[3] = j;
				std::cout << "pos size in rdmPos: " << positions.size() << "\n";
				return positions;
			}
		}
	}
}

std::vector<int> AI::bestMove(std::vector<Piece*> pieces1, std::vector<Piece*> pieces2, Board& board)
{
	int bestMove = INT_MIN;
	int newMove = 0;
	int fromPos1 = 0, fromPos2 = 0;
	int bestPos1 = 0, bestPos2 = 0;

	for (auto piece : pieces1)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
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
		randomPositions = testMove(pieces1, pieces2, board);
		return randomPositions;
	}
}

bool AI::ableToMove(Piece*& piece, Board& board)
{
	int boardWidth = 8, boardHeight = 8;

	for (int i = 0; i < boardWidth; i++)
	{
		for (int j = 0; j < boardHeight; j++)
		{
			if (piece->canMove(i, j, board)) {
				return true;
			}
		}
	}
	return false;
}

int AI::minMax(int pos1, int pos2, int depth, bool maximizingPlayer, Piece*& piece, Board& board)
{
	if (depth == 0) {
		if (piece->getColor() == 'w' && board.getOwner(pos1, pos2) == 'b')
		{
			if (board.getCharAt(pos1, pos2) == 'P')
				return 10;
			if (board.getCharAt(pos1, pos2) == 'R')
				return 50;
			if (board.getCharAt(pos1, pos2) == 'n')
				return 30;
			if (board.getCharAt(pos1, pos2) == 'B')
				return 30;
			if (board.getCharAt(pos1, pos2) == 'Q')
				return 90;
			if (board.getCharAt(pos1, pos2) == 'K')
				return 900;
		}
		else if (piece->getColor() == 'b' && board.getOwner(pos1, pos2) == 'w')
		{
			if (board.getCharAt(pos1, pos2) == 'P')
				return -10;
			if (board.getCharAt(pos1, pos2) == 'R')
				return -50;
			if (board.getCharAt(pos1, pos2) == 'n')
				return -30;
			if (board.getCharAt(pos1, pos2) == 'B')
				return -30;
			if (board.getCharAt(pos1, pos2) == 'Q')
				return -90;
			if (board.getCharAt(pos1, pos2) == 'K')
				return -900;
		}
	}

	if (maximizingPlayer)
	{
		int maxEval = INT_MIN;
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (piece->canMove(i, j, board))
				{
					int eval = minMax(i, j, depth - 1, false, piece, board);
					maxEval = max(eval, maxEval);
				}

			}
		}
		return maxEval;

	}
	else
	{
		int minEval = INT_MAX;
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (piece->canMove(i, j, board))
				{
					int eval = minMax(i, j, depth - 1, true, piece, board);
					minEval = min(eval, minEval);
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