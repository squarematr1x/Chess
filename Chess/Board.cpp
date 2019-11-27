#include <iostream>
#include "Board.h"

Board::Board()
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

void Board::printBoard()
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

void Board::updateBoard(int row1, int col1, int row2, int col2, char name, char color)
{
	setCharAt(row1, col1, '.');
	setCharAt(row2, col2, name);
	setOwner(row1, col1, '.');
	setOwner(row2, col2, color);
}

void Board::copyBoard(Board& board)
{
	m_board.resize(8);
	m_owned.resize(8);

	m_atStart = board.getStarted();
	m_boardValue = board.getBoardValue();

	for (std::size_t i = 0; i < 8; ++i)
	{
		for (std::size_t j = 0; j < 8; ++j) 
		{
			m_board[i][j] = board.getCharAt(i, j);
		}
	}

	for (std::size_t i = 0; i < 8; ++i)
	{
		for (std::size_t j = 0; j < 8; ++j)
			m_owned[i][j] = board.getOwner(i, j);
	}
}

void Board::updateBoardValue()
{
	m_boardValue = 0;

	for (std::size_t i = 0; i < m_board.size(); i++)
	{
		for (std::size_t j = 0; j < m_board.size(); j++)
		{
			if (getCharAt(i, j) == 'P')
			{
				if (getOwner(i, j) == 'w')
					m_boardValue += 10;
				else if (getOwner(i, j) == 'b')
					m_boardValue -= 10;
			}
			if (getCharAt(i, j) == 'R')
			{
				if (getOwner(i, j) == 'w')
					m_boardValue += 50;
				else if (getOwner(i, j) == 'b')
					m_boardValue -= 50;
			}
			if (getCharAt(i, j) == 'n')
			{
				if (getOwner(i, j) == 'w')
					m_boardValue += 30;
				else if (getOwner(i, j) == 'b')
					m_boardValue -= 30;
			}
			if (getCharAt(i, j) == 'B')
			{
				if (getOwner(i, j) == 'w')
					m_boardValue += 30;
				else if (getOwner(i, j) == 'b')
					m_boardValue -= 30;
			}
			if (getCharAt(i, j) == 'Q')
			{
				if (getOwner(i, j) == 'w')
					m_boardValue += 90;
				else if (getOwner(i, j) == 'b')
					m_boardValue -= 90;
			}
			if (getCharAt(i, j) == 'K')
			{
				if (getOwner(i, j) == 'w')
					m_boardValue += 90;
				else if (getOwner(i, j) == 'b')
					m_boardValue -= 90;
			}
		}
	}
}