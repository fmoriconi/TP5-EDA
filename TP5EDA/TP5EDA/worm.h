#pragma once

#include <allegro5\allegro5.h>
#include <allegro5\allegro_image.h>
#include "position.h"
#include "general.h"

#define AMOUNT_OF_WALKING_IMAGES 15		//total amount of different bitmaps that involve the walking process for a worm.
#define AMOUNT_OF_JUMPING_IMAGES 10		//total amount of different bitmaps that involve the jumping process for a worm.

class worm {
private:
	position pos;
	wormState_t estado;
	ALLEGRO_BITMAP * drawState;

	static ALLEGRO_BITMAP * walkImgs[AMOUNT_OF_WALKING_IMAGES];
	static ALLEGRO_BITMAP * jmpImgs[AMOUNT_OF_JUMPING_IMAGES];
	static ALLEGRO_BITMAP * quietImg;
	unsigned int tickCount;

public:
	worm();
	static bool setStateImgs();
	void setPos(float x, float y);
	position getPos();
	ALLEGRO_BITMAP * getToDrawState(); 
	ALLEGRO_BITMAP * setNewDrawState(wormState_t newState);
	void refresh(void * userData);
	void startWalking();
};