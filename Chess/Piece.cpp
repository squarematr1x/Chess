#include "Piece.h"

class Pawn : public Piece
{
public:
	Pawn(char color, int pos1, int pos2)
		: Piece(color, 'P', pos1, pos2)
	{
	}

	~Pawn()
	{
	}

	bool canMove(int row, int col, Board& board)
	{
		if (m_color == 'b')
		{
			if (row == m_pos1 + 1 && col == m_pos2 && board.getOwner(row, col) == '.')
				return true;
			else if (row == m_pos1 + 2 && col == m_pos2 && m_pos1 == 1 && board.getOwner(row, col) == '.' && board.getOwner(m_pos1 + 1, col) == '.')
				return true;
			else if (row == m_pos1 + 1 && col == m_pos2 + 1 && board.getOwner(row, col) == 'w')
				return true;
			else if (row == m_pos1 + 1 && col == m_pos2 - 1 && board.getOwner(row, col) == 'w')
				return true;
		}

		else if (m_color == 'w')
		{
			if (row == m_pos1 - 1 && col == m_pos2 && board.getOwner(row, col) == '.')
				return true;
			else if (row == m_pos1 - 2 && col == m_pos2 && m_pos1 == 6 && board.getOwner(row, col) == '.' && board.getOwner(m_pos1 - 1, col) == '.')
				return true;
			else if (row == m_pos1 - 1 && col == m_pos2 - 1 && board.getOwner(row, col) == 'b')
				return true;
			else if (row == m_pos1 - 1 && col == m_pos2 + 1 && board.getOwner(row, col) == 'b')
				return true;
		}
		return false;
	}
};

class Rook : public Piece
{
public:
	Rook(char color, int pos1, int pos2)
		: Piece(color, 'R', pos1, pos2)
	{
	}

	~Rook()
	{
	}

	bool openPathTo(int row1, int col1, int row2, int col2, Board& board)
	{
		if (row1 == row2) {
			if (col1 < col2)
			{
				for (int i = col1 + 1; i < col2; i++)
				{
					if (board.getCharAt(row1, i) != '.')
						return false;
				}
			}
			else
			{
				for (int i = col2 + 1; i < col1; i++)
				{
					if (board.getCharAt(row1, i) != '.')
						return false;
				}
			}
		}
		else if (col1 == col2) {
			if (row1 < row2)
			{
				for (int i = row1 + 1; i < row2; i++)
				{
					if (board.getCharAt(i, col1) != '.')
						return false;
				}
			}
			else
			{
				for (int i = row2 + 1; i < row1; i++)
				{
					if (board.getCharAt(i, col1) != '.')
						return false;
				}
			}
		}
		return true;
	}

	bool canMove(int row, int col, Board& board)
	{
		if (!openPathTo(m_pos1, m_pos2, row, col, board))
			return false;

		if (m_color != board.getOwner(row, col))
		{
			if (row == m_pos1 && col != m_pos2)
				return true;
			else if (row != m_pos1 && col == m_pos2)
				return true;
		}
		return false;
	}
};

class Knight : public Piece
{
public:
	Knight(char color, int pos1, int pos2)
		: Piece(color, 'n', pos1, pos2)
	{
	}

	~Knight()
	{
	}

	bool canMove(int row, int col, Board& board)
	{
		if (m_color != board.getOwner(row, col))
		{
			if (row == m_pos1 + 1 && (col == m_pos2 - 2 || col == m_pos2 + 2))
				return true;
			else if (row == m_pos1 + 2 && (col == m_pos2 - 1 || col == m_pos2 + 1))
				return true;
			else if (row == m_pos1 - 1 && (col == m_pos2 - 2 || col == m_pos2 + 2))
				return true;
			else if (row == m_pos1 - 2 && (col == m_pos2 - 1 || col == m_pos2 + 1))
				return true;
		}
		return false;
	}
};

class Bishop : public Piece
{
public:
	Bishop(char color, int pos1, int pos2)
		: Piece(color, 'B', pos1, pos2)
	{
	}

	~Bishop()
	{
	}

	bool openPathTo(int row, int col, Board& board)
	{
		int rowOffset = 0;
		int colOffset = 0;

		if (row > m_pos1)
			rowOffset = 1;
		else
			rowOffset = -1;

		if (col > m_pos2)
			colOffset = 1;
		else
			colOffset = -1;

		int j = m_pos2 + colOffset;
		for (int i = m_pos1 + rowOffset; i != row; i += rowOffset)
		{
			if (board.getOwner(i, j) != '.')
				return false;

			j += colOffset;
		}
		return true;
	}

	bool canMove(int row, int col, Board& board)
	{
		if (std::abs(row - m_pos1) != std::abs(col - m_pos2) || m_color == board.getOwner(row, col))
			return false;
		if (!openPathTo(row, col, board))
			return false;

		return true;
	}
};

class Queen : public Piece
{
public:
	Queen(char color, int pos1, int pos2)
		: Piece(color, 'Q', pos1, pos2)
	{
	}

	~Queen()
	{
	}

	bool openPathTo(int row, int col, Board& board)
	{
		int rowOffset = 0;
		int colOffset = 0;

		if (row == m_pos1 && col == m_pos2)
			return false;

		if (row > m_pos1)
			rowOffset = 1;
		else if (row < m_pos1)
			rowOffset = -1;

		if (col > m_pos2)
			colOffset = 1;
		else if (col < m_pos2)
			colOffset = -1;

		if (m_pos1 != row) 
		{
			int j = m_pos2 + colOffset;
			for (int i = m_pos1 + rowOffset; i != row; i += rowOffset)
			{
				std::cout << "These: " << i << "," << j << "\n";
				if (board.getOwner(i, j) != '.')
					return false;
				j += colOffset;
			}
		}
		else
		{
			int i = m_pos1;
			for (int j = m_pos2 + colOffset; j != col; j += colOffset)
			{
				std::cout << "These: " << i << "," << j << "\n";
				if (board.getOwner(i, j) != '.')
					return false;
			}
		}
		return true;
	}

	bool canMove(int row, int col, Board& board)
	{
		if (!openPathTo(row, col, board))
		{
			return false;
		}

		if (m_color != board.getOwner(row, col)) {
			if (std::abs(row - m_pos1) == std::abs(col - m_pos2) && m_color != board.getOwner(row, col))
				return true;
			else if (row - m_pos1 == 0 || col - m_pos2 == 0)
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
	King(char color, int pos1, int pos2)
		: Piece(color, 'K', pos1, pos2)
	{
	}

	~King()
	{
	}

	bool canMove(int row, int col, Board& board)
	{
		if (m_color != board.getOwner(row, col))
		{
			for (std::size_t i = 0; i != kingPositions.size(); i++)
			{
				if (row == m_pos1 + kingPositions[i][0] && col == m_pos2 + kingPositions[i][1])
					return true;
			}
		}
		return false;
	}
};