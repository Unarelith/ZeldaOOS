/*
	* =====================================================================================
	*
	*       Filename:  door.h
	*
	*    Description:  Simple door system
	*
	*        Version:  1.0
	*        Created:  20/01/2014 19:53:37
	*       Revision:  none
	*       Compiler:  gcc
	*
	*         Author:  Quentin BAZIN, <quent42340@gmail.com>
	*        Company:  Deloptia
	*
	* =====================================================================================
	*/
#ifndef DOOR_H_
#define DOOR_H_

struct s_door
 {
		uint16_t map_id;
		
		uint16_t x;
		uint16_t y;
		
		uint8_t direction;
		
		uint16_t next_door_id;
	};

typedef struct s_door t_door;

t_door *door_new(uint16_t area, uint8_t map_x, uint8_t map_y, uint16_t x, uint16_t y, uint8_t direction, uint16_t next_door_id);
void door_free(t_door *door);

#endif // DOOR_H_
