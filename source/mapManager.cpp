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

u16 plainNonPassable[127] = {
	7,28,29,30,31,44,45,46,47,60,61,62,63,64,65,66,67,68,69,70,71,76,78,79,112,113,114,115,116,117,
	118,119,120,121,122,123,124,125,128,129,130,131,132,133,134,135,136,137,138,139,140,141,144,145,146,147,148,149,
	150,151,152,153,154,155,156,157,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,175,176,177,178,179,
	180,181,182,183,184,185,186,187,188,192,193,194,195,196,197,198,199,200,201,203,204,232,233,234,235,236,237,239,
	240,241,242,243,244,245,246,247,250,251,252,254,255
};

Tileset* initTilesets() {
	Tileset plain = {plainTiles, plainPal, plainNonPassable};
	
	Tileset* tilesets = new Tileset[TILESETS];
	tilesets[0] = plain;
	
	return tilesets;
}

Map** initMaps(u8 mapBg) {
	Tileset* tilesets = initTilesets();
	
	Map* a1 = new Map(&tilesets[0], "/maps/a1.map", 16, 12, 16, 16, 0, 0, mapBg);
	Map* a2 = new Map(&tilesets[0], "/maps/a2.map", 16, 12, 16, 16, 1, 0, mapBg);
	Map* b1 = new Map(&tilesets[0], "/maps/b1.map", 16, 12, 16, 16, 0, 1, mapBg);
	Map* b2 = new Map(&tilesets[0], "/maps/b2.map", 16, 12, 16, 16, 1, 1, mapBg);
	
	Map** maps = new Map*[MAPS];
	maps[0] = a1;
	maps[1] = a2;
	maps[2] = b1;
	maps[3] = b2;
	
	return maps;
}
