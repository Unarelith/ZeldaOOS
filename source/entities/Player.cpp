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
#include "Player.hpp"

#include "link.h"

u8 linkAnimations[8][4] = {
	// Movement
	{4, 0},
	{5, 1},
	{6, 2},
	{7, 3},
	
	// Sword attack
	{ 8, 12, 12, 12},
	{ 9, 13, 13, 13},
	{10, 14, 14, 14},
	{11, 15, 15, 15}
};

Player::Player() : Character(SCREEN_UP, (10 << 4), (5 << 4), 0, 0, SprSize_16x16, 0, 4, 64, 0, linkTiles, linkPal) {
	// Movement
	addAnimation(2, linkAnimations[0], 150);
	addAnimation(2, linkAnimations[1], 150);
	addAnimation(2, linkAnimations[2], 150);
	addAnimation(2, linkAnimations[3], 150);
	
	// Sword attack
	addAnimation(4, linkAnimations[4], 90);
	addAnimation(4, linkAnimations[5], 90);
	addAnimation(4, linkAnimations[6], 90);
	addAnimation(4, linkAnimations[7], 90);
	
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

void Player::update() {
	if(m_state != State::Attacking) {
		move();
	}
	
	if(keysHeld() & KEY_A || m_state == State::Attacking) {
		useSword();
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
	
	if(!(keysHeld() & KEY_A) && m_state == State::Attacking && isAnimationAtEnd(m_direction + 4)) {
		m_state = State::Idle;
		
		SpriteManager::sword->clear();
	}
	
	if(m_state == State::Attacking
	&& SpriteManager::sword->isAnimationAtFrame(m_direction, 3)) {
		if(m_direction == Direction::Up
		&& grassTile(m_x + 2, m_y - 4)
		&& grassTile(m_x + 6, m_y - 4)) {
			MapManager::currentMap->setDisplayTile(int(m_x + 4) >> 4, int(m_y - 4) >> 4, 2);
			SpriteManager::addGrassDestroyAnimation(int(m_x + 4) >> 4, int(m_y - 4) >> 4);
		}
		
		if(m_direction == Direction::Down
		&& grassTile(m_x + 2, m_y + 16 + 4)
		&& grassTile(m_x + 6, m_y + 16 + 4)) {
			MapManager::currentMap->setDisplayTile(int(m_x + 4) >> 4, int(m_y + 16 + 4) >> 4, 2);
			SpriteManager::addGrassDestroyAnimation(int(m_x + 4) >> 4, int(m_y + 16 + 4) >> 4);
		}
		
		if(m_direction == Direction::Left
		&& grassTile(m_x - 5, m_y + 8)
		&& grassTile(m_x - 5, m_y + 11)) {
			MapManager::currentMap->setDisplayTile(int(m_x - 5) >> 4, int(m_y + 10) >> 4, 2);
			SpriteManager::addGrassDestroyAnimation(int(m_x - 5) >> 4, int(m_y + 10) >> 4);
		}
		
		if(m_direction == Direction::Right
		&& grassTile(m_x + 16 + 5, m_y + 8)
		&& grassTile(m_x + 16 + 5, m_y + 11)) {
			MapManager::currentMap->setDisplayTile(int(m_x + 16 + 5) >> 4, int(m_y + 10) >> 4, 2);
			SpriteManager::addGrassDestroyAnimation(int(m_x + 16 + 5) >> 4, int(m_y + 10) >> 4);
		}
	}
}

void Player::move() {
	m_state = State::Idle;
	
	if(keysHeld() & KEY_LEFT) {
		m_vx = -1;
		m_state = State::Moving;
		
		if(!(keysHeld() & KEY_DOWN) && !(keysHeld() & KEY_UP) && !(keysHeld() & KEY_RIGHT)) {
			m_direction = Direction::Left;
		}
	}
	
	if(keysHeld() & KEY_RIGHT) {
		m_vx = 1;
		m_state = State::Moving;
		
		if(!(keysHeld() & KEY_DOWN) && !(keysHeld() & KEY_LEFT) && !(keysHeld() & KEY_UP)) {
			m_direction = Direction::Right;
		}
	}
	
	if(keysHeld() & KEY_UP) {
		m_vy = -1;
		m_state = State::Moving;
		
		if(!(keysHeld() & KEY_DOWN) && !(keysHeld() & KEY_LEFT) && !(keysHeld() & KEY_RIGHT)) {
			m_direction = Direction::Up;
		}
	}
	
	if(keysHeld() & KEY_DOWN) {
		m_vy = 1;
		m_state = State::Moving;
		
		if(!(keysHeld() & KEY_UP) && !(keysHeld() & KEY_LEFT) && !(keysHeld() & KEY_RIGHT)) {
			m_direction = Direction::Down;
		}
	}
}

void Player::useSword() {
	if(m_state != State::Attacking) {
		m_state = State::Attacking;
		
		resetAnimation(m_direction + 4);
		startAnimation(m_direction + 4);
		
		playAnimation(m_x, m_y, m_direction + 4);
		
		SpriteManager::sword->playAnimation(m_x + m_animations[m_direction + 4].position[0][0], m_y + m_animations[m_direction + 4].position[0][1], m_direction);
		
		switch(m_direction) {
			case Direction::Left:
				m_vx = -4;
				break;
			case Direction::Right:
				m_vx = 4;
				break;
			case Direction::Up:
				m_vy = -3;
				break;
			case Direction::Down:
				m_vy = 3;
				break;
		}
	}
	else if(!isAnimationAtEnd(m_direction + 4)) {
		playAnimation(m_x, m_y, m_direction + 4);
		
		if(!SpriteManager::sword->isAnimationAtEnd(m_direction)) {
			SpriteManager::sword->playAnimation(m_x + m_animations[m_direction + 4].position[0][0], m_y + m_animations[m_direction + 4].position[0][1], m_direction);
		}
	} else {
		if(m_animations[m_direction + 4].isPlaying) {
			switch(m_direction) {
				case Direction::Left:
					m_vx = 4;
					break;
				case Direction::Right:
					m_vx = -4;
					break;
				case Direction::Up:
					m_vy = 3;
					break;
				case Direction::Down:
					m_vy = -3;
					break;
			}
			
			stopAnimation(m_direction + 4);
		}
		
		drawFrame(m_x, m_y, m_direction);
		
		SpriteManager::sword->drawPositionedFrame(m_x, m_y, m_direction, 3);
	}
}

