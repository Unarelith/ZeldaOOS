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
#include <math.h>

#include "Tools.hpp"
#include "MapManager.hpp"
#include "DoorManager.hpp"
#include "CharacterManager.hpp"

#include "link.h"

u8 linkAnimations[4][4] = {
	{4, 0},
	{5, 1},
	{6, 2},
	{7, 3}
};

Player::Player() : Character(0, (10 << 4), (5 << 4), 0, 0, SprSize_16x16, 0, 4, 32, 0, linkTiles, linkPal) {
	addAnimation(2, linkAnimations[0], 150);
	addAnimation(2, linkAnimations[1], 150);
	addAnimation(2, linkAnimations[2], 150);
	addAnimation(2, linkAnimations[3], 150);
	
	setSpritePriority(m_screen, m_id, 1);
	
	m_inDoor = false;
}

Player::~Player() {
}

void Player::testCollisions() {
	Character::testCollisions();
	
	doorCollisions();
}

void Player::doorCollisions() {
	if(onDoor(m_x + 8, m_y + 8) && !m_inDoor) {
		m_vx = 0;
		m_vy = 0;
		
		Door *door = DoorManager::findDoor(m_x, m_y, MapManager::currentMap->zone(), MapManager::currentMap->x(), MapManager::currentMap->y());
		Door nextDoor = DoorManager::doors[door->nextDoorID];
		
		MapManager::initDoorTransition();
		
		MapManager::currentMap = MapManager::maps[nextDoor.zone][nextDoor.mapX + nextDoor.mapY * sqrt(MapManager::maps[nextDoor.zone].size())];
		
		m_x = nextDoor.spawnX;
		m_y = nextDoor.spawnY;
		
		m_direction = nextDoor.spawnDirection;
		
		draw();
		
		MapManager::currentMap->load();
		
		MapManager::doorTransition();
		
		m_inDoor = true;
		
		ndsDelay(250);
	}
	
	if(!onDoor(m_x +  2, m_y +  2)
	&& !onDoor(m_x + 14, m_y +  2)
	&& !onDoor(m_x +  2, m_y + 14)
	&& !onDoor(m_x + 14, m_y + 14)) {
		m_inDoor = false;
	}
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

void Player::useSword() {
	CharacterManager::sword->playAnimation(m_x, m_y, m_direction);
}

