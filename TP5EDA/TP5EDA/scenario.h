#pragma once
#include <allegro5\allegro.h>
#include "worm.h"

class scenario {
private:
	worm worm1; //El escenario debe contener dos worms.
	worm worm2;

public:
	//scenario();
	ALLEGRO_BITMAP * mainStage;
	ALLEGRO_BITMAP * background;
	void setInitialPos(worm& wormn);
	position getWormPos(wormenum n);
};