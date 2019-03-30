#pragma once
#define boardwidth 3
#define boardheight 3
#include "tile.h"//don't include iostream

class board
{
public:
	board(int x,int y);

	void swap(int x1, int y1, int x2, int y2);//moves tiles from two locations
	tile * getTile(int x,int y);
	bool movetile(int x, int y,char dir);//should use bellow
	bool moveup(int x, int y);//should check for empty
	bool movedown(int x, int y);//return true if good
	bool moveleft(int x, int y);
	bool moveright(int x, int y);


	int alltiles(tile ** t,int n);//fill the list with tile pointers &tiles[][]
	int realx(tile * t);
	int realy(tile * t);
	int boardx(tile * t);
	int boardy(tile *);
	int samerow(tile * t, tile[boardwidth]);
	int samecol(tile * t, tile[boardwidth]);

	int inversions(); // return the inversion in the board
	char* toString();

	void initalizePosition();
	void move();

	char possibledir(int x, int y);

private:
	int x, y;
	tile tiles[boardheight][boardwidth];

};




