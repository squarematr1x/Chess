#include "Moves.h"
#include "Piece.cpp"

void Moves::promote(std::vector<Piece*>& pieces, Piece*& pawn, int indx, Board& board)
{
	char choice;
	std::cout << "Promote pawn (y/n)? ";
	std::cin >> choice;

	if (choice == 'y' || choice == 'Y')
	{
		Position pos = pawn->getPos();
		char color = pawn->color();
		char option;

		delete pawn;

		while (1)
		{
			std::cout << "Promote your pawn to Queen (Q), Knight (n), Rook (R) or Bishop (B): ";
			std::cin >> option;

			if (option == 'q' || option == 'Q')
			{
				pieces.push_back(new Queen(color, pos));
				board.setPieceAt(pos, 'Q');
				break;
			}
			else if (option == 'n' || option == 'N')
			{
				pieces.push_back(new Knight(color, pos));
				board.setPieceAt(pos, 'n');
				break;
			}
			else if (option == 'r' || option == 'R')
			{
				pieces.push_back(new Rook(color, pos));
				board.setPieceAt(pos, 'R');
				break;
			}
			else if (option == 'b' || option == 'B')
			{
				pieces.push_back(new Bishop(color, pos));
				board.setPieceAt(pos, 'B');
				break;
			}
			else
				std::cout << "Invalid input. Try Queen (Q), Knight (n), Rook (R) or Bishop (B)\n";
		}
	}
	// Removing empty elements
	pieces.erase(pieces.begin() + indx);
}

bool Moves::check(std::vector<Piece*> pieces, Position pos, Board& board)
{
	for (auto p : pieces)
	{
		if (p->canMove(pos, board))
			return true;
	}
	return false;
}

bool Moves::checkMate(std::vector<Piece*> pieces1, std::vector<Piece*> pieces2, Piece* king, Board& board)
{
	int possibilitiesToSurvive = 0;

	if (canKingMove(pieces2, king, board))
		possibilitiesToSurvive++;
	if (killAttacker(pieces1, pieces2, king, board))
		possibilitiesToSurvive++;
	if (saveKing(pieces1, pieces1, king, board))
		possibilitiesToSurvive++;

	if (possibilitiesToSurvive > 0)
		return false;
	else
	{
		std::cout << "Check Mate!\n";
		return true;
	}
}

// Can king move
bool Moves::canKingMove(std::vector<Piece*> pieces, Piece* king, Board& board)
{
	Position to;
	int legalPositions = 0;

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			to = king->getPos();
			if (to.row + i >= 0 && to.row + i <= 7 && to.col + j >= 0 && to.col + j <= 7)
			{
				to.row = to.row + i;
				to.col = to.col + j;
				if (king->canMove(to, board))
				{
					if (!check(pieces, to, board))
					{
						std::cout << "Legal positions available!\n";
						legalPositions++;
					}
				}
			}
		}
	}

	if (legalPositions > 0)
		return true;
	else
		return false;
}

bool Moves::saveKing(std::vector<Piece*> pieces1, std::vector<Piece*> pieces2, Piece* king, Board& board)
{
	Position to;

	Board tempBoard;
	tempBoard.copyBoard(board);

	for (std::size_t i = 0; i != pieces1.size(); i++)
	{
		for (int row = -1; row <= 1; row++)
		{
			for (int col = -1; col <= 1; col++)
			{
				to = king->getPos();
				if (to.row + row >= 0 && to.row + row <= 7 && to.col + col >= 0 && to.col + col <= 7)
				{
					to.row = to.row + row;
					to.col = to.col + col;
					if (pieces1[i]->canMove(to, board) && pieces1[i]->name() != 'K')
					{
						tempBoard.updateBoard(pieces1[i]->getPos(), to, pieces1[i]->name(), pieces1[i]->color());
						if (!check(pieces2, king->getPos(), tempBoard))
						{
							std::cout << "To rescue: " << pieces1[i]->name() << '\n';
							return true;
						}
						tempBoard.copyBoard(board);
					}
				}
			}
		}
	}
	return false;
}

bool Moves::killAttacker(std::vector<Piece*> pieces1, std::vector<Piece*> pieces2, Piece* king, Board& board)
{
	int attackers = 0;
	Position attackerPos{ 0, 0 };

	for (auto piece : pieces2)
	{
		if (piece->canMove(king->getPos(), board))
		{
			attackerPos = piece->getPos();
			attackers++;
		}
	}

	if (attackers > 1)
		return false;

	for (auto piece : pieces1)
	{
		if (piece->canMove(attackerPos, board))
		{
			std::cout << "Can kill attacker: " << piece->name() << '\n';
			return true;
		}
	}
	return false;
}

void Moves::move(Position from, Position to, std::vector<Piece*>& p1, std::vector<Piece*>& p2, Board& board, bool& gameOver)
{
	int removeId = 0;
	bool replaced = false;
	bool removed = false;

	for (std::size_t i = 0; i != p2.size(); i++)
	{
		if (to.row == p2[i]->row() && to.col == p2[i]->col())
		{
			removeId = i;
			removed = true;
			break;
		}
	}

	for (std::size_t i = 0; i != p1.size(); i++)
	{
		if (from.row == p1[i]->row() && from.col == p1[i]->col())
		{
			if (p1[i]->canMove(to, board))
			{
				replaced = true;
				board.updateBoard(from, to, p1[i]->name(), p1[i]->color());
				p1[i]->updatePos(to);
				p1[i]->tellInfo();
				std::cout << "was moved\n";

				if (p1[i]->name() == 'P' && p1[i]->color() == 'w' && to.row == 0)
					promote(p1, p1[i], i, board);

				else if (p1[i]->name() == 'P' && p1[i]->color() == 'b' && to.row == 7)
					promote(p1, p1[i], i, board);
			}
			else
				std::cout << "Invalid move. Try again.\n";
		}
	}

	if (removed == true && replaced == true)
	{
		p2[removeId]->tellInfo();
		std::cout << "was destroyed\n";
		
		if (p2[removeId]->name() == 'K')
			gameOver = true;

		delete p2[removeId];
		p2.erase(p2.begin() + removeId);
	}
	std::cout << '\n';
}

void Moves::updateCheckFlag(bool& setCheck, Position& pos, std::vector<Piece*>& p1, std::vector<Piece*>& p2, Board& board)
{
	for (auto piece : p1)
	{
		if (piece->name() == 'K')
		{
			pos = piece->getPos();
			if (check(p2, pos, board))
			{
				setCheck = true;
				break;
			}
			else
			{
				setCheck = false;
				break;
			}
		}
	}
}

void Moves::updateCheckMateFlag(bool& gameOver, std::vector<Piece*>& p1, std::vector<Piece*>& p2, Board& board)
{
	std::cout << "Check!\n";
	for (auto piece : p1)
	{
		if (piece->name() == 'K')
		{
			if (checkMate(p1, p2, piece, board))
			{
				gameOver = true;
				break;
			}
		}
	}
}
