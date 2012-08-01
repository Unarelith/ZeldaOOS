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
#ifndef MAP_H
#define MAP_H

typedef struct {
	const u32 *tiles;
	u32 tilesLen;
	const u16 *palette;
	u32 paletteLen;
	u16 *info;
} Tileset;

class Map {
	public:
		Map(Tileset *tileset, char *filename, u16 width, u16 height, u16 tileWidth, u16 tileHeight, u8 bg);
		~Map();
			
		// Initialize the map
		void init();
		
		// Scroll the map
		void scroll(s16 xx, s16 yy);
		
		// Outdoor to indoor transition
		void indoorTransInit();
		void indoorTrans();
		
		// Setting functions
		void setTile(s16 tileX, s16 tileY, u16 tile); // Set a tile with coordinates
		
		// Get functions
		u16 getTile(s16 tileX, s16 tileY); // Get a tile with coordinates
		u16 *map() const { return m_map; }
		Map *nextMap() const { return m_nextMap; }
		u16 width() const { return m_width; }
		u16 height() const { return m_height; }
		Tileset *tileset() const { return m_tileset; }
		u8 bg() const { return m_bg; }
		u16 id() const { return m_id; }
		u16 mapX() const { return m_mapX; }
		u16 mapY() const { return m_mapY; }
		
		// Number of maps
		static int nbMaps;
		
		u16 screenPos(s16 x, s16 y) const;
		
		// Absolute map scrolling coordinates
		static s16 scrollX;
		static s16 scrollY;
		
	private:
		// Map id
		u16 m_id;
		
		// Map position
		u16 m_mapX;
		u16 m_mapY;
		
		// Map
		u16 *m_map;
		
		// Next map
		Map *m_nextMap;
		
		// Map filename
		char *m_filename;
		
		// Map bg
		u8 m_bg;
		
		// Tileset
		Tileset *m_tileset;
		
		// Map size
		u16 m_width;
		u16 m_height;
		
		// Tile size
		u16 m_tileWidth;
		u16 m_tileHeight;
		
		// Put tile
		void putTile(s16 x, s16 y, const Map *map, s16 mapX, s16 mapY);
};

#endif // MAP_H
