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

#define AREA_NB 3
#define TILESET_NB 3

extern uint8_t g_area_sizes[AREA_NB];
extern t_tileset **g_tilesets;
extern t_map ***g_maps;
extern t_map *g_current_map;

extern uint8_t g_plain_info[256];
extern uint8_t g_indoor_info[256];
extern uint8_t g_underground_info[256];

extern uint8_t g_non_passable_tiles[13];
extern uint8_t g_change_map_tiles[3];

void map_manager_load_tilesets();
void map_manager_load_maps();

void map_manager_load_all();
void map_manager_free_all();

void map_manager_init_transition();
void map_manager_transition();

bool in_table(uint8_t t[], uint8_t n);
bool in_tiles(int16_t tile_x, int16_t tile_y, uint8_t tiles[]);
bool passable(int16_t x, int16_t y);

#endif // MAP_MANAGER_H_
