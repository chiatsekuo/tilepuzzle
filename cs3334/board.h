#pragma once
#define boardwidth 3
#define boardheight 3
#include "tile.h"//don't include iostream

class board
{
public:
	board(int x,int y);
	board(board*from);
	void swap(int x1, int y1, int x2, int y2);//moves tiles from two locations
	


	int alltiles(tile ** t,int n);//fill the list with tile pointers &tiles[][]
	int boardx(tile * t);
	int boardy(tile *);

	//int samerow(tile * t, tile[boardwidth]);
	//int samecol(tile * t, tile[boardwidth]);

	int inversions(); // return the inversion in the board
	char* toString();

	void initalizePosition();
	void move();

	int getwidth();
	int getheight();

	

	tile tiles[boardheight][boardwidth];
private:
	int x, y;
	

};

class oneBlankGame: public board {

public:
	oneBlankGame(int x, int y);

	bool movetile(int x, int y, char dir);//should use bellow
	bool moveup(int x, int y);//should check for empty
	bool movedown(int x, int y);//return true if good
	bool moveleft(int x, int y);
	bool moveright(int x, int y);
	char possibledir(int x, int y);
	int numOfMoves();
	bool doMove(int i);
	void setEmpty();
private:
	int emptx, empty;

};

bool isInboard(int x, int y);


