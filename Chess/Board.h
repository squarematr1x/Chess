#pragma once
#include <iostream>
#include <vector>

class Board
{
private:
	std::vector<std::vector<char>> m_board;
	std::vector<std::vector<char>> m_owned;
	bool m_atStart = true;

public:
	Board()
	{
		m_board.resize(8);
		m_owned.resize(8);

		// Creating 8x8 game board
		for (std::size_t i = 0; i < 8; ++i)
		{
			for (std::size_t j = 0; j < 8; ++j)
				m_board[i].push_back('.');
		}

		// Ownership of each node (white/black/.)
		for (std::size_t i = 0; i < 8; ++i)
		{
			for (std::size_t j = 0; j < 8; ++j)
				m_owned[i].push_back('.');
		}
	}

	void printBoard()
	{
		std::cout << "   A  B  C  D  E  F  G  H \n";
		std::cout << "   -----------------------\n";
		for (std::size_t i = 0; i < m_board.size(); i++)
		{
			std::cout << m_board.size() - i << "|";
			for (std::size_t j = 0; j < m_board.size(); j++)
			{
				std::cout << " " << getCharAt(i, j) << " ";
			}
			if (m_atStart)
			{
				if (i == 0 || i == 1)
					std::cout << "  <--- Black Player";
				else if (i == 6 || i == 7)
					std::cout << "  <--- White Player";
			}
			std::cout << '\n';
		}
		std::cout << '\n';
	}

	void updateBoard(int row1, int col1, int row2, int col2, char name, char color)
	{
		setCharAt(row1, col1, '.');
		setCharAt(row2, col2, name);
		setOwner(row1, col1, '.');
		setOwner(row2, col2, color);
	}

	void started() { m_atStart = false; }
	char getCharAt(int row, int col) { return m_board[row][col]; }
	void setCharAt(int row, int col, char name) { m_board[row][col] = name; }
	char getOwner(int row, int col) { return m_owned[row][col]; }
	void setOwner(int row, int col, char owner) { m_owned[row][col] = owner; }
};