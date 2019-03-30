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
	if (false) {
		return true;
	}
	else {
		return false;
	}
}

bool board::movedown(int x, int y)
{
	return false;
}

bool board::moveleft(int x, int y)
{
	return false;
}

bool board::moveright(int x, int y)
{
	return false;
}

int board::alltiles(tile ** t, int n)
{
	int index = 0;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			t[index] = &tiles[j][i];
			index++;
		}
	}
		
	return 0;
}

char * board::toString()
{
	return nullptr;
}
