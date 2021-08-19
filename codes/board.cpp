#include "board.h"
#include <stdlib.h>
#include <string.h>


board::board(int x, int y)
{
	this->x = x;
	this->y = y;

	wholeimage = al_create_bitmap(getwidth(), getheight());
	al_set_target_bitmap(wholeimage);
	ALLEGRO_BITMAP * image = al_load_bitmap("image.jpg");
	al_draw_scaled_bitmap(image,0,0,al_get_bitmap_width(image), al_get_bitmap_height(image),0,0, getwidth(), getheight(),0);



	for (int i = 0; i < boardwidth; i++) {
		for (int j = 0; j < boardheight; j++) {
			if (i == boardwidth - 1 && j == boardheight - 1) {
				tiles[boardwidth - 1][boardheight - 1] = visualtile();
			}
			else {
				tiles[j][i] = visualtile((j)*boardwidth + i + 1);
			}
			tiles[j][i].setimage(al_create_sub_bitmap(wholeimage, i*tilewidth, j*tileheight, tilewidth, tileheight));
		}
	}
	al_destroy_bitmap(image);
}

board::board(board * from)
{
	for (int y = 0; y < boardheight; y++) {
		for (int x = 0; x < boardwidth; x++) {
			if (from->tiles[y][x].isempty()) {
				this->tiles[y][x] = basetile();
			
			}
			else {
				this->tiles[y][x] = basetile();
				tiles[y][x].setvalue(from->tiles[y][x].getvalue());
			}
		}
	}
}

void board::swap(int x1, int y1, int x2, int y2)
{
	visualtile temp=tiles[y1][x1];
	tiles[y1][x1] = tiles[y2][x2];
	tiles[y2][x2] = temp;
}

int board::getx()
{
	return x;
}

int board::gety()
{
	return y;
}

int board::setx(int v)
{
	x = v;
	return 0;
}

int board::sety(int v)
{
	y = v;
	return 0;
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
	delete arr;
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

int board::aiinversion()
{
	int count = 0;
	int value;

	visualtile ** arr = new visualtile*[boardwidth * boardheight];
	this->alltiles(arr, boardwidth * boardheight);
	for (int i = 0; i < boardwidth * boardheight; i++) {
		for (int j = i + 1; j < boardwidth * boardheight; j++) {
			if (arr[i]->isempty()) {
				count++;
			}
			else if (arr[i]->getvalue() > arr[j]->getvalue()){
				count++;
			}
		}

	}
	delete arr;
	return count;
}

int board::aimanhattandistance()
{
	int count = 0;
	int value;

	visualtile ** arr = new visualtile*[boardwidth * boardheight];
	this->alltiles(arr, boardwidth * boardheight);
	for (int i = 0; i < boardwidth * boardheight; i++) {
		if (!arr[i]->isempty()) {
			count += abs(arr[i]->getvalue() - (i+1));
		}
		
	}
	delete arr;
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

int board::samerow(visualtile * t, visualtile*fil[boardwidth])
{
	int y = boardy(t);
	for (int i = 0; i < boardwidth; i++) {
		fil[i]=&tiles[y][i];
	}
	return boardwidth;
}

int board::samecol(visualtile * t, visualtile * fil[boardheight])
{
	int x = boardx(t);
	for (int i = 0; i < boardheight; i++) {
		fil[i] = &tiles[i][x];
	}
	return boardheight;
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

bool board::issame(board * other)
{
	for (int x = 0; x < boardwidth; x++) {
		for (int y = 0; y < boardheight; y++) {
			if (tiles[x][y].getvalue() != other->tiles[x][y].getvalue()) {
				return false;
			}
		}
	}

	return true;
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

oneBlankGame::oneBlankGame(int x, int y) :board(x, y)
{

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
	if (isInboard(empty - 1, emptx)) num++;
	if (isInboard(empty, emptx + 1))num++;
	if (isInboard(empty + 1, emptx))num++;
	if (isInboard(empty, emptx - 1))num++;
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
				break;
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


/*********************************************************************second game************************************************************************/
rowChangeGame::rowChangeGame(int x, int y):board(x, y)
{
	ALLEGRO_BITMAP*temp = tiles[boardwidth - 1][boardheight - 1].getimage();
	tiles[boardwidth - 1][boardheight - 1] = visualtile(boardheight*boardwidth);
	tiles[boardwidth - 1][boardheight - 1].setimage(temp);
}
rowChangeGame::rowChangeGame(rowChangeGame * from):board((board*)from)
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
	for (int i = 0; i < boardheight-1; i++) {
		swap(x, i, x, i + 1);
	}
	return true;
}

bool rowChangeGame::movedown(int x, int y)
{
	for (int i = boardheight - 1; i > 0; i--) {
		swap(x, i, x, i - 1);
	}
	return true;
}

bool rowChangeGame::moveleft(int x, int y)
{
	for (int i = 0; i < boardwidth-1; i++) {
		swap(i, y, i+1, y);
	}
	return true;
}

bool rowChangeGame::moveright(int x, int y)
{
	for (int i = boardwidth - 1; i > 0 ; i--) {
		swap(i, y, i -1 , y);
	}
	return true;
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
oneBlankGame::oneBlankGame(oneBlankGame * from) :board((board *)from)
{
	this->setEmpty();
}


int rowChangeGame::numOfMoves()
{
	int num = 0;
	this->setEmpty();
	if (isInboard(emptx - 1, empty)) num++;
	if (isInboard(empty, emptx + 1))num++;
	if (isInboard(empty + 1, emptx))num++;
	if (isInboard(empty, emptx + 1))num++;
	return 12;
}

bool rowChangeGame::doMove(int i)
{
	switch (i) {
	case 0:
		return movetile(0, 0, 'u');
	case 1:
		return movetile(0, 0, 'd');
	case 2:
		return movetile(0, 0, 'l');
	case 3:
		return movetile(0, 0, 'r');
	case 4:
		return movetile(1, 1, 'u');
	case 5:
		return movetile(1, 1, 'd');
	case 6:
		return movetile(1, 1, 'l');
	case 7:
		return movetile(1, 1, 'r');
	case 8:
		return movetile(2, 2, 'u');
	case 9:
		return movetile(2, 2, 'd');
	case 10:
		return movetile(2, 2, 'l');
	case 11:
		return movetile(2, 2, 'r');
	}
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
