#pragma once
#include <iostream>
#include "Board.h"

class Pawn;
class Rook;
class Knight;
class Bishop;
class Queen;
class King;

class Piece
{
protected:
	char m_color;
	char m_name;
	int m_pos1;
	int m_pos2;

public:
	Piece(char color, char name, int pos1, int pos2)
		: m_color(color), m_name(name), m_pos1(pos1), m_pos2(pos2)
	{
	}

	virtual ~Piece()
	{
	}

	char getColor() { return m_color; }
	char getName() { return m_name; }
	int getPos1() { return m_pos1; }
	int getPos2() { return m_pos2; }

	void tellPos() { std::cout << "(" << getPos1() << ", " << getPos2() << ")\n"; }

	void tellInfo()
	{
		std::string color;
		std::string name;

		getColor() == 'w' ? color = "White" : color = "Black";

		if (getName() == 'P')
			name = "pawn";
		else if (getName() == 'R')
			name = "rook";
		else if (getName() == 'n')
			name = "knight";
		else if (getName() == 'B')
			name = "bishop";
		else if (getName() == 'Q')
			name = "queen";
		else
			name = "king";

		std::cout << color << " " << name << " ";
	}

	virtual bool canMove(int row, int col, Board& board)
	{
		updatePos(row, col);
		(void)board;
		return true;
	}

	void updatePos(int row, int col)
	{
		m_pos1 = row;
		m_pos2 = col;
	}
};