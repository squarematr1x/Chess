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

enum class StartingPosition
{
	SELECTED,
	NOT_SELECTED
};

int inputRow(bool selected)
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

char inputCol(bool selected)
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

int gameMode()
{
	std::string sGameMode = "";
	while (true)
	{
		std::cin >> sGameMode;
		if (sGameMode != "1" && sGameMode != "2")
		{
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			std::cout << "Game mode (1 =  player vs. player & 2 = player vs. CPU): ";
		}
		else
			break;
	}
	int gameMode = std::stoi(sGameMode);
	return gameMode;
}

void intializePieces(std::vector<Piece*>& whitePieces, std::vector<Piece*>& blackPieces)
{
	int colSpecial = 0;
	int colPawn = 0;

	for (std::size_t i = 0; i != whitePieces.size(); i++)
	{
		if (i < 8)
		{
			if (colSpecial == 0 || colSpecial == 7)
			{
				whitePieces[i] = new Rook('w', Position{ 7, colSpecial });
				blackPieces[i] = new Rook('b', Position{ 0, colSpecial });
			}
			else if (colSpecial == 1 || colSpecial == 6)
			{
				whitePieces[i] = new Knight('w', Position{ 7, colSpecial });
				blackPieces[i] = new Knight('b', Position{ 0, colSpecial });
			}
			else if (colSpecial == 2 || colSpecial == 5)
			{
				whitePieces[i] = new Bishop('w', Position{ 7, colSpecial });
				blackPieces[i] = new Bishop('b', Position{ 0, colSpecial });
			}
			else if (colSpecial == 4)
			{
				whitePieces[i] = new Queen('w', Position{ 7, colSpecial });
				blackPieces[i] = new King('b', Position{ 0, colSpecial });
			}
			else if (colSpecial == 3)
			{
				whitePieces[i] = new King('w', Position{ 7, colSpecial });
				blackPieces[i] = new Queen('b', Position{ 0, colSpecial });
			}
			colSpecial++;
		}
		else
		{
			whitePieces[i] = new Pawn('w', Position{ 6, colPawn });
			blackPieces[i] = new Pawn('b', Position{ 1, colPawn });
			colPawn++;
		}
	}
}

void destroyPieces(std::vector<Piece*>& whitePieces, std::vector<Piece*>& blackPieces)
{
	for (auto piece : whitePieces)
		delete piece;

	for (auto piece : blackPieces)
		delete piece;
}

int main()
{
	Board board;
	Moves moves;
	AI AI(board);

	enum Mode
	{
		PLAYER_VS_PLAYER = 1,
		PLAYER_VS_CPU = 2
	};

	enum Turn
	{
		BLACK,
		WHITE
	};

	std::vector<Piece*> whitePieces;
	std::vector<Piece*> blackPieces;

	whitePieces.resize(16);
	blackPieces.resize(16);

	// Initializing chess pieces
	intializePieces(whitePieces, blackPieces);

	for (auto& wp : whitePieces)
	{
		board.setPieceAt(wp->getRow(), wp->getCol(), wp->getName());
		board.setColorAt(wp->getRow(), wp->getCol(), wp->getColor());
	}

	for (auto& bp : blackPieces)
	{
		board.setPieceAt(bp->getRow(), bp->getCol(), bp->getName());
		board.setColorAt(bp->getRow(), bp->getCol(), bp->getColor());
	}
	board.started();

	// For converting player input to corresponding positions
	std::map<int, int> coord1 = { {1, 7}, {2, 6}, {3, 5}, {4, 4}, {5, 3}, {6, 2} , {7, 1}, {8, 0} };
	std::map<char, int> coord2 = { {'a', 0}, {'b', 1}, {'c', 2}, {'d', 3}, {'e', 4}, {'f', 5} , {'g', 6}, {'h', 7} };

	bool gameOver = false;
	int turn = WHITE;
	int mode;

	std::cout << "Welcome to Chess\n";
	std::cout << "Player vs. Player (1)\n";
	std::cout << "Player vs. CPU (2)\n";
	std::cout << '\n';
	std::cout << "Game mode: ";
	mode = gameMode();
	std::cout << '\n';

	// Game loop
	while (1)
	{
		board.printBoard();

		Position from{ 0,0 };
		Position to{ 0,0 };

		char cCol1, cCol2;
		bool checkW = false, checkB = false;

		turn == WHITE ? std::cout << "White player's turn\n" : std::cout << "Black player's turn\n";

		// Checking if current state of the game is check
		moves.updateCheckFlag(checkW, from, whitePieces, blackPieces, board);
		moves.updateCheckFlag(checkB, from, blackPieces, whitePieces, board);

		if (checkW)
			moves.updateCheckMateFlag(gameOver, from, whitePieces, blackPieces, board);

		if (checkB)
			moves.updateCheckMateFlag(gameOver, from, blackPieces, whitePieces, board);

		if (gameOver)
			break;

		if (mode == PLAYER_VS_PLAYER || (mode == PLAYER_VS_CPU && turn == WHITE))
		{
			std::cout << "Select from:\n";
			std::cout << "row1 (1..8): ";
			from.row = inputRow(false);
			from.row = coord1.at(from.row);
			std::cout << "col1 (A..H): ";
			cCol1 = inputCol(false);
			from.col = coord2.at(cCol1);

			std::cout << "Move to:\n";
			std::cout << "row2 (1..8): ";
			to.row = inputRow(true);
			to.row = coord1.at(to.row);
			std::cout << "col2 (A..H): ";
			cCol2 = inputCol(true);
			to.col = coord2.at(cCol2);
			std::cout << '\n';
		}

		if (mode == PLAYER_VS_PLAYER)
		{
			if (turn == WHITE && board.getColorAt(from) == 'w')
			{
				moves.move(from, to, whitePieces, blackPieces, board);
				if (board.getColorAt(from) != 'w')
					turn = BLACK;
			}
			else if (turn == BLACK && board.getColorAt(from) == 'b')
			{
				moves.move(from, to, blackPieces, whitePieces, board);
				if (board.getColorAt(from) != 'b')
					turn = WHITE;
			}
		}
		else
		{
			if (turn == WHITE && board.getColorAt(from) == 'w')
			{
				moves.move(from, to, whitePieces, blackPieces, board);
				if (board.getColorAt(from) != 'w')
					turn = BLACK;
			}
			else if (turn == BLACK)
			{
				std::vector<Position> AIPos;
				AIPos.resize(2);

				AI.getBoard().copyBoard(board);
				AIPos = AI.move(blackPieces, whitePieces, board);

				Position fromAI = AIPos[0];
				Position toAI = AIPos[1];

				moves.move(fromAI, toAI, blackPieces, whitePieces, board);

				turn = WHITE;
			}
		}
		board.updateBoardValue();
	}

	destroyPieces(whitePieces, blackPieces);

	return 0;
}