#ifndef MAP_H
#define MAP_H

#include "main.h"

class Map {
	public:
		// Construct & Destruct
		Map(UL_IMAGE* image, char* filename, u16 width, u16 height, u16 tileWidth, u16 tileHeight);
		~Map();
		
		// Draw the map
		void draw();
		
		// Scroll the map
		void scroll(s16 x, s16 y);
		
		// Set a tile with coordinates
		void setTile(s16 x, s16 y, u16 tile);
		
		// Get a tile with coordinates
		u16 getTile(s16 x, s16 y);
		
	private:
		// Map
		UL_MAP * s_map;
		
		// Tileset
		UL_IMAGE* s_image;
		
		// Map filename
		char* s_filename;
		
		// Map size
		u16 s_width;
		u16 s_height;
		
		// Tile size
		u16 s_tileWidth;
		u16 s_tileHeight;
	
};

#endif // MAP_H
