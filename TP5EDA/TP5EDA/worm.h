#pragma once

#include <allegro5\allegro5.h>
#include "position.h"
#include "general.h"

class worm {
private:
	position pos;
	worm_state estado;
	ALLEGRO_BITMAP ** walkImgs;
	ALLEGRO_BITMAP ** jmpImgs;
	unsigned int tickCount;

public:
	worm();
	void setPos(float x, float y);
	void refresh(void * userData);
	void startWalking();
	position getPos();
};