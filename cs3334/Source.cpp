#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

#include "board.h"
#include <random>
#define boarderedge 0
using namespace std;

ALLEGRO_DISPLAY * screen;
ALLEGRO_FONT *font;

void drawtile(int x,int y,int w,int h,int v);
void drawblanktile(int x, int y, int w, int h);
void drawtileimage(int x, int y, ALLEGRO_BITMAP* image);

int main() {


	if (!al_init()) {
		exit(-1);
	}
	if (!al_init_font_addon()) {
		exit(-1);
	}
	if (!al_init_primitives_addon()) {
		exit(-1);
	}
	if (!al_init_ttf_addon()) {
		exit(-1);
	}
	if (!al_init_image_addon()) {
		exit(-1);
	}

	oneBlankGame game = oneBlankGame(100, 100);
	al_set_target_backbuffer(screen);
	cout << game.inversions() << endl;
	game.initalizePosition();

	font = al_load_ttf_font("consola.ttf", 72, 0);

	screen = al_create_display(500,500);
	ALLEGRO_EVENT_QUEUE * queue;
	ALLEGRO_TIMER * timer;

	al_install_keyboard();
	al_install_mouse();

	queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 20.0);

	al_start_timer(timer);
	al_register_event_source(queue, al_get_display_event_source(screen));
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_mouse_event_source());

	bool done = false;
	while (!done) {
		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);

		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			done = true;
		}
		else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {

			cout << "mouse at " << event.mouse.x << ", " << event.mouse.y << endl;
			tile ** tilelist = new tile*[boardwidth*boardheight];
			game.alltiles(tilelist, boardwidth*boardheight);

			for (int i = 0; i < boardwidth*boardheight; i++) {
				if (tilelist[i]->isinside(event.mouse.x, event.mouse.y)) {
					int xclicked = game.boardx(tilelist[i]);
					int yclicked = game.boardy(tilelist[i]);
					char dir = game.possibledir(xclicked,yclicked);
					game.movetile(xclicked, yclicked, dir);
					break;
				}
			}

			cout << game.inversions() << endl;

			delete tilelist;

		}
		else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			if (event.keyboard.keycode == ALLEGRO_KEY_R) {
				for (int i = 0; i < 1000; i++) {
					int possible = game.numOfMoves();

					int choice = rand() % possible;

					game.doMove(choice);
				}
			}
		}
		else if (event.type == ALLEGRO_EVENT_TIMER) {

			tile ** tilelist = new tile*[boardwidth*boardheight];
			
			game.alltiles(tilelist, boardwidth*boardheight);

			game.move();

			al_clear_to_color(al_map_rgb(255, 255, 255));
			
			for (int i = 0; i < boardwidth*boardheight; i++) {
				tile * dr = tilelist[i];
				if (!dr->isempty()){
					drawtileimage(dr->getx(), dr->gety(), dr->getimage());
					drawtile(dr->getx(), dr->gety(), dr->getw(), dr->geth(), dr->getvalue());
				}
				else {
					drawblanktile(dr->getx(), dr->gety(), dr->getw(), dr->geth());
				}
			}
			

			al_flip_display();
			delete tilelist;
		}

	}
	//system("pause");

}

void drawtile(int x, int y, int w, int h, int v)
{
	drawblanktile(x, y, w, h);
	x += boarderedge;
	y += boarderedge;
	char text[10] = { 0 };
	_itoa_s(v, text,10);
	al_draw_text(font, al_map_rgb(0, 0, 0), x + (w / 2) - (al_get_text_width(font,text)/2), y+w/3, ALLEGRO_ALIGN_LEFT,text);

}

void drawblanktile(int x, int y, int w, int h)
{
	x += boarderedge;
	y += boarderedge;
	al_draw_rectangle(x, y, x + w, y + h, al_map_rgb(0, 0, 0), 2);
}

void drawtileimage(int x, int y, ALLEGRO_BITMAP * image)
{
	al_draw_bitmap(image, x, y, 0);

}
