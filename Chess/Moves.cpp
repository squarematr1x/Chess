#include "Moves.h"
#include "Piece.cpp"

void Moves::promote(std::vector<Piece*>& pieces, Piece*& pawn, int indx, Board& board)
{
	char choice;
	std::cout << "Promote pawn (y/n)? ";
	std::cin >> choice;

	if (choice == 'y' || choice == 'Y')
	{
		int row = pawn->getPos1();
		int col = pawn->getPos2();
		char color = pawn->getColor();
		char option;

		delete pawn;

		while (1)
		{
			std::cout << "Promote your pawn to Queen (Q), Knight (n), Rook (R) or Bishop (B): ";
			std::cin >> option;

			if (option == 'q' || option == 'Q')
			{
				pieces.push_back(new Queen(color, position{ row, col }));
				board.setPieceAt(row, col, 'Q');
				break;
			}
			else if (option == 'n' || option == 'N')
			{
				pieces.push_back(new Knight(color, position{ row, col }));
				board.setPieceAt(row, col, 'n');
				break;
			}
			else if (option == 'r' || option == 'R')
			{
				pieces.push_back(new Rook(color, position{ row, col }));
				board.setPieceAt(row, col, 'R');
				break;
			}
			else if (option == 'b' || option == 'B')
			{
				pieces.push_back(new Bishop(color, position{ row, col }));
				board.setPieceAt(row, col, 'B');
				break;
			}
			else
				std::cout << "Invalid input. Try again.\n";
		}
	}
	// Removing empty elements
	pieces.erase(pieces.begin() + indx);
}

bool Moves::check(std::vector<Piece*> pieces, position pos, Board& board)
{
	for (auto p : pieces)
	{
		if (p->canMove(pos, board))
			return true;
	}
	return false;
}

bool Moves::checkMate(std::vector<Piece*> pieces, Piece* king, Board& board)
{
	position to = king->getPos();

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (to.row + i >= 0 && to.row + i <= 7 && to.col + j >= 0 && to.col + j <= 7)
			{
				to.row = to.row + i;
				to.col = to.col + j;
				if (king->canMove(to, board))
				{
					if (!check(pieces, to, board))
						return false;
				}
			}

		}
	}
	std::cout << "Check Mate!\n";
	return true;
}

void Moves::move(position from, position to, std::vector<Piece*>& p1, std::vector<Piece*>& p2, Board& board)
{
	int removeId = 0;
	bool replaced = false;
	bool removed = false;

	for (std::size_t i = 0; i != p2.size(); i++)
	{
		if (to.row == p2[i]->getPos1() && to.col == p2[i]->getPos2())
		{
			removeId = i;
			removed = true;
			break;
		}
	}

	for (std::size_t i = 0; i != p1.size(); i++)
	{
		if (from.row == p1[i]->getPos1() && from.col == p1[i]->getPos2())
		{
			if (p1[i]->canMove(to, board))
			{
				replaced = true;
				board.updateBoard(from.row, from.col, to.row, to.col, p1[i]->getName(), p1[i]->getColor());
				p1[i]->updatePos(to);
				p1[i]->tellInfo();
				std::cout << "was moved\n";

				if (p1[i]->getName() == 'P' && p1[i]->getColor() == 'w' && to.row == 0)
					promote(p1, p1[i], i, board);

				else if (p1[i]->getName() == 'P' && p1[i]->getColor() == 'b' && to.row == 7)
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
		delete p2[removeId];
		p2.erase(p2.begin() + removeId);
	}
	std::cout << '\n';
}

void Moves::updateCheckFlag(bool& setCheck, position& pos, std::vector<Piece*>& p1, std::vector<Piece*>& p2, Board& board)
{
	for (auto p : p1)
	{
		if (p->getName() == 'K')
		{
			pos = p->getPos();
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

void Moves::updateCheckMateFlag(bool& gameOver, position& pos, std::vector<Piece*>& p1, std::vector<Piece*>& p2, Board& board)
{
	std::cout << "Check!\n";
	for (auto p : p1)
	{
		if (p->getName() == 'K')
		{
			pos = p->getPos();
			if (checkMate(p2, p, board))
			{
				gameOver = true;
				break;
			}
		}
	}
}