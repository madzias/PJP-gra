#include<allegro5\allegro.h>
#include<allegro5\allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>

#define PI 3.14159265

const int width = 700;
const int height = 900;

int mouse_x;
int mouse_y;

enum State {
	NOWA_GRA,
	WCZYTAJ,
	REKORDY,
	INSTRUKCJA,
	RANKING,
	O_AUTORZE,
	WYJSCIE,
	MENU
};

float object_rand(float *x, float *y, float *delta_x, float *delta_y) {
	int tablica1[] = { 0, width, 2, 2 };
	int tablica2[] = { 0, height };

	srand(time(NULL));

	*x = rand() % tablica1[4];
	if ((*x == 0) | (*x == width)) {
		*y = (rand() % height) + 1;
	}
	else {
		*y = tablica2[rand() % 2];
		*x = (rand() % width) + 1;
	}

	if ((*x == 0 && *y > height / 2) | (*y == 0 && *x <= width / 2)) {
		*delta_x = ((rand() % 10) + 1);
		*delta_y = ((rand() % 10) + 1);
	}
	else if ((*x == 0 && *y <= height / 2) | (*y == height && *x <= width / 2)) {
		*delta_x = ((rand() % 10) + 1);
		*delta_y = -((rand() % 10) + 1);
	}
	else if ((*x == width && *y <= height / 2) | (*y == height && *x > width / 2)) {
		*delta_x = -((rand() % 10) + 1);
		*delta_y = ((rand() % 10) + 1);
	}
	else if ((*x == width && *y > height / 2) | (*y == 0 && *x > width / 2)) {
		*delta_x = -((rand() % 10) + 1);
		*delta_y = -((rand() % 10) + 1);
	}

	if (*delta_x == 0) {
		*delta_x = *delta_x + 5;
	}
	else if (*delta_y == 0) {
		*delta_y = *delta_y + 5;
	}
	return 0;
}

