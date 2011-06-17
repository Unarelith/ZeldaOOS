#include "game.h"
#include "efs_lib.h"

Game::Game() {
	// Set up default exception handler
	defaultExceptionHandler();
	
	// Initialize random seed
	srand(time(NULL));
	
	// Setup the video modes
	videoSetMode(MODE_0_2D);
	videoSetModeSub(MODE_0_2D);
	
	// Setup VRAM banks
	vramSetPrimaryBanks(VRAM_A_MAIN_SPRITE,
						VRAM_B_MAIN_BG_0x06000000,
						VRAM_C_SUB_BG,
						VRAM_D_SUB_SPRITE);
	
	// Initialize the console
	PrintConsole bottomScreen;
	consoleInit(&bottomScreen, 1, BgType_Text4bpp, BgSize_T_256x256, 2, 0, false, true);
	
	printf("EFS loading...");
	
	// Initialize EFS filesystem
	if(!EFS_Init(EFS_AND_FAT | EFS_DEFAULT_DEVICE, NULL)) {
		printf("FATAL ERROR: Bad filesystem init");
		while(1) { swiWaitForVBlank(); }
	}
	
	printf("EFS loaded!");
	
	// Initialize the oam ( Sprite system )
	oamInit(&oamMain, SpriteMapping_Bmp_1D_256, false);
	oamInit(&oamSub, SpriteMapping_Bmp_1D_256, false);
	
	// Initialize the background
	s_bg = bgInit(0, BgType_Text8bpp, BgSize_T_512x512, 0, 1);
	s_bgSub = bgInitSub(0, BgType_Text8bpp, BgSize_T_512x512, 4, 1);
	
	pressStartScreen();
}

Game::~Game() {
}

void Game::pressStartScreen() {
	consoleClear();
	
	dmaCopy(titleScreenTiles, bgGetGfxPtr(s_bgSub), titleScreenTilesLen);
	dmaCopy(titleScreenPal, BG_PALETTE_SUB, titleScreenPalLen);
	dmaCopy(titleScreenMap, bgGetMapPtr(s_bgSub), titleScreenMapLen);
	
	while(1) {
		swiWaitForVBlank();
		
		bgUpdate();
		oamUpdate(&oamSub);
	}
}
