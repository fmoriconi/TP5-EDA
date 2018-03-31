#pragma once
#include <allegro5\allegro.h>
#include "worm.h"

class scenario {
private:
	worm worm1; //El escenario debe contener dos worms.
	worm worm2;
	ALLEGRO_BITMAP * mainStage;
	ALLEGRO_BITMAP * background;
	bool gameFinished;
	bool setBackgroundAndMainStage();

public:
	void draw(void);
	bool gameFinished(void);
	scenario();
	virtual ~scenario();
	bool  errorLoading;
	position getWormPos(wormenum n);
};