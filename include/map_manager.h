/*
	* =====================================================================================
	*
	*       Filename:  map_manager.h
	*
	*    Description:  A simple manager for map system
	*
	*        Version:  1.0
	*        Created:  19/01/2014 21:11:25
	*       Revision:  none
	*       Compiler:  gcc
	*
	*         Author:  Quentin BAZIN, <quent42340@gmail.com>
	*        Company:  Deloptia
	*
	* =====================================================================================
	*/
#ifndef MAP_MANAGER_H_
#define MAP_MANAGER_H_

#define AREA_NB 1
#define TILESET_NB 1

extern uint8_t g_area_sizes[AREA_NB];
extern t_tileset **g_tilesets;
extern t_map ***g_maps;
extern t_map *g_current_map;

void map_manager_load_tilesets();
void map_manager_load_maps();

void map_manager_load_all();
void map_manager_free_all();

#endif // MAP_MANAGER_H_
