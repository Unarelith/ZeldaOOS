#include "game.h"

Map* Game::currentMap;

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
			pressStartSpr1->drawFrame(85, 152, 0);
			pressStartSpr2->drawFrame(117, 152, 0);
			pressStartSpr3->drawFrame(149, 152, 0);
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
		acorn->drawFrame(8, 64+((curPos-1)*32), 0);
		
		// Draw link sprite
		linkts->drawFrame(138, 74, 0, 1);
		
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

void Game::init() {
	dmaCopy(statsBitmap, bgGetGfxPtr(s_bg), statsBitmapLen);
	
	Sprite::loadAllIcons(SCREEN_UP);
	
	Player* link = new Player;
	
	Map** maps = initMaps(s_mapBg);
	//currentMap = maps[0];
	Map* a1 = maps[0];
	a1->init();
	
	while(1) {
		// Read keys data
		scanKeys();
		
		// Draw map
		a1->draw();
		
		// Move link
		link->move();
		
		// Draw sprite
		link->draw();
		
		// Wait the VBL
		swiWaitForVBlank();
	}
}
