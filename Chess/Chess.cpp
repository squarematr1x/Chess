#include <iostream>
#include <vector>
#include <map>
#include <climits>    
#include <string>
#include "Board.h"
#include "Piece.h"
#include "AI.h"
#include "Moves.h"
#include "Piece.cpp"

int getInputRow(bool selected)
{
	std::string srow = "";
	while (true)
	{
		std::cin >> srow;
		if (srow != "1" && srow != "2" && srow != "3" && srow != "4" &&
			srow != "5" && srow != "6" && srow != "7" && srow != "8")
		{
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			if (!selected)
				std::cout << "row1 (1...8): ";
			else
				std::cout << "row2 (1...8): ";
		}
		else
			break;
	}
	int row = std::stoi(srow);
	return row;
}

char getInputCol(bool selected)
{
	std::string scol = "";
	while (true)
	{
		std::cin >> scol;
		
		// Accepting both upper and lower case
		for (auto& c : scol)
			c = (char)tolower(c);

		if (scol != "a" && scol != "b" && scol != "c" && scol != "d" &&
			scol != "e" && scol != "f" && scol != "g" && scol != "h")
		{
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			if (!selected)
				std::cout << "col1 (A...H): ";
			else
				std::cout << "col2 (A...H): ";
		}
		else
			break;
	}
	char col = scol[0];
	return col;
}

int main()
{
	Board board;
	Moves moves;
	AI AI(board);

	std::vector<Piece*> whitePieces;
	std::vector<Piece*> blackPieces;

	std::map<int, int> coord1 = { {1, 7}, {2, 6}, {3, 5}, {4, 4}, {5, 3}, {6, 2} , {7, 1}, {8, 0} };
	std::map<char, int> coord2 = { {'a', 0}, {'b', 1}, {'c', 2}, {'d', 3}, {'e', 4}, {'f', 5} , {'g', 6}, {'h', 7} };

	whitePieces.resize(16);
	blackPieces.resize(16);

	int colSpecial = 0;
	int colPawn = 0;

	// Turn 0: white, 1: black
	int turn = 0;

	// Initializing chess pieces
	for (std::size_t i = 0; i != whitePieces.size(); i++)
	{
		if (i < 8)
		{
			if (colSpecial == 0 || colSpecial == 7)
			{
				whitePieces[i] = new Rook('w', 7, colSpecial);
				blackPieces[i] = new Rook('b', 0, colSpecial);
			}
			else if (colSpecial == 1 || colSpecial == 6)
			{
				whitePieces[i] = new Knight('w', 7, colSpecial);
				blackPieces[i] = new Knight('b', 0, colSpecial);
			}
			else if (colSpecial == 2 || colSpecial == 5)
			{
				whitePieces[i] = new Bishop('w', 7, colSpecial);
				blackPieces[i] = new Bishop('b', 0, colSpecial);
			}
			else if (colSpecial == 4)
			{
				whitePieces[i] = new Queen('w', 7, colSpecial);
				blackPieces[i] = new King('b', 0, colSpecial);
			}
			else if (colSpecial == 3)
			{
				whitePieces[i] = new King('w', 7, colSpecial);
				blackPieces[i] = new Queen('b', 0, colSpecial);
			}
			colSpecial++;
		}
		else
		{
			whitePieces[i] = (new Pawn('w', 6, colPawn));
			blackPieces[i] = (new Pawn('b', 1, colPawn));
			colPawn++;
		}
	}

	for (auto& wp : whitePieces)
	{
		board.setCharAt(wp->getPos1(), wp->getPos2(), wp->getName());
		board.setOwner(wp->getPos1(), wp->getPos2(), wp->getColor());
	}

	for (auto& bp : blackPieces)
	{
		board.setCharAt(bp->getPos1(), bp->getPos2(), bp->getName());
		board.setOwner(bp->getPos1(), bp->getPos2(), bp->getColor());
	}

	bool gameOver = false;
	bool pvp = true;
	board.started();

	// Game loop
	while (1)
	{
		board.printBoard();

		int row1 = 0, col1 = 0, row2 = 0, col2 = 0;
		char cCol1, cCol2;
		bool checkW = false, checkB = false;

		turn == 0 ? std::cout << "White player's turn\n" : std::cout << "Black player's turn\n";

		// Checking if check or check mate
		moves.setCheckFlag(checkW, row1, col1, whitePieces, blackPieces, board);
		moves.setCheckFlag(checkB, row1, col1, blackPieces, whitePieces, board);

		if (checkW)
		{
			moves.setCheckMateFlag(gameOver, row1, col1, whitePieces, blackPieces, board);
		}
		if (checkB)
		{
			moves.setCheckMateFlag(gameOver, row1, col1, blackPieces, whitePieces, board);
		}

		if (gameOver)
			break;

		if (pvp) 
		{
			if (!checkW && turn == 0 || !checkB && turn == 1)
			{
				std::cout << "Select from:\n";
				std::cout << "row1 (1...8): ";
				row1 = getInputRow(false);
				row1 = coord1.at(row1);
				std::cout << "col1 (A...H): ";
				cCol1 = getInputCol(false);
				col1 = coord2.at(cCol1);
			}

			std::cout << "Move to:\n";
			std::cout << "row2 (1...8): ";
			row2 = getInputRow(true);
			row2 = coord1.at(row2);
			std::cout << "col2 (A...H): ";
			cCol2 = getInputCol(true);
			col2 = coord2.at(cCol2);
			std::cout << '\n';
		}
		else
		{
			if (!checkW && turn == 0)
			{
				std::cout << "Select from:\n";
				std::cout << "row1 (1...8): ";
				row1 = getInputRow(false);
				row1 = coord1.at(row1);
				std::cout << "col1 (A...H): ";
				cCol1 = getInputCol(false);
				col1 = coord2.at(cCol1);
				std::cout << "Move to:\n";
				std::cout << "row2 (1...8): ";
				row2 = getInputRow(true);
				row2 = coord1.at(row2);
				std::cout << "col2 (A...H): ";
				cCol2 = getInputCol(true);
				col2 = coord2.at(cCol2);
				std::cout << '\n';
			}
		}

		if (pvp)
		{
			if (turn == 0 && board.getOwner(row1, col1) == 'w')
			{
				moves.selectAndMove(row1, col1, row2, col2, whitePieces, blackPieces, board);
				if (board.getOwner(row1, col1) != 'w')
					turn = 1;
			}
			else if (turn == 1 && board.getOwner(row1, col1) == 'b')
			{
				moves.selectAndMove(row1, col1, row2, col2, blackPieces, whitePieces, board);
				if (board.getOwner(row1, col1) != 'b')
					turn = 0;
			}
		}
		else
		{
			if (turn == 0 && board.getOwner(row1, col1) == 'w')
			{
				moves.selectAndMove(row1, col1, row2, col2, whitePieces, blackPieces, board);
				if (board.getOwner(row1, col1) != 'w')
					turn = 1;
			}
			else if (turn == 1)
			{
				std::vector<int> AIPos;
				AIPos.resize(4);

				AI.getBoard().copyBoard(board);
				AIPos = AI.move(blackPieces, whitePieces, board);
				moves.selectAndMove(AIPos[0], AIPos[1], AIPos[2], AIPos[3], blackPieces, whitePieces, board);

				turn = 0;
			}
		}
		board.updateBoardValue();
	}

	for (auto piece : whitePieces)
		delete piece;

	for (auto piece : blackPieces)
		delete piece;

	return 0;
}