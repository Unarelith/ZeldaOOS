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

#include "main.h"

u16 nonePassableTiles[12] = {
	1,3,4,5,6,8,9,10,12,16,17,18
};

u16 plainInfo[256] = {
	0,0,0,0,0,0,0,3,2,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
	0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
	0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
	1,1,1,1,5,5,1,1,0,0,0,0,4,0,1,1,
	1,1,1,1,5,5,1,1,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,
	1,1,1,1,1,1,1,1,1,1,0,6,1,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,1,
	8,9,10,11,12,13,13,1,14,15,1,16,17,0,18,1
};

Tileset* initTilesets() {
	Tileset plain = {plainTiles, plainPal, plainInfo};

	Tileset* tilesets = new Tileset[TILESETS];
	tilesets[0] = plain;

	return tilesets;
}

Map** initMaps(u8 mapBg) {
	Tileset* tilesets = initTilesets();

	Map* a1 = new Map(&tilesets[0], "/maps/a1.map", 16, 12, 16, 16, mapBg);
	Map* a2 = new Map(&tilesets[0], "/maps/a2.map", 16, 12, 16, 16, mapBg);
	Map* b1 = new Map(&tilesets[0], "/maps/b1.map", 16, 12, 16, 16, mapBg);
	Map* b2 = new Map(&tilesets[0], "/maps/b2.map", 16, 12, 16, 16, mapBg);

	Map** maps = new Map*[WM_SIZE * WM_SIZE];
	maps[0] = a1;
	maps[1] = a2;
	maps[2] = b1;
	maps[3] = b2;

	return maps;
}
