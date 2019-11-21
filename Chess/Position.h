#pragma once
class Position
{
private:
	int m_from1;
	int m_from2;
	int m_to1;
	int m_to2;

public:
	Position(int from1, int from2, int to1, int to2)
		: m_from1(from1), m_from2(from2), m_to1(to1), m_to2(to2)
	{
	}
	int from1() { return m_from1; }
	int from2() { return m_from2; }
	int to1() { return m_to1; }
	int to2() { return m_to2; }
};

