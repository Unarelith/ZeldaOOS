/*
 * =====================================================================================
 *
 *       Filename:  Game.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  16/07/2014 13:32:07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#include <stdio.h>

#include <nds.h>
#include <filesystem.h>
#include <math.h>
#include <time.h>

#include "MapManager.hpp"
#include "DoorManager.hpp"
#include "CharacterManager.hpp"
#include "Game.hpp"

Game::Game() {
	defaultExceptionHandler();
	
	srand(time(NULL));
	
	initNitroFS();
	initVideo();
	initSpriteSystem();
	
	Timer::initSystemTimer();
	
	MapManager::init();
	
	DoorManager::init();
	
	CharacterManager::init();
	
	SpriteManager::init();
	
	m_continue = true;
}

Game::~Game() {
	SpriteManager::free();
	
	CharacterManager::free();
	
	DoorManager::free();
	
	MapManager::free();
}

void Game::initNitroFS() {
	if(!nitroFSInit(NULL)) {
		consoleDemoInit();
		
		printf("NitroFS init error\n");
		printf("\nIf you're on a real NDS, try HBMenu\n");
		printf("Or another linker menu supporting argv");
		
		while(1) {
			swiWaitForVBlank();
		}
	}
}

void Game::initVideo() {
	videoSetMode(MODE_5_2D);
	videoSetModeSub(MODE_5_2D);
	
	vramSetBankA(VRAM_A_MAIN_BG_0x06000000);
	vramSetBankB(VRAM_B_MAIN_SPRITE_0x06400000);
	vramSetBankC(VRAM_C_SUB_BG_0x06200000);
	vramSetBankD(VRAM_D_SUB_SPRITE);
}

void Game::initSpriteSystem() {
	enableSprites(SCREEN_UP, 0);
	enableSprites(SCREEN_DOWN, 0);
}

void Game::mainLoop() {
	MapManager::currentMap->load();
	
	while(1) {
		scanKeys();
		
		SpriteManager::updateAnimations();
		
		CharacterManager::player->update();
		
		CharacterManager::player->draw();
		
		swiWaitForVBlank();
	}
}

