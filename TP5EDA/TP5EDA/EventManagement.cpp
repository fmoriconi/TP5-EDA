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

	this->drawingTimer = al_create_timer(1.0 / FPS);
	if (!drawingTimer) {
		std::cout << "ERROR: Failed to create timer." << std::endl;
		errorLoading = true;
	}
	this->movingTimerWorm1 = al_create_timer(1.0 / MOVE_FPS);
	this->movingTimerWorm2 = al_create_timer(1.0 / MOVE_FPS);
	
	if (!errorLoading && !movingTimerWorm1) {
		std::cout << "ERROR: Failed to create timer." << std::endl;
		errorLoading = true;
	}

	if (!errorLoading && !movingTimerWorm1) {
		std::cout << "ERROR: Failed to create timer." << std::endl;
		errorLoading = true;
	}

	event_queue = al_create_event_queue();
	if (!errorLoading && !event_queue) {
		std::cout << "ERROR: failed to create event_queue!" << std::endl;
		al_destroy_timer(drawingTimer);
		al_destroy_timer(movingTimerWorm1);
		al_destroy_timer(movingTimerWorm2);
		errorLoading = true;
	}

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(drawingTimer));
	al_register_event_source(event_queue, al_get_timer_event_source(movingTimerWorm1));
	al_register_event_source(event_queue, al_get_timer_event_source(movingTimerWorm2));

	al_start_timer(drawingTimer);

	this->move = false;
	this->redraw = false;
	this->gameFinished = false;
}


EventManagement::~EventManagement()
{
	al_destroy_timer(drawingTimer);
	al_destroy_timer(movingTimerWorm1);
	al_destroy_timer(movingTimerWorm2);
	al_destroy_event_queue(event_queue);
}

//recibe y procesa un evento por teclado. 
void EventManagement::receiveEvent(scenario& stage) {

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
				al_start_timer(movingTimerWorm1);
				break;
			case W1_MOV_LEFT:
				this->keyPressed = LEFT;
				this->keyPressedWorm = WORM1;
				al_start_timer(movingTimerWorm1);
				break;
			case W1_MOV_JUMP:
				this->keyPressed = UP;
				this->keyPressedWorm = WORM1;
				al_start_timer(movingTimerWorm1);
				break;

			case W2_MOV_RIGHT:
				this->keyPressed = RIGHT;
				this->keyPressedWorm = WORM2;
				al_start_timer(movingTimerWorm2);
				break;
			case W2_MOV_LEFT:
				this->keyPressed = LEFT;
				this->keyPressedWorm = WORM2;
				al_start_timer(movingTimerWorm2);
				break;
			case W2_MOV_JUMP:
				this->keyPressed = UP;
				this->keyPressedWorm = WORM2;
				al_start_timer(movingTimerWorm2);
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode)
			{
			case W1_MOV_RIGHT:
			case W1_MOV_LEFT:
			case W1_MOV_JUMP:
				if (ev.keyboard.keycode == keyPressed) { //Tomo acción solo si la tecla que levanté es la que en principio estaba presionando.
					this->keyPressedWorm = WORM1;
					al_stop_timer(movingTimerWorm1);
				}

				break;
			case W2_MOV_RIGHT:
			case W2_MOV_LEFT:
			case W2_MOV_JUMP:
				if (ev.keyboard.keycode == keyPressed) { //Tomo acción solo si la tecla que levanté es la que en principio estaba presionando.
					this->keyPressedWorm = WORM2;
					al_stop_timer(movingTimerWorm2);
				}
			}
			this->keyPressed = NO_MOV;
		}
		else if (ev.type == ALLEGRO_EVENT_TIMER) {

			if ((ev.timer.source == (this->movingTimerWorm1)) || (ev.timer.source == this->movingTimerWorm2))
				this->move = true;

			else if (ev.timer.source == this->drawingTimer) {

				this->redraw = true;

				if (this->move == true && !stage.getLoopState(this->keyPressedWorm)) {
					this->drawWorm = true;
				}
				else
				{
					drawWorm = false;
					this->move = false;
					stage.setLoopState(this->keyPressedWorm, false);

				}
			}
		}
	}

}

void EventManagement::handleEvent(scenario& stage) {

	if (this->drawWorm) {
		if (this->keyPressed == NO_MOV) {			//caso en que se solto la tecla o esta suelta ya.
			if (this->keyPressedWorm == WORM1) {
				stage.resetTicksFor(WORM1);			//RESETEA EL TIEMPO DE ESPERA PERO ADEMAS DICE QUE NO SE PUEDE MOVER EL WORM!!!
			}
			else if (this->keyPressedWorm == WORM2) {
				stage.resetTicksFor(WORM2);			//RESETEA EL TIEMPO DE ESPERA PERO ADEMAS DICE QUE NO SE PUEDE MOVER EL WORM!!!
			}
		}
		else {
			stage.tickFor(this->keyPressedWorm);
			stage.handleWormMovement(this->keyPressedWorm, this->keyPressed);

		}
		this->drawWorm = false; //En falso para que solo se dibuje una vez por frame.
	}

}

void EventManagement::finishGame(void) {
	this->gameFinished = true;
}
bool EventManagement::gameIsFinished(void) {
	return this->gameFinished;
}

bool EventManagement::shouldRedraw(void) {
	return this->redraw;
}
