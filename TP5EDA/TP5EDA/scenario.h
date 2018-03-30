#pragma once
#include <allegro5\allegro.h>

class scenario {
	private:
		worm worm1; //El escenario debe contener dos worms.
		worm worm2;

	public:
		ALLEGRO_BITMAP * mainStage;
		ALLEGRO_BITMAP * background;
};