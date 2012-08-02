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
#ifndef MAPMANAGER_H
#define MAPMANAGER_H

// Number of tilesets
#define TILESETS 2

// World map size
#define WM_SIZE 3

// Tiles tables
extern u16 nonPassableTiles[12];
extern u16 changeMapTiles[2];

extern u16 doorUp[1];
extern u16 doorDown[1];
extern u16 doorLeft[1];
extern u16 doorRight[1];

typedef struct {
	u8 tilesetID;
	char *mapfile;
	u16 width, height;
	u16 tileWidth, tileHeight;
	u8 bg;
} SubMap;

Tileset *initTilesets();
Map **initMaps(u8 mapBg);

#endif // MAPMANAGER_H
