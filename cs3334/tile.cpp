#include "tile.h"

visualtile::visualtile():basetile()
{
}
visualtile::visualtile(int v): basetile(v){
	image = al_create_bitmap(100, 100);
	ALLEGRO_BITMAP * temp = al_load_bitmap("image.jpg");
	
	al_set_target_bitmap(image);
	al_draw_scaled_bitmap(temp, 0, 0, al_get_bitmap_width(temp), al_get_bitmap_height(temp), 0, 0, tilewidth, tileheight, 0);
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


