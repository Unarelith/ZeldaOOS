/*---------------------------------------------------------------------------------

    The Legend of Zelda: Oracle of Secrets
    Copyright (C) 2011 Pixelda quent42340@gmail.com

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
#include "main.h"

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
	
Player::Player() : Sprite(SCREEN_DOWN, 0, SprSize_16x16, 0) {
	loadTiles(SCREEN_DOWN, 0, 32, SprColors_16, linkTiles);
	loadPalette(SCREEN_DOWN, 0, linkPal);
	
	s_x = 240;
	s_y = 128;
	s_vx = 0;
	s_vy = 0;
	s_direction = DIR_LEFT;
	
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

bool in_table(u16* t, u16 n) {
	int i = 0;
	while(t[i]) {
		if(t[i] == n) {
			return true;
		}
		i++;
	}
	return false;
}

bool passable(s16 caseX, s16 caseY) {
	if(in_table(Game::currentMap->tileset()->nonPassable, Game::currentMap->getTile(caseX, caseY))) {
		return false;
	} else {
		return true;
	}
}

void Player::testCollisions() {
	if(	(!passable((s_x + 4 + s_vx) / 16	, (s_y + 6) 		/ 16)) || // Left up
		(!passable((s_x - 4 + s_vx) / 16 + 1, (s_y + 6) 		/ 16)) || // Right up
		(!passable((s_x + 4 + s_vx) / 16	, (s_y - 1 + 15) 	/ 16)) || // Left down
		(!passable((s_x - 4 + s_vx) / 16 + 1, (s_y - 1 + 15) 	/ 16)))   // Right down
	{
			s_vx = 0;
	}
	if(	(!passable((s_x + 4) / 16		, (s_y + 6 + s_vy) / 16		)) || // Up left
		(!passable((s_x + 4) / 16		, (s_y - 1 + s_vy) / 16 + 1	)) || // Down left
		(!passable((s_x - 4 + 15) / 16	, (s_y + 6 + s_vy) / 16		)) || // Up right
		(!passable((s_x - 4 + 15) / 16	, (s_y - 1 + s_vy) / 16 + 1	)))   // Down right
	{
			s_vy = 0;
	}
}

void Player::move() {
	if((keysHeld() & KEY_UP)) {
		s_vy = -1; // Set vertical speed vector negative
		
		if((!(keysHeld() & KEY_DOWN)) && (!(keysHeld() & KEY_LEFT)) && (!(keysHeld() & KEY_RIGHT))) {
			s_direction = DIR_UP; // Set direction to up
		}
	}
	
	if((keysHeld() & KEY_DOWN)) {
		s_vy = 1; // Set vertical speed vector positive
		
		if((!(keysHeld() & KEY_UP)) && (!(keysHeld() & KEY_LEFT)) && (!(keysHeld() & KEY_RIGHT))) {
			s_direction = DIR_DOWN; // Set direction to down
		}
	}
	
	if((keysHeld() & KEY_LEFT)) {
		s_vx = -1; // Set horizontal speed vector negative
		
		if((!(keysHeld() & KEY_UP)) && (!(keysHeld() & KEY_DOWN)) && (!(keysHeld() & KEY_RIGHT))) {
			s_direction = DIR_LEFT; // Set direction to left
		}
	}
	
	if((keysHeld() & KEY_RIGHT)) {
		s_vx = 1; // Set horizontal speed vector positive
		
		if((!(keysHeld() & KEY_UP)) && (!(keysHeld() & KEY_DOWN)) && (!(keysHeld() & KEY_LEFT))) {
			s_direction = DIR_RIGHT; // Set direction to right
		}
	}
	
	if(s_x > 256 - 16) { // Scroll right
		s_vx = 0;
		s_vy = 0;
		
		for(int i = 0 ; i < 32 ; i++) {
			Game::currentMap->scroll(8, 0);
			if(s_x > 8) {
				s_x -= 8;
			}
			draw();
			swiWaitForVBlank();
		}
		
		Game::currentMap = Game::currentMap->nextMap();
	}
	if(s_x < 0) { // Scroll left
		s_vx = 0;
		s_vy = 0;
		
		for(int i = 0 ; i < 32 ; i++) {
			Game::currentMap->scroll(-8, 0);
			if(s_x < 256 - 16 - 8) {
				s_x += 8;
			}
			draw();
			swiWaitForVBlank();
		}
		
		Game::currentMap = Game::currentMap->nextMap();
	}
	if(s_y > 192 - 16) { // Scroll down
		s_vx = 0;
		s_vy = 0;
		
		for(int i = 0 ; i < 24 ; i++) {
			Game::currentMap->scroll(0, 8);
			if(s_y > 8) {
				s_y -= 8;
			}
			draw();
			swiWaitForVBlank();
		}
		
		Game::currentMap = Game::currentMap->nextMap();
	}
	if(s_y < 0) { // Scroll up
		s_vx = 0;
		s_vy = 0;
		
		for(int i = 0 ; i < 24 ; i++) {
			Game::currentMap->scroll(0, -8);
			if(s_y < 192 - 16 - 8) {
				s_y += 8;
			}
			draw();
			swiWaitForVBlank();
		}
		
		Game::currentMap = Game::currentMap->nextMap();
	}
	
	// Test collisions
	testCollisions();
	
	// Add speed vectors to coordinates ( move the player )
	s_x += s_vx;
	s_y += s_vy;
	
	// Reset speed vectors
	s_vx = 0;
	s_vy = 0;
}

void Player::draw() {
	// If all directional keys are released
	if((!(keysHeld() & KEY_UP)) && (!(keysHeld() & KEY_DOWN)) && (!(keysHeld() & KEY_LEFT)) && (!(keysHeld() & KEY_RIGHT))) {
		drawFrame(s_x, s_y, s_direction); // Draw a simple frame
	} else {
		playAnimation(s_x, s_y, s_direction); // Play player's animation
	}
}
