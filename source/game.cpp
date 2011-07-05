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
	
	//init();
	pressStartScreen();
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
	
	Player* link = new Player;
	
	u16 nonPassable[127] = {
		7,28,29,30,31,44,45,46,47,60,61,62,63,64,65,66,67,68,69,70,71,76,78,79,112,113,114,115,116,117,
		118,119,120,121,122,123,124,125,128,129,130,131,132,133,134,135,136,137,138,139,140,141,144,145,146,147,148,149,
		150,151,152,153,154,155,156,157,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,175,176,177,178,179,
		180,181,182,183,184,185,186,187,188,192,193,194,195,196,197,198,199,200,201,203,204,232,233,234,235,236,237,239,
		240,241,242,243,244,245,246,247,250,251,252,254,255
	};
	
	Tileset tileset = {plainTiles, plainPal, nonPassable};
	
	Map* a1 = new Map(&tileset, "/maps/a1.map", 16, 12, 16, 16, s_mapBg);
	currentMap = a1;
	
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
