#pragma once
#define width
#define height



class tile {

public:
	tile();
	tile(int);
	bool isempty();
	//getters and setters
	//add width and height in defilne ^
	bool isinside(int x, int y);// true if point is in side


private:
	int value;
	int x;
	int y;
	bool isitEmpty;


};