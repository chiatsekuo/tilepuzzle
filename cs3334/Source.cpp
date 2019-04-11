#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include "ai.h"
#include "board.h"
#include <random>
#define boarderedge 0
using namespace std;

ALLEGRO_DISPLAY * screen;
ALLEGRO_FONT *font;
ALLEGRO_EVENT_QUEUE * queue;
ALLEGRO_TIMER * timer;

void drawtile(int x,int y,int w,int h,int v);
void drawblanktile(int x, int y, int w, int h);
void drawtileimage(int x, int y, ALLEGRO_BITMAP* image);
void drawgame(board*game);
int oneblankgame();
int wraparoundgame();


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

	
	//rowChangeGame game = rowChangeGame(100, 100);


	font = al_load_ttf_font("consola.ttf", 72, 0);

	screen = al_create_display(500,500);
	

	al_install_keyboard();
	al_install_mouse();

	queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 20.0);

	al_start_timer(timer);
	al_register_event_source(queue, al_get_display_event_source(screen));
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_mouse_event_source());

	oneblankgame();
	//wraparoundgame();
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

void drawgame(board * game)
{
	visualtile ** tilelist = new visualtile*[boardwidth*boardheight];
	game->alltiles(tilelist, boardwidth*boardheight);

	for (int i = 0; i < boardwidth*boardheight; i++) {
		visualtile * dr = tilelist[i];
		if (!dr->isempty()) {
			drawtileimage(dr->getx(), dr->gety(), dr->getimage());
			drawtile(dr->getx(), dr->gety(), dr->getw(), dr->geth(), dr->getvalue());
			if (dr->getx() < game->getx()) {
				drawtileimage(dr->getx()+game->getwidth(), dr->gety(), dr->getimage());
				drawtile(dr->getx()+game->getwidth(), dr->gety(), dr->getw(), dr->geth(), dr->getvalue());
			}
			if (dr->getx()+tilewidth > game->getx()+game->getwidth()) {
				drawtileimage(dr->getx() - game->getwidth(), dr->gety(), dr->getimage());
				drawtile(dr->getx() - game->getwidth(), dr->gety(), dr->getw(), dr->geth(), dr->getvalue());
			}

			if (dr->gety() < game->gety()) {
				drawtileimage(dr->getx(), dr->gety()+game->getheight(), dr->getimage());
				drawtile(dr->getx(), dr->gety() + game->getheight(), dr->getw(), dr->geth(), dr->getvalue());
			}
			if (dr->gety() + tileheight > game->gety() + game->getheight()) {
				drawtileimage(dr->getx() , dr->gety() - game->getheight(), dr->getimage());
				drawtile(dr->getx(), dr->gety() - game->getheight(), dr->getw(), dr->geth(), dr->getvalue());
			}
		}
		else {
			drawblanktile(dr->getx(), dr->gety(), dr->getw(), dr->geth());
		}

	}
	
	al_draw_filled_rectangle(game->getx()-5, game->gety(), game->getx() + game->getwidth()+5, game->gety() - tileheight,al_map_rgb(255,255,255));
	al_draw_filled_rectangle(game->getx()-5, game->gety()+game->getwidth(), game->getx() + game->getwidth()+5, game->gety() + game->getwidth() + tileheight, al_map_rgb(255, 255, 255));
	al_draw_filled_rectangle(game->getx(), game->gety()-5, game->getx()-tilewidth, game->gety()+game->getheight()+5, al_map_rgb(255, 255, 255));
	al_draw_filled_rectangle(game->getx()+game->getwidth(), game->gety() - 5, game->getx() + game->getwidth() + tilewidth, game->gety() + game->getheight()+5, al_map_rgb(255, 255, 255));
	delete tilelist;
}

