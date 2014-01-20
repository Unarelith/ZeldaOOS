/*
	* =====================================================================================
	*
	*       Filename:  door_manager.c
	*
	*    Description:  Simple manager for door system
	*
	*        Version:  1.0
	*        Created:  20/01/2014 20:02:45
	*       Revision:  none
	*       Compiler:  gcc
	*
	*         Author:  Quentin BAZIN, <quent42340@gmail.com>
	*        Company:  Deloptia
	*
	* =====================================================================================
	*/
#include <stdio.h>
#include <nds.h>
#include "tileset.h"
#include "map.h"
#include "door.h"
#include "door_manager.h"

t_door **g_doors;

void door_manager_init_all()
 {
		g_doors = (t_door **)malloc(DOOR_NB * sizeof(t_door *));
		
		g_doors[0] = door_new(0, 0, 0, 6 << 4, 3 << 4, 0, 1);
		g_doors[1] = door_new(1, 0, 0, (7 << 4) + 8, 11 << 4, 3, 0);
		
		g_doors[2] = door_new(1, 0, 0, 3 << 4, 2 << 4, 0, 3);
		g_doors[3] = door_new(1, 1, 0, 4 << 4, 8 << 4, 3, 2);
		
		g_doors[4] = door_new(0, 1, 2, 2 << 4, 7 << 4, 0, 5);
		g_doors[5] = door_new(2, 0, 0, (7 << 4) + 8, 11 << 4, 3, 4);
	}

void      door_manager_free_all()
 {
		uint8_t i;
		
		if(g_doors)
		 {
				for(i = 0 ; i < DOOR_NB ; i++)
				 {
						door_free(g_doors[i]);
					}
				free(g_doors);
			}
	}

uint16_t   door_manager_find_door_id(int16_t x, int16_t y, uint16_t area, uint8_t map_x, uint8_t map_y)
 {
	 uint16_t i;
		for(i = 0 ; i < DOOR_NB; i++)
		 {
				//printf("%d, %d, %d, %d | %d, %d\n", g_doors[i]->x >> 4, g_doors[i]->y >> 4, x >> 4, y >> 4, g_doors[i]->map_id, map_get_id_by_position(area, map_x, map_y));
				if(((g_doors[i]->x >> 4  == x >> 4) || (g_doors[i]->x >> 4 == (x >> 4) + 1) || (g_doors[i]->x >> 4 == (x >> 4) - 1))
				&& ((g_doors[i]->y >> 4  == y >> 4) || (g_doors[i]->y >> 4 == (y >> 4) + 1) || (g_doors[i]->y >> 4 == (y >> 4) - 1))
				&&  (g_doors[i]->map_id == map_get_id_by_position(area, map_x, map_y)))
				 {
						return i;
					}
			}
		return 6;
	}

