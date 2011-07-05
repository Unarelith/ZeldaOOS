#ifndef MAP_H
#define MAP_H
#include "main.h"

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
		void scroll(s16 x, s16 y);
		
		// Setting functions
		void setTile(s16 tileX, s16 tileY, u16 tile); // Set a tile with coordinates
		
		// Get functions
		u16 getTile(s16 tileX, s16 tileY); // Get a tile with coordinates
		u16* map() const { return s_map; }
		Tileset* tileset() const { return s_tileset; }
		
	private:
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
		
};

#endif // MAP_H
