#pragma once

#include <allegro5/allegro.h>
#include "scenario.h"

class EventManagement
{
public:

	EventManagement(ALLEGRO_DISPLAY * display);
	~EventManagement();
	void receiveEvent();			//checks for events and updates its info accordingly
	void handleEvent(scenario& stage); //applies changes to the scenario object so that the worms and stage will reflect the user input.
	void finishGame(void);			//informs the event manager the game has finished.
	bool gameIsFinished(void);		//returns true if the game has finished
	bool shouldRedraw(void);
	bool errorLoading;

private:

	wormEnum_t keyPressedWorm;
	wormMoves_t keyPressed;
	bool gameFinished;			//boolean that indicates whether the game has finished or not. 
	bool move;                  //boolean that indicates when actions regarding the movingTimer should be taken.
	bool redraw;                  //boolean that indicates when actions regarding the drawingTimer should be taken.

	ALLEGRO_EVENT_QUEUE * event_queue;
	ALLEGRO_TIMER * drawingTimer;
	ALLEGRO_TIMER * movingTimer;
	ALLEGRO_EVENT ev;


};
