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
	u16* nonPassable;
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
		
		// Setting functions
		void setTile(s16 tileX, s16 tileY, u16 tile); // Set a tile with coordinates
		
		// Get functions
		u16 getTile(s16 tileX, s16 tileY); // Get a tile with coordinates
		u16* map() const { return s_map; }
		u16 width() const { return s_width; }
		Tileset* tileset() const { return s_tileset; }
		
		// Number of maps
		static int nbMaps;
		
	private:
		// Map id
		int s_id;
		
		// Map
		u16* s_map;
		
		// Map filename
		char* s_filename;
		
		// Map bg
		u8 s_bg;
		
		// Tileset
		Tileset* s_tileset;
		
		// Map scrolling coordinates
		s16 s_scrollX;
		s16 s_scrollY;
		
		// Map size
		u16 s_width;
		u16 s_height;
		
		// Tile size
		u16 s_tileWidth;
		u16 s_tileHeight;
		
		// Put tile
		void putTile(s16 x, s16 y, const u16* map, u16 mapX, u16 mapY, u16 mapWidth, u8 zone = 0);
		
};

#endif // MAP_H
