#pragma once
#define tilewidth 100
#define tileheight 100
#define speed 10

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>



class basetile {
public:
	basetile();
	basetile(int);
	bool isempty();
	int getvalue();
	void setvalue(int v);
private:
	int value;
	bool isitEmpty;
};

class visualtile:public basetile {

public:
	visualtile operator=(const basetile& b);
	visualtile();
	visualtile(int);
	
	int getx();
	void setx(int v);
	int gety();
	void sety(int v);
	int getw();
	int geth();
	
	int adjx(int v);
	int adjy(int v);

	bool gopos(int x, int y);
	//getters and setters
	//add width and height in defilne ^
	bool isinside(int x, int y);// true if point is in side
	ALLEGRO_BITMAP* getimage();
	void setimage(ALLEGRO_BITMAP*im);

private:
	ALLEGRO_BITMAP * image;
	int x=0;
	int y=0;
};