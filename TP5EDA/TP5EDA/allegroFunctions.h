#pragma once
#include "scenario.h"

bool allegroInit(); //Funci�n encargada de inicializar Allegro en el programa. Devuelve false si no hay error, true si lo hay.

void displayInit();

void allegroShutdown(scenario); //Funci�n encargada de destruir Allegro al finalizar el programa.