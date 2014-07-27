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

#include "sword.h"
#include "grassDestroy.h"
#include "grassEffect.h"
#include "waterEffect.h"

Player *CharacterManager::player = nullptr;

Sprite *CharacterManager::sword = nullptr;
Sprite *CharacterManager::grassDestroy = nullptr;
Sprite *CharacterManager::grassEffect = nullptr;
Sprite *CharacterManager::lowWaterEffect = nullptr;

u8 swordAnimation[4][4] = {
	{0, 4,  8,  8},
	{1, 5,  9,  9},
	{2, 6, 10, 10},
	{3, 7, 11, 11}
};

s16 swordPosition[4][4][2] = {
	{{-12,   0}, {-12,  12}, {  0,  16}, {  0,  16}},
	{{  0, -12}, { 12, -12}, { 12,   0}, { 12,   0}},
	{{  0, -12}, {-12, -12}, {-12,   0}, {-12,   0}},
	{{ 12,   0}, { 12, -12}, {  0, -12}, {  0, -12}}
};

u8 grassDestroyAnimation[6] = {0, 1, 2, 3, 4, 5};

u8 lowWaterEffectAnimation[3] = {0, 1, 2};

void CharacterManager::init() {
	player = new Player();
	
	sword = new Sprite(0, 1, SprSize_16x16, 32, 4, 48, 0, swordTiles, nullptr);
	setSpritePriority(0, 1, 0);
	sword->addAnimation(4, swordAnimation[0], 100, swordPosition[0]);
	sword->addAnimation(4, swordAnimation[1], 100, swordPosition[1]);
	sword->addAnimation(4, swordAnimation[2], 100, swordPosition[2]);
	sword->addAnimation(4, swordAnimation[3], 100, swordPosition[3]);
	
	grassDestroy = new Sprite(0, 2, SprSize_32x32, 80, 16, 96, 0, grassDestroyTiles, nullptr);
	setSpritePriority(0, 2, 0);
	grassDestroy->addAnimation(6, grassDestroyAnimation, 50);
	
	grassEffect = new Sprite(0, 3, SprSize_16x16, 176, 4, 4, 0, grassEffectTiles, nullptr);
	setSpritePriority(0, 3, 0);
	
	lowWaterEffect = new Sprite(0, 4, SprSize_16x16, 180, 4, 12, 0, waterEffectTiles, nullptr);
	setSpritePriority(0, 4, 0);
	lowWaterEffect->addAnimation(3, lowWaterEffectAnimation, 150);
}

void CharacterManager::free() {
	delete lowWaterEffect;
	delete grassEffect;
	delete grassDestroy;
	delete sword;
	
	delete player;
}

