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

static uint8_t g_map_bg;
static uint16_t g_map_counter = 0;


void map_system_init()
 {
  g_map_bg = bgInit(0, BgType_Text8bpp, BgSize_T_512x512, 8, 2);
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
		map->scroll_x = x * 256;
		map->scroll_y = y * 192;
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
  
  for(y = 0 ; y < map->height ; y++)
   {
    for(x = 0 ; x < map->width ; x++)
     {
      map_load_tile(map, x, y, 0, 0);
     }
   }
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
		
		//next_map = g_maps[map->area][map->x + dx + (map->y + dy) * g_area_sizes[map->area]];
		next_map = NULL;
		
		//g_player->vx = 0;
		//g_player->vy = 0;
		
		if(dx != 0)
		 {
				for(i = 0 ; i < 32 ; i++)
				 {
						if((i & 1) || !(i & 15))
						 {
								//g_player->x -= 8 * dx; // With sprites?
							}
						else
						 {
								//g_player->x -= 7 * dx; // With sprites?
							}
						
						for(j = 0 ; j < 8 * abs(dx) ; j++)
						 {
								if(!(map->scroll_x & 15))
								 {
          for(k = map->scroll_y / map->tileset->tile_size ; k < map->scroll_y / map->tileset->tile_size + 12 ; k++)
											{
												if(dx > 0)
												 {
												  map_load_tile(next_map, map->scroll_x / map->tileset->tile_size, k, 16, 0);
													}
												else
												 {
												  map_load_tile(next_map, map->scroll_x / map->tileset->tile_size, k, -1, -1);
													}
											}
									}
								
								map->scroll_x += dx;
							}
		    
	    	bgSetScroll(g_map_bg, map->scroll_x, map->scroll_y);
    		bgUpdate();
						
						//character_render(g_player); // With sprites?
						
						swiWaitForVBlank();
					}
			}
		else if(dy != 0)
		 {
				for(i = 0 ; i < 24 ; i++)
				 {
						if((i & 1) && (i & 7) < 7)
						 {
								//g_player->y -= 8 * dy; // With sprites?
							}
						else
						 {
								//g_player->y -= 7 * dy; // With sprites?
							}
						
						for(j = 0 ; j < 8 * abs(dy) ; j++)
						 {
								if(!(map->scroll_y & 15))
								 {
          for(k = map->scroll_x / map->tileset->tile_size ; k < map->scroll_x / map->tileset->tile_size + 16 ; k++)
											{
												if(dx > 0)
												 {
												  map_load_tile(next_map, k, map->scroll_y / map->tileset->tile_size, 12, 0);
													}
												else
												 {
												  map_load_tile(next_map, k, map->scroll_y / map->tileset->tile_size, -1, -1);
													}
											}
									}
								
								map->scroll_x += dx;
							}
		    
	    	bgSetScroll(g_map_bg, map->scroll_x, map->scroll_y);
    		bgUpdate();
						
						//character_render(g_player); // With sprites?
						
						swiWaitForVBlank();
					}
			}
		
		//g_current_map = next_map;
	}

