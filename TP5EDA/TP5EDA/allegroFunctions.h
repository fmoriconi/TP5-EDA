#pragma once
#include "scenario.h"

bool allegroInit(); //Función encargada de inicializar Allegro en el programa. Devuelve false si no hay error, true si lo hay.

void displayInit();

void allegroShutdown(scenario); //Función encargada de destruir Allegro al finalizar el programa.