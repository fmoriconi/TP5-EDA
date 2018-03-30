#include "allegroFunctions.h"
#include <iostream>

using namespace std;

int main(void) {

	if (!allegroInit()) {



		allegroShutdown();
	}
	else {
		cout << "Allegro initialization has failed. Press any key to end the program." << endl; //Caso de error
		getchar();
	}


	return 0;
}