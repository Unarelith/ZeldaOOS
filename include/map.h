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

#ifndef MAP_H
#define MAP_H

typedef struct {
	const u32* tiles;
	const u16* palette;
	u16* info;
} Tileset;

class Map {
	public:
		// Construct & Destruct
		Map(Tileset* tileset, char* filename, u16 width, u16 height, u16 tileWidth, u16 tileHeight, u8 bg);
		~Map();
		
		// Initialize the map
		void init();
		
		// Draw the map
		void draw();
		
		// Scroll the map
		void scroll(s16 xx, s16 yy);
		
		// Indoor transition
		void indoorTransInit();
		void indoorTrans();
		
		// Setting functions
		void setTile(s16 tileX, s16 tileY, u16 tile); // Set a tile with coordinates
		
		// Get functions
		u16 getTile(s16 tileX, s16 tileY); // Get a tile with coordinates
		u16* map() const { return s_map; }
		Map* nextMap() const { return s_nextMap; }
		u16 width() const { return s_width; }
		u16 height() const { return s_height; }
		Tileset* tileset() const { return s_tileset; }
		u8 bg() const { return s_bg; }
		int id() const { return s_id; }
		u16 mapX() const { return s_mapX; }
		u16 mapY() const { return s_mapY; }
		
		// Number of maps
		static int nbMaps;
		
		u16 screenPos(s16 x, s16 y) const;
		
		// Absolute map scrolling coordinates
		static s16 scrollX;
		static s16 scrollY;
		
	private:
		// Map id
		int s_id;
		
		// Map position
		u16 s_mapX;
		u16 s_mapY;
		
		// Map
		u16* s_map;
		
		// Next map
		Map* s_nextMap;
		
		// Map filename
		char* s_filename;
		
		// Map bg
		u8 s_bg;
		
		// Tileset
		Tileset* s_tileset;
		
		// Map size
		u16 s_width;
		u16 s_height;
		
		// Tile size
		u16 s_tileWidth;
		u16 s_tileHeight;
		
		// Put tile
		void putTile(s16 x, s16 y, const Map* map, s16 mapX, s16 mapY);
		
};

#endif // MAP_H