int oneblankgame()
{
	oneBlankGame game = oneBlankGame(100, 100);
	al_set_target_backbuffer(screen);
	game.initalizePosition();
	bot * solver = nullptr;
	bool done = false;
	while (!done) {
		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);

		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			done = true;
		}
		else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			visualtile ** tilelist = new visualtile*[boardwidth*boardheight];
			game.alltiles(tilelist, boardwidth*boardheight);

			for (int i = 0; i < boardwidth*boardheight; i++) {
				if (tilelist[i]->isinside(event.mouse.x, event.mouse.y)) {
					int xclicked = game.boardx(tilelist[i]);
					int yclicked = game.boardy(tilelist[i]);
					char dir = game.possibledir(xclicked,yclicked);
					game.movetile(xclicked, yclicked, dir);
					ALLEGRO_KEYBOARD_STATE keys;
					al_get_keyboard_state(&keys);
					break;
				}
			}
			cout << "inv: " << game.inversions() << " ai: " << game.aiinversion() << " man: " << game.aimanhattandistance() << endl;
			delete tilelist;
		}
		else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			if (event.keyboard.keycode == ALLEGRO_KEY_R) {
				for (int i = 0; i < 1000; i++) {
					int possible = game.numOfMoves();

					int choice = rand() % possible;

					game.doMove(choice);
				}
				solver = nullptr;
			}
			else if (event.keyboard.keycode == ALLEGRO_KEY_S) {
				cout << "solve" << endl;

				if (solver == nullptr) { solver = new bot(&game); };
				while (!solver->foundanswer()) {
					solver->expand();
				}
				solver->loadbest();
				cout << "bestpath: ";
				for (int i = 0; i < solver->stepssize; i++) {
					cout << solver->steps[i] << ", ";
				}
				cout << endl;

				game.doMove(solver->findbest());
				cout << "open size: " << solver->openlist.size() << endl;
				cout << "closed size: " << solver->closed.size() << endl;
				cout << "current inversions: " << game.inversions() << " depth of search: " << solver->depth << " solved to: " << solver->solvedto << endl;
			}
		}
		else if (event.type == ALLEGRO_EVENT_TIMER) {

			visualtile ** tilelist = new visualtile*[boardwidth*boardheight];

			game.alltiles(tilelist, boardwidth*boardheight);

			game.move();

			al_clear_to_color(al_map_rgb(255, 255, 255));

			for (int i = 0; i < boardwidth*boardheight; i++) {
				visualtile * dr = tilelist[i];
				if (!dr->isempty()) {
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
	return 0;
}

int wraparoundgame()
{
	rowChangeGame game = rowChangeGame(100, 100);
	al_set_target_backbuffer(screen);
	game.initalizePosition();
	bot * solver = nullptr;
	bool done = false;

	int xdownpos=0;
	int ydownpos=0;
	visualtile * downtile=nullptr;
	while (!done) {
		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);

		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			done = true;
		}
		else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			visualtile ** tilelist = new visualtile*[boardwidth*boardheight];
			game.alltiles(tilelist, boardwidth*boardheight);
			xdownpos = event.mouse.x;
			ydownpos = event.mouse.y;

			for (int i = 0; i < boardwidth*boardheight; i++) {
				if (tilelist[i]->isinside(event.mouse.x, event.mouse.y)) {
					downtile = tilelist[i];
					break;
				}
			}
			cout << "inv: " << game.inversions() << " ai: " << game.aiinversion() << " man: " << game.aimanhattandistance() << endl;
			delete tilelist;
		}
		else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			xdownpos = 0;
			ydownpos = 0;
			downtile = nullptr;
		}
		else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			if (event.keyboard.keycode == ALLEGRO_KEY_R) {
				for (int i = 0; i < 1000; i++) {
					int possible = game.numOfMoves();

					int choice = rand() % possible;

					game.doMove(choice);
				}
				solver = nullptr;
			}
			else if (event.keyboard.keycode == ALLEGRO_KEY_S) {
				cout << "solve" << endl;

				/*if (solver == nullptr) { solver = new bot(&game); };
				while (!solver->foundanswer()) {
					solver->expand();
				}
				solver->loadbest();
				cout << "bestpath: ";
				for (int i = 0; i < solver->stepssize; i++) {
					cout << solver->steps[i] << ", ";
				}
				cout << endl;

				game.doMove(solver->findbest());
				cout << "open size: " << solver->openlist.size() << endl;
				cout << "closed size: " << solver->closed.size() << endl;
				cout << "current inversions: " << game.inversions() << " depth of search: " << solver->depth << " solved to: " << solver->solvedto << endl;
				*/
			}
		}
		else if (event.type == ALLEGRO_EVENT_TIMER) {

			visualtile ** tilelist = new visualtile*[boardwidth*boardheight];

			game.alltiles(tilelist, boardwidth*boardheight);

			ALLEGRO_MOUSE_STATE Mouse;
			al_get_mouse_state(&Mouse);
			if (al_mouse_button_down(&Mouse,1)) {
				int changex = Mouse.x - xdownpos;
				int changey = Mouse.y - ydownpos;
				game.initalizePosition();
				if (downtile) {
					if (abs(changex) > abs(changey)) {
						visualtile ** same = new visualtile*[boardwidth];
						game.samerow(downtile,same);
						for (int i = 0; i < boardwidth; i++) {
							same[i]->adjx(changex);
						}
						if (abs(changex) > tilewidth / 2) {//make a move
							int indexoftile=0;
							for (int i = 0; i < boardwidth; i++) {
								if (same[i] == downtile) {
									indexoftile = i;
									break;
								}
							}
							if (changex > 0) {
								game.movetile(game.boardx(downtile), game.boardy(downtile),'r');
								downtile = same[(indexoftile+1)%boardwidth];//setup as if the move starts from a the tile to the side
								xdownpos += tilewidth;//mouse the mouse to center over other tile
							}
							else{
								game.movetile(game.boardx(downtile), game.boardy(downtile), 'l');
								downtile = same[(indexoftile + boardwidth - 1) % boardwidth];
								xdownpos -= tilewidth;
							}
						}
						delete same;
						
						
					}
					else {
						visualtile ** same = new visualtile*[boardheight];
						game.samecol(downtile, same);
						for (int i = 0; i < boardheight; i++) {
							same[i]->adjy(changey);
						}

						if (abs(changey) > tileheight / 2) {//make a move
							int indexoftile = 0;
							for (int i = 0; i < boardheight; i++) {
								if (same[i] == downtile) {
									indexoftile = i;
									break;
								}
							}
							if (changey > 0) {
								game.movetile(game.boardx(downtile), game.boardy(downtile), 'd');
								downtile = same[(indexoftile + 1) % boardheight];//setup as if the move starts from a the tile to the side
								ydownpos += tileheight;//mouse the mouse to center over other tile
							}
							else {
								game.movetile(game.boardx(downtile), game.boardy(downtile), 'u');
								downtile = same[(indexoftile + boardheight - 1) % boardheight];
								ydownpos -= tileheight;
							}
						}
						delete same;
					}
				}
			}
			else {
				game.move();
			}



			al_clear_to_color(al_map_rgb(255, 255, 255));

			drawgame(&game);


			al_flip_display();
			delete tilelist;
		}

	}
	return 0;
}
