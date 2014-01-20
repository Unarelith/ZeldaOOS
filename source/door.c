/*
	* =====================================================================================
	*
	*       Filename:  door.c
	*
	*    Description:  Simple door system
	*
	*        Version:  1.0
	*        Created:  20/01/2014 19:55:09
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

t_door   *door_new(uint16_t area,
		                 uint8_t  map_x,
		                 uint8_t  map_y,
																			uint16_t x,
																			uint16_t y,
																			uint8_t  direction,
																			uint16_t next_door_id)
 {
	 t_door *door;
		
		door = (t_door *)malloc(sizeof(t_door));
		door->map_id = map_get_id_by_position(area, map_x, map_y);
		door->x = x;
		door->y = y;
		door->direction = direction;
		door->next_door_id = next_door_id;
		
		return door;
	}

void door_free(t_door *door)
 {
		if(door)
		 {
				free(door);
			}
	}

