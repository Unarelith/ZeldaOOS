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
#include <stdio.h>
#include <sys/stat.h>
#include <cmath>
#include "timer.h"
#include "sprites.h"
#include "map.h"
#include "mapManager.h"
#include "player.h"
#include "door.h"
#include "game.h"

using namespace std;

int Map::nbMaps = 0;

s16 Map::scrollX = 0;
s16 Map::scrollY = 0;

vector<vector<Map*>> Map::groups;

Map::Map(Tileset *tileset, char *filename, u16 width, u16 height, u16 tileWidth, u16 tileHeight, u8 bg, s16 group, s16 mapX, s16 mapY) {
	m_id = nbMaps;
	nbMaps++;
	
	m_tileset = tileset;
	m_filename = filename;
	m_width = width;
	m_height = height;
	m_tileWidth = tileWidth;
	m_tileHeight = tileHeight;
	
	// Make temporary table to get map file data
	u16* table = (u16*)malloc(m_width * m_height * sizeof(u16));
	
	// Load map from file
	struct stat file_status;
	if(stat(filename, &file_status) != 0){
		printf("Unable to load %s", m_filename);
	}
	int filesize = file_status.st_size;
	
	FILE* f = fopen(filename, "r");
	fread(table, 2, filesize, f);
	fclose(f);
	
	m_map = table;
	m_bg = bg;
	
	m_group = group;
	if(m_group != -1) {
		if((s16)groups.size() == m_group) {
			vector<Map*> v;
			v.push_back(this);
			groups.push_back(v);
		}
		else if((s16)groups.size() > m_group) {
			groups[m_group].push_back(this);
		} else {
			consoleClear();
			printf("Fatal error. Code: 03\n");
			printf("%d, %d", m_group, groups.size());
			while(1) swiWaitForVBlank();
		}
	}
	
	m_mapY = ((mapY == -1) ? (m_id / WM_SIZE) : (mapY));
	m_mapX = ((mapX == -1) ? (m_id - m_mapY * WM_SIZE) : (mapX));
}

Map::~Map() {
}

void Map::init() {
	dmaCopy(m_tileset->tiles, bgGetGfxPtr(m_bg), m_tileset->tilesLen);
	dmaCopy(m_tileset->palette, BG_PALETTE, m_tileset->paletteLen);
	
	u16 x, y;
	for(y = 0 ; y < 12 ; y++) {
		for(x = 0 ; x < 16 ; x++) {
			putTile(x, y, this, x, y);
		}
	}
}

void Map::initOTF() {
	dmaCopy(m_tileset->tiles, bgGetGfxPtr(m_bg), m_tileset->tilesLen);
	dmaCopy(m_tileset->palette, BG_PALETTE, m_tileset->paletteLen);
	
	u16 x, y;
	for(y = scrollY / 16 ; y < scrollY / 16 + 12 ; y++) {
		for(x = scrollX / 16 ; x < scrollX / 16 + 16 ; x++) {
			putTile(x, y, this, x, y);
		}
	}
}

u16 Map::screenPos(s16 x, s16 y) const {
	return ((x & 31) + ((x & 32) << 5) + ((y & 31) << 5) + ((y & 32) << 6));
}

void Map::putTile(s16 x, s16 y, const Map* map, s16 mapX, s16 mapY) {
	mapX &= 15;
	mapY %= 12;
	u16 *mapPtr = (u16*)bgGetMapPtr(m_bg);
	mapPtr[screenPos(x * 2, y * 2)] = map->map()[mapX + mapY * map->width()] * 4;
	mapPtr[screenPos(x * 2 + 1, y * 2)] = map->map()[mapX + mapY * map->width()] * 4 + 1;
	mapPtr[screenPos(x * 2, y * 2 + 1)] = map->map()[mapX + mapY * map->width()] * 4 + 2;
	mapPtr[screenPos(x * 2 + 1, y * 2 + 1)] = map->map()[mapX + mapY * map->width()] * 4 + 3;
}

s16 findMapID(s16 mapX, s16 mapY, vector<Map*> group) {
	for(s16 i = 0 ; i < (s16)group.size() ; i++) {
		if((group[i]->mapX() == mapX) && (group[i]->mapY() == mapY)) {
			return i;
		}
	}
	return -1;
}

