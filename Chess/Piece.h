#pragma once

#include <iostream>
#include "Board.h"

struct position
{
	int row;
	int col;
};

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
	position m_pos;

public:
	Piece(char color, char name, position pos)
		: m_color(color), m_name(name), m_pos(pos)
	{
	}

	virtual ~Piece()
	{
	}

	char getColor()   { return m_color;    }
	char getName()	  { return m_name;     }
	int getPos1()	  { return m_pos.row;  }
	int getPos2()	  { return m_pos.col;  }
	position getPos() { return m_pos;      }

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

	virtual bool canMove(position pos, Board& board)
	{
		updatePos(pos);
		(void)board;
		return true;
	}

	void updatePos(position pos)
	{
		m_pos = pos;
	}
};