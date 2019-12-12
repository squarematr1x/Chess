#include <iostream>
#include "Board.h"

Board::Board()
{
	m_board.resize(8);

	// Creating 8x8 game board
	for (std::size_t i = 0; i < 8; ++i)
	{
		for (std::size_t j = 0; j < 8; ++j)
			m_board[i].push_back(square {'.', '.'});
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
			std::cout << " " << getPieceAt(i, j) << " ";
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
	setPieceAt(row1, col1, '.');
	setPieceAt(row2, col2, name);
	setColorAt(row1, col1, '.');
	setColorAt(row2, col2, color);

	updateBoardValue();
}

void Board::copyBoard(Board& board)
{
	m_board.resize(8);

	m_atStart = board.getStarted();
	m_boardValue = board.getBoardValue();

	for (std::size_t i = 0; i < 8; ++i)
	{
		for (std::size_t j = 0; j < 8; ++j) 
		{
			square sqr = { board.getPieceAt(i, j) , board.getColorAt(i, j) };
			m_board[i][j] = sqr;
		}
	}
}

void Board::updateBoardValue()
{
	m_boardValue = 0;

	for (std::size_t i = 0; i < m_board.size(); i++)
	{
		for (std::size_t j = 0; j < m_board.size(); j++)
		{
			if (getPieceAt(i, j) == 'P')
			{
				if (getColorAt(i, j) == 'w')
					m_boardValue += 10;
				else if (getColorAt(i, j) == 'b')
					m_boardValue -= 10;
			}
			else if (getPieceAt(i, j) == 'R')
			{
				if (getColorAt(i, j) == 'w')
					m_boardValue += 50;
				else if (getColorAt(i, j) == 'b')
					m_boardValue -= 50;
			}
			else if (getPieceAt(i, j) == 'n')
			{
				if (getColorAt(i, j) == 'w')
					m_boardValue += 30;
				else if (getColorAt(i, j) == 'b')
					m_boardValue -= 30;
			}
			else if (getPieceAt(i, j) == 'B')
			{
				if (getColorAt(i, j) == 'w')
					m_boardValue += 30;
				else if (getColorAt(i, j) == 'b')
					m_boardValue -= 30;
			}
			else if (getPieceAt(i, j) == 'Q')
			{
				if (getColorAt(i, j) == 'w')
					m_boardValue += 90;
				else if (getColorAt(i, j) == 'b')
					m_boardValue -= 90;
			}
			else if (getPieceAt(i, j) == 'K')
			{
				if (getColorAt(i, j) == 'w')
					m_boardValue += 90;
				else if (getColorAt(i, j) == 'b')
					m_boardValue -= 90;
			}
		}
	}
}