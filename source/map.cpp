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

Map::Map(Tileset* tileset, char* filename, u16 width, u16 height, u16 tileWidth, u16 tileHeight, u8 bg) {
	s_tileset = tileset;
	s_filename = filename;
	s_width = width;
	s_height = height;
	s_tileWidth = tileWidth;
	s_tileHeight = tileHeight;
	
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
    char* buffer = (char*)malloc(sizeof(char) * filesize);
    fread(buffer, 1, filesize, f);
    fclose(f);
    // (Now buffer contains the map file)
    int counter = 0;
    char* token;
    u16 tile;
    const char delimiters[] = "|";
    token = strtok(buffer, delimiters);
    tile = (u16)atof(token);
    table[counter] = tile;
    counter++;
    while(token != NULL){
        token = strtok(NULL, delimiters);
        if(token != NULL){
            tile = (u16)atof(token);
            table[counter] = tile;
        }
        counter++;
    }
    free(buffer);
	
	s_map = table;
	s_bg = bg;
}

Map::~Map() {
}

void Map::init() {
	dmaCopy(s_tileset->tiles, bgGetGfxPtr(s_bg), plainTilesLen);
	dmaCopy(s_tileset->palette, BG_PALETTE_SUB, plainPalLen);
	
	u16* mapPtr = (u16*)bgGetMapPtr(s_bg);
	u16 x, y;
	for(y = 0 ; y < 16 ; y++) {
		for(x = 0 ; x < 16 ; x++) {
			mapPtr[x * 2 + y * 2 * 32] = s_map[(x + s_scrollX / 16) + (y + s_scrollY / 16) * s_width] * 4;
			mapPtr[x * 2 + 1 + y * 2 * 32] = s_map[(x + s_scrollX / 16) + (y + s_scrollY / 16) * s_width] * 4 + 1;
			mapPtr[x * 2 + (y * 2 + 1) * 32] = s_map[(x + s_scrollX / 16) + (y + s_scrollY / 16) * s_width] * 4 + 2;
			mapPtr[x * 2 + 1 + (y * 2 + 1) * 32] = s_map[(x + s_scrollX / 16) + (y + s_scrollY / 16) * s_width] * 4 + 3;
		}
	}
}

void Map::draw() {
	u16* mapPtr = (u16*)bgGetMapPtr(s_bg);
	u16 x, y;
	for(y = 0 ; y < 16 ; y++) {
		for(x = 0 ; x < 16 ; x++) {
			mapPtr[x * 2 + y * 2 * 32] = s_map[(x + s_scrollX / 16) + (y + s_scrollY / 16) * s_width] * 4;
			mapPtr[x * 2 + 1 + y * 2 * 32] = s_map[(x + s_scrollX / 16) + (y + s_scrollY / 16) * s_width] * 4 + 1;
			mapPtr[x * 2 + (y * 2 + 1) * 32] = s_map[(x + s_scrollX / 16) + (y + s_scrollY / 16) * s_width] * 4 + 2;
			mapPtr[x * 2 + 1 + (y * 2 + 1) * 32] = s_map[(x + s_scrollX / 16) + (y + s_scrollY / 16) * s_width] * 4 + 3;
		}
	}
}

void Map::scroll(s16 x, s16 y) {
	s_scrollX = x;
	s_scrollY = y;
}

void Map::setTile(s16 tileX, s16 tileY, u16 tile) {
	s_map[tileX + tileY * s_width] = tile;
}

u16 Map::getTile(s16 tileX, s16 tileY) {
	return s_map[tileX + tileY * s_width];
}
