#include <iostream>
#include "Board.h"
#include "Piece.h"

Board::Board()
{
	m_board.resize(8);

	// Creating 8x8 game board
	for (std::size_t i = 0; i < 8; ++i)
	{
		for (std::size_t j = 0; j < 8; ++j)
			m_board[i].push_back(Square {'.', '.'});
	}
}

void Board::printBoard()
{
	std::cout << "   A  B  C  D  E  F  G  H \n";
	std::cout << "   -----------------------\n";

	Position pos;
	for (std::size_t i = 0; i < m_board.size(); i++)
	{
		std::cout << m_board.size() - i << "|";
		for (std::size_t j = 0; j < m_board.size(); j++)
		{
			pos.row = i;
			pos.col = j;
			std::cout << " " << PieceAt(pos) << " ";
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

void Board::updateBoard(Position pos1, Position pos2, char name, char color)
{
	setPieceAt(pos1, '.');
	setPieceAt(pos2, name);
	setColorAt(pos1, '.');
	setColorAt(pos2, color);

	updateBoardValue();
}

void Board::copyBoard(Board& board)
{
	m_board.resize(8);

	m_atStart = board.isStarted();
	m_boardValue = board.BoardValue();

	for (std::size_t i = 0; i < 8; ++i)
	{
		for (std::size_t j = 0; j < 8; ++j) 
		{
			Position pos{ (int)i, (int)j };
			Square sqr = { board.PieceAt(pos) , board.ColorAt(pos) };
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
			Position pos{ (int)i, (int)j };
			if (PieceAt(pos) == 'P')
			{
				if (ColorAt(pos) == 'w')
					m_boardValue += 10;
				else if (ColorAt(pos) == 'b')
					m_boardValue -= 10;
			}
			else if (PieceAt(pos) == 'R')
			{
				if (ColorAt(pos) == 'w')
					m_boardValue += 50;
				else if (ColorAt(pos) == 'b')
					m_boardValue -= 50;
			}
			else if (PieceAt(pos) == 'n')
			{
				if (ColorAt(pos) == 'w')
					m_boardValue += 30;
				else if (ColorAt(pos) == 'b')
					m_boardValue -= 30;
			}
			else if (PieceAt(pos) == 'B')
			{
				if (ColorAt(pos) == 'w')
					m_boardValue += 40;
				else if (ColorAt(pos) == 'b')
					m_boardValue -= 40;
			}
			else if (PieceAt(pos) == 'Q')
			{
				if (ColorAt(pos) == 'w')
					m_boardValue += 90;
				else if (ColorAt(pos) == 'b')
					m_boardValue -= 90;
			}
			else if (PieceAt(pos) == 'K')
			{
				if (ColorAt(pos) == 'w')
					m_boardValue += 90;
				else if (ColorAt(pos) == 'b')
					m_boardValue -= 90;
			}
		}
	}
}