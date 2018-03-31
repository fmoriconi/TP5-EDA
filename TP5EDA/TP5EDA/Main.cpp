#include "allegroFunctions.h"
#include <iostream>
#include "scenario.h"
#include "scenario.cpp"
#include "general.h"

using namespace std;

int main(void) {
	
	srand(time(NULL));

	ALLEGRO_DISPLAY * display = NULL;

	if ((!allegroInit()) && (display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT))){

		scenario stage;

		if (stage.errorLoading) {
			un_init_allegro();
			cout << "Allegro Error while creating scenario. Press any key to end the program." << endl; //Caso de error
			getchar();
		}
		else {
			while (!stage.gameFinished()) {
				//primero falta recibir eventos!!!
				//handleEvents()!!!!!
				drawDisplay(stage);
				//delay??
			}
			
			getchar();
			allegroShutdown(stage);
		}
	}
	else {
		cout << "Allegro initialization has failed. Press any key to end the program." << endl; //Caso de error
		getchar();
	}


	return 0;
}