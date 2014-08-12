/*
 * =====================================================================================
 *
 *       Filename:  Map.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  16/07/2014 13:42:53
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#ifndef MAP_HPP_
#define MAP_HPP_

#include <string>

#include "Tileset.hpp"

class Map {
	public:
		Map(Tileset *tileset, std::string filename, u16 width, u16 height, u16 zone, u16 x, u16 y);
		~Map();
		
		u16 screenPos(s16 x, s16 y) const;
		
		void load();
		void loadTile(s16 x, s16 y, s8 offsetX = 0, s8 offsetY = 0);
		void loadTileInMemory(s16 x, s16 y, u16 tile);
		
		void setDisplayTile(u16 tileX, u16 tileY, u16 tile);
		u16 getDisplayTile(u16 tileX, u16 tileY);
		
		u16 getTile(u16 tileX, u16 tileY);
		
		static s16 scrollX;
		static s16 scrollY;
		
		Tileset *tileset() const { return m_tileset; }
		
		u16 zone() const { return m_zone; }
		
		u16 x() const { return m_x; }
		u16 y() const { return m_y; }
		
	private:
		Tileset *m_tileset;
		
		u16 m_width;
		u16 m_height;
		
		u16 m_zone;
		
		u16 m_x;
		u16 m_y;
		
		u16 *m_data;
};

#endif // MAP_HPP_
