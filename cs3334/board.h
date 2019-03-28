#pragma once
#define boardwidth 3
#define boardheight 3
#include "tile.h"
#include <iostream>
using namespace std;

class board
{
public:
	board();

	void swap(int x1, int y1, int x2, int y2);//moves tiles from two locations
	tile * getTile(int x,int y);
	bool movetile(int x, int y,char dir);//should use bellow
	bool moveup(int x, int y);//should check for empty
	bool movedown(int x, int y);
	bool moveleft(int x, int y);
	bool moveright(int x, int y);

	int realx(tile * t);
	int realy(tile * t);
	int samerow(tile * t, tile[boardwidth]);
	int samecol(tile * t, tile[boardwidth]);

	int inversions(); // return the inversion in the board
	char* toString();
private:

	tile tiles[boardheight][boardwidth];

};

