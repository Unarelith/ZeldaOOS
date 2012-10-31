/*---------------------------------------------------------------------------------

	Eleandra
	Copyright (C) 2012 Quentin BAZIN quent42340@gmail.com
	
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

---------------------------------------------------------------------------------*/
#include <nds.h>
#include <fat.h>
#include <filesystem.h>
#include <cstdio>
#include <ctime>
#include "timer.h"
#include "sprites.h"
#include "player.h"
#include "NPC.h"
#include "map.h"
#include "mapManager.h"
#include "door.h"
#include "game.h"

Map *Game::currentMap;
Map **Game::maps;
Tileset *Game::tilesets;
u8 Game::transBg;
Player *Game::talek = 0;
Door** Game::doors;

Game::Game() {
	// Set up default exception handler
	defaultExceptionHandler();
	
	// Initialize random seed
	srand(time(NULL));
	
	// Setup video modes
	videoSetMode(MODE_5_2D);
	videoSetModeSub(MODE_5_2D);
	
	// Setup VRAM banks
	vramSetPrimaryBanks(VRAM_A_MAIN_SPRITE,
						VRAM_B_MAIN_BG_0x06000000,
						VRAM_C_SUB_BG,
						VRAM_D_SUB_SPRITE);
	
	// Initialize console
	consoleInit(NULL, 0, BgType_Text4bpp, BgSize_T_256x256, 0, 1, false, true);
	
	// Initialize main backgrounds
	m_bg = bgInit(3, BgType_Bmp16, BgSize_B16_256x256, 6, 0);
	transBg = bgInit(1, BgType_Text8bpp, BgSize_T_256x256, 4, 5);
	bgSetPriority(transBg, 0);
	m_mapBg = bgInit(0, BgType_Text8bpp, BgSize_T_512x512, 0, 1);
	bgSetPriority(m_mapBg, 1);
	
	// Initialize sub background
	m_bgSub = bgInitSub(3, BgType_Bmp16, BgSize_B16_256x256, 2, 0);
	
	// Initialize sprite system
	enableSprites(SCREEN_UP, 0);
	enableSprites(SCREEN_DOWN, 0);
	
	for(int i = 0 ; i < 128 ; i++) {
		setSpritePriority(SCREEN_UP, i, 1);
	}
	
	printf("NitroFS loading...\n");
	
	// Initialize EFS filesystem
	if(!nitroFSInit()) {
		printf("FATAL ERROR: Bad nitroFS init\n");
		while(1) { swiWaitForVBlank(); }
	}
	
	printf("NitroFS loaded!\n");
	
	// Initialize timer system
	Timer::initTimers();
	
	consoleClear();
	
	// Temporary "Press Start" screen
	while(!(keysDown() & KEY_START) && !(keysDown() & KEY_TOUCH)) {
		scanKeys();
		
		printf("\x1b[10;10HPress Start");
		
		swiWaitForVBlank();
	}
	
	NPC::loadAllNPCs();
	Map::NPCs = initNPCs();
	
	// Go to main loop
	mainLoop();
}

Game::~Game() {
}

void Game::mainLoop() {
	// Init player
	talek = new Player;
	
	// Init maps system
	maps = initMaps(m_mapBg);
	tilesets = initTilesets();
	
	// Init doors system
	doors = initDoors();
	
	currentMap = maps[0];
	currentMap->initOTF();
	
	while(!(keysDown() & KEY_A)) {
		scanKeys();
		
		consoleClear();
		
		// Move talek
		talek->move();
		
		// Draw sprite
		talek->draw();
		
		// Draw NPCs
		currentMap->drawNPCs();
		
		// Test the scrolling
		scroll();
		
		printf("\x1b[10;13HPress A");
		printf("\x1b[12;15H%d", currentMap->id());
		printf("\x1b[14;15H%d", currentMap->map()[((talek->x() + 5) >> 4) + ((talek->y() + 15) >> 4) * currentMap->width()]);
		printf("\x1b[16;15H%d", currentMap->tileset()->info[currentMap->map()[((talek->x() + 5) >> 4) + ((talek->y() + 15) >> 4) * currentMap->width()]]);
		printf("\x1b[18;13H%d, %d", Map::scrollX, Map::scrollY);
		printf("\x1b[20;13H%d, %d", currentMap->mapX(), currentMap->mapY());
		printf("\x1b[22;10H%d, %d", talek->x() >> 4, talek->y() >> 4);
		
		swiWaitForVBlank();
	}
}

void Game::scroll() {
	// Scroll right
	if(talek->x() > 256 - 16 + 2) {
		talek->vx(0);
		talek->vy(0);
		
		for(int i = 0 ; i < 32 ; i++) {
			if ((i & 1) || (!(i & 15))) talek->x(talek->x() - 8); else talek->x(talek->x() - 7);
			
			currentMap->scroll(8, 0);
			talek->draw();
			swiWaitForVBlank();
		}
		
		currentMap = currentMap->nextMap();
	}
	
	// Scroll left
	if(talek->x() < 0 - 2) {
		talek->vx(0);
		talek->vy(0);
		
		for(int i = 0 ; i < 32 ; i++) {
			if ((i & 1) || (!(i & 15))) talek->x(talek->x() + 8); else talek->x(talek->x() + 7);
			
			currentMap->scroll(-8, 0);
			talek->draw();
			swiWaitForVBlank();
		}
		
		currentMap = currentMap->nextMap();
	}
	
	// Scroll down
	if(talek->y() > 192 - 16 + 1) {
		talek->vx(0);
		talek->vy(0);
		
		for(int i = 0 ; i < 24 ; i++) {
			if ((i & 1) && ((i & 7) < 7)) talek->y(talek->y() - 8); else talek->y(talek->y() - 7);
			
			currentMap->scroll(0, 8);
			talek->draw();
			swiWaitForVBlank();
		}
		
		currentMap = currentMap->nextMap();
	}
	
	// Scroll up
	if(talek->y() < 0 - 2) {
		talek->vx(0);
		talek->vy(0);
		
		for(int i = 0 ; i < 24 ; i++) {
			if ((i & 1) && ((i & 7) < 7)) talek->y(talek->y() + 8); else talek->y(talek->y() + 7);
			
			currentMap->scroll(0, -8);
			talek->draw();
			swiWaitForVBlank();
		}
		
		currentMap = currentMap->nextMap();
	}
}

