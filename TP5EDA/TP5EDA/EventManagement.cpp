#include "EventManagement.h"
#include "scenario.h"
#include "general.h"

#include <iostream>
using namespace std;



#define W1_MOV_RIGHT ALLEGRO_KEY_RIGHT
#define W1_MOV_LEFT ALLEGRO_KEY_LEFT
#define W1_MOV_JUMP ALLEGRO_KEY_UP

#define W2_MOV_RIGHT ALLEGRO_KEY_D
#define W2_MOV_LEFT ALLEGRO_KEY_A
#define W2_MOV_JUMP ALLEGRO_KEY_W

EventManagement::EventManagement(ALLEGRO_DISPLAY * display)
{
	this->errorLoading = false;

	this->drawingTimer = al_create_timer(1.0 / FPS);
	if (!drawingTimer) {
		std::cout << "ERROR: Failed to create timer." << std::endl;
		errorLoading = true;
	}
	this->movingTimer = al_create_timer(1.0 / MOVE_FPS);

	if ( !errorLoading &&  !movingTimer) {
		std::cout << "ERROR: Failed to create timer." << std::endl;
		errorLoading = true;
	}

	event_queue = al_create_event_queue();
	if ( !errorLoading && !event_queue) {
		std::cout << "ERROR: failed to create event_queue!" << std::endl;
		al_destroy_timer(drawingTimer);
		al_destroy_timer(movingTimer);
		errorLoading = true;
	}
	
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(drawingTimer));
	al_register_event_source(event_queue, al_get_timer_event_source(movingTimer));

	al_start_timer(drawingTimer);

	this->move = false;
	this->redraw = true;
	this->gameFinished = false;
}


EventManagement::~EventManagement()
{
	al_destroy_timer(drawingTimer);
	al_destroy_timer(movingTimer);
	al_destroy_event_queue(event_queue);
}

//recibe y procesa un evento por teclado. 
void EventManagement::receiveEvent() {

	if (al_get_next_event(event_queue, &ev)) //Toma un evento de la cola, en caso de que esta no este vacia.
	{

		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			this->finishGame();
			return;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {

			case W1_MOV_RIGHT:
				this->keyPressed = RIGHT;
				this->keyPressedWorm = WORM1;
				al_start_timer(movingTimer);
				printf("Timer started\n");
				break;
			case W1_MOV_LEFT:
				this->keyPressed = LEFT;
				this->keyPressedWorm = WORM1;
				al_start_timer(movingTimer);
				printf("Timer started\n");
				break;
			case W1_MOV_JUMP:
				this->keyPressed = UP;
				this->keyPressedWorm = WORM1;
				al_start_timer(movingTimer);
				printf("Timer started\n");
				break;

			case W2_MOV_RIGHT:
				this->keyPressed = RIGHT;
				this->keyPressedWorm = WORM2;
				al_start_timer(movingTimer);
				printf("Timer started\n");
				break;
			case W2_MOV_LEFT:
				this->keyPressed = LEFT;
				this->keyPressedWorm = WORM2;
				al_start_timer(movingTimer);
				printf("Timer started\n");
				break;
			case W2_MOV_JUMP:
				this->keyPressed = UP;
				this->keyPressedWorm = WORM2;
				al_start_timer(movingTimer);
				printf("Timer started\n");
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			this->keyPressed = NO_MOV;
			al_stop_timer(movingTimer);
			printf("Timer stopped\n");
		}
		else if (ev.type == ALLEGRO_EVENT_TIMER) {

			if (ev.timer.source == this->movingTimer)
			{
				this->move = true;
				//printf("Made it to move\n");
			}
			else if (ev.timer.source == this->drawingTimer)
			{
				this->redraw = true;
				framesDrawn++;
				//printf("Made it to drawingTimer\n");
			}
		}
	}
}

void EventManagement::handleEvent(scenario& stage) {
	if (move)
		stage.handleWormMovement(this->keyPressedWorm, this->keyPressed);
	if (framesDrawn == 50) {
		framesDrawn = 0;
		move = false;
	}
}

void EventManagement::finishGame(void) {
	this->gameFinished = true;
}

bool EventManagement::gameIsFinished(void) {
	return this->gameFinished;
}

bool EventManagement::shouldRedraw(void) {
	bool shouldI = redraw;
	redraw = false;
	return shouldI;
}




