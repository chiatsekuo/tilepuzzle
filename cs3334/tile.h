#pragma once
#define tilewidth 100
#define tileheight 100
#define speed 10

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

class tile {

public:
	tile();
	tile(int);
	bool isempty();
	int getx();
	void setx(int v);
	int gety();
	void sety(int v);
	int getw();
	int geth();
	int getvalue();
	int adjx(int v);
	int adjy(int v);

	bool gopos(int x, int y);
	//getters and setters
	//add width and height in defilne ^
	bool isinside(int x, int y);// true if point is in side
	ALLEGRO_BITMAP* getimage();


private:
	ALLEGRO_BITMAP * image;
	int value;
	int x=0;
	int y=0;
	bool isitEmpty;


};