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

	char color() const      { return m_color;    }
	char name() const       { return m_name;     }
	int row() const	        { return m_pos.row;  }
	int col() const         { return m_pos.col;  }
	Position getPos() const { return m_pos;      }

	void tellPos() { std::cout << "(" << row() << ", " << col() << ")\n"; }

	void tellInfo()
	{
		std::string pieceColor;
		std::string pieceName;

		color() == 'w' ? pieceColor = "White" : pieceColor = "Black";

		if (name() == 'P')
			pieceName = "pawn";
		else if (name() == 'R')
			pieceName = "rook";
		else if (name() == 'n')
			pieceName = "knight";
		else if (name() == 'B')
			pieceName = "bishop";
		else if (name() == 'Q')
			pieceName = "queen";
		else
			pieceName = "king";

		std::cout << pieceColor << " " << pieceName << " ";
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