int main()
{
	bool done = false;
	bool draw = true;

	float delfin_x = -1, delfin_y = -1;
	float delta_delfin_x = 2, delta_delfin_y = 2;
	float *w_delfin_x = &delfin_x, *w_delfin_y = &delfin_y;
	float *w_delta_delfin_x = &delta_delfin_x, *w_delta_delfin_y = &delta_delfin_y;

	float wrog_x = -1, wrog_y = -1;
	float delta_wrog_x = 2, delta_wrog_y = 2;
	float *w_wrog_x = &wrog_x, *w_wrog_y = &wrog_y;
	float *w_delta_wrog_x = &delta_wrog_x, *w_delta_wrog_y = &delta_wrog_y;

	float friend_ship_x = -1, friend_ship_y = -1;
	float delta_friend_ship_x = 2, delta_friend_ship_y = 2;
	float *w_friend_ship_x = &friend_ship_x, *w_friend_ship_y = &friend_ship_y;
	float *w_delta_friend_ship_x = &delta_friend_ship_x, *w_delta_friend_ship_y = &delta_friend_ship_y;

	float mina_x = -1, mina_y = -1;
	float delta_mina_x = 2, delta_mina_y = 2;
	float *w_mina_x = &mina_x, *w_mina_y = &mina_y;
	float *w_delta_mina_x = &delta_mina_x, *w_delta_mina_y = &delta_mina_y;

	float delta_angle = 0.01;
	float angle = 6;
	float mnoznik_lvl = 0.1;

	float a;
	float b;

	int state = MENU;

	int menu_x = 350;
	int menu_y = 200;

	int punkty = 0;
	int level = 1;



	al_init();
	al_init_primitives_addon();
	al_install_keyboard();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_mouse();

	ALLEGRO_DISPLAY *display = al_create_display(width, height);
	ALLEGRO_TIMER *timer = al_create_timer(1.0 / 60);
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	ALLEGRO_FONT *font_i = al_load_ttf_font("BAUHS93.ttf", 15, NULL);
	ALLEGRO_FONT *font = al_load_ttf_font("BAUHS93.ttf", 30, NULL);
	ALLEGRO_FONT *font_n = al_load_ttf_font("BAUHS93.ttf", 60, NULL);
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_set_window_position(display, 200, 200);
	al_start_timer(timer);

	if (!al_init())
	{
		printf("failed to initialise allegro");
	}

	if (!display)
	{
		printf("failed to initialise display");
	}




	while (!done) {
		ALLEGRO_EVENT events;
		al_wait_for_event(event_queue, &events);

		if (events.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (events.keyboard.keycode) {
			case ALLEGRO_KEY_SPACE:
				delta_angle = -delta_angle;
				break;
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			}
		}

		if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if (state == MENU)
			{
				if (mouse_x > menu_x - 50 && mouse_x < menu_x+50 && mouse_y > menu_y && mouse_y < menu_y + 30)
				{
					al_draw_rectangle(menu_x - 5, menu_x + 35, menu_y - 5, menu_y + 35, al_map_rgb(34, 139, 34), 5);
					if (events.mouse.button & 1) {
						state = NOWA_GRA;
					}
				}
				else if (mouse_x > menu_x - 50 && mouse_x < menu_x + 50 && mouse_y > menu_y + 60 && mouse_y < menu_y + 90)
				{
					if (events.mouse.button & 1) {
						state = WCZYTAJ;
					}
				}
				else if (mouse_x > menu_x - 50 && mouse_x < menu_x + 50 && mouse_y > menu_y + 120 && mouse_y < menu_y + 150)
				{
					if (events.mouse.button & 1) {
						state = INSTRUKCJA;
					}
				}
				else if (mouse_x > menu_x - 50 && mouse_x < menu_x + 50 && mouse_y > menu_y + 180 && mouse_y < menu_y + 210)
				{
					if (events.mouse.button & 1) {
						state = RANKING;
					}
				}
				else if (mouse_x > menu_x - 50 && mouse_x < menu_x + 50 && mouse_y > menu_y + 240 && mouse_y < menu_y + 270)
				{
					if (events.mouse.button & 1) {
						state = O_AUTORZE;
					}
				}
				else if (mouse_x > menu_x - 50 && mouse_x < menu_x + 50 && mouse_y > menu_y + 300 && mouse_y < menu_y + 330)
				{
					if (events.mouse.button & 1) {
						done = true;
					}
				}
			}
		}
		
		if (events.type == ALLEGRO_EVENT_MOUSE_AXES)
			{
				mouse_x = events.mouse.x;
				mouse_y = events.mouse.y;
			}

		if (events.type == ALLEGRO_EVENT_TIMER) {
			draw = true;
			angle = angle + delta_angle;
			delfin_x = delfin_x + mnoznik_lvl * delta_delfin_x;
			delfin_y = delfin_y + mnoznik_lvl * delta_delfin_y;
			if ((delfin_x < 0) | (delfin_x > width) | (delfin_y < 0) | (delfin_y > height)) {
				object_rand(w_delfin_x, w_delfin_y, w_delta_delfin_x, w_delta_delfin_y);
			}

			wrog_x = 1.1*wrog_x + mnoznik_lvl * delta_wrog_x;
			wrog_y = 1.1*wrog_y + mnoznik_lvl * delta_wrog_y;
			if ((wrog_x < 0) | (wrog_x > width) | (wrog_y < 0) | (wrog_y > height)) {
				object_rand(w_wrog_x, w_wrog_y, w_delta_wrog_x, w_delta_wrog_y);
			}

			friend_ship_x = 0.8*friend_ship_x + mnoznik_lvl * delta_friend_ship_x;
			friend_ship_y = 0.8*friend_ship_y + mnoznik_lvl * delta_friend_ship_y;
			if ((friend_ship_x < 0) | (friend_ship_x > width) | (friend_ship_y < 0) | (friend_ship_y > height)) {
				object_rand(w_friend_ship_x, w_friend_ship_y, w_delta_friend_ship_x, w_delta_friend_ship_y);
			}

			mina_x = 0.9*mina_x + mnoznik_lvl * delta_mina_x;
			mina_y = (mina_y + mnoznik_lvl * delta_mina_y);
			if ((mina_x < 0) | (mina_x > width) | (mina_y < 0) | (mina_y > height)) {
				object_rand(w_mina_x, w_mina_y, w_delta_mina_x, w_delta_mina_y);
			}






			if (draw && al_event_queue_is_empty(event_queue))
			{
				draw = false;
				if (state == NOWA_GRA)
				{
					al_draw_text(font_n, al_map_rgb(34, 139, 34), 350, 20, ALLEGRO_ALIGN_CENTER, "SONAR 1.0");
					al_draw_textf(font, al_map_rgb(34, 139, 34), 20, 80, ALLEGRO_ALIGN_LEFT, "PUNKTY: %i", punkty);
					al_draw_textf(font, al_map_rgb(34, 139, 34), 600, 80, ALLEGRO_ALIGN_RIGHT, "POZIOM: %i", level);
					al_draw_circle(width / 2, height / 2 + 100, 280, al_map_rgb(34, 139, 34), 2);
					al_draw_circle(width / 2, height / 2 + 100, 200, al_map_rgb(34, 139, 34), 2);
					al_draw_circle(width / 2, height / 2 + 100, 120, al_map_rgb(34, 139, 34), 2);
					al_draw_filled_circle(delfin_x, delfin_y, 15, al_map_rgb(51, 255, 255));
					al_draw_filled_circle(wrog_x, wrog_y, 11, al_map_rgb(255, 0, 0));
					al_draw_filled_circle(friend_ship_x, friend_ship_y, 7, al_map_rgb(19, 198, 0));
					al_draw_filled_circle(mina_x, 0.9*mina_y, 9, al_map_rgb(160, 160, 160));
					al_draw_line(width / 2, height / 2 + 100, ((width / 2) + 1000) * cos(angle), ((height / 2) + 1000) * sin(angle), al_map_rgb(34, 100, 34), 3);

					a = tan(angle);
					b = height / 2 + 100 - a*(width / 2);
					//printf("%f %f\n", a, b);

					if (delfin_y > 0.95*a*delfin_x + b && delfin_y < 1.05*a*delfin_x + b) {
						object_rand(w_delfin_x, w_delfin_y, w_delta_delfin_x, w_delta_delfin_y);
						punkty = punkty - 100;
					}
					if (wrog_y > 0.95*a*wrog_x + b && wrog_y < 1.05*a*wrog_x + b) {
						object_rand(w_wrog_x, w_wrog_y, w_delta_wrog_x, w_delta_wrog_y);
						punkty = punkty + 50;
					}
					if (mina_y > 0.95*a*mina_x + b && mina_y < 1.05*a*mina_x + b) {
						object_rand(w_mina_x, w_mina_y, w_delta_mina_x, w_delta_mina_y);
						punkty = punkty + 100;
					}
					if (friend_ship_y > 0.95*a*friend_ship_x + b && friend_ship_y < 1.05*a*friend_ship_x + b) {
						object_rand(w_friend_ship_x, w_friend_ship_y, w_delta_friend_ship_x, w_delta_friend_ship_y);
					}
				}
				else if (state == MENU)
				{
					al_draw_text(font_n, al_map_rgb(34, 139, 34), 350, 20, ALLEGRO_ALIGN_CENTER, "SONAR 1.0");
					al_draw_multiline_text(font, al_map_rgb(34, 139, 34), 350, 200, 200, 60, ALLEGRO_ALIGN_CENTER, "NOWA GRA \nWCZYTAJ \nINSTRUKCJA \nRANKING \nO AUTORZE \nWYJSCIE");
					if (mouse_x > menu_x - 100 && mouse_x < menu_x + 100 && mouse_y > menu_y && mouse_y < menu_y + 30)
					{
						al_draw_line(0, menu_y + 15, menu_x - 100, menu_y + 15, al_map_rgb(34, 139, 34), 2);
						al_draw_line(menu_x + 100, menu_y + 15, width, menu_y + 15, al_map_rgb(34, 139, 34), 2);
					}
					else if (mouse_x > menu_x - 50 && mouse_x < menu_x + 50 && mouse_y > menu_y + 60 && mouse_y < menu_y + 90) {
						al_draw_line(0, menu_y + 75, menu_x - 100, menu_y + 75, al_map_rgb(34, 139, 34), 2);
						al_draw_line(menu_x + 100, menu_y + 75, width, menu_y + 75, al_map_rgb(34, 139, 34), 2);
					}
					else if (mouse_x > menu_x - 50 && mouse_x < menu_x + 50 && mouse_y > menu_y + 120 && mouse_y < menu_y + 150)
					{
						al_draw_line(0, menu_y + 135, menu_x - 100, menu_y + 135, al_map_rgb(34, 139, 34), 2);
						al_draw_line(menu_x + 100, menu_y + 135, width, menu_y + 135, al_map_rgb(34, 139, 34), 2);
					}
					else if (mouse_x > menu_x - 50 && mouse_x < menu_x + 50 && mouse_y > menu_y + 180 && mouse_y < menu_y + 210)
					{
						al_draw_line(0, menu_y + 195, menu_x - 100, menu_y + 195, al_map_rgb(34, 139, 34), 2);
						al_draw_line(menu_x + 100, menu_y + 195, width, menu_y + 195, al_map_rgb(34, 139, 34), 2);
					}
					else if (mouse_x > menu_x - 50 && mouse_x < menu_x + 50 && mouse_y > menu_y + 240 && mouse_y < menu_y + 270)
					{
						al_draw_line(0, menu_y + 255, menu_x - 100, menu_y + 255, al_map_rgb(34, 139, 34), 2);
						al_draw_line(menu_x + 100, menu_y + 255, width, menu_y + 255, al_map_rgb(34, 139, 34), 2);
					}
					else if (mouse_x > menu_x - 50 && mouse_x < menu_x + 50 && mouse_y > menu_y + 300 && mouse_y < menu_y + 330)
					{
						al_draw_line(0, menu_y + 315, menu_x - 100, menu_y + 315, al_map_rgb(34, 139, 34), 2);
						al_draw_line(menu_x + 100, menu_y + 315, width, menu_y + 315, al_map_rgb(34, 139, 34), 2);
					}
				}
				else if (state == O_AUTORZE) {
					al_draw_text(font, al_map_rgb(34, 139, 34), 350, 200, ALLEGRO_ALIGN_CENTER, "AUTOR: MAGDA SMIGIELSKA");
				}
				else if (state == INSTRUKCJA) {
					al_draw_text(font, al_map_rgb(34, 139, 34), 350, 100, ALLEGRO_ALIGN_CENTER, "INSTRUKCJA");
					al_draw_multiline_text(font_i, al_map_rgb(34, 139, 34), 350, 180, 600, 30, ALLEGRO_ALIGN_CENTER, "UZYWAJAC SPACJI \nKIERUJ WKAZNIKIEM SONARA I LAP ZBLIZAJACE SIE ELEMENTY");
				}
				al_flip_display();
				al_clear_to_color(al_map_rgb(0, 0, 0));
			}
		}
	}

	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	return 0;
}