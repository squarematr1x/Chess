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
	Position m_pos;

public:
	Piece(char color, char name, Position pos)
		: m_color(color), m_name(name), m_pos(pos)
	{
	}

	virtual ~Piece()
	{
	}

	char getColor()   { return m_color;    }
	char getName()	  { return m_name;     }
	int getRow()	  { return m_pos.row;  }
	int getCol()	  { return m_pos.col;  }
	Position getPos() { return m_pos;      }

	void tellPos() { std::cout << "(" << getRow() << ", " << getCol() << ")\n"; }

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

	virtual bool canMove(Position pos, Board& board)
	{
		updatePos(pos);
		(void)board;
		return true;
	}

	void updatePos(Position pos)
	{
		m_pos = pos;
	}
};