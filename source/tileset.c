/*
 * =====================================================================================
 *
 *       Filename:  tileset.c
 *
 *    Description:  Tileset system for maps
 *
 *        Version:  1.0
 *        Created:  16/01/2014 20:11:32
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


t_tileset   *tileset_new(uint8_t *info,
		                       uint8_t tile_size,
                         const uint32_t *tiles,
                         uint32_t tiles_length,
                         const uint16_t *palette,
                         uint32_t pal_length)
 {
  t_tileset *tileset;
  
  tileset = (t_tileset *)malloc(sizeof(t_tileset));
  tileset->info = info;
		tileset->tile_size = tile_size;
  tileset->tiles = tiles;
  tileset->tiles_length = tiles_length;
  tileset->palette = palette;
  tileset->pal_length = pal_length;
  
  return tileset;
 }

void tileset_free(t_tileset *tileset)
 {
  if(tileset)
   {
    free(tileset);
   }
 }

