#pragma once
#include <allegro5\allegro.h>
#include <iostream>
#include "scenario.h"


#define SCENARIO "Scenario.png"
#define BACKGROUND "mountains.png"

scenario::scenario() {
	this->worm1 = worm();
	this->worm2 = worm();

	this->errorLoading = this->setBackgroundAndMainStage();

	if (!this->errorLoading)
		this->errorLoading = this->worm1.setStateImgs();

	if (!this->errorLoading)
		this->gameFinished = false;
	else
		this->gameFinished = true;
} 

scenario::~scenario() {

	al_destroy_bitmap(this->mainStage);
	al_destroy_bitmap(this->background);

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
		std::cout << "ERROR: Could not initialize bitmaps." << std::endl;
		abort = true;

	}
	if (!(this->background = al_load_bitmap(BACKGROUND))) {
		std::cout << "ERROR: Could not initialize bitmaps." << std::endl;
		abort = true;
	}
	
	return abort;
}

void scenario::draw(void)
{
	al_draw_scaled_bitmap(this->background, 0, 0, al_get_bitmap_width(this->background), al_get_bitmap_height(this->background), 0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, 0); //Dibujo el fondo
	al_draw_bitmap(this->mainStage, 0, 0, 0); //Dibujo el escenario 

	//draw de los worms en el escenario.
	al_draw_bitmap(this->worm1.getToDrawState(), this->worm1.getPos().coordX, this->worm1.getPos().coordY, 0);
	al_draw_bitmap(this->worm2.getToDrawState(), this->worm2.getPos().coordX, this->worm2.getPos().coordY, 0); 
}

bool scenario::gameFinished(void) {
	return this->gameFinished;
}


