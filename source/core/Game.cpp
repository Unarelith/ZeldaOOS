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

#include "MapManager.hpp"
#include "CharacterManager.hpp"
#include "Game.hpp"

Game::Game() {
	defaultExceptionHandler();
	
	initNitroFS();
	initVideo();
	initSpriteSystem();
	
	Timer::initSystemTimer();
	
	MapManager::init();
	
	CharacterManager::init();
	
	m_continue = true;
}

Game::~Game() {
	CharacterManager::free();
	
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
	enableSprites(0, 0);
	enableSprites(1, 0);
	
	for(u8 i = 0 ; i < 128 ; i++) {
		setSpritePriority(0, i, 1);
	}
}

void Game::mainLoop() {
	MapManager::currentMap->load();
	
	while(1) {
		scanKeys();
		
		CharacterManager::player->draw();
		
		swiWaitForVBlank();
	}
}

