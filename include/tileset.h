/*
 * =====================================================================================
 *
 *       Filename:  tileset.h
 *
 *    Description:  Tileset system for maps
 *
 *        Version:  1.0
 *        Created:  16/01/2014 20:10:16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#ifndef TILESET_H_
#define TILESET_H_

struct s_tileset
 {
  uint8_t *info;
		
		uint8_t tile_size;
  
  const uint32_t *tiles;
  uint32_t tiles_length;
  
  const uint16_t *palette;
  uint32_t pal_length;
 };

typedef struct s_tileset t_tileset;

t_tileset *tileset_new(uint8_t *info, uint8_t tile_size, const uint32_t *tiles, uint32_t tiles_length, const uint16_t *palette, uint32_t pal_length);
void tileset_free(t_tileset *tileset);

#endif // TILESET_H_
