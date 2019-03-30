#pragma once
#define width 20
#define height 20



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
	//getters and setters
	//add width and height in defilne ^
	bool isinside(int x, int y);// true if point is in side


private:
	int value;
	int x=0;
	int y=0;
	bool isitEmpty;


};