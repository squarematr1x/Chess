#pragma once

#include <vector>

struct Square 
{
	char piece;
	char color;
};

struct Position
{
	int row;
	int col;
};

class Board
{
private:
	std::vector<std::vector<Square>> m_board;
	bool m_atStart { true };
	int m_boardValue { 0 };

public:
	Board();
	void printBoard();
	void updateBoard(int row1, int col1, int row2, int col2, char name, char color);

	bool getStarted() { return m_atStart;  }
	void started()    { m_atStart = false; }

	char getPieceAt(int row, int col)			  { return m_board[row][col].piece;         }
	void setPieceAt(int row, int col, char name)  { m_board[row][col].piece = name;         }
	char getColorAt(Position pos)			      { return m_board[pos.row][pos.col].color; }
	void setColorAt(int row, int col, char owner) { m_board[row][col].color = owner;        }
	int getBoardValue()							  { return m_boardValue;                    }

	void updateBoardValue();
	void copyBoard(Board& board);
};