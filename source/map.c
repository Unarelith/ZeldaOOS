/*
 * =====================================================================================
 *
 *       Filename:  map.c
 *
 *    Description:  Map system with scrolling
 *
 *        Version:  1.0
 *        Created:  14/01/2014 22:06:57
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
#include "libs5.h"
#include "timer.h"
#include "animation.h"
#include "sprite.h"
#include "character.h"
#include "tileset.h"
#include "map.h"
#include "map_manager.h"
#include "character_manager.h"

uint8_t g_map_bg;
uint8_t g_transition_bg;

int16_t g_map_scroll_x = 0;
int16_t g_map_scroll_y = 0;

static uint16_t g_map_counter = 0;

void map_system_init()
 {
  g_map_bg = bgInit(0, BgType_Text8bpp, BgSize_T_512x512, 0, 1);
		g_transition_bg = bgInit(1, BgType_Text8bpp, BgSize_T_256x256, 4, 5);
		bgSetPriority(g_map_bg, 1);
		bgSetPriority(g_transition_bg, 0);
 }

t_map   *map_new(t_tileset *tileset,
                 char      *filename,
                 uint16_t  width,
                 uint16_t  height,
                 uint16_t  area,
                 uint8_t   x,
                 uint8_t   y)
 {
  t_map *map;
  FILE  *f;
  
  map = (t_map *)malloc(sizeof(t_map));
  map->id = g_map_counter++;
  map->tileset = tileset;
  map->width = width;
  map->height = height;
  map->area = area;
  map->x = x;
  map->y = y;
  map->data = (uint16_t *)malloc(width * height * sizeof(uint16_t));
  
  f = fopen(filename, "r");
  if(!f)
   {
    map_free(map);
    return NULL;
   }
  fread(map->data, 2, width * height * 2, f);
  fclose(f);
  
  return map;
 }

void map_free(t_map *map)
 {
  if(map)
   {
    if(map->data)
     {
      free(map->data);
     }
    free(map);
   }
 }

uint16_t map_bg_pos(uint16_t x, uint16_t y)
 {
  return ((x & 31) + ((x & 32) << 5)) + (((y & 31) << 5) + ((y & 32) << 6));
 }

void       map_load(t_map *map)
 {
  uint16_t x;
  uint16_t y;
  
  dmaCopy(map->tileset->tiles, bgGetGfxPtr(g_map_bg), map->tileset->tiles_length);
  dmaCopy(map->tileset->palette, BG_PALETTE, map->tileset->pal_length);
		
		g_map_scroll_x = map->x * 256;
		g_map_scroll_y = map->y * 192;
  
  for(y = g_map_scroll_y >> 4 ; y < (g_map_scroll_y >> 4) + map->height ; y++)
   {
    for(x = g_map_scroll_x >> 4 ; x < (g_map_scroll_x >> 4) + map->width ; x++)
     {
      map_load_tile(map, x, y, 0, 0);
     }
   }
		
		bgSetScroll(g_map_bg, g_map_scroll_x, g_map_scroll_y);
		bgUpdate();
 }

void       map_load_tile(t_map *map, uint16_t x, uint16_t y, int8_t offset_x, int8_t offset_y)
 {
  uint16_t data_x;
  uint16_t data_y;
  
  data_x = x & 15;
  data_y = y % 12;
		
		x += offset_x;
		y += offset_y;
  
  ((uint16_t *)bgGetMapPtr(g_map_bg))[map_bg_pos(x * 2,     y * 2    )] = map->data[data_x + data_y * map->width] * 4;
  ((uint16_t *)bgGetMapPtr(g_map_bg))[map_bg_pos(x * 2 + 1, y * 2    )] = map->data[data_x + data_y * map->width] * 4 + 1;
  ((uint16_t *)bgGetMapPtr(g_map_bg))[map_bg_pos(x * 2,     y * 2 + 1)] = map->data[data_x + data_y * map->width] * 4 + 2;
  ((uint16_t *)bgGetMapPtr(g_map_bg))[map_bg_pos(x * 2 + 1, y * 2 + 1)] = map->data[data_x + data_y * map->width] * 4 + 3;
 }

void       map_change_map(t_map *map, int8_t dx, int8_t dy)
 {
	 t_map    *next_map;
		uint16_t i, j, k;
		
		next_map = g_maps[map->area][(map->x + dx) + (map->y + dy) * g_area_sizes[map->area]];
	 
		g_player->vx = 0;
		g_player->vy = 0;
		
		if(dx != 0)
		 {
				for(i = 0 ; i < 32 ; i++)
				 {
						if((i & 1) || !(i & 15))
						 {
								g_player->x -= 8 * dx; // With sprites?
							}
						else
						 {
								g_player->x -= 7 * dx; // With sprites?
							}
						
						for(j = 0 ; j < 8 * abs(dx) ; j++)
						 {
								if(!(g_map_scroll_x & 15))
								 {
          for(k = g_map_scroll_y / map->tileset->tile_size ; k < g_map_scroll_y / map->tileset->tile_size + 12 ; k++)
											{
												if(dx > 0)
												 {
												  map_load_tile(next_map, g_map_scroll_x / map->tileset->tile_size, k, 16, 0);
													}
												else
												 {
												  map_load_tile(next_map, g_map_scroll_x / map->tileset->tile_size - 1, k, 0, 0);
													}
											}
									}
								
								g_map_scroll_x += dx;
							}
		    
	    	bgSetScroll(g_map_bg, g_map_scroll_x, g_map_scroll_y);
    		bgUpdate();
						
						character_render(g_player); // With sprites?
						
						swiWaitForVBlank();
					}
			}
		else if(dy != 0)
		 {
				for(i = 0 ; i < 24 ; i++)
				 {
						if((i & 1) && (i & 7) < 7)
						 {
								g_player->y -= 8 * dy; // With sprites?
							}
						else
						 {
								g_player->y -= 7 * dy; // With sprites?
							}
						
						for(j = 0 ; j < 8 * abs(dy) ; j++)
						 {
								if(!(g_map_scroll_y & 15))
								 {
          for(k = g_map_scroll_x / map->tileset->tile_size ; k < g_map_scroll_x / map->tileset->tile_size + 16 ; k++)
											{
												if(dy > 0)
												 {
												  map_load_tile(next_map, k, g_map_scroll_y / map->tileset->tile_size, 0, 12);
													}
												else
												 {
												  map_load_tile(next_map, k, g_map_scroll_y / map->tileset->tile_size - 1, 0, 0);
													}
											}
									}
								
								g_map_scroll_y += dy;
							}
		    
	    	bgSetScroll(g_map_bg, g_map_scroll_x, g_map_scroll_y);
    		bgUpdate();
						
						character_render(g_player); // With sprites?
						
						swiWaitForVBlank();
					}
			}
		
		g_current_map = next_map;
	}

uint8_t map_get_tile(t_map *map, int16_t tile_x, int16_t tile_y)
 {
	 if(tile_x + tile_y * map->width < map->width * map->height)
		 {
				return map->data[tile_x + tile_y * map->width];
			}
		else
		 {
				return 0;
			}
	}

uint16_t   map_get_id_by_position(uint16_t area, uint8_t map_x, uint8_t map_y)
 {
	 uint16_t i;
		uint16_t offset;
		
		offset = 0;
		for(i = 0 ; i < area ; i++)
		 {
				offset += (g_area_sizes[i] * g_area_sizes[i]);
			}
		
		//printf("(%d):(%d;%d) => (%d)\n", area, map_x, map_y, offset + map_x + map_y * g_area_sizes[area]);
		return offset + map_x + map_y * g_area_sizes[area];
	}

t_map      *map_get_by_id(uint16_t id)
 {
  uint16_t i;
		uint16_t temp_id;
		
		temp_id = 0;
		for(i = 0 ; i <= AREA_NB ; i++)
		 {
    if(temp_id > id)
				 {
						//printf("%d / %d / %d - %d\n", i - 1, id, temp_id, id - (temp_id - g_area_sizes[i - 1] * g_area_sizes[i - 1]));
						return g_maps[i - 1][id - (temp_id - g_area_sizes[i - 1] * g_area_sizes[i - 1])];
					}
				if(i < AREA_NB)
				 {
		    temp_id += (g_area_sizes[i] * g_area_sizes[i]);
					}
			}
		return NULL;
	}

