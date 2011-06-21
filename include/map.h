#ifndef MAP_H
#define MAP_H

#include "main.h"

typedef struct {
	UL_IMAGE* image;
	u16* nonPassable;
} Tileset;

class Map {
	public:
		// Construct & Destruct
		Map(Tileset* tileset, char* filename, u16 width, u16 height, u16 tileWidth, u16 tileHeight);
		~Map();
		
		// Draw the map
		void draw();
		
		// Scroll the map
		void scroll(s16 x, s16 y);
		
		// Setting functions
		void setTile(s16 x, s16 y, u16 tile); // Set a tile with coordinates
		
		// Get functions
		u16 getTile(s16 x, s16 y); // Get a tile with coordinates
		UL_MAP* map() const { return s_map; }
		Tileset* tileset() const { return s_tileset; }
		
	private:
		// Map
		UL_MAP * s_map;
		
		// Tileset
		Tileset* s_tileset;
		
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
