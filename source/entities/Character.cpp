/*
 * =====================================================================================
 *
 *       Filename:  Character.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  16/07/2014 15:30:20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#include "MapManager.hpp"
#include "CharacterManager.hpp"

Character::Character(u8 screen, s16 x, s16 y, u8 direction, u8 id, s5_dimension size, u8 baseTile, u16 tileSize, u16 nbTiles, u8 paletteSlot, const void *tilesData, const void *palData) : Sprite(screen, id, size, baseTile, tileSize, nbTiles, paletteSlot, tilesData, palData) {
	m_state = State::Idle;
	
	m_x = x;
	m_y = y;
	
	m_vx = 0;
	m_vy = 0;
	
	m_direction = Direction::Down;
}

Character::~Character() {
}

void Character::draw() {
	if(m_state == State::Idle){
		drawFrame(m_x, m_y, m_direction);
	}
	else if(m_state == State::Moving) {
		playAnimation(m_x, m_y, m_direction);
	}
}

void Character::testCollisions() {
	mapCollisions();
}

void Character::mapCollisions() {
	u8 collisionMatrix[4][4] = {
		{12, 8,12,13},
		{ 3, 8, 3,13},
		{ 5, 5,10, 5},
		{ 5,15,10,15}
	};
	
	for(u8 i = 0 ; i < 4 ; i++) {
		bool test;
		
		if(i == 0) {
			test = (m_vx > 0);
		}
		else if(i == 1) {
			test = (m_vx < 0);
		}
		else if(i == 2) {
			test = (m_vy < 0);
		}
		else if(i == 3) {
			test = (m_vy > 0);
		}
		
		if(test
		&& (!passable(m_x + collisionMatrix[i][0], m_y + collisionMatrix[i][1])
		||  !passable(m_x + collisionMatrix[i][2], m_y + collisionMatrix[i][3]))) {
			if(i < 2)	m_vx = 0;
			else		m_vy = 0;
			
			if( passable(m_x + collisionMatrix[i][2], m_y + collisionMatrix[i][3])
			&& !passable(m_x + collisionMatrix[i][0], m_y + collisionMatrix[i][1])) {
				if(i < 2 && m_vy == 0)	m_vy = 1;
				else if(    m_vx == 0)	m_vx = 1;
			}
			
			if( passable(m_x + collisionMatrix[i][0], m_y + collisionMatrix[i][1])
			&& !passable(m_x + collisionMatrix[i][2], m_y + collisionMatrix[i][3])) {
				if(i < 2 && m_vy == 0)	m_vy = -1;
				else if(    m_vx == 0)	m_vx = -1;
			}
		}
	}
	
	if(((stairsTile(m_x +  2, m_y +  2))
	||  (stairsTile(m_x + 14, m_y +  2))
	||  (stairsTile(m_x +  2, m_y + 14))
	||  (stairsTile(m_x + 14, m_y + 14)))
	&& m_vy != 0) {
		m_vx /= 2;
		m_vy /= 2;
	}
	
	if((lowGrassTile(m_x +  2, m_y +  2))
	|| (lowGrassTile(m_x + 14, m_y +  2))
	|| (lowGrassTile(m_x +  2, m_y + 14))
	|| (lowGrassTile(m_x + 14, m_y + 14))) {
		m_vx /= 4;
		m_vx *= 3;
		
		m_vy /= 4;
		m_vy *= 3;
		
		CharacterManager::grassEffect->drawFrame(m_x, m_y, 0);
	} else {
		CharacterManager::grassEffect->clear();
	}
	
	if((lowWaterTile(m_x +  2, m_y +  2))
	|| (lowWaterTile(m_x + 14, m_y +  2))
	|| (lowWaterTile(m_x +  2, m_y + 14))
	|| (lowWaterTile(m_x + 14, m_y + 14))) {
		CharacterManager::lowWaterEffect->playAnimation(m_x, m_y + 8, 0);
	} else {
		CharacterManager::lowWaterEffect->clear();
	}
}

