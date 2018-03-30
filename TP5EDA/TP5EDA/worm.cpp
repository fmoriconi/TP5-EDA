#include "worm.h"

#define XMAXSTARTINGPOS 1212
#define XMINSTARTINGPOS 701
#define YSTARTINGPOS 616

worm::worm() {
	float startingX = XMINSTARTINGPOS + (rand() % (XMAXSTARTINGPOS - XMINSTARTINGPOS));	
	this->setPos(startingX, YSTARTINGPOS);
}

void worm::setPos(float posx, float posy) {
	pos.setPos(posx, posy);
}

position worm::getPos() {
	return pos;
}