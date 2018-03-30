#include "allegroFunctions.h"
#include <iostream>
#include "scenario.h"
#include "general.h"

using namespace std;

int main(void) {

	srand(time(NULL));

	scenario stage;
	ALLEGRO_DISPLAY * display;

	if ((!allegroInit(stage)) && (display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT))){

		drawDisplay(stage);
		
		getchar();

		allegroShutdown(stage);
	}
	else {
		cout << "Allegro initialization has failed. Press any key to end the program." << endl; //Caso de error
		getchar();
	}


	return 0;
}