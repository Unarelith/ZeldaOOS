#ifndef GAME_H
#define GAME_H

#include "main.h"
#include "timer.h"
#include "sprite.h"
#include "player.h"
#include "map.h"
#include "weapon.h"

#include "titleScreen2.h"
#include "titleScreen_png.h"
#include "pressStart_png.h"
#include "fileSelect_png.h"
#include "acorn_png.h"
#include "linkts_png.h"
#include "plain_png.h"

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
