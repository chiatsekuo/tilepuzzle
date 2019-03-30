#pragma once
#define width 100
#define height 100



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
	//getters and setters
	//add width and height in defilne ^
	bool isinside(int x, int y);// true if point is in side


private:
	int value;
	int x=0;
	int y=0;
	bool isitEmpty;


};