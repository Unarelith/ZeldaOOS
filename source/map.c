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
      map_load_tile(map, x, y);
     }
   }
 }

void       map_load_tile(t_map *map, uint16_t x, uint16_t y)
 {
  uint16_t data_x;
  uint16_t data_y;
  
  data_x = x & 15;
  data_y = y % 12;
  
  ((uint16_t *)bgGetMapPtr(g_map_bg))[map_bg_pos(x * 2,     y * 2    )] = map->data[data_x + data_y * map->width] * 4;
  ((uint16_t *)bgGetMapPtr(g_map_bg))[map_bg_pos(x * 2 + 1, y * 2    )] = map->data[data_x + data_y * map->width] * 4 + 1;
  ((uint16_t *)bgGetMapPtr(g_map_bg))[map_bg_pos(x * 2,     y * 2 + 1)] = map->data[data_x + data_y * map->width] * 4 + 2;
  ((uint16_t *)bgGetMapPtr(g_map_bg))[map_bg_pos(x * 2 + 1, y * 2 + 1)] = map->data[data_x + data_y * map->width] * 4 + 3;
 }

