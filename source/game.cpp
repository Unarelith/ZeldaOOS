/*---------------------------------------------------------------------------------

    The Legend of Zelda: Oracle of Secrets
    Copyright (C) 2011 Pixelda quent42340@gmail.com

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
#include "game.h"

Map* Game::currentMap;
Player* Game::link;
Map** Game::maps;

Game::Game() {
	// Set up default exception handler
	defaultExceptionHandler();
	
	// Initialize random seed
	srand(time(NULL));
	
	videoSetMode(MODE_5_2D);
	videoSetModeSub(MODE_5_2D);
	
	vramSetBankA(VRAM_A_MAIN_SPRITE);
	vramSetBankB(VRAM_B_MAIN_BG_0x06000000);
	vramSetBankC(VRAM_C_SUB_BG);
	vramSetBankD(VRAM_D_SUB_SPRITE);
	
	consoleInit(NULL, 0, BgType_Text4bpp, BgSize_T_256x256, 0, 1, true, true);
	
	// Initialize backgrounds
	s_bg = bgInit(3, BgType_Bmp16, BgSize_B16_256x256, 2, 0);
	s_bgSub = bgInitSub(3, BgType_Bmp16, BgSize_B16_256x256, 2, 0);
	s_mapBg = bgInitSub(0, BgType_Text8bpp, BgSize_T_512x512, 0, 1);
	
	enableSprites(SCREEN_UP, 0);
	enableSprites(SCREEN_DOWN, 0);
	
	printf("NitroFS loading...\n");
	
	// Initialize EFS filesystem
	if(!nitroFSInit()) {
		printf("FATAL ERROR: Bad nitroFS init\n");
		while(1) { swiWaitForVBlank(); }
	}
	
	printf("NitroFS loaded!\n");
	
	Timer::initTimers();
	
	init();
	//pressStartScreen();
}

Game::~Game() {
}

void Game::pressStartScreen() {
	dmaCopy(titleScreenBitmap, bgGetGfxPtr(s_bgSub), titleScreenBitmapLen);
	
	loadTiles(SCREEN_DOWN, 0, 11, SprColors_16, pressStartTiles);
	loadPalette(SCREEN_DOWN, 0, pressStartPal);
	
	Sprite* pressStartSpr1 = new Sprite(SCREEN_DOWN, 0, SprSize_32x8, 0);
	Sprite* pressStartSpr2 = new Sprite(SCREEN_DOWN, 1, SprSize_32x8, 4);
	Sprite* pressStartSpr3 = new Sprite(SCREEN_DOWN, 2, SprSize_32x8, 8);
	
	Timer pressStartTimer;
	pressStartTimer.start();
	
	while(1) {
		// Read keys data
		scanKeys();
		
		if((keysDown() & KEY_START) || (keysDown() & KEY_TOUCH)) {
			break;
		}
		
		//Draw the image in the screen
		
		if(pressStartTimer.time() > 750) {
			//ulDrawImageXY(pressStartImg, 85, 152);
			pressStartSpr1->draw(85, 152);
			pressStartSpr2->draw(117, 152);
			pressStartSpr3->draw(149, 152);
			if(pressStartTimer.time() > 1500) {
				pressStartTimer.reset();
				pressStartTimer.start();
			}
		} else {
			pressStartSpr1->clear();
			pressStartSpr2->clear();
			pressStartSpr3->clear();
		}
		
		// Wait the VBlank
		swiWaitForVBlank();
	}
	
	delete pressStartSpr1;
	delete pressStartSpr2;
	delete pressStartSpr3;
	
	titleScreen();
}

void Game::titleScreen() {
	consoleClear();
	
	dmaCopy(titleScreenBitmap, bgGetGfxPtr(s_bg), titleScreenBitmapLen);
	dmaCopy(fileSelectBitmap, bgGetGfxPtr(s_bgSub), fileSelectBitmapLen);
	
	loadTiles(SCREEN_DOWN, 0, 2, SprColors_16, acornTiles);
	loadTiles(SCREEN_DOWN, 2, 12, SprColors_16, linktsTiles);
	loadPalette(SCREEN_DOWN, 0, gfxPal);
	loadPalette(SCREEN_DOWN, 1, linktsPal);
	
	Sprite* acorn = new Sprite(SCREEN_DOWN, 0, SprSize_8x16, 0);
	Sprite* linkts = new Sprite(SCREEN_DOWN, 1, SprSize_16x16, 2);
	
	int curPos = 1;
	
	while(1) {
		// Read keys data
		scanKeys();
		
		//Draw acorn sprite
		acorn->draw(8, 64+((curPos-1)*32));
		
		// Draw link sprite
		linkts->draw(138, 74, 1);
		
		if(keysDown() & KEY_UP) {
			curPos--;
		}
		else if(keysDown() & KEY_DOWN) {
			curPos++;
		}
		
		if(curPos < 1) {
			curPos = 3;
		}
		else if(curPos > 3){
			curPos = 1;
		}
		
		if(keysHeld() & KEY_A) {
			break;
		}
		
		// Wait the VBlank
		swiWaitForVBlank();
	}
	
	delete acorn;
	delete linkts;
	
	init();
}

int swordAnimations[4] = {0, 1, 2, 3};

void Game::init() {
	dmaCopy(statsBitmap, bgGetGfxPtr(s_bg), statsBitmapLen);
	
	Sprite::loadAllIcons(SCREEN_UP);
	
	Sprite swordIcon(SCREEN_UP, 1, SprSize_8x16, 46);
	
	Weapon sword(&swordIcon, (Sprite*)NULL);
	sword.setKey(W_KEY_B);
	
	link = new Player;
	
	maps = initMaps(s_mapBg);
	
	currentMap = maps[0];
	currentMap->init();
	
	while(1) {
		// Read keys data
		scanKeys();
		
		// Move link
		link->move();
		
		// Draw sprite
		link->draw();
		
		// Draw sword icon
		sword.drawIcon();
		
		if(keysDown() & KEY_A) {
			for(int i = 0 ; i < 32 ; i++) {
				currentMap->scroll(8, 0);
				swiWaitForVBlank();
			}
			currentMap = currentMap->nextMap();
		}
		if(keysDown() & KEY_B) {
			for(int i = 0 ; i < 24 ; i++) {
				currentMap->scroll(0, 8);
				swiWaitForVBlank();
			}
			currentMap = currentMap->nextMap();
		}
		if(keysDown() & KEY_X) {
			for(int i = 0 ; i < 24 ; i++) {
				currentMap->scroll(0, -8);
				swiWaitForVBlank();
			}
			currentMap = currentMap->nextMap();
		}
		if(keysDown() & KEY_Y) {
			for(int i = 0 ; i < 32 ; i++) {
				currentMap->scroll(-8, 0);
				swiWaitForVBlank();
			}
			currentMap = currentMap->nextMap();
		}
		
		// Wait the VBL
		swiWaitForVBlank();
	}
}
