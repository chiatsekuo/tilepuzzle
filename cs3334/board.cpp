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
		if (tiles[y - 1][x] == NULL && y-1 >=0) {
			moveup(x, y - 1);
			return true;
		}
		else
			return false;
	case 'r':
		if (tiles[y][x + 1] == NULL && x + 1 <= width) {
			moveright(x + 1, y);
			return true;
		}
		else
			return false;
	case 'd':
		if (tiles[y + 1][x] == NULL && y + 1 <= height) {
			movedown(x, y + 1);
			return true;
		}
		else
			return false;
	case 'l':
		if (tiles[x - 1][y] == NULL && x - 1 >= 0) {
			moveleft(x - 1, y);
			return true;
		}
		else
			return false;
	}
	return false;
}

char * board::toString()
{
	
}
