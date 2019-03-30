#include "tile.h"

tile::tile()
{
	isitEmpty = true;
}
tile::tile(int v) {
	value = v;
}

bool tile::isempty()
{
	return isitEmpty;
}

int tile::getx()
{
	return x;
}

void tile::setx(int v)
{
	x = v;
}

int tile::gety()
{
	return y;
}

void tile::sety(int v)
{
	y = v;
}

int tile::getw()
{
	return width;
}

int tile::geth()
{
	return height;
}

int tile::getvalue()
{
	return value;
}

bool tile::isinside(int x, int y)
{
	if (x > this->x&&x < this->x + this->getw()) {
		if (y > this->y&&y < this->y + this->geth()) {
			return true;
		}
	}
	return false;
}
