/*
 * =====================================================================================
 *
 *       Filename:  Player.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  16/07/2014 15:32:25
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#include "MapManager.hpp"
#include "Player.hpp"

#include "link.h"

u8 linkAnimations[4][4] = {
	{4, 0},
	{5, 1},
	{6, 2},
	{7, 3}
};

Player::Player() : Character(0, (10 << 4), (5 << 4), 0, 2, SprSize_16x16, 32, 4, 32, 0, linkTiles, linkPal) {
	addAnimation(2, linkAnimations[0], 100);
	addAnimation(2, linkAnimations[1], 100);
	addAnimation(2, linkAnimations[2], 100);
	addAnimation(2, linkAnimations[3], 100);
}

Player::~Player() {
}

void Player::move() {
	m_moving = false;
	
	if(keysHeld() & KEY_LEFT) {
		m_vx = -1;
		m_moving = true;
		
		if(!(keysHeld() & KEY_DOWN) && !(keysHeld() & KEY_UP) && !(keysHeld() & KEY_RIGHT)) {
			m_direction = Direction::Left;
		}
	}
	
	if(keysHeld() & KEY_RIGHT) {
		m_vx = 1;
		m_moving = true;
		
		if(!(keysHeld() & KEY_DOWN) && !(keysHeld() & KEY_LEFT) && !(keysHeld() & KEY_UP)) {
			m_direction = Direction::Right;
		}
	}
	
	if(keysHeld() & KEY_UP) {
		m_vy = -1;
		m_moving = true;
		
		if(!(keysHeld() & KEY_DOWN) && !(keysHeld() & KEY_LEFT) && !(keysHeld() & KEY_RIGHT)) {
			m_direction = Direction::Up;
		}
	}
	
	if(keysHeld() & KEY_DOWN) {
		m_vy = 1;
		m_moving = true;
		
		if(!(keysHeld() & KEY_UP) && !(keysHeld() & KEY_LEFT) && !(keysHeld() & KEY_RIGHT)) {
			m_direction = Direction::Down;
		}
	}
	
	testCollisions();
	
	m_x += m_vx;
	m_y += m_vy;
	
	m_vx = 0;
	m_vy = 0;
	
	if(m_x > 256 - 16 + 2) {
		MapManager::scrollMaps(1, 0);
	}
	else if(m_x < -2) {
		MapManager::scrollMaps(-1, 0);
	}
	else if(m_y > 192 - 16 + 1) {
		MapManager::scrollMaps(0, 1);
	}
	else if(m_y < 0) {
		MapManager::scrollMaps(0, -1);
	}
}

