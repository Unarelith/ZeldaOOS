#ifndef GAME_H
#define GAME_H

#include "main.h"
#include "sprite.h"

#include "titleScreen.h"
#include "pressStart.h"

class Game {
	public:
		// Construct & Destruct
		Game();
		~Game();
		
		// Interface
		void pressStartScreen();
		
	private:
		int s_bg; // BG id returned by bgInit()
		int s_bgSub; // Sub BG id returned by bgInitSub()
		int s_bg16Sub; // Sub 16bit BG id returned by bgInitSub()
};

#endif // GAME_H
