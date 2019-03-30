#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include "board.h"
#define boarderedge 20
using namespace std;

ALLEGRO_DISPLAY * screen;
ALLEGRO_FONT *font;

void drawtile(int x,int y,int w,int h,int v);

int main() {

	board game=board();
	game.initalizePosition();
	cout << game.toString() << endl;
	game.movedown(2, 1);
	cout << game.toString() << endl;
	game.movedown(2, 0);
	cout << game.toString() << endl;
	game.moveleft(2, 0);
	cout << game.toString() << endl;
	cout << "sliding block puzzle" << endl;
	
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
		}
		else if (event.type == ALLEGRO_EVENT_TIMER) {

			tile ** tilelist = new tile*[boardwidth*boardheight];
			
			game.alltiles(tilelist, boardwidth*boardheight);

			

			al_clear_to_color(al_map_rgb(255, 255, 255));
			
			for (int i = 0; i < boardwidth*boardheight; i++) {
				tile * dr = tilelist[i];
				if (!dr->isempty()){
					drawtile(dr->getx(), dr->gety(), dr->getw(), dr->geth(), dr->getvalue());
				}
			}
			

			al_flip_display();
			//delete tilelist;
		}

	}
	//system("pause");

}

void drawtile(int x, int y, int w, int h, int v)
{
	x += boarderedge;
	y += boarderedge;
	al_draw_rectangle(x,y,x+w,y+h,al_map_rgb(0,0,0),2);
	char text[10] = { 0 };
	_itoa_s(v, text,10);
	al_draw_text(font, al_map_rgb(0, 0, 0), x + (w / 2) - (al_get_text_width(font,text)/2), y+w/3, ALLEGRO_ALIGN_LEFT,text);

}
