#include <iostream>
#include "Game.h"


//Software to make a game, Starded on window
int main() {

	//Init srand()
	std::srand(static_cast<unsigned>(time(NULL)));

	//Init Game engine
	Game game;
	
	//Game loop
	while (game.getWindowIsOpen()) {
	

		//Update
		game.update();


		//Render
		game.render();
	}
	//End of application
	return 0;
}