#pragma once

#include <allegro5\allegro5.h>
#include "position.h"
#include "general.h"

class worms {
private:
	position pos;
	worm_state estado;
	ALLEGRO_BITMAP ** walkImgs;
	ALLEGRO_BITMAP ** jmpImgs;
	unsigned int tickCount;
public:
	void refresh(void * userData);
	void startWalking();
};