#include "tile.h"

tile::tile()
{
	isitEmpty = true;
	value = 10;
}
tile::tile(int v) {
	value = v;
	isitEmpty = false;
	image = al_create_bitmap(100, 100);
	ALLEGRO_BITMAP * temp = al_load_bitmap("image.jpg");
	
	al_set_target_bitmap(image);
	al_draw_scaled_bitmap(temp, 0, 0, al_get_bitmap_width(temp), al_get_bitmap_height(temp), 0, 0, tilewidth, tileheight, 0);
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
	return tilewidth;
}

int tile::geth()
{
	return tileheight;
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


bool tile::isinside(int x, int y)
{
	if (x > this->x&&x < this->x + this->getw()) {
		if (y > this->y&&y < this->y + this->geth()) {
			return true;
		}
	}
	return false;
}

ALLEGRO_BITMAP * tile::getimage()
{
	return image;
}


