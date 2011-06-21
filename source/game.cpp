#include "game.h"
#include "efs_lib.h"

Game::Game() {
	// Set up default exception handler
	defaultExceptionHandler();
	
	// Initialize random seed
	srand(time(NULL));
	
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
	
	ulDebug("EFS loading...");
	
	// Initialize EFS filesystem
	if(!EFS_Init(EFS_AND_FAT | EFS_DEFAULT_DEVICE, NULL)) {
		ulDebug("FATAL ERROR: Bad filesystem init");
		while(1) { swiWaitForVBlank(); }
	}
	
	ulDebug("EFS loaded!");
	
	Timer::initTimers();
	
	//videoSetModeSub(MODE_5_2D);
	//vramSetBankC(VRAM_C_SUB_BG);
	//s_bg = bgInitSub(3, BgType_Bmp8, BgSize_B8_256x256, 0, 0);
	
	init();
	//pressStartScreen();
}

Game::~Game() {
}

void Game::pressStartScreen() {
	UL_IMAGE* titleScreenImg = ulLoadImageFilePNG((const char*)titleScreen_png, sizeof(titleScreen_png), UL_IN_VRAM, UL_PF_PAL8);
	if(!titleScreenImg) {
		ulDebug("titleScreen image error");
	}
	
	UL_IMAGE* pressStartImg = ulLoadImageFilePNG((const char*)pressStart_png, sizeof(pressStart_png), UL_IN_VRAM, UL_PF_PAL8);
	if(!pressStartImg) {
		ulDebug("pressStart image error");
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
	
	/*dmaCopy(titleScreen2Bitmap, BG_GFX_SUB, titleScreen2BitmapLen);
	dmaCopy(titleScreen2Pal, BG_PALETTE_SUB, titleScreen2PalLen);*/
	
	UL_IMAGE* fileSelectImg = ulLoadImageFilePNG((const char*)fileSelect_png, sizeof(fileSelect_png), UL_IN_VRAM, UL_PF_PAL8);
	if(!fileSelectImg) {
		ulDebug("fileSelect image error");
	}
	
	UL_IMAGE* acornImg = ulLoadImageFilePNG((const char*)acorn_png, sizeof(acorn_png), UL_IN_VRAM, UL_PF_PAL8);
	if(!acornImg) {
		ulDebug("acorn image error");
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
	Player* link = new Player;
	
	UL_IMAGE* tileset = ulLoadImageFilePNG((const char*)plain_png, sizeof(plain_png), UL_IN_VRAM, UL_PF_PAL8);
	if(!tileset) {
		ulDebug("tileset loading error");
	}
	
	Map* a1 = new Map(tileset, "efs:/a1.map", 16, 12, 16, 16);
	
	//ulDebug("\nvram available: %d\n", ulGetTexVramAvailMemory());
	
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
		
		// End the drawing
		ulEndDrawing();
		
		// Wait the VBlank (synchronize at 60 fps)
		ulSyncFrame();
	}
}
