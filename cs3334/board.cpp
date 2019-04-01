#include "board.h"
#include <stdlib.h>
#include <string.h>


board::board(int x, int y)
{
	this->x = x;
	this->y = y;
	for (int i = 0; i < boardwidth; i++) {
		for (int j = 0; j < boardheight; j++) {
			if (i == boardwidth - 1 && j == boardheight - 1) {
				tiles[boardwidth - 1][boardheight - 1] = visualtile();
			}
			else {
				tiles[j][i] = visualtile((j)*boardwidth + i + 1);
			}
		}
	}
}

board::board(board * from)
{
	for (int y = 0; y < boardheight; y++) {
		for (int x = 0; x < boardwidth; x++) {
			tiles[y][x] = from->tiles[y][x].getvalue();
		}
	}
}

void board::swap(int x1, int y1, int x2, int y2)
{
	visualtile temp=tiles[y1][x1];
	tiles[y1][x1] = tiles[y2][x2];
	tiles[y2][x2] = temp;
}

bool oneBlankGame::movetile(int x, int y, char dir)
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

bool oneBlankGame::moveup(int x, int y)
{
	if (y == 0 || !tiles[y-1][x].isempty()) {
		return false;
	}
	else {
		swap(x, y, x, y-1);
		return true;
	}
}

bool oneBlankGame::movedown(int x, int y)
{
	if (y == boardheight-1 || !tiles[y+1][x].isempty()) {
		return false;
	}
	else {
		swap(x, y, x, y + 1 );
		return true;
	}
}

bool oneBlankGame::moveleft(int x, int y)
{
	if (x == 0 || !tiles[y][x-1].isempty()) {
		return false;
	}
	else {
		swap(x, y, x-1, y);
		return true;
	}
}

bool oneBlankGame::moveright(int x, int y)
{
	if (x == boardwidth-1 || !tiles[y][x+1].isempty()) {
		return false;
	}
	else {
		swap(x, y, x + 1, y);
		return true;
	}
}

int board::alltiles(visualtile ** t, int n)
{
	int index = 0;
	for (int i = 0; i < boardheight; i++) {
		for (int j = 0; j < boardwidth; j++) {
			t[index] = &tiles[i][j];
			index++;
		}
	}
	return 0;
}

int board::inversions()
{
	int count = 0;
	int value;

	visualtile ** arr = new visualtile* [boardwidth * boardheight];
	this->alltiles(arr, boardwidth * boardheight);
	for (int i = 0; i < boardwidth * boardheight; i++) {
		if (arr[i]->isempty())
			i++;
		for (int j = i + 1; j < boardwidth * boardheight; j++) {
			if (arr[i]->getvalue() > arr[j]->getvalue())
				count++;
		}
		
	}
	/*

	for (int i = 0; i < boardheight; i++) {
		for (int j = 0; j < boardwidth; j++) {
			value = tiles[i][j].getvalue();

			for (int k = 0; k < boardheight; k++) {
				for (int l = 0; l < boardwidth; l++) {
					if ((k == i && j < l) || (k > i)) {
						if (tiles[k][l].getvalue() > value) {
							count++;
						}
					} 
				}
			}
		}
	}
	*/
	return count;
}

int board::boardx(visualtile * t)
{
	for (int i = 0; i < boardheight; i++) {
		for (int j = 0; j < boardwidth; j++) {
			if (t == &tiles[j][i]) {
				return i;
			}
		}
	}
}

int board::boardy(visualtile * t)
{
	for (int i = 0; i < boardheight; i++) {
		for (int j = 0; j < boardwidth; j++) {
			if (t == &tiles[j][i]) {
				return j;
			}
		}
	}
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
			tiles[i][j].sety(tileheight*i + y);
			tiles[i][j].setx(tilewidth*j + x);
		}
	}
}

void board::move()
{
	for (int i = 0; i < boardheight; i++) {
		for (int j = 0; j < boardwidth; j++) {
			tiles[i][j].gopos(tilewidth*j + x, tileheight*i + y);
		}
	}
}

int board::getwidth()
{
	return boardwidth * tilewidth;
}

int board::getheight()
{
	return boardheight * tileheight;
}

char oneBlankGame::possibledir(int x, int y)
{
	if (tiles[y - 1][x].isempty() && y > 0) {
		return 'u';
	}
	else if (tiles[y][x + 1].isempty() && x < boardwidth - 1) {
		return 'r';
	}
	else if (tiles[y + 1][x].isempty() && y < boardheight - 1) {
		return 'd';
	}
	else if (tiles[y][x - 1].isempty() && x > 0) {
		return 'l';
	}
	else
		return 'o';
	
}

