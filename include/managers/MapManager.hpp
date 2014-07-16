/*
 * =====================================================================================
 *
 *       Filename:  MapManager.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  16/07/2014 14:21:14
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#ifndef MAPMANAGER_HPP_
#define MAPMANAGER_HPP_

#include <vector>

#include "Map.hpp"

namespace MapManager {
	void init();
	void free();
	
	void initTilesets();
	void initMaps();
	
	void scrollMaps(s8 dx, s8 dy);
	
	extern u16 mapBg;
	
	extern std::vector<Tileset*> tilesets;
	extern std::vector<std::vector<Map*>> maps;
	
	extern Map *currentMap;
	
	void initDoorTransition();
	void doorTransition();
};

bool inTable(u8 t[], u8 n);
bool inTiles(s16 tileX, s16 tileY, u8 tiles[]);

bool passable(s16 x, s16 y);
bool onDoor(s16 x, s16 y);

#endif // MAPMANAGER_HPP_
