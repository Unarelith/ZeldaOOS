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
#include <stdio.h>
#include "timer.h"
#include "sprites.h"
#include "player.h"
#include "NPC.h"
#include "map.h"
#include "mapManager.h"
#include "door.h"
#include "game.h"

Door** initDoors() {
	Door** doors = new Door*[DOORS];
	
	doors[0] = new Door{0, 6 << 4, 3 << 4, DIR_DOWN, 1};
	doors[1] = new Door{MAP_IN(1), (7 << 4) + 8, 11 << 4, DIR_UP, 0};
	doors[2] = new Door{MAP_IN(1), 3 << 4, 2 << 4, DIR_DOWN, 3};
	doors[3] = new Door{MAP_IN(2), 4 << 4, 8 << 4, DIR_UP, 2};
	doors[4] = new Door{7, 2 << 4, 7 << 4, DIR_DOWN, 5};
	doors[5] = new Door{MAP_IN(3), (7 << 4) + 8, 11 << 4, DIR_UP, 4};
	
	return doors;
}

s16 findDoorID(s16 x, s16 y, u16 mapID) {
	Door** doors = Game::doors;
	for(u16 i = 0; i < DOORS ; i++) {
		printf("%d, %d, %d, %d | %d, %d\n", doors[i]->x >> 4, doors[i]->y >> 4, x >> 4, y >> 4, doors[i]->mapID, mapID);
		if(((doors[i]->x >> 4 == x >> 4) || (doors[i]->x >> 4 == (x >> 4) + 1) || (doors[i]->x >> 4 == (x >> 4) - 1)) && ((doors[i]->y >> 4 == y >> 4) || (doors[i]->y >> 4 == (y >> 4) + 1)) && (doors[i]->mapID == mapID)) {
			return i;
		}
	}
	return -1;
}