int oneBlankGame::numOfMoves()
{
	int num = 0;
	this->setEmpty();
	if (isInboard(emptx - 1, empty)) num++;
	if (isInboard(empty, emptx + 1))num++;
	if (isInboard(empty + 1, emptx))num++;
	if (isInboard(empty, emptx + 1))num++;
	return num;
}

bool oneBlankGame::doMove(int i)
{
	this->setEmpty();
	if (isInboard(empty + 1, emptx)) {
		if (i == 0) {
			return movetile(emptx, empty+1, 'u');
		}
		else {
			i--;
		}
	}
	if (isInboard(empty, emptx - 1)) {
		if (i == 0) {
			return movetile(emptx-1, empty, 'r');
		}
		else {
			i--;
		}
	}
	if (isInboard(empty - 1, emptx)) {
		if (i == 0) {
			return movetile(emptx, empty-1, 'd');
		}
		else {
			i--;
		}
	}
	if (isInboard(empty, emptx+1)) {
		if (i == 0) {
			return movetile(emptx+1, empty, 'l');
		}
		else {
			i--;
		}
	}
	return false;
}

void oneBlankGame::setEmpty()
{
	for (int i = 0; i < boardheight; i++) {
		for (int j = 0; j < boardwidth; j++) {
			if (tiles[i][j].isempty()) {
				emptx = j;
				empty = i;
			}
		}
	}
}

bool isInboard(int y, int x)
{
	if (y >= 0 && y <= boardheight - 1 && x >= 0 && x <= boardwidth - 1) {
		return true;
	}
	return false;
}

oneBlankGame::oneBlankGame(int x, int y):board(x,y)
{

}

rowChangeGame::rowChangeGame(int x, int y):board(x, y)
{
}
bool rowChangeGame::movetile(int x, int y, char dir)
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

bool rowChangeGame::moveup(int x, int y)
{
	if (y == 0 || !tiles[y - 1][x].isempty()) {
		return false;
	}
	else {
		swap(x, y, x, y - 1);
		return true;
	}
}

bool rowChangeGame::movedown(int x, int y)
{
	if (y == boardheight - 1 || !tiles[y + 1][x].isempty()) {
		return false;
	}
	else {
		swap(x, y, x, y + 1);
		return true;
	}
}

bool rowChangeGame::moveleft(int x, int y)
{
	if (x == 0 || !tiles[y][x - 1].isempty()) {
		return false;
	}
	else {
		swap(x, y, x - 1, y);
		return true;
	}
}

bool rowChangeGame::moveright(int x, int y)
{
	if (x == boardwidth - 1 || !tiles[y][x + 1].isempty()) {
		return false;
	}
	else {
		swap(x, y, x + 1, y);
		return true;
	}
}
char rowChangeGame::possibledir(int x, int y)
{
	if (tiles[y - 1][x].isempty() && y > 0) {
		return 'u';
	}
	else if (tiles[y][x + 1].isempty() && x < boardwidth - 1) {
		return 'r';
	}
	else if (tiles[y + 1][x].isempty() && y < boardheight - 1) {
		return 'd';
	}
	else if (tiles[y][x - 1].isempty() && x > 0) {
		return 'l';
	}
	else
		return 'o';

}

int rowChangeGame::numOfMoves()
{
	int num = 0;
	this->setEmpty();
	if (isInboard(emptx - 1, empty)) num++;
	if (isInboard(empty, emptx + 1))num++;
	if (isInboard(empty + 1, emptx))num++;
	if (isInboard(empty, emptx + 1))num++;
	return num;
}

bool rowChangeGame::doMove(int i)
{
	this->setEmpty();
	if (isInboard(empty + 1, emptx)) {
		if (i == 0) {
			return movetile(emptx, empty + 1, 'u');
		}
		else {
			i--;
		}
	}
	if (isInboard(empty, emptx - 1)) {
		if (i == 0) {
			return movetile(emptx - 1, empty, 'r');
		}
		else {
			i--;
		}
	}
	if (isInboard(empty - 1, emptx)) {
		if (i == 0) {
			return movetile(emptx, empty - 1, 'd');
		}
		else {
			i--;
		}
	}
	if (isInboard(empty, emptx + 1)) {
		if (i == 0) {
			return movetile(emptx + 1, empty, 'l');
		}
		else {
			i--;
		}
	}
	return false;
}

void rowChangeGame::setEmpty()
{
	for (int i = 0; i < boardheight; i++) {
		for (int j = 0; j < boardwidth; j++) {
			if (tiles[i][j].isempty()) {
				emptx = j;
				empty = i;
			}
		}
	}
}
bool rowChangeGame::movetile(int x, int y, char dir)
{
	return false;
}
