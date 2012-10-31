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

#include "blue_boy.h"
#include "blue_man.h"
#include "farore.h"
#include "postman.h"
#include "red_girl.h"
#include "red_woman.h"
#include "yellow_oldwoman.h"

unsigned int NPC::nbNPCs = 0;

// Fill animations table
int NPCanimations[4][4] = {
	{4,0},
	{5,1},
	{6,2},
	{7,3},
};

void NPC::loadAllNPCs() {
	loadTiles(SCREEN_UP, 32, 32, SprColors_16, blue_boyTiles);
	loadTiles(SCREEN_UP, 64, 32, SprColors_16, blue_manTiles);
	loadTiles(SCREEN_UP, 96, 32, SprColors_16, faroreTiles);
	loadTiles(SCREEN_UP, 128, 32, SprColors_16, red_girlTiles);
	loadTiles(SCREEN_UP, 160, 32, SprColors_16, red_womanTiles);
	loadTiles(SCREEN_UP, 192, 32, SprColors_16, yellow_oldwomanTiles);
	
	loadPalette(SCREEN_UP, 1, blue_boyTiles);
}

NPC::NPC(s16 x, s16 y, PlayerDirection direction, NPCType type, u16 map) : Sprite(SCREEN_UP, nbNPCs + 1, SprSize_16x16, 32) {
	m_id = nbNPCs;
	nbNPCs++;
	
	m_x = x;
	m_y = y;
	m_direction = direction;
	m_map = map;
	m_type = type;
	
	switch(m_type) {
		case NPC_BLUE_BOY:
			break;
		case NPC_BLUE_MEN:
			break;
		case NPC_FARORE:
			break;
		case NPC_POSTMAN:
			break;
		case NPC_RED_GIRL:
			break;
		case NPC_RED_WOMAN:
			break;
		case NPC_YELLOW_OLDWOMAN:
			break;
		default:
			break;
	}
	
	// Add animations to player's sprite
	addAnimation(2, NPCanimations[0], 250); // Down
	addAnimation(2, NPCanimations[1], 250); // Right
	addAnimation(2, NPCanimations[2], 250); // Left
	addAnimation(2, NPCanimations[3], 250); // Up
}

NPC::~NPC() {
}

void NPC::draw() {
	playAnimation(m_x, m_y, m_direction, 1); // Play animation
}

