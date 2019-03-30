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
		if (moveup(x, y)) {
			return true;
		}
		else {
			return false;
		}
	case 'r':
		if (moveup(x, y)) {
			return true;
		}
		else {
			return false;
		}
	case 'd':
		if (moveup(x, y)) {
			return true;
		}
		else {
			return false;
		}
	case 'l':
		if (moveup(x, y)) {
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

bool board::moveup(int x, int y)
{
	return false;
}

char * board::toString()
{
	return 0;
}
