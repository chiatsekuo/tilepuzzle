#pragma once
#define width
#define height



class tile {

public:
	tile();
	tile(int);
	bool isempty();

private:
	int value;
	int x;
	int y;
	bool isitEmpty;


};