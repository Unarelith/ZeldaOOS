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
		u8 s_bg; // BG id
		u8 s_mapBg; // Map BG id
};

#endif // GAME_H
