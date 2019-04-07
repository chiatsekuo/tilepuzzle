#include "tile.h"

visualtile visualtile::operator=(const basetile& b)
{
	visualtile end;
	end.image = nullptr;
	end.x = 0;
	end.y = 0;

	return end;
}

visualtile::visualtile():basetile()
{
}
visualtile::visualtile(int v): basetile(v){
}

basetile::basetile()
{
	isitEmpty = true;
	value = 10;
}

basetile::basetile(int v)
{
	value = v;
	isitEmpty = false;
}

bool basetile::isempty()
{
	return isitEmpty;
}

int visualtile::getx()
{
	return x;
}

void visualtile::setx(int v)
{
	x = v;
}

int visualtile::gety()
{
	return y;
}

void visualtile::sety(int v)
{
	y = v;
}

int visualtile::getw()
{
	return tilewidth;
}

int visualtile::geth()
{
	return tileheight;
}

int basetile::getvalue()
{
	return value;
}

void basetile::setvalue(int v)
{
	isitEmpty = false;
	value = v;
}

int visualtile::adjx(int v)
{
	x += v;
	return x;
}

int visualtile::adjy(int v)
{
	y += v;
	return y;
}

bool visualtile::gopos(int x, int y)
{
	if (this->x == x && this->y == y) {
		return true;
	}
	if (this->x > speed+x) {
		adjx(-speed);
	}
	else if(this->x < x-speed) {
		adjx(speed);
	}
	else {
		setx(x);
	}

	if (this->y > speed+ y) {
		adjy(-speed);
	}
	else if (this->y < -speed+ y) {
		adjy(speed);
	}
	else {
		sety(y);
	}
	return false;
}


bool visualtile::isinside(int x, int y)
{
	if (x > this->x&&x < this->x + this->getw()) {
		if (y > this->y&&y < this->y + this->geth()) {
			return true;
		}
	}
	return false;
}

ALLEGRO_BITMAP * visualtile::getimage()
{
	return image;
}

void visualtile::setimage(ALLEGRO_BITMAP * im)
{
	image = im;
}


