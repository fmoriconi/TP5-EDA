#include "worm.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;



#define WALK_IMGS "wwalk-F"
#define JMP_IMGS "wjump-F"

#define WWALK1 "wwalk-F1.png"

#define TICK_TIME 60 * 1.0/MOVE_FPS
#define MIN_WAITING_TICKS 10	


string intToString(int i);

worm::worm(wormEnum_t wormN, unsigned int wormQty) {
	float startingX = XMINSTARTINGPOS + (rand() % ((XMAXSTARTINGPOS - XMINSTARTINGPOS)/(wormQty)))*wormN;	//La división divide el escenario por la cantidad de worms, y cada uno aparecerá en su fracción correspondiente de forma ordenada. (Escalable para cualquier cantidad de Worms).
	this->jmpIndex = 0;
	this->walkIndex = 0;
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


 wormState_t worm::getState() {
	 return this->estado;
 }

 void worm::startWalking(wormMoves_t direction) {

	 switch (direction) {
	 case RIGHT:
		 this->estado = WALKING_RIGHT;
		 break;
	 case LEFT:
		 this->estado = WALKING_LEFT;
		 break;
	 }
	 this->tickCount = 0;
	 this->walkIndex = 0;
	 this->drawState = this->walkImgs[this->walkIndex];

 }

 void worm::startJumping() {
	 this->estado = JUMPING;
	 this->tickCount = 0;
	 this->jmpIndex = 0;
	 this->drawState = this->jmpImgs[jmpIndex];

 }
 void worm::jumpingTick() {
	 this->tickCount++;
 }
 void worm::walkingTick() {

	 this->tickCount++;
	 double desplazamientoX = 0;

	 if (this->tickCount > MIN_WAITING_TICKS ) {

		 //http://worms2d.info/Worm_Walking

		 switch (this->tickCount) {

		 case MIN_WAITING_TICKS + 24:
		 case (MIN_WAITING_TICKS + 28):
		 case (MIN_WAITING_TICKS + 30):
		 case (MIN_WAITING_TICKS + 32):
			 desplazamientoX = 0.25;
			 break;

		 case (MIN_WAITING_TICKS + 2):
		 case (MIN_WAITING_TICKS + 6):
		 case (MIN_WAITING_TICKS + 8):
		 case (MIN_WAITING_TICKS + 10):
		 case (MIN_WAITING_TICKS + 12):
			 desplazamientoX = 0.5;
			 break;

		 case (MIN_WAITING_TICKS + 20):
			 desplazamientoX = 1.25;
			 break;

		 case (MIN_WAITING_TICKS + 14):
		 case (MIN_WAITING_TICKS + 18):
			 desplazamientoX = 1.5;
			 break;

		 case (MIN_WAITING_TICKS + 16):
			 desplazamientoX = 1.75;
			 break;

		 default:
			 desplazamientoX = 0;
			 break;
		 }

		 this->setPos(this->getPos().coordX + desplazamientoX, this->getPos().coordY);
		 //FALTA EL LOOP O LLENAR LOS ARREGLOS DE OTRA MANERA!!!!
		 if ( (this->walkIndex + 1) < AMOUNT_OF_JUMPING_IMAGES) 
			 this->walkIndex++;
		 else 
			 this->walkIndex = 0;
		 
		 this->drawState = walkImgs[walkIndex];
	 }
 }

 void worm::handleMovement(wormMoves_t direction) {

 }
 ALLEGRO_BITMAP * worm::walkImgs[AMOUNT_OF_WALKING_IMAGES] = { NULL };
 ALLEGRO_BITMAP * worm::jmpImgs[AMOUNT_OF_JUMPING_IMAGES] = { NULL };
 ALLEGRO_BITMAP * worm::quietImg = { NULL };