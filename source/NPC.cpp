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
#include <cstdio>
#include "timer.h"
#include "sprites.h"
#include "player.h"
#include "NPC.h"
#include "map.h"
#include "mapManager.h"
#include "door.h"
#include "game.h"

unsigned int NPC::nbNPCs = 0;

// Fill animations table
int NPCanimations[4][4] = {
	{4,0},
	{5,1},
	{6,2},
	{7,3},
};

NPC::NPC(s16 x, s16 y, bool move, s8 area, PlayerDirection direction, const void *tiles, const void *pal, u16 map) : Sprite(SCREEN_UP, nbNPCs + 1, SprSize_16x16, 0) {
	m_id = nbNPCs;
	nbNPCs++;
	
	m_x = x;
	m_y = y;
	m_vx = 0;
	m_vy = 0;
	m_move = move;
	m_areaY = m_areaX = area;
	m_direction = direction;
	m_map = map;
	
	//loadTiles(SCREEN_UP, 32, 32, SprColors_16, tiles);
	//loadPalette(SCREEN_UP, 1, pal);
	
	// Add animations to player's sprite
	addAnimation(2, NPCanimations[0], 100); // Down
	addAnimation(2, NPCanimations[1], 100); // Right
	addAnimation(2, NPCanimations[2], 100); // Left
	addAnimation(2, NPCanimations[3], 100); // Up
}

NPC::~NPC() {
}

bool NPC::inTable(u16 t[], u16 n) {
	int i = 0;
	while(t[i]) {
		if(t[i] == n) {
			return true;
		}
		i++;
	}
	return false;
}

bool NPC::passable(s16 caseX, s16 caseY) {
	if(inTable(nonPassableTiles, Game::currentMap->tileset()->info[Game::currentMap->getTile(caseX, caseY)])) {
		return false;
	} else {
		return true;
	}
}

bool NPC::inTiles(s16 caseX, s16 caseY, u16 t[]) {
	if(inTable(t, Game::currentMap->tileset()->info[Game::currentMap->getTile(caseX, caseY)])) {
		return true;
	} else {
		return false;
	}
}

void NPC::testCollisions() {
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
		
		printf("Truc");
		
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

void NPC::move() {
	if(Timer::osTime % 2 == 0) {
		int dir = rand()%4;
		if(dir == 0) {
			m_vy = -1; // Set vertical speed vector negative
			
			if((!(keysHeld() & KEY_DOWN)) && (!(keysHeld() & KEY_LEFT)) && (!(keysHeld() & KEY_RIGHT))) {
				m_direction = DIR_UP; // Set direction to up
			}
		}
		
		if(dir == 1) {
			m_vy = 1; // Set vertical speed vector positive
			
			if((!(keysHeld() & KEY_UP)) && (!(keysHeld() & KEY_LEFT)) && (!(keysHeld() & KEY_RIGHT))) {
				m_direction = DIR_DOWN; // Set direction to down
			}
		}
		
		if(dir == 2) {
			m_vx = -1; // Set horizontal speed vector negative
			
			if((!(keysHeld() & KEY_UP)) && (!(keysHeld() & KEY_DOWN)) && (!(keysHeld() & KEY_RIGHT))) {
				m_direction = DIR_LEFT; // Set direction to left
			}
		}
		
		if(dir == 3) {
			m_vx = 1; // Set horizontal speed vector positive
			
			if((!(keysHeld() & KEY_UP)) && (!(keysHeld() & KEY_DOWN)) && (!(keysHeld() & KEY_LEFT))) {
				m_direction = DIR_RIGHT; // Set direction to right
			}
		}
		
		// Test collisions
		testCollisions();
		
		// Add speed vectors to coordinates ( move the NPC )
		m_x += m_vx;
		m_y += m_vy;
		
		// Reset speed vectors
		m_vx = 0;
		m_vy = 0;
	}
}

void NPC::draw() {
	// If all directional keys are released
	if(!(keysHeld() & (KEY_UP | KEY_DOWN | KEY_LEFT | KEY_RIGHT))) {
		drawFrame(m_x, m_y, m_direction); // Draw a simple frame
	} else {
		playAnimation(m_x, m_y, m_direction); // Play animation
	}
}

