#include <iostream>
#include "allegroFunctions.h"
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\bitmap.h>
#include <allegro5\allegro_primitives.h>
#include "general.h"

using namespace std;

#define SCENARIO "Scenario.png"
#define BACKGROUND "mountains.png"

bool allegroInit(scenario& stage) {

	bool abort = false;
	/*Si hay un error, ponemos abort en true de modo tal que la primer condición "abort == false"
	resulte falsa y no compruebe la segunda (Que es la inicialización correcta), aprovechando 
	el hecho de que C++ es lazy para no continuar inicializando tras un error, además de devolver abort e indicar el error. */

	if (!al_init()) {
		cout << "ERROR: Could not initialize Allegro." << endl;
		abort = true;
	}

	if ((abort == false) && !(al_init_primitives_addon())) {
		cout << "ERROR: Could not initialize Allegro Primitives." << endl;
		abort = true;
	}

	if ((abort == false) && !(al_install_keyboard())) {
		cout << "ERROR: Could not install keyboard." << endl;
		al_shutdown_primitives_addon();
		abort = true;
	}

	if ((abort == false) && !(al_init_image_addon())) {
		cout << "ERROR: Could not initialize image addons." << endl;
		al_shutdown_primitives_addon();
		al_uninstall_system();
		abort = true;
	}
	if ((abort == false) && !((stage.mainStage = al_load_bitmap(SCENARIO)))){
		cout << "ERROR: Could not initialize bitmaps." << endl;
		al_shutdown_image_addon();
		al_shutdown_primitives_addon();
		al_uninstall_system();
		abort = true;
	}
	if ((abort == false) && !((stage.background = al_load_bitmap(BACKGROUND)))) {
		cout << "ERROR: Could not initialize bitmaps." << endl;
		al_shutdown_image_addon();
		al_shutdown_primitives_addon();
		al_uninstall_system();
		abort = true;
	}



	return abort;

}


void drawDisplay(scenario& stage) {
	al_draw_scaled_bitmap(stage.background, 0,0, al_get_bitmap_width(stage.background),al_get_bitmap_height(stage.background),0,0,DISPLAY_WIDTH,DISPLAY_HEIGHT,0);
	al_draw_bitmap(stage.mainStage,0, 0, 0);
	al_flip_display();
}

void allegroShutdown(scenario& stage)
{
	al_destroy_bitmap(stage.mainStage);
	al_destroy_bitmap(stage.background);
	al_shutdown_primitives_addon();
	al_shutdown_image_addon();
	al_uninstall_system();
}