#include "worm.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;



#define WALK_IMGS "wwalk-F"
#define JMP_IMGS "wjump-F"

#define WWALK1 "wwalk-F1.png"

string intToString(int i);

worm::worm(wormEnum_t wormN, unsigned int wormQty) {
	float startingX = XMINSTARTINGPOS + (rand() % ((XMAXSTARTINGPOS - XMINSTARTINGPOS)/(wormQty)))*wormN;	//La división divide el escenario por la cantidad de worms, y cada uno aparecerá en su fracción correspondiente de forma ordenada. (Escalable para cualquier cantidad de Worms).
	this->setPos(startingX, YSTARTINGPOS);
	this->estado = QUIET;
	this->refresh();
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
		string str = WALK_IMGS + intToString(i+1) + ".png";

		if (!(walkImgs[i] = al_load_bitmap(str.c_str()))) {
			abort = true;
			break;
		}
		
	}

	for (int i = 0; i < AMOUNT_OF_JUMPING_IMAGES; i++) {
		jmpImgs[i] = NULL;
		string str = JMP_IMGS + intToString(i + 1) + ".png";

		if (!(jmpImgs[i] = al_load_bitmap(str.c_str()))){
			abort = true;
			break;
		}
	}

	if (!(quietImg = al_load_bitmap(WWALK1)))
		abort = true;

	if (abort)
		std::cout << "ERROR: Could not initialize bitmaps." << std::endl;

	return abort;
}

 void worm::refresh() {
	 if (estado == QUIET) {
		 drawState = walkImgs[0];
	 }
 }

 string intToString(int i) {
	 stringstream ss;
	 ss << i;
	 string str = ss.str();
	 return str;
 }

 void worm::handleMovement(wormMoves_t direction) {

 }

 wormState_t worm::getState() {
	 return this->estado;
 }
 ALLEGRO_BITMAP * worm::walkImgs[AMOUNT_OF_WALKING_IMAGES] = { NULL };
 ALLEGRO_BITMAP * worm::jmpImgs[AMOUNT_OF_JUMPING_IMAGES] = { NULL };
 ALLEGRO_BITMAP * worm::quietImg = { NULL };