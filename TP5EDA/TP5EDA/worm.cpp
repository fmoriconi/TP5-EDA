#include "worm.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;



#define WALK_IMGS "wwalk-F"
#define JMP_IMGS "wjump-F"
#define FILEFORMAT ".png"

#define WWALK1 "wwalk-F1.png"

#define TICK_TIME 60 * 1.0/MOVE_FPS
#define MIN_WAITING_TICKS 10
#define WARMUPFRAMES 3
#define WALKFRAMES 45 // 42 + warmup 


#define RIGHTFACTOR 1
#define LEFTFACTOR -1

string intToString(int i);

worm::worm(wormEnum_t wormN, unsigned int wormQty) {
	float startingX = XMINSTARTINGPOS + ((rand() % ((XMAXSTARTINGPOS - XMINSTARTINGPOS))/(wormQty)))*wormN;	//La divisi�n divide el escenario por la cantidad de worms, y cada uno aparecer� en su fracci�n correspondiente de forma ordenada. (Escalable para cualquier cantidad de Worms).
	this->jmpIndex = 0;
	this->walkIndex = 0;
	this->frameNum = 0;
	this->setPos(startingX, YSTARTINGPOS);
	this->estado = QUIET;
	this->refresh();
	this->facedSide = RIGHT;
	this->loopIsOver = false;
	this->shouldMove = false;
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

wormMoves_t worm::getFacedSide() {
	return this->facedSide;
}

 bool worm::setStateImgs() {

	bool abort = false;

	quietImg = NULL;

	for (int i = 0; i < AMOUNT_OF_WALKING_IMAGES; i++) {
		walkImgs[i] = NULL;
		string str = WALK_IMGS + intToString(i+1) + FILEFORMAT;

		if (!(walkImgs[i] = al_load_bitmap(str.c_str()))) {
			abort = true;
			break;
		}
		
	}

	for (int i = 0; i < AMOUNT_OF_JUMPING_IMAGES; i++) {
		jmpImgs[i] = NULL;
		string str = JMP_IMGS + intToString(i + 1) + FILEFORMAT;

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
	 if (this->shouldMove) {
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

 }

 void worm::startJumping() {
	 if (this->shouldMove) {
		 this->estado = JUMPING;
		 this->tickCount = 0;
		 this->jmpIndex = 0;
		 this->drawState = this->jmpImgs[jmpIndex];
	 }


 }

 void worm::jumpingTick() {
	 this->tickCount++;
 }

 void worm::walkingTick(wormMoves_t direction) {

	 int side = 0; //Segun la direcci�n, har� que el desplazamiento en X sea positivo o negativo

	 if (direction == RIGHT)
		 side = RIGHTFACTOR;
	 else
		 side = LEFTFACTOR;

	 double desplazamientoX = 0;


	 if (!((this->walkIndex) < (AMOUNT_OF_WALKING_IMAGES-1)))
	 {
		 this->walkIndex = 0;
	 }

	 if (this->frameNum < WARMUPFRAMES) {
		 this->drawState = walkImgs[walkIndex];
		 frameNum++;
		 walkIndex++;
	 }
	 else if (this->frameNum == WARMUPFRAMES) {
		 this->drawState = walkImgs[walkIndex];
		 walkIndex = 0;
		 frameNum++;

	 }
	 else if (this->frameNum < WALKFRAMES) {

		 this->drawState = walkImgs[walkIndex];
		 frameNum++;
		 walkIndex++;
		 if (walkIndex == 13) {
			desplazamientoX = (27.0 * (double)side) / 3.0;
			walkIndex = 0;
		 }
	 }
	 else {
		 frameNum = 0;
		 this->estado = QUIET;
		 this->loopIsOver = true;
	 }



		 if ( (this->getPos().coordX + desplazamientoX > XMINSTARTINGPOS) && (this->getPos().coordX + desplazamientoX < XMAXSTARTINGPOS)) {
			 this->setPos(this->getPos().coordX + desplazamientoX, this->getPos().coordY);
		 }
		 else if (this->getPos().coordX + desplazamientoX < XMINSTARTINGPOS) {
			 this->setPos(XMINSTARTINGPOS, this->getPos().coordY);
		 }
		 else if (this->getPos().coordX + desplazamientoX > XMAXSTARTINGPOS) {
			 this->setPos(XMAXSTARTINGPOS, this->getPos().coordY);
		 }




		//printf("X: %f Y: %f \n", this->getPos().coordX, this->getPos().coordY);
		 //FALTA EL LOOP O LLENAR LOS ARREGLOS DE OTRA MANERA!!!!


		 

		 // printf("%d \n", direction);



		 

}

 void worm::handleMovement(wormMoves_t direction) {

 }

 void worm::setFacedSide(wormMoves_t direction) {
	 facedSide = direction;
 }

 void worm::resetTicks(void) {
	 this->ticks = 0;
	 this->shouldMove = false;
 }
 void worm::tick(void) {
	 this->ticks++;
	 if (this->ticks > MIN_WAITING_TICKS) {
		 this->shouldMove = true;
		 this->ticks = 0;		//NO DEBE SER LLAMADO CON RESETTICKS!
	 }
 }
 ALLEGRO_BITMAP * worm::walkImgs[AMOUNT_OF_WALKING_IMAGES] = { NULL };
 ALLEGRO_BITMAP * worm::jmpImgs[AMOUNT_OF_JUMPING_IMAGES] = { NULL };
 ALLEGRO_BITMAP * worm::quietImg = { NULL };