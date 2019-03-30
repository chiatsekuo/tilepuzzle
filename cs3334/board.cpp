#include "board.h"
#include <stdlib.h>
#include <string.h>

board::board()
{
	for (int i = 0; i < boardwidth; i++) {
		for (int j = 0; j < boardheight; j++) {
			tiles[j][i] = tile((j)*boardwidth + i+1);
		}
	}
}

void board::swap(int x1, int y1, int x2, int y2)
{
	tile temp=tiles[y1][x1];
	tiles[y1][x1] = tiles[y2][x2];
	tiles[y2][x2] = temp;
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
	if (y == 0 || !tiles[y-1][x].isempty()) {
		return false;
	}
	else {
		swap(x, y, x, y-1);
		return true;
	}
}

bool board::movedown(int x, int y)
{
	if (y == boardheight-1 || !tiles[y+1][x].isempty()) {
		return false;
	}
	else {
		swap(x, y, x, y + 1 );
		return true;
	}
}

bool board::moveleft(int x, int y)
{
	if (x == 0 || !tiles[y][x-1].isempty()) {
		return false;
	}
	else {
		swap(x, y, x-1, y);
		return true;
	}
}

bool board::moveright(int x, int y)
{
	if (x == boardwidth-1 || !tiles[y][x+1].isempty()) {
		return false;
	}
	else {
		swap(x, y, x + 1, y);
		return true;
	}
}

int board::alltiles(tile ** t, int n)
{
	int index = 0;
	for (int i = 0; i < boardwidth; i++) {
		for (int j = 0; j < boardheight; j++) {
			t[index] = &tiles[j][i];
			index++;
		}
	}
	return 0;
}

char * board::toString()
{
	char * arr = new char[3*boardheight*boardwidth + 1];
	memset(arr, 0, 3 * boardheight*boardwidth + 1);
	int index = 0;
	for (int y = 0; y < boardheight; y++) {
		for (int x = 0; x < boardwidth; x++) {
			char buf[3] = { 0 };
			_itoa_s(tiles[y][x].getvalue(), buf, 10);
			strcat_s(arr, 3*boardheight*boardwidth + 1, buf);
		}
		strcat_s(arr, 3 * boardheight*boardwidth + 1, "\n");
	}
	return arr;
}

void board::initalizePosition()
{
	for (int i = 0; i < boardheight; i++) {
		for (int j = 0; j < boardwidth; j++) {
			tiles[i][j].sety(height*i);
			tiles[i][j].setx(width*j);
		}
	}
}
