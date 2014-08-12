/*
 * =====================================================================================
 *
 *       Filename:  SpriteManager.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  28/07/2014 17:05:11
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#include <math.h>

#include "SpriteManager.hpp"

#include "sword.h"
#include "grassDestroy.h"
#include "grassEffect.h"
#include "waterEffect.h"
#include "heart.h"

Sprite *SpriteManager::sword = nullptr;
Sprite *SpriteManager::grassDestroy = nullptr;
Sprite *SpriteManager::grassEffect = nullptr;
Sprite *SpriteManager::lowWaterEffect = nullptr;
Sprite *SpriteManager::heart = nullptr;

std::vector<std::pair<Sprite, u32>> SpriteManager::tmpanims;
std::vector<std::pair<Sprite, u32>> SpriteManager::anims;

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

u8 heartAnimation[4] = {0, 0, 0, 0};

s16 heartPosition[4][2] = {
	{4, 1},
	{4, 2},
	{4, 3},
	{4, 4}
};

void SpriteManager::init() {
	sword = new Sprite(SCREEN_UP, 1, SprSize_16x16, 64, 4, 48, 0, swordTiles, nullptr);
	setSpritePriority(SCREEN_UP, 1, 0);
	sword->addAnimation(4, swordAnimation[0], 100, swordPosition[0]);
	sword->addAnimation(4, swordAnimation[1], 100, swordPosition[1]);
	sword->addAnimation(4, swordAnimation[2], 100, swordPosition[2]);
	sword->addAnimation(4, swordAnimation[3], 100, swordPosition[3]);
	
	grassDestroy = new Sprite(SCREEN_UP, 2, SprSize_32x32, 112, 16, 96, 0, grassDestroyTiles, nullptr);
	setSpritePriority(SCREEN_UP, 2, 0);
	grassDestroy->addAnimation(6, grassDestroyAnimation, 50);
	
	grassEffect = new Sprite(SCREEN_UP, 3, SprSize_16x16, 208, 4, 4, 0, grassEffectTiles, nullptr);
	setSpritePriority(SCREEN_UP, 3, 0);
	
	lowWaterEffect = new Sprite(SCREEN_UP, 4, SprSize_16x16, 212, 4, 12, 0, waterEffectTiles, nullptr);
	setSpritePriority(SCREEN_UP, 4, 0);
	lowWaterEffect->addAnimation(3, lowWaterEffectAnimation, 100);
	
	heart = new Sprite(SCREEN_UP, 5, SprSize_8x8, 224, 1, 1, 0, heartTiles, nullptr);
	setSpritePriority(SCREEN_UP, 5, 2);
	heart->addAnimation(4, heartAnimation, 75, heartPosition);
}

void SpriteManager::free() {
	delete heart;
	delete lowWaterEffect;
	delete grassEffect;
	delete grassDestroy;
	delete sword;
}

void SpriteManager::updateAnimations() {
	u8 i = 81;
	for(auto &it : anims) {
		it.first.setID(i);
		setSpritePriority(SCREEN_UP, i, 2);
		if(!it.first.isAnimationAtEnd(0)) {
			it.first.playAnimation((it.second & 0xFFFF) << 4, it.second >> 12, 0);
		} else {
			it.first.stopAnimation(0);
			it.first.drawPositionedFrame((it.second & 0xFFFF) << 4, it.second >> 12, 0, it.first.getAnimationFrame(0) - 1);
		}
		i++;
	}
	
	i = 101;
	for(auto &it : tmpanims) {
		it.first.setID(i);
		if(!it.first.isAnimationAtEnd(0)) {
			it.first.playAnimation(((it.second & 0xFFFF) << 4) - 8, (it.second >> 12) - 8, 0);
		} else {
			it.first.clear();
			tmpanims.erase(tmpanims.begin() + i - 101);
		}
		i++;
	}
}

void SpriteManager::addGrassDestroyAnimation(u16 tileX, u16 tileY) {
	tmpanims.push_back(std::make_pair(Sprite(*grassDestroy), tileX | (tileY << 16)));
}

void SpriteManager::addHeartAnimation(u16 tileX, u16 tileY) {
	anims.push_back(std::make_pair(Sprite(*heart), tileX | (tileY << 16)));
}