void Map::scroll(s16 xx, s16 yy) {
	if(xx > 0) { // Scroll right
		if(m_group != -1) m_nextMap = Game::maps[groups[m_group][findMapID(m_mapX + 1, m_mapY, groups[m_group])]->id()];
		else m_nextMap = Game::maps[m_mapX + 1 + m_mapY * WM_SIZE];
		
		for(int i = 0 ; (i < xx) && (scrollX < m_width * WM_SIZE * 16 - 256) ; i++) {
			if(!(scrollX & 15)) {
				for(int j = scrollY / 16 ; j < scrollY / 16 + 12 ; j++) {
					putTile(scrollX / 16 + 16, j, m_nextMap, scrollX / 16, j);
				}
			}
			scrollX++; // Scroll the map
		}
		
		REG_BG0HOFS = scrollX & 1023; // Scroll the BG
	}
	else if(xx < 0) { // Scroll left
		if(m_group != -1) m_nextMap = Game::maps[groups[m_group][findMapID(m_mapX - 1, m_mapY, groups[m_group])]->id()];
		else m_nextMap = Game::maps[m_mapX - 1 + m_mapY * WM_SIZE];
		
		for(int i = 0 ; (i < -xx) && (scrollX > 0) ; i++) {
			if(!(scrollX & 15)) {
				for(int j = scrollY / 16 ; j < scrollY / 16 + 12 ; j++) {
					putTile(scrollX / 16 - 1, j, m_nextMap, scrollX / 16 - 1, j);
				}
			}
			scrollX--; // Scroll the map
		}
		
		REG_BG0HOFS = scrollX & 1023; // Scroll the BG
	}
	
	if(yy > 0) { // Scroll down
		if(m_group != -1) m_nextMap = Game::maps[groups[m_group][findMapID(m_mapX, m_mapY + 1, groups[m_group])]->id()];
		else m_nextMap = Game::maps[m_mapX + (m_mapY + 1) * WM_SIZE];
		
		for(int i = 0 ; (i < yy) && (scrollY < m_height * WM_SIZE * 16 - 192) ; i++) {
			if(!(scrollY & 15)) {
				for(int j = scrollX / 16 ; j < scrollX / 16 + 16 ; j++) {
					putTile(j, scrollY / 16 + 12, m_nextMap, j, scrollY / 16);
				}
			}
			scrollY++; // Scroll the map
		}
		
		REG_BG0VOFS = scrollY & 1023; // Scroll the BG
	}
	else if(yy < 0) { // Scroll up
		if(m_group != -1) m_nextMap = Game::maps[groups[m_group][findMapID(m_mapX, m_mapY - 1, groups[m_group])]->id()];
		else m_nextMap = Game::maps[m_mapX + (m_mapY - 1) * WM_SIZE];
		
		for(int i = 0 ; (i < -yy) && (scrollY > 0) ; i++) {
			if(!(scrollY & 15)) {
				for(int j = scrollX / 16 ; j < scrollX / 16 + 16 ; j++) {
					putTile(j, scrollY / 16 - 1, m_nextMap, j, scrollY / 16 - 1);
				}
			}
			scrollY--; // Scroll the map
		}
		
		REG_BG0VOFS = scrollY & 1023; // Scroll the BG
	}
}

void Map::indoorTransInit() {
	BG_PALETTE_SUB[255] = ARGB16(1, 0x1F, 0x1E, 0x19);
	
	dmaFillWords(0xFFFFFFFF, bgGetGfxPtr(Game::transBg) + 32, 64);
	dmaFillWords(0x00010001, bgGetMapPtr(Game::transBg), 32 * 24 * 2);
}

void Map::indoorTrans() {
	u16* map = bgGetMapPtr(Game::transBg);
	for(u16 x = 0 ; x < 16 ; x++) {
		swiWaitForVBlank();
		for(u16 y = 0 ; y < 24 ; y++) {
			map[(15 - x) + (y << 5)] = 0;
			map[(16 + x) + (y << 5)] = 0;
		}
	}
}

void Map::setTile(s16 tileX, s16 tileY, u16 tile) {
	m_map[tileX + tileY * m_width] = tile;
}

u16 Map::getTile(s16 tileX, s16 tileY) {
	// That's only a bypass
	if(m_map[tileX + tileY * m_width] < sqrt(m_tileset->tilesLen)) {
		return m_map[tileX + tileY * m_width];
	} else {
		return 0;
	}
}

