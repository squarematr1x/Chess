#pragma once

#include <vector>

class Board
{
private:
	std::vector<std::vector<char>> m_board;
	std::vector<std::vector<char>> m_owned;
	bool m_atStart = true;
	int m_boardValue = 0;

public:
	Board();
	void printBoard();
	void updateBoard(int row1, int col1, int row2, int col2, char name, char color);
	void started() { m_atStart = false; }
	char getCharAt(int row, int col) { return m_board[row][col]; }
	void setCharAt(int row, int col, char name) { m_board[row][col] = name; }
	char getOwner(int row, int col) { return m_owned[row][col]; }
	void setOwner(int row, int col, char owner) { m_owned[row][col] = owner; }
	int getBoardValue() { return m_boardValue; }
	void updateBoardValue();
};