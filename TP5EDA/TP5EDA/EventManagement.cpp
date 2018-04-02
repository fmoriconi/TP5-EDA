#include "EventManagement.h"
#include "scenario.h"
#include "general.h"

#include <iostream>
using namespace std;



#define W2_MOV_RIGHT ALLEGRO_KEY_RIGHT
#define W2_MOV_LEFT ALLEGRO_KEY_LEFT
#define W2_MOV_JUMP ALLEGRO_KEY_UP

#define W1_MOV_RIGHT ALLEGRO_KEY_D
#define W1_MOV_LEFT ALLEGRO_KEY_A
#define W1_MOV_JUMP ALLEGRO_KEY_W

EventManagement::EventManagement(ALLEGRO_DISPLAY * display)
{
	this->errorLoading = false;
	this->takeInputAgain = true;
	this->drawingTimer = al_create_timer(1.0 / FPS);

	this->countFrames = false;
 	this-> beingHeld = false;



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
void EventManagement::receiveEvent(scenario& stage) {

	if (al_get_next_event(event_queue, &ev)) //Toma un evento de la cola, en caso de que esta no este vacia.
	{
		if (beingHeld) {
			this->takeInputAgain = false;
			countFrames = true;
			stage.setLoopState(this->keyPressedWorm, false);
		}


		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			this->finishGame();
			return;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN && (this->takeInputAgain) == true) {

			switch (ev.keyboard.keycode) {

			case W1_MOV_RIGHT:
				this->keyPressed = RIGHT; //Indico la dirección
				this->keyPressedWorm = WORM1; //Y a cual Worm corresponde
				al_stop_timer(movingTimer); //Si habia tocado otra tecla antes, paro el timer.
				al_start_timer(movingTimer); //Y lo inicio de nuevo.

				break;

			case W1_MOV_LEFT:
				this->keyPressed = LEFT;
				this->keyPressedWorm = WORM1;
				al_stop_timer(movingTimer);
				al_start_timer(movingTimer);

				break;

			case W1_MOV_JUMP:
				this->keyPressed = UP;
				this->keyPressedWorm = WORM1;
				al_stop_timer(movingTimer);
				al_start_timer(movingTimer);

				break;

			case W2_MOV_RIGHT:
				this->keyPressed = RIGHT;
				this->keyPressedWorm = WORM2;

				al_stop_timer(movingTimer);
				al_start_timer(movingTimer);

				break;

			case W2_MOV_LEFT:
				this->keyPressed = LEFT;
				this->keyPressedWorm = WORM2;

				al_stop_timer(movingTimer);
				al_start_timer(movingTimer);

				break;

			case W2_MOV_JUMP:
				this->keyPressed = UP;
				this->keyPressedWorm = WORM2;

				al_stop_timer(movingTimer);
				al_start_timer(movingTimer);

				break;

			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			al_stop_timer( movingTimer);
			beingHeld = false;
		}
		else if (ev.type == ALLEGRO_EVENT_TIMER) {

			if (ev.timer.source == this->movingTimer)
			{
				beingHeld = true;
				this->takeInputAgain = false;
				this->countFrames = true;
				al_stop_timer(movingTimer);
			}
			else if (ev.timer.source == this->drawingTimer)
			{
				this->redraw = true;

				if (countFrames && (stage.getLoopState(this->keyPressedWorm) != true)){
					this->move = true;
				}
				else
				{
					this->takeInputAgain = true;
					countFrames = false;
					this->move = false;
					stage.setLoopState(this->keyPressedWorm, false);

				}
			}
		}
	}
}

void EventManagement::handleEvent(scenario& stage) {
	if (move) {
		stage.handleWormMovement(this->keyPressedWorm, this->keyPressed);
	}
	this->move = false;

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




