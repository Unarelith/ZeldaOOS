/*---------------------------------------------------------------------------------

	Zelda: Oracle Of Secrets
	Copyright (C) 2011 Pixelda ( ex Pixelua )
		* Quent42340
		* Fantasix
	
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
	
	Special thanks:
		- libnds creators and mainteners
		- Brunni for the µLib
		- µLua team
			* Risike
			* Fantasix
			* Reylak
			* Grahack
			* thermo_nono
			* Papymouge
			* and others
		- #dev-fr users
			* Morukutsu
			* ludo6431
			* smealum
			* EvlTroopa
			* Synthesis
			* Caillou
	
---------------------------------------------------------------------------------*/
#include "main.h"
int i;

//int animation[2] = {1,2};

int main(void) {
	// Initialize game
	Game* game = new Game;
	
	while(1);
	
	delete game;
	
	/*videoSetMode(MODE_0_2D);
	vramSetBankA(VRAM_A_MAIN_SPRITE);
	
	enableSprites(0, 0);
	enableSprites(1, 0);
	
	Timer::initTimers();
	
	loadTiles(0, 0, 12, SprColors_16, linktsTiles);
	loadTiles(0, 12, 32, SprColors_16, linkTiles);
	loadTiles(0, 44, 2, SprColors_16, dongeonkeyTiles);
	loadPalette(0, 0, gfxPal);
	loadPalette(0, 1, linkPal);
	loadPalette(0, 2, linktsPal);
	Sprite link_ts(SCREEN_UP, 0, SprSize_16x16, 0);
	link_ts.addAnimation(2, animation, 400);
	
	while(1) {
		link_ts.playAnimation(5, 5, 0, 2);
		//drawSprite(0, 0, 5, 5, SprSize_16x16, SprColors_16, 0, 2);
		//drawSprite(0, 1, 5, 30, SprSize_16x16, SprColors_16, 12, 1);
		//drawSprite(0, 2, 50, 5, SprSize_8x16, SprColors_16, 44, 0);
		
		swiWaitForVBlank();
	}*/
}
