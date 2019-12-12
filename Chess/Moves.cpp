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
				pieces.push_back(new Queen(color, row, col));
				board.setPieceAt(row, col, 'Q');
				break;
			}
			else if (option == 'n' || option == 'N')
			{
				pieces.push_back(new Knight(color, row, col));
				board.setPieceAt(row, col, 'n');
				break;
			}
			else if (option == 'r' || option == 'R')
			{
				pieces.push_back(new Rook(color, row, col));
				board.setPieceAt(row, col, 'R');
				break;
			}
			else if (option == 'b' || option == 'B')
			{
				pieces.push_back(new Bishop(color, row, col));
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

bool Moves::check(std::vector<Piece*> pieces, int row, int col, Board& board)
{
	for (auto p : pieces)
	{
		if (p->canMove(row, col, board))
			return true;
	}
	return false;
}

bool Moves::checkMate(std::vector<Piece*> pieces, Piece* king, Board& board)
{
	int pos1 = king->getPos1();
	int pos2 = king->getPos2();

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (pos1 + i >= 0 && pos1 + i <= 7 && pos2 + j >= 0 && pos2 + j <= 7)
			{
				if (king->canMove(pos1 + i, pos2 + j, board))
				{
					if (!check(pieces, pos1 + i, pos2 + j, board))
						return false;
				}
			}

		}
	}
	std::cout << "Check Mate!\n";
	return true;
}

void Moves::move(int row1, int col1, int row2, int col2, std::vector<Piece*>& p1, std::vector<Piece*>& p2, Board& board)
{
	int removeId = 0;
	bool replaced = false;
	bool removed = false;

	for (std::size_t i = 0; i != p2.size(); i++)
	{
		if (row2 == p2[i]->getPos1() && col2 == p2[i]->getPos2())
		{
			removeId = i;
			removed = true;
			break;
		}
	}

	for (std::size_t i = 0; i != p1.size(); i++)
	{
		if (row1 == p1[i]->getPos1() && col1 == p1[i]->getPos2())
		{
			if (p1[i]->canMove(row2, col2, board))
			{
				replaced = true;
				board.updateBoard(row1, col1, row2, col2, p1[i]->getName(), p1[i]->getColor());
				p1[i]->updatePos(row2, col2);
				p1[i]->tellInfo();
				std::cout << "was moved\n";

				if (p1[i]->getName() == 'P' && p1[i]->getColor() == 'w' && row2 == 0)
					promote(p1, p1[i], i, board);

				else if (p1[i]->getName() == 'P' && p1[i]->getColor() == 'b' && row2 == 7)
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

void Moves::updateCheckFlag(bool& setCheck, int& row, int& col, std::vector<Piece*>& pieces1, std::vector<Piece*>& pieces2, Board& board)
{
	for (auto p : pieces1)
	{
		if (p->getName() == 'K')
		{
			row = p->getPos1();
			col = p->getPos2();
			if (check(pieces2, row, col, board))
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

void Moves::updateCheckMateFlag(bool& gameOver, int& row, int& col, std::vector<Piece*>& pieces1, std::vector<Piece*>& pieces2, Board& board)
{
	std::cout << "Check!\n";
	for (auto p : pieces1)
	{
		if (p->getName() == 'K')
		{
			row = p->getPos1();
			col = p->getPos2();
			if (checkMate(pieces2, p, board))
			{
				gameOver = true;
				break;
			}
		}
	}
}