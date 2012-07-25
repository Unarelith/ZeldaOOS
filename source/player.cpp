/*---------------------------------------------------------------------------------

	Eleandra
	Copyright (C) 2012 Quentin BAZIN quent42340@gmail.com
	
	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
	
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	
	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

---------------------------------------------------------------------------------*/
#include <nds.h>
#include "timer.h"
#include "sprites.h"
#include "map.h"
#include "mapManager.h"
#include "player.h"
#include "link.h"
#include "game.h"

// Fill animations table
int animations[12][4] = {
	{4,0},
	{5,1},
	{6,2},
	{7,3},
	{8,12,16,16},
	{9,13,17,17},
	{10,14,18,18},
	{11,15,19,19},
	{20,24},
	{21,25},
	{22,26},
	{23,27}
};
	
Player::Player() : Sprite(SCREEN_UP, 0, SprSize_16x16, 0) {
	//loadTiles(SCREEN_UP, 0, 32, SprColors_16, linkTiles);
	//loadPalette(SCREEN_UP, 0, linkPal);
	
	m_x = 240;
	m_y = 128;
	m_vx = 0;
	m_vy = 0;
	m_direction = DIR_LEFT;
	
	// Add animations to player's sprite
	addAnimation(2, animations[0], 100); // Down
	addAnimation(2, animations[1], 100); // Right
	addAnimation(2, animations[2], 100); // Left
	addAnimation(2, animations[3], 100); // Up
	addAnimation(4, animations[4], 50);
	addAnimation(4, animations[5], 50);
	addAnimation(4, animations[6], 50);
	addAnimation(4, animations[7], 50);
	addAnimation(2, animations[8], 100);
	addAnimation(2, animations[9], 100);
	addAnimation(2, animations[10], 100);
	addAnimation(2, animations[11], 100);
}

Player::~Player() {
}

bool Player::inTable(u16 t[], u16 n) {
	int i = 0;
	while(t[i]) {
		if(t[i] == n) {
			return true;
		}
		i++;
	}
	return false;
}

bool Player::passable(s16 caseX, s16 caseY) {
	if(inTable(nonPassableTiles, Game::currentMap->tileset()->info[Game::currentMap->getTile(caseX, caseY)])) {
		return false;
	} else {
		return true;
	}
}

bool Player::inTiles(s16 caseX, s16 caseY, u16 t[]) {
	if(inTable(t, Game::currentMap->tileset()->info[Game::currentMap->getTile(caseX, caseY)])) {
		return true;
	} else {
		return false;
	}
}

void Player::testCollisions() {
	// Right
	if((m_vx > 0) && ((!passable((m_x + 12) >> 4, (m_y + 8) >> 4)) || (!passable((m_x + 12) >> 4, (m_y + 13) >> 4)))) {
		m_vx = 0;
		
		// Obstacle up
		if((!passable((m_x + 12) >> 4, (m_y + 8) >> 4)) && passable((m_x + 12) >> 4, (m_y + 13) >> 4)) {
			if(m_vy == 0) m_vy = 1;
		}
		// Obstacle down
		if((!passable((m_x + 12) >> 4, (m_y + 13) >> 4)) && passable((m_x + 12) >> 4, (m_y + 8) >> 4)) {
			if(m_vy == 0) m_vy = -1;
		}
	}
	
	// Left
	if((m_vx < 0) && ((!passable((m_x + 3) >> 4, (m_y + 8) >> 4)) || (!passable((m_x + 3) >> 4, (m_y + 13) >> 4)))) {
		m_vx = 0;
		
		// Obstacle up
		if((!passable((m_x + 3) >> 4, (m_y + 8) >> 4)) && passable((m_x + 3) >> 4, (m_y + 13) >> 4)) {
			if(m_vy == 0) m_vy = 1;
		}
		// Obstacle down
		if((!passable((m_x + 3) >> 4, (m_y + 13) >> 4)) && passable((m_x + 3) >> 4, (m_y + 8) >> 4)) {
			if(m_vy == 0) m_vy = -1;
		}
	}
	
	// Up
	if((m_vy < 0) && ((!passable((m_x + 5) >> 4, (m_y + 5) >> 4)) || (!passable((m_x + 10) >> 4, (m_y + 5) >> 4)))) {
		m_vy = 0;
		
		// Obstacle left
		if((!passable((m_x + 5) >> 4, (m_y + 5) >> 4)) && passable((m_x + 10) >> 4, (m_y + 5) >> 4)) {
			if(m_vx == 0) m_vx = 1;
		}
		// Obstacle right
		if((!passable((m_x + 10) >> 4, (m_y + 5) >> 4)) && passable((m_x + 5) >> 4, (m_y + 5) >> 4)) {
			if(m_vx == 0) m_vx = -1;
		}
	}
	
	// Down
	if((m_vy > 0) && ((!passable((m_x + 5) >> 4, (m_y + 15) >> 4)) || (!passable((m_x + 10) >> 4, (m_y + 15) >> 4)))) {
		m_vy = 0;
		
		// Obstacle left
		if((!passable((m_x + 5) >> 4, (m_y + 15) >> 4)) && passable((m_x + 10) >> 4, (m_y + 15) >> 4)) {
			if(m_vx == 0) m_vx = 1;
		}
		// Obstacle right
		if((!passable((m_x + 10) >> 4, (m_y + 15) >> 4)) && passable((m_x + 5) >> 4, (m_y + 15) >> 4)) {
			if(m_vx == 0) m_vx = -1;
		}
	}
}

void Player::move() {
	if((keysHeld() & KEY_UP)) {
		m_vy = -1; // Set vertical speed vector negative
		
		if((!(keysHeld() & KEY_DOWN)) && (!(keysHeld() & KEY_LEFT)) && (!(keysHeld() & KEY_RIGHT))) {
			m_direction = DIR_UP; // Set direction to up
		}
	}
	
	if((keysHeld() & KEY_DOWN)) {
		m_vy = 1; // Set vertical speed vector positive
		
		if((!(keysHeld() & KEY_UP)) && (!(keysHeld() & KEY_LEFT)) && (!(keysHeld() & KEY_RIGHT))) {
			m_direction = DIR_DOWN; // Set direction to down
		}
	}
	
	if((keysHeld() & KEY_LEFT)) {
		m_vx = -1; // Set horizontal speed vector negative
		
		if((!(keysHeld() & KEY_UP)) && (!(keysHeld() & KEY_DOWN)) && (!(keysHeld() & KEY_RIGHT))) {
			m_direction = DIR_LEFT; // Set direction to left
		}
	}
	
	if((keysHeld() & KEY_RIGHT)) {
		m_vx = 1; // Set horizontal speed vector positive
		
		if((!(keysHeld() & KEY_UP)) && (!(keysHeld() & KEY_DOWN)) && (!(keysHeld() & KEY_LEFT))) {
			m_direction = DIR_RIGHT; // Set direction to right
		}
	}
	
	// Test collisions
	testCollisions();

	// Add speed vectors to coordinates ( move the player )
	m_x += m_vx;
	m_y += m_vy;
	
	// Reset speed vectors
	m_vx = 0;
	m_vy = 0;
}

void Player::draw() {
	// If all directional keys are released
	if(!(keysHeld() & (KEY_UP | KEY_DOWN | KEY_LEFT | KEY_RIGHT))) {
		drawFrame(m_x, m_y, m_direction); // Draw a simple frame
	} else {
		playAnimation(m_x, m_y, m_direction); // Play player's animation
	}
}

