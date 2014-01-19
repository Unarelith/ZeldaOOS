/*
 * =====================================================================================
 *
 *       Filename:  map.h
 *
 *    Description:  Map system with scrolling
 *
 *        Version:  1.0
 *        Created:  14/01/2014 22:05:59
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#ifndef MAP_H_
#define MAP_H_

struct s_map
 {
  uint16_t id;
  
  t_tileset *tileset;
  
  uint16_t width;
  uint16_t height;
  
  uint16_t area;
  uint8_t x;
  uint8_t y;
		
  uint16_t *data;
 };

typedef struct s_map t_map;

void map_system_init();

t_map *map_new(t_tileset *tileset, char *filename, uint16_t width, uint16_t height, uint16_t area, uint8_t x, uint8_t y);
void map_free(t_map *map);

uint16_t map_bg_pos(uint16_t x, uint16_t y);

void map_load(t_map *map);
void map_load_tile(t_map *map, uint16_t x, uint16_t y, int8_t offset_x, int8_t offset_y);

void map_change_map(t_map *map, int8_t dx, int8_t dy);

uint8_t map_get_tile(t_map *map, int16_t tile_x, int16_t tile_y);

#endif // MAP_H_
