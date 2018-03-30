#pragma once
#include "scenario.h"

bool allegroInit(scenario& stage); //Función encargada de inicializar Allegro en el programa. Devuelve false si no hay error, true si lo hay.

void drawDisplay(scenario& stage);

void allegroShutdown(scenario& stage); //Función encargada de destruir Allegro al finalizar el programa.