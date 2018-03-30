#pragma once
#include <allegro5\allegro.h>
#include "scenario.h"

#define XMAXSTARTINGPOS 1212
#define XMINSTARTINGPOS 701
#define YSTARTINGPOS 616
/*
scenario::scenario() {
	setInitialPos(worm1);
	setInitialPos(worm2);
} */

void scenario::setInitialPos(worm& wormn) {
	float startingX = XMINSTARTINGPOS + (rand() % (XMAXSTARTINGPOS - XMINSTARTINGPOS));	
	wormn.setPos(startingX, YSTARTINGPOS);
}

position scenario::getWormPos(wormenum n) {

	position wormpos;
	if (n == wormn1) {
		wormpos = worm1.getPos();
	}
	else {
		wormpos = worm2.getPos();
	}
	return wormpos;
}