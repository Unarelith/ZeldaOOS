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
	
	pressStartScreen();
}

Game::~Game() {
}

void Game::pressStartScreen() {
	UL_IMAGE* titleScreenImg = ulLoadImageFilePNG((const char*)titleScreen_png, sizeof(titleScreen_png), UL_IN_RAM, UL_PF_PAL8);
	if(!titleScreenImg) {
		ulDebug("titleScreen image error");
	}
	
	UL_IMAGE* pressStartImg = ulLoadImageFilePNG((const char*)pressStart_png, sizeof(pressStart_png), UL_IN_RAM, UL_PF_PAL8);
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
		
		//Wait the VBlank (synchronize at 60 fps)
		ulSyncFrame();
	}
	
	ulDeleteImage(titleScreenImg);
	ulDeleteImage(pressStartImg);
	
	titleScreen();
}

void Game::titleScreen() {
	/*consoleClear();
	
	dmaCopy(titleScreen2Bitmap, BG_GFX_SUB, titleScreen2BitmapLen);
	dmaCopy(titleScreen2Pal, BG_PALETTE_SUB, titleScreen2PalLen);*/
	
	UL_IMAGE* fileSelectImg = ulLoadImageFilePNG((const char*)fileSelect_png, sizeof(fileSelect_png), UL_IN_RAM, UL_PF_PAL8);
	if(!fileSelectImg) {
		ulDebug("fileSelect image error");
	}
	
	UL_IMAGE* acornImg = ulLoadImageFilePNG((const char*)acorn_png, sizeof(acorn_png), UL_IN_RAM, UL_PF_PAL8);
	if(!acornImg) {
		ulDebug("acorn image error");
	}
	
	Sprite3D* link = new Sprite3D((const char*)link_png, sizeof(link_png), 16, 16);
	
	int curPos = 1;
	
	while(1) {
		// Read keys data
		ulReadKeys(0);
		
		if((ul_keys.pressed.start) || (ul_keys.touch.click)) {
			break;
		}
		
		// Start the drawing
		ulStartDrawing2D();
		
		//Draw the image in the screen
		ulDrawImage(fileSelectImg);
		ulDrawImageXY(acornImg, 8, 64+((curPos-1)*32));
		
		// Draw sprite
		link->drawFrame(138, 74, 1);
		
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
		
		//Wait the VBlank (synchronize at 60 fps)
		ulSyncFrame();
	}
	
	ulDeleteImage(fileSelectImg);
	ulDeleteImage(acornImg);
	
	init();
}

void Game::init() {
	
}
