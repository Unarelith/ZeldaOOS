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
	
	grassEffect = new Sprite(0, 1, SprSize_16x16, 32, 4, 4, 0, grassEffectTiles, nullptr);
	setSpritePriority(0, 1, 0);
	
	lowWaterEffect = new Sprite(0, 2, SprSize_16x16, 36, 4, 12, 0, waterEffectTiles, nullptr);
	setSpritePriority(0, 2, 0);
	lowWaterEffect->addAnimation(3, lowWaterEffectAnimation, 150);
}

void CharacterManager::free() {
	delete lowWaterEffect;
	delete grassEffect;
	
	delete player;
}

