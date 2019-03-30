#include "tile.h"

tile::tile()
{
	isitEmpty = true;
}
tile::tile(int v) {
	value = v;
	isitEmpty = false;
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

int tile::adjx(int v)
{
	x += v;
	return x;
}

int tile::adjy(int v)
{
	y += v;
	return y;
}

bool tile::gopos(int x, int y)
{
	if (this->x = x && this->y == y) {
		return true;
	}
	if (this->x > x) {
		adjx(-speed);
	}
	else if(this->x < x) {
		adjx(speed);
	}

	if (this->y > y) {
		adjy(-speed);
	}
	else if (this->y < y) {
		adjy(speed);
	}
	return false;
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


