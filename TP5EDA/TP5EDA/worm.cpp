#include "worm.h"
#include <iostream>
using namespace std;

#define XMAXSTARTINGPOS 1212
#define XMINSTARTINGPOS 701
#define YSTARTINGPOS 616
/*
#define WALK_IMGS "wwalk - F"
#define JMP_IMGS "wjump-F"
*/
#define WWALK1 "wwalk-F1.png"
#define WWALK2 "wwalk-F2.png"
#define WWALK3 "wwalk-F3.png"
#define WWALK4 "wwalk-F4.png"
#define WWALK5 "wwalk-F5.png"
#define WWALK6 "wwalk-F6.png"
#define WWALK7 "wwalk-F7.png"
#define WWALK8 "wwalk-F8.png"
#define WWALK9 "wwalk-F9.png"
#define WWALK10 "wwalk-F10.png"
#define WWALK11 "wwalk-F11.png"
#define WWALK12 "wwalk-F12.png"
#define WWALK13 "wwalk-F13.png"
#define WWALK14 "wwalk-F14.png"
#define WWALK15 "wwalk-F15.png"

#define WJUMP1 "wjump-F1.png"
#define WJUMP2 "wjump-F2.png"
#define WJUMP3 "wjump-F3.png"
#define WJUMP4 "wjump-F4.png"
#define WJUMP5 "wjump-F5.png"
#define WJUMP6 "wjump-F6.png"
#define WJUMP7 "wjump-F7.png"
#define WJUMP8 "wjump-F8.png"
#define WJUMP9 "wjump-F9.png"
#define WJUMP10 "wjump-F10.png"

worm::worm() {
	this->estado = QUIET;
	float startingX = XMINSTARTINGPOS + (rand() % (XMAXSTARTINGPOS - XMINSTARTINGPOS));	
	this->setPos(startingX, YSTARTINGPOS);
}

void worm::setPos(float posx, float posy) {
	pos.setPos(posx, posy);
}

position worm::getPos() {
	return pos;
}
ALLEGRO_BITMAP * worm::getToDrawState() {
	return this->drawState;
}



 bool worm::setStateImgs() {

	bool abort = false;

	quietImg = NULL;

	for (int i = 0; i < AMOUNT_OF_WALKING_IMAGES; i++) {
		walkImgs[i] = NULL;
		jmpImgs[i] = NULL;
	}

	if (!(walkImgs[0] = al_load_bitmap(WWALK1)))
		abort = true;
	else if (!(walkImgs[1] = al_load_bitmap(WWALK2)))
		abort = true;
	else if (!(walkImgs[2] = al_load_bitmap(WWALK3)))
		abort = true;
	else if (!(walkImgs[3] = al_load_bitmap(WWALK4)))
		abort = true;
	else if (!(walkImgs[4] = al_load_bitmap(WWALK5)))
		abort = true;
	else if (!(walkImgs[5] = al_load_bitmap(WWALK6)))
		abort = true;
	else if (!(walkImgs[6] = al_load_bitmap(WWALK7)))
		abort = true;
	else if (!(walkImgs[7] = al_load_bitmap(WWALK8)))
		abort = true;
	else if (!(walkImgs[8] = al_load_bitmap(WWALK9)))
		abort = true;
	else if (!(walkImgs[9] = al_load_bitmap(WWALK10)))
		abort = true;
	else if (!(walkImgs[10] = al_load_bitmap(WWALK11)))
		abort = true;
	else if (!(walkImgs[11] = al_load_bitmap(WWALK12)))
		abort = true;
	else if (!(walkImgs[12] = al_load_bitmap(WWALK13)))
		abort = true;
	else if (!(walkImgs[13] = al_load_bitmap(WWALK14)))
		abort = true;
	else if (!(walkImgs[14] = al_load_bitmap(WWALK15)))
		abort = true;

	else if (!(jmpImgs[0] = al_load_bitmap(WJUMP1)))
		abort = true;
	else if (!(jmpImgs[1] = al_load_bitmap(WJUMP2)))
		abort = true;
	else if (!(jmpImgs[2] = al_load_bitmap(WJUMP3)))
		abort = true;
	else if (!(jmpImgs[3] = al_load_bitmap(WJUMP4)))
		abort = true;
	else if (!(jmpImgs[4] = al_load_bitmap(WJUMP5)))
		abort = true;
	else if (!(jmpImgs[5] = al_load_bitmap(WJUMP6)))
		abort = true;
	else if (!(jmpImgs[6] = al_load_bitmap(WJUMP7)))
		abort = true;
	else if (!(jmpImgs[7] = al_load_bitmap(WJUMP8)))
		abort = true;
	else if (!(jmpImgs[8] = al_load_bitmap(WJUMP9)))
		abort = true;
	else if (!(jmpImgs[9] = al_load_bitmap(WJUMP10)))
		abort = true;

	else if (!(quietImg = al_load_bitmap(WWALK1)))
		abort = true;

	if (abort)
		std::cout << "ERROR: Could not initialize bitmaps." << std::endl;

	return abort;
}
