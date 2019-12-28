#include "Piece.h"

class Pawn : public Piece
{
public:
	Pawn(char color, Position pos)
		: Piece(color, 'P', pos)
	{
	}

	~Pawn()
	{
	}

	bool canMove(Position pos, Board& board)
	{
		if (m_color == 'b')
		{
			if (pos.row == m_pos.row + 1 && pos.col == m_pos.col && board.getColorAt(pos) == '.')
				return true;
			else if (pos.row == m_pos.row + 1 && pos.col == m_pos.col + 1 && board.getColorAt(pos) == 'w')
				return true;
			else if (pos.row == m_pos.row + 1 && pos.col == m_pos.col - 1 && board.getColorAt(pos) == 'w')
				return true;
			else if (pos.row == m_pos.row + 2 && pos.col == m_pos.col && m_pos.row == 1)
			{
				Position newPos{ m_pos.row + 1, pos.col };
				if (board.getColorAt(pos) == '.' && board.getColorAt(newPos) == '.')
					return true;
			}
		}

		else if (m_color == 'w')
		{
			if (pos.row == m_pos.row - 1 && pos.col == m_pos.col && board.getColorAt(pos) == '.')
				return true;
			else if (pos.row == m_pos.row - 1 && pos.col == m_pos.col - 1 && board.getColorAt(pos) == 'b')
				return true;
			else if (pos.row == m_pos.row - 1 && pos.col == m_pos.col + 1 && board.getColorAt(pos) == 'b')
				return true;
			else if (pos.row == m_pos.row - 2 && pos.col == m_pos.col && m_pos.row == 6)
			{
				Position newPos{ m_pos.row - 1, pos.col };
				if (board.getColorAt(pos) == '.' && board.getColorAt(newPos) == '.')
					return true;
			}
		}
		return false;
	}
};

class Rook : public Piece
{
public:
	Rook(char color, Position pos)
		: Piece(color, 'R', pos)
	{
	}

	~Rook()
	{
	}

	bool openPathTo(Position pos, Board& board)
	{
		if (m_pos.row == pos.row) {
			if (m_pos.col < pos.col)
			{
				for (int i = m_pos.col + 1; i < pos.col; i++)
				{
					if (board.getPieceAt(m_pos.row, i) != '.')
						return false;
				}
			}
			else
			{
				for (int i = pos.col + 1; i < m_pos.col; i++)
				{
					if (board.getPieceAt(m_pos.row, i) != '.')
						return false;
				}
			}
		}
		else if (m_pos.col == pos.col) {
			if (m_pos.row < pos.row)
			{
				for (int i = m_pos.row + 1; i < pos.row; i++)
				{
					if (board.getPieceAt(i, m_pos.col) != '.')
						return false;
				}
			}
			else
			{
				for (int i = pos.row + 1; i < m_pos.row; i++)
				{
					if (board.getPieceAt(i, m_pos.col) != '.')
						return false;
				}
			}
		}
		return true;
	}

	bool canMove(Position pos, Board& board)
	{
		if (!openPathTo(pos, board))
			return false;

		if (m_color != board.getColorAt(pos))
		{
			if (pos.row == m_pos.row && pos.col != m_pos.col)
				return true;
			else if (pos.row != m_pos.row && pos.col == m_pos.col)
				return true;
		}
		return false;
	}
};

class Knight : public Piece
{
public:
	Knight(char color, Position pos)
		: Piece(color, 'n', pos)
	{
	}

	~Knight()
	{
	}

	bool canMove(Position pos, Board& board)
	{
		if (m_color != board.getColorAt(pos))
		{
			if (pos.row == m_pos.row + 1 && (pos.col == m_pos.col - 2 || pos.col == m_pos.col + 2))
				return true;
			else if (pos.row == m_pos.row + 2 && (pos.col == m_pos.col - 1 || pos.col == m_pos.col + 1))
				return true;
			else if (pos.row == m_pos.row - 1 && (pos.col == m_pos.col - 2 || pos.col == m_pos.col + 2))
				return true;
			else if (pos.row == m_pos.row - 2 && (pos.col == m_pos.col - 1 || pos.col == m_pos.col + 1))
				return true;
		}
		return false;
	}
};

class Bishop : public Piece
{
public:
	Bishop(char color, Position pos)
		: Piece(color, 'B', pos)
	{
	}

	~Bishop()
	{
	}

	bool openPathTo(Position pos, Board& board)
	{
		int rowOffset = 0;
		int colOffset = 0;

		if (pos.row > m_pos.row)
			rowOffset = 1;
		else if (pos.row < m_pos.row)
			rowOffset = -1;
		else
			rowOffset = 0;

		if (pos.col > m_pos.col)
			colOffset = 1;
		else if (pos.col < m_pos.col)
			colOffset = -1;
		else
			colOffset = 0;

		int j = m_pos.col + colOffset;
		for (int i = m_pos.row + rowOffset; i != pos.row; i += rowOffset)
		{
			Position newPos{ i, j };
			if (board.getColorAt(newPos) != '.')
				return false;

			j += colOffset;
		}
		return true;
	}

	bool canMove(Position pos, Board& board)
	{
		if (std::abs(pos.row - m_pos.row) != std::abs(pos.col - m_pos.col) || m_color == board.getColorAt(pos))
			return false;
		if (!openPathTo(pos, board))
			return false;

		return true;
	}
};

class Queen : public Piece
{
public:
	Queen(char color, Position pos)
		: Piece(color, 'Q', pos)
	{
	}

	~Queen()
	{
	}

	bool openPathTo(Position pos, Board& board)
	{
		Rook rook = Rook(m_color, m_pos);
		if (rook.canMove(pos, board))
		{
			return true;
		}
		
		Bishop bishop = Bishop(m_color, m_pos);
		if (bishop.canMove(pos, board))
		{
			return true;
		}
		return false;
	}

	bool canMove(Position pos, Board& board)
	{
		if (!openPathTo(pos, board))
		{
			return false;
		}

		if (m_color != board.getColorAt(pos)) {
			if (std::abs(pos.row - m_pos.row) == std::abs(pos.col - m_pos.col) && 
				m_color != board.getColorAt(pos))
				return true;
			else if (pos.row - m_pos.row == 0 || pos.col - m_pos.col == 0)
				return true;
		}
		return false;
	}
};

class King : public Piece
{
private:
	std::vector<std::vector<int>> kingPositions = { {-1, -1}, {-1, 0}, {-1, 1},
													{0, -1},           {0, 1},
													{1, -1},  {1, 0},  {1, 1} };

public:
	King(char color, Position pos)
		: Piece(color, 'K', pos)
	{
	}

	~King()
	{
	}

	bool canMove(Position pos, Board& board)
	{
		if (m_color != board.getColorAt(pos))
		{
			for (std::size_t i = 0; i != kingPositions.size(); i++)
			{
				if (pos.row == m_pos.row + kingPositions[i][0] && pos.col == m_pos.col + kingPositions[i][1])
					return true;
			}
		}
		return false;
	}
};