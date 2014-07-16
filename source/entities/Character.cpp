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
#include "Character.hpp"

Character::Character(u8 screen, s16 x, s16 y, u8 direction, u8 id, s5_dimension size, u8 baseTile, u16 tileSize, u16 nbTiles, u8 paletteSlot, const void *tilesData, const void *palData) : Sprite(screen, id, size, baseTile, tileSize, nbTiles, paletteSlot, tilesData, palData) {
	m_x = x;
	m_y = y;
	
	m_vx = 0;
	m_vy = 0;
	
	m_direction = Direction::Down;
	
	m_moving = false;
}

Character::~Character() {
}

void Character::draw() {
	if(m_moving) {
		playAnimation(m_x, m_y, m_direction);
	} else {
		drawFrame(m_x, m_y, m_direction);
	}
}

