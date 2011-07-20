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

int Map::nbMaps = 0;

s16 Map::scrollX = 0;
s16 Map::scrollY = 0;

Map::Map(Tileset* tileset, char* filename, u16 width, u16 height, u16 tileWidth, u16 tileHeight, u8 bg) {
	s_id = nbMaps;
	nbMaps++;
	
	s_mapY = s_id / WM_SIZE;
	s_mapX = s_id - s_mapY * WM_SIZE;
	
	s_tileset = tileset;
	s_filename = filename;
	s_width = width;
	s_height = height;
	s_tileWidth = tileWidth;
	s_tileHeight = tileHeight;
	
	// Make temporary table to get map file data
	u16* table;
	table = (u16*)malloc(s_width * s_height * sizeof(u16));
	
	// Load map from file
	int filesize;
	struct stat file_status;
	if(stat(filename, &file_status) != 0){
		printf("Unable to load %s", s_filename);
	}
	filesize = file_status.st_size;
	FILE* f = fopen(filename, "r");
	fread(table, 2, filesize, f);
	fclose(f);
	
	s_map = table;
	s_bg = bg;
}

Map::~Map() {
}

void Map::init() {
	dmaCopy(s_tileset->tiles, bgGetGfxPtr(s_bg), plainTilesLen);
	dmaCopy(s_tileset->palette, BG_PALETTE_SUB, plainPalLen);
	
	u16 x, y;
	for(y = 0 ; y < 12 ; y++) {
		for(x = 0 ; x < 16 ; x++) {
			putTile(x, y, this, x, y);
		}
	}
}

void Map::draw() {
}

u16 Map::screenPos(s16 x, s16 y) const {
	return ((x & 31) + ((x & 32) << 5) + ((y & 31) << 5) + ((y & 32) << 6));
}

void Map::putTile(s16 x, s16 y, const Map* map, s16 mapX, s16 mapY) {
	mapX &= 15;
	mapY %= 12;
	u16* mapPtr = (u16*)bgGetMapPtr(s_bg);
	mapPtr[screenPos(x * 2, y * 2)] = map->map()[mapX + mapY * map->width()] * 4;
	mapPtr[screenPos(x * 2 + 1, y * 2)] = map->map()[mapX + mapY * map->width()] * 4 + 1;
	mapPtr[screenPos(x * 2, y * 2 + 1)] = map->map()[mapX + mapY * map->width()] * 4 + 2;
	mapPtr[screenPos(x * 2 + 1, y * 2 + 1)] = map->map()[mapX + mapY * map->width()] * 4 + 3;
}

void Map::scroll(s16 xx, s16 yy) {
	consoleClear();

	if(xx > 0) { // Scroll right		
		s_nextMap = Game::maps[s_mapX + 1 + s_mapY * WM_SIZE]; // Next map to scroll on
		
		for(int i = 0 ; (i < xx) && (scrollX < s_width * 2 * 16 - 256) ; i++) {

			iprintf("\x1b[5;0H%08x\n%d\n%08x\n", (int)s_nextMap, s_nextMap->id(), (int)s_nextMap->map());

			if(!(scrollX & 15)) {
				for(int j = scrollY / 16 ; j < scrollY / 16 + 12 ; j++) {
					putTile(scrollX / 16 + 16, j, s_nextMap, scrollX / 16, j);
				}
			}
			scrollX++; // Scroll the map*
		}
		
		REG_BG0HOFS_SUB = scrollX & 1023; // Scroll the BG

		iprintf("%4d\t%4d\n", scrollX, scrollY);
	}
	else if(xx < 0) { // Scroll left
		s_nextMap = Game::maps[s_mapX - 1 + s_mapY * WM_SIZE]; // Next map to scroll on
		
		for(int i = 0 ; (i < -xx) && (scrollX > 0) ; i++) {

			iprintf("\x1b[5;0H%08x\n%d\n%08x\n", (int)s_nextMap, s_nextMap->id(), (int)s_nextMap->map());

			if(!(scrollX & 15)) {
				for(int j = scrollY / 16 ; j < scrollY / 16 + 12 ; j++) {
					putTile(scrollX / 16 - 1, j, s_nextMap, scrollX / 16 - 1, j);
				}
			}
			scrollX--; // Scroll the map
		}
		
		REG_BG0HOFS_SUB = scrollX & 1023; // Scroll the BG

		iprintf("%4d\t%4d\n", scrollX, scrollY);
	}
	
	if(yy > 0) { // Scroll down
		s_nextMap = Game::maps[s_mapX + (s_mapY + 1) * WM_SIZE]; // Next map to scroll on
		
		for(int i = 0 ; (i < yy) && (scrollY < s_height * 2 * 16 - 192) ; i++) {

			iprintf("\x1b[5;0H%08x\n%d\n%08x\n", (int)s_nextMap, s_nextMap->id(), (int)s_nextMap->map());

			if(!(scrollY & 15)) {
				for(int j = scrollX / 16 ; j < scrollX / 16 + 16 ; j++) {
					putTile(j, scrollY / 16 + 12, s_nextMap, j, scrollY / 16);
				}
			}
			scrollY++; // Scroll the map
		}
		
		REG_BG0VOFS_SUB = scrollY & 1023; // Scroll the BG

		iprintf("%4d\t%4d\n", scrollX, scrollY);
	}
	else if(yy < 0) { // Scroll up
		s_nextMap = Game::maps[s_mapX + (s_mapY - 1) * WM_SIZE]; // Next map to scroll on
		
		for(int i = 0 ; (i < -yy) && (scrollY > 0) ; i++) {

			iprintf("\x1b[5;0H%08x\n%d\n%08x\n", (int)s_nextMap, s_nextMap->id(), (int)s_nextMap->map());

			if(!(scrollY & 15)) {
				for(int j = scrollX / 16 ; j < scrollX / 16 + 16 ; j++) {
					putTile(j, scrollY / 16 - 1, s_nextMap, j, scrollY / 16 - 1);
				}
			}
			scrollY--; // Scroll the map
		}
		
		REG_BG0VOFS_SUB = scrollY & 1023; // Scroll the BG

		iprintf("%4d\t%4d\n", scrollX, scrollY);
	}
}

void Map::setTile(s16 tileX, s16 tileY, u16 tile) {
	s_map[tileX + tileY * s_width] = tile;
}

u16 Map::getTile(s16 tileX, s16 tileY) {
	return s_map[tileX + tileY * s_width];
}
