#include "board.h"

board::board()
{
}

void board::swap(int x1, int y1, int x2, int y2)
{
	int tempx, tempy;
	tempx = x1;
	x1 = x2;
	x2 = tempx;
	tempy = y1;
	y1 = y2;
	y2 = tempy;
}

bool board::movetile(int x, int y, char dir)
{
	switch (dir) {
	case 'u':
		if (moveup(x, y))
			return true;
		return false;
	case 'r':
		if (moveright(x, y))
			return true;
		return false;
	case 'd':
		if (movedown(x, y))
			return true;
		return false;
	case 'l':
		if (moveleft(x, y))
			return true;
		return false;
	}
	return false;
}

bool board::moveup(int x, int y)
{
	if (tiles[y][x].getvalue()!=0 && y - 1 >= 0) {
		swap(x, y, x, y - 1);
		return true;
	}
	return false;
}

bool board::movedown(int x, int y)
{
	
}

bool board::moveleft(int x, int y)
{
	if (tiles[x - 1][y] == 0 && x - 1 >= 0) {
		swap(x, y, x - 1, y);
		return true;
	}
	return false;
}

bool board::moveright(int x, int y)
{
	if (tiles[y][x + 1] == 0 && x + 1 <= width) {
		swap(x, y, x+1, y);
		return true;
	}
	return false;
}

char * board::toString()
{
	return nullptr;
}
