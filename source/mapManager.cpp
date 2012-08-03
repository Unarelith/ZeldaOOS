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
#include <nds.h>
#include "map.h"
#include "mapManager.h"
#include "plain.h"
#include "indoor.h"

/*	Tiles informations:
		0: Passable
		1: Non passable
		2: Slows and can be cutted
		3: Non passable but can be cutted and can be lifted
		4: Non passable but can be burned
		6: Fireplace
		7: Hole
		8: Empty chest
		9: Closed chest
		10: Placard
		11: Doors
			111: Up
			112: Down
			113: Left
			114: Right
		12: Rock, can be lifted
		13: Soft soil
		14: Stairs
		15: Stairs to underground
		16: Cane of Somaria's cube
		17: Hook's rock
		18: Mass of earth
*/

u16 nonPassableTiles[12] = {
	1,3,4,5,6,8,9,10,12,16,17,18
};

u16 changeMapTiles[2] = {
	11,15
};

u16 doorUp[1] = {111};
u16 doorDown[1] = {112};
u16 doorLeft[1] = {113};
u16 doorRight[1] = {114};

u16 plainInfo[256] = {
	0,0,0,0,0,0,0,3,2,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
	0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
	0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
	1,1,1,1,1,1,1,1,0,0,0,0,4,0,1,1,
	1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,
	1,1,1,1,1,1,1,1,1,1,111,6,1,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,1,
	8,9,10,7,12,13,13,1,14,15,1,16,17,0,18,1
};

u16 indoorInfo[256] = {
	0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,
	1,1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,
	1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,0,
	1,1,1,1,1,1,1,1,1,1,0,112,112,1,1,0,
	1,1,1,1,1,1,1,1,1,1,0,112,111,0,0,0,
	1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,
	1,1,0,0,0,0,1,1,1,1,1,1,1,0,1,1,
	1,1,0,0,0,0,1,1,1,1,1,1,0,1,1,1,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	8,9,10,7,0,0,1,12,15,15,111,15,0,0,0,0
};

Tileset* initTilesets() {
	Tileset plain = {plainTiles, plainTilesLen, plainPal, plainPalLen, plainInfo};
	Tileset indoor = {indoorTiles, indoorTilesLen, indoorPal, indoorPalLen, indoorInfo};

	Tileset* tilesets = new Tileset[TILESETS];
	tilesets[0] = plain;
	tilesets[1] = indoor;

	return tilesets;
}

Map** initMaps(u8 mapBg) {
	Tileset* tilesets = initTilesets();
	
	Map* a1 = new Map(&tilesets[0], "/maps/a1.map", 16, 12, 16, 16, mapBg);
	Map* a2 = new Map(&tilesets[0], "/maps/a2.map", 16, 12, 16, 16, mapBg);
	Map* a3 = new Map(&tilesets[0], "/maps/a3.map", 16, 12, 16, 16, mapBg);
	Map* b1 = new Map(&tilesets[0], "/maps/b1.map", 16, 12, 16, 16, mapBg);
	Map* b2 = new Map(&tilesets[0], "/maps/b2.map", 16, 12, 16, 16, mapBg);
	Map* b3 = new Map(&tilesets[0], "/maps/b3.map", 16, 12, 16, 16, mapBg);
	Map* c1 = new Map(&tilesets[0], "/maps/c1.map", 16, 12, 16, 16, mapBg);
	Map* c2 = new Map(&tilesets[0], "/maps/c2.map", 16, 12, 16, 16, mapBg);
	Map* c3 = new Map(&tilesets[0], "/maps/c3.map", 16, 12, 16, 16, mapBg);
	Map* in1 = new Map(&tilesets[1], "/maps/in1.map", 16, 12, 16, 16, mapBg);
	Map* in2 = new Map(&tilesets[1], "/maps/in2.map", 16, 12, 16, 16, mapBg);
	
	Map** maps = new Map*[WM_SIZE * WM_SIZE + 2];
	maps[0] = a1;
	maps[1] = a2;
	maps[2] = a3;
	maps[3] = b1;
	maps[4] = b2;
	maps[5] = b3;
	maps[6] = c1;
	maps[7] = c2;
	maps[8] = c3;
	maps[MAP_IN(1)] = in1;
	maps[MAP_IN(2)] = in2;
	
	return maps;
}

