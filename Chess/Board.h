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
	void updateBoard(Position pos1, Position pos2, char name, char color);

	bool isStarted() const { return m_atStart;  }
	void started()         { m_atStart = false; }

	char PieceAt(Position pos) const { return m_board[pos.row][pos.col].piece; }
	void setPieceAt(Position pos, char name) { m_board[pos.row][pos.col].piece = name; }
	char ColorAt(Position pos) const { return m_board[pos.row][pos.col].color;  }
	void setColorAt(Position pos, char owner) { m_board[pos.row][pos.col].color = owner; }

	int BoardValue() const { return m_boardValue; }

	void updateBoardValue();
	void copyBoard(Board& board);
};
