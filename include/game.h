#ifndef GAME_H
#define GAME_H

#include "main.h"

#include "titleScreen2.h"
#include "stats.h"

class Game {
	public:
		// Construct & Destruct
		Game();
		~Game();
		
		// Interface
		void pressStartScreen();
		void titleScreen();
		
		// Initialisation
		void init();
		
		// Static variables
		static Map* currentMap;
		
	private:
		int s_bg; // Sub BG id returned by bgInitSub()
};

#endif // GAME_H
