/*
 * =====================================================================================
 *
 *       Filename:  Map.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  16/07/2014 13:43:06
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#include <stdio.h>

#include <nds.h>

#include "MapManager.hpp"

s16 Map::scrollX = 0;
s16 Map::scrollY = 0;

Map::Map(Tileset *tileset, std::string filename, u16 width, u16 height, u16 zone, u16 x, u16 y) {
	m_tileset = tileset;
	
	m_width = width;
	m_height = height;
	
	m_zone = zone;
	
	m_x = x;
	m_y = y;
	
	m_data = new u16[m_width * m_height];
	
	FILE *f = fopen(filename.c_str(), "r");
	if(!f) {
		consoleDemoInit();
		
		printf("Couldn't load %s", filename.c_str());
		
		while(1) swiWaitForVBlank();
	}
	
	fread(m_data, 2, m_width * m_height * 2, f);
	
	fclose(f);
}

Map::~Map() {
	delete[] m_data;
}

u16 Map::screenPos(s16 x, s16 y) const {
	return ((x & 31) + ((x & 32) << 5) + ((y & 31) << 5) + ((y & 32) << 6));
}

void Map::load() {
	dmaCopy(m_tileset->tiles, bgGetGfxPtr(MapManager::mapBg), m_tileset->tilesLength);
	dmaCopy(m_tileset->palette, BG_PALETTE, m_tileset->palLength);
	
	scrollX = m_x * 256;
	scrollY = m_y * 192;
	
	for(u16 y = scrollY / 16 ; y < scrollY / 16 + 12 ; y++) {
		for(u16 x = scrollX / 16 ; x < scrollX / 16 + 16 ; x++) {
			loadTile(x, y);
		}
	}
	
	bgSetScroll(MapManager::mapBg, scrollX, scrollY);
	bgUpdate();
}

void Map::loadTile(s16 x, s16 y, s8 offsetX, s8 offsetY) {
	u16 dataX = x & 15;
	u16 dataY = y % 12;
	
	x += offsetX;
	y += offsetY;
	
	u16 *mapPtr = (u16*)bgGetMapPtr(MapManager::mapBg);
	mapPtr[screenPos(x * 2    , y * 2    )] = m_data[dataX + dataY * m_width] * 4;
	mapPtr[screenPos(x * 2 + 1, y * 2    )] = m_data[dataX + dataY * m_width] * 4 + 1;
	mapPtr[screenPos(x * 2    , y * 2 + 1)] = m_data[dataX + dataY * m_width] * 4 + 2;
	mapPtr[screenPos(x * 2 + 1, y * 2 + 1)] = m_data[dataX + dataY * m_width] * 4 + 3;
}

void Map::setTile(u16 tileX, u16 tileY, u16 tile) {
	if(tileX + tileY * m_width < m_width * m_height) {
		m_data[tileX + tileY * m_width] = tile;
		loadTile(m_x * 256 / 16 + tileX, m_y * 192 / 16 + tileY);
	}
}

u16 Map::getTile(u16 tileX, u16 tileY) {
	if(tileX + tileY * m_width < m_width * m_height) {
		return m_data[tileX + tileY * m_width];
	} else {
		return 0;
	}
}

