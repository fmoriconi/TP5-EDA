#pragma once
#include <allegro5\allegro.h>
#include "scenario.h"


#define SCENARIO "Scenario.png"
#define BACKGROUND "mountains.png"

scenario::scenario() {
	this->worm1 = worm();
	this->worm2 = worm();
	this->errorLoading = this->setBackgroundAndMainStage();

} 

position scenario::getWormPos(wormenum n) {

	position wormpos;
	if (n == WORM1) {
		wormpos = worm1.getPos();
	}
	else {
		wormpos = worm2.getPos();
	}
	return wormpos;
}

bool scenario::setBackgroundAndMainStage(void) {
	bool abort = false;

	this->mainStage = NULL;
	this->background = NULL;

	if (!(this->mainStage = al_load_bitmap(SCENARIO))) {
		cout << "ERROR: Could not initialize bitmaps." << endl;
		abort = true;

	}
	if (!(this->background = al_load_bitmap(BACKGROUND))) {
		cout << "ERROR: Could not initialize bitmaps." << endl;
		abort = true;
		/*
		*/
	}
	
	return abort;
}



