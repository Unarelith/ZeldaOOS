/*
	* =====================================================================================
	*
	*       Filename:  door_manager.h
	*
	*    Description:  Simple manager for door system
	*
	*        Version:  1.0
	*        Created:  20/01/2014 20:02:12
	*       Revision:  none
	*       Compiler:  gcc
	*
	*         Author:  Quentin BAZIN, <quent42340@gmail.com>
	*        Company:  Deloptia
	*
	* =====================================================================================
	*/
#ifndef DOOR_MANAGER_H
#define DOOR_MANAGER_H

#define DOOR_NB 6

extern t_door **g_doors;

void door_manager_init_all();
void door_manager_free_all();

uint16_t door_manager_find_door_id(int16_t x, int16_t y, uint16_t area, uint8_t map_x, uint8_t map_y);

#endif // DOOR_MANAGER_H
