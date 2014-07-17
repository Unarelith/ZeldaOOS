/*
 * =====================================================================================
 *
 *       Filename:  CharacterManager.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  16/07/2014 15:33:46
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#include "CharacterManager.hpp"

#include "grassEffect.h"
#include "waterEffect.h"

Player *CharacterManager::player = nullptr;

Sprite *CharacterManager::grassEffect = nullptr;
Sprite *CharacterManager::lowWaterEffect = nullptr;

u8 lowWaterEffectAnimation[3] = {0, 1, 2};

void CharacterManager::init() {
	player = new Player();
	
	grassEffect = new Sprite(0, 0, SprSize_16x16, 0, 4, 4, 0, grassEffectTiles, nullptr);
	
	lowWaterEffect = new Sprite(0, 1, SprSize_16x16, 4, 4, 12, 0, waterEffectTiles, nullptr);
	lowWaterEffect->addAnimation(3, lowWaterEffectAnimation, 150);
}

void CharacterManager::free() {
	delete lowWaterEffect;
	delete grassEffect;
	
	delete player;
}

