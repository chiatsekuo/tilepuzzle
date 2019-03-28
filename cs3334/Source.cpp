#include <iostream>
#include <allegro5/allegro.h>
using namespace std;

int main() {

	cout << "sliding block puzzle" << endl;
	al_init();
	ALLEGRO_DISPLAY * screen = al_create_display(500,500);
	ALLEGRO_EVENT_QUEUE * queue;
	ALLEGRO_TIMER * timer;

	al_install_keyboard();
	al_install_mouse();

	queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 20.0);



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

		}

	}
	system("pause");

}