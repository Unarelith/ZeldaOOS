/*
 * =====================================================================================
 *
 *       Filename:  MapManager.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  16/07/2014 14:21:22
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#include <math.h>

#include <nds.h>

#include "TilesInfos.hpp"
#include "TilesetsInfos.hpp"
#include "MapManager.hpp"
#include "CharacterManager.hpp"

#include "plain.h"
#include "indoor.h"
#include "underground.h"

u16 MapManager::mapBg;
u16 MapManager::transitionBg;

std::vector<Tileset*> MapManager::tilesets;
std::vector<std::vector<Map*>> MapManager::maps;

Map *MapManager::currentMap = nullptr;

void MapManager::init() {
	mapBg = bgInit(0, BgType_Text8bpp, BgSize_T_512x512, 0, 1);
	transitionBg = bgInit(1, BgType_Text8bpp, BgSize_T_256x256, 4, 5);
	
	bgSetPriority(mapBg, 2);
	bgSetPriority(transitionBg, 0);
	
	initTilesets();
	
	initMaps();
	
	currentMap = maps[0][0];
}

void MapManager::free() {
	while(maps.size() != 0) {
		while(maps.back().size() != 0) {
			delete maps.back().back();
			maps.back().pop_back();
		}
		
		maps.pop_back();
	}
}

void MapManager::initTilesets() {
	tilesets.push_back(new Tileset(TilesetsInfos::plainInfo, plainTiles, plainTilesLen, plainPal, plainPalLen));
	tilesets.push_back(new Tileset(TilesetsInfos::indoorInfo, indoorTiles, indoorTilesLen, indoorPal, indoorPalLen));
	tilesets.push_back(new Tileset(TilesetsInfos::undergroundInfo, undergroundTiles, undergroundTilesLen, undergroundPal, undergroundPalLen));
}

void MapManager::initMaps() {
	std::vector<Map*> overworld;
	overworld.push_back(new Map(tilesets[0], "/maps/a1.map", 16, 12, 0, 0, 0));
	overworld.push_back(new Map(tilesets[0], "/maps/a2.map", 16, 12, 0, 1, 0));
	overworld.push_back(new Map(tilesets[0], "/maps/a3.map", 16, 12, 0, 2, 0));
	overworld.push_back(new Map(tilesets[0], "/maps/b1.map", 16, 12, 0, 0, 1));
	overworld.push_back(new Map(tilesets[0], "/maps/b2.map", 16, 12, 0, 1, 1));
	overworld.push_back(new Map(tilesets[0], "/maps/b3.map", 16, 12, 0, 2, 1));
	overworld.push_back(new Map(tilesets[0], "/maps/c1.map", 16, 12, 0, 0, 2));
	overworld.push_back(new Map(tilesets[0], "/maps/c2.map", 16, 12, 0, 1, 2));
	overworld.push_back(new Map(tilesets[0], "/maps/c3.map", 16, 12, 0, 2, 2));
	maps.push_back(overworld);
	
	std::vector<Map*> indoor;
	indoor.push_back(new Map(tilesets[1], "/maps/ina1.map", 16, 12, 1, 0, 0));
	indoor.push_back(new Map(tilesets[1], "/maps/ina2.map", 16, 12, 1, 1, 0));
	indoor.push_back(nullptr);
	indoor.push_back(nullptr);
	maps.push_back(indoor);
	
	std::vector<Map*> cave1;
	cave1.push_back(new Map(tilesets[2], "/maps/ca1a1.map", 16, 12, 2, 0, 0));
	cave1.push_back(new Map(tilesets[2], "/maps/ca1a2.map", 16, 12, 2, 1, 0));
	cave1.push_back(nullptr);
	cave1.push_back(new Map(tilesets[2], "/maps/ca1b2.map", 16, 12, 2, 1, 1));
	maps.push_back(cave1);
	
	std::vector<Map*> cave2;
	cave2.push_back(new Map(tilesets[2], "/maps/ca2a1.map", 16, 12, 3, 0, 0));
	cave2.push_back(new Map(tilesets[2], "/maps/ca2a2.map", 16, 12, 3, 1, 0));
	cave2.push_back(new Map(tilesets[2], "/maps/ca2b1.map", 16, 12, 3, 0, 1));
	cave2.push_back(nullptr);
	maps.push_back(cave2);
}

void MapManager::scrollMaps(s8 dx, s8 dy) {
	Map *nextMap = maps[currentMap->zone()][currentMap->x() + dx + (currentMap->y() + dy) * sqrt(maps[currentMap->zone()].size())];
	
	CharacterManager::player->vx(0);
	CharacterManager::player->vy(0);
	
	if(dx != 0) {
		for(u8 i = 0 ; i < 32 ; i++) {
			if((i & 1) || !(1 & 15)) {
				CharacterManager::player->x(CharacterManager::player->x() - 8 * dx);
			} else {
				CharacterManager::player->x(CharacterManager::player->x() - 7 * dx);
			}
			
			for(u8 j = 0 ; j < 8 * abs(dx) ; j++) {
				if(!(Map::scrollX & 15)) {
					for(u16 k = Map::scrollY / 16 ; k < Map::scrollY / 16 + 12 ; k++) {
						if(dx > 0) {
							nextMap->loadTile(Map::scrollX / 16, k, 16);
						} else {
							nextMap->loadTile(Map::scrollX / 16 - 1, k);
						}
					}
				}
				
				Map::scrollX += dx;
			}
			
			bgSetScroll(mapBg, Map::scrollX, Map::scrollY);
			bgUpdate();
			
			CharacterManager::player->draw();
			
			swiWaitForVBlank();
		}
	}
	
	if(dy != 0) {
		for(u8 i = 0 ; i < 24 ; i++) {
			if((i & 1) && (i & 7) < 7) {
				CharacterManager::player->y(CharacterManager::player->y() - 8 * dy);
			} else {
				CharacterManager::player->y(CharacterManager::player->y() - 7 * dy);
			}
			
			for(u8 j = 0 ; j < 8 * abs(dy) ; j++) {
				if(!(Map::scrollY & 15)) {
					for(u16 k = Map::scrollX/ 16 ; k < Map::scrollX / 16 + 16 ; k++) {
						if(dy > 0) {
							nextMap->loadTile(k, Map::scrollY / 16, 0, 12);
						} else {
							nextMap->loadTile(k, Map::scrollY / 16 - 1);
						}
					}
				}
				
				Map::scrollY += dy;
			}
			
			bgSetScroll(mapBg, Map::scrollX, Map::scrollY);
			bgUpdate();
			
			CharacterManager::player->draw();
			
			swiWaitForVBlank();
		}
	}
	
	currentMap = nextMap;
}

void MapManager::initDoorTransition() {
	dmaFillWords(0xFFFFFFFF, bgGetGfxPtr(transitionBg) + 32, 64);
	dmaFillWords(0x00010001, bgGetMapPtr(transitionBg), 32 * 24 * 2);
}

void MapManager::doorTransition() {
	for(u8 x = 0 ; x < 16 ; x++) {
		swiWaitForVBlank();
		
		for(u8 y = 0 ; y < 24 ; y++) {
			((u16*)bgGetMapPtr(transitionBg))[(15 - x) + (y << 5)] = 0;
			((u16*)bgGetMapPtr(transitionBg))[(16 + x) + (y << 5)] = 0;
		}
	}
}

bool inTable(u8 t[], u8 n) {
	while(*t) {
		if(*t == n) {
			return true;
		}
		t++;
	}
	return false;
}

bool inTiles(s16 tileX, s16 tileY, u8 tiles[]) {
	return inTable(tiles, MapManager::currentMap->tileset()->info[MapManager::currentMap->getTile(tileX, tileY)]);
}

bool passable(s16 x, s16 y) {
	u8 tile = MapManager::currentMap->tileset()->info[MapManager::currentMap->getTile(x >> 4, y >> 4)];
	if(tilesInfo[tile][(x & 0xF) / 8 + (y & 0xF) / 8 * 2] == 1) {
		return false;
	} else {
		return true;
	}
}

bool onDoor(s16 x, s16 y) {
	u8 tile = MapManager::currentMap->tileset()->info[MapManager::currentMap->getTile(x >> 4, y >> 4)];
	if(tilesInfo[tile][(x & 0xF) / 8 + (y & 0xF) / 8 * 2] == 2) {
		return true;
	} else {
		return false;
	}
}

bool isTile(s16 x, s16 y, u8 tile) {
	return MapManager::currentMap->tileset()->info[MapManager::currentMap->getTile(x >> 4, y >> 4)] == tile;
}

bool stairsTile(s16 x, s16 y) {
	return isTile(x, y, 11);
}

bool lowGrassTile(s16 x, s16 y) {
	return isTile(x, y, 12);
}

bool lowWaterTile(s16 x, s16 y) {
	return isTile(x, y, 13);
}

bool grassTile(s16 x, s16 y) {
	return isTile(x, y, 14) || lowGrassTile(x, y);
}

