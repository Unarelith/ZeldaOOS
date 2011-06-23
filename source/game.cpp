#include "game.h"
#include "efs_lib.h"

Map* Game::currentMap;

Game::Game() {
	// Set up default exception handler
	defaultExceptionHandler();
	
	// Initialize random seed
	srand(time(NULL));
	
	videoSetModeSub(MODE_5_2D);
	
	vramSetBankC(VRAM_C_SUB_BG);
	vramSetBankD(VRAM_D_SUB_SPRITE);
	
	ul_isConsoleInited = 1;
	consoleInit(NULL, 0, BgType_Text4bpp, BgSize_T_256x256, 22, 3, false, true);
	
	s_bg = bgInitSub(3, BgType_Bmp8, BgSize_B8_256x256, 5, 0);
	
	oamInit(&oamSub, SpriteMapping_1D_256, false);
	
    // Initialization of µLibrary
    ulInit(UL_INIT_ALL);
    ulInitGfx();
    ulInitText();
	
    // Use magenta as a transparent color
    ulSetTransparentColor(RGB15(31, 0, 31));
	
	// Set main LCD
	ulSetMainLcd(0);
    
    // Banks A-B for textures VRAM
    ulSetTexVramParameters(UL_BANK_A | UL_BANK_B, VRAM_A, 256 << 10);
	
	ulDebug("EFS loading...\n");
	
	// Initialize EFS filesystem
	if(!EFS_Init(EFS_AND_FAT | EFS_DEFAULT_DEVICE, NULL)) {
		ulDebug("FATAL ERROR: Bad filesystem init\n");
		while(1) { swiWaitForVBlank(); }
	}
	
	ulDebug("EFS loaded!\n");
	
	Timer::initTimers();
	
	init();
	//pressStartScreen();
}

Game::~Game() {
}

void Game::pressStartScreen() {
	UL_IMAGE* titleScreenImg = ulLoadImageFilePNG((const char*)titleScreen_png, sizeof(titleScreen_png), UL_IN_VRAM, UL_PF_PAL8);
	if(!titleScreenImg) {
		ulDebug("titleScreen image error\n");
	}
	
	UL_IMAGE* pressStartImg = ulLoadImageFilePNG((const char*)pressStart_png, sizeof(pressStart_png), UL_IN_VRAM, UL_PF_PAL8);
	if(!pressStartImg) {
		ulDebug("pressStart image error\n");
	}
	
	Timer pressStartTimer;
	pressStartTimer.start();
	
	while(1) {
		// Read keys data
		ulReadKeys(0);
		
		if((ul_keys.pressed.start) || (ul_keys.touch.click)) {
			break;
		}
		
		// Start the drawing
		ulStartDrawing2D();
		
		//Draw the image in the screen
		ulDrawImage(titleScreenImg);
		
		if(pressStartTimer.time() > 750) {
			ulDrawImageXY(pressStartImg, 85, 152);
			if(pressStartTimer.time() > 1500) {
				pressStartTimer.reset();
				pressStartTimer.start();
			}
		}
		
		// End the drawing
		ulEndDrawing();
		
		// Wait the VBlank (synchronize at 60 fps)
		ulSyncFrame();
	}
	
	ulDeleteImage(titleScreenImg);
	ulDeleteImage(pressStartImg);
	
	titleScreen();
}

void Game::titleScreen() {
	consoleClear();
	
	dmaCopy(titleScreen2Bitmap, bgGetGfxPtr(s_bg), titleScreen2BitmapLen);
	dmaCopy(titleScreen2Pal, BG_PALETTE_SUB, titleScreen2PalLen);
	
	UL_IMAGE* fileSelectImg = ulLoadImageFilePNG((const char*)fileSelect_png, sizeof(fileSelect_png), UL_IN_VRAM, UL_PF_PAL8);
	if(!fileSelectImg) {
		ulDebug("fileSelect image error\n");
	}
	
	UL_IMAGE* acornImg = ulLoadImageFilePNG((const char*)acorn_png, sizeof(acorn_png), UL_IN_VRAM, UL_PF_PAL8);
	if(!acornImg) {
		ulDebug("acorn image error\n");
	}
	
	Sprite3D* linkts = new Sprite3D((const char*)linkts_png, sizeof(linkts_png), 16, 16);
	
	int curPos = 1;
	
	while(1) {
		// Read keys data
		ulReadKeys(0);
		
		// Start the drawing
		ulStartDrawing2D();
		
		//Draw the image in the screen
		ulDrawImage(fileSelectImg);
		ulDrawImageXY(acornImg, 8, 64+((curPos-1)*32));
		
		// Draw sprite
		linkts->drawFrame(138, 74, 1);
		
		// End the drawing
		ulEndDrawing();
		
		if(ul_keys.pressed.up) {
			curPos--;
		}
		else if(ul_keys.pressed.down) {
			curPos++;
		}
		
		if(curPos < 1) {
			curPos = 3;
		}
		else if(curPos > 3){
			curPos = 1;
		}
		
		if(ul_keys.pressed.A) {
			break;
		}
		
		// Wait the VBlank (synchronize at 60 fps)
		ulSyncFrame();
	}
	
	ulDeleteImage(fileSelectImg);
	ulDeleteImage(acornImg);
	
	delete linkts;
	
	init();
}

void Game::init() {
	dmaCopy(statsBitmap, bgGetGfxPtr(s_bg), statsBitmapLen);
	dmaCopy(statsPal, BG_PALETTE_SUB, statsPalLen);
	
	Player* link = new Player;
	
	u16 nonPassable[127] = {
		7,28,29,30,31,44,45,46,47,60,61,62,63,64,65,66,67,68,69,70,71,76,78,79,112,113,114,115,116,117,
		118,119,120,121,122,123,124,125,128,129,130,131,132,133,134,135,136,137,138,139,140,141,144,145,146,147,148,149,
		150,151,152,153,154,155,156,157,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,175,176,177,178,179,
		180,181,182,183,184,185,186,187,188,192,193,194,195,196,197,198,199,200,201,203,204,232,233,234,235,236,237,239,
		240,241,242,243,244,245,246,247,250,251,252,254,255
	};
	
	Tileset tileset = {0, nonPassable};
	tileset.image = ulLoadImageFilePNG((const char*)plain_png, sizeof(plain_png), UL_IN_VRAM, UL_PF_PAL8);
	if(!tileset.image) {
		ulDebug("tileset loading error\n");
	}
	
	Map* a1 = new Map(&tileset, "efs:/maps/a1.map", 16, 12, 16, 16);
	
	//ulDebug("\nvram available: %d\n", ulGetTexVramAvailMemory());
	
	currentMap = a1;
	
	Weapon sword(swordL1Tiles, swordL1Pal, "Sword", 1);
	
	while(1) {
		// Read keys data
		ulReadKeys(0);
		
		// Start the drawing
		ulStartDrawing2D();
		
		// Draw map
		a1->draw();
		
		// Move link
		link->move();
		
		// Draw sprite
		link->draw();
		
		// Draw sword icon
		sword.drawIcon(W_KEY_B);
		
		// End the drawing
		ulEndDrawing();
		
		// Wait the VBlank (synchronize at 60 fps)
		ulSyncFrame();
		
		// Update oam engine
		oamUpdate(&oamSub);
	}
}
