/*
 * =====================================================================================
 *
 *       Filename:  character.c
 *
 *    Description:  Character structure
 *
 *        Version:  1.0
 *        Created:  16/01/2014 18:32:54
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
#include "player.h"

t_character   *character_new(uint8_t      screen,
                             int16_t      x,
                             int16_t      y,
                             uint8_t      direction,
                             uint8_t      id,
                             s5_dimension size,
                             uint8_t      base_tile,
                             uint16_t     tile_size,
                             uint16_t     nb_tiles,
                             uint8_t      palette,
                             const void   *tiles_data,
                             const void   *pal_data,
                             uint8_t      type)
 {
  t_character *character;
  
  character = (t_character *)malloc(sizeof(t_character));
  character->x = x;
  character->y = y;
  character->vx = 0;
  character->vy = 0;
  character->direction = direction;
  character->sprite = sprite_new(screen, id, size, base_tile, tile_size, nb_tiles, palette, tiles_data, pal_data);
  character->moving = false;
  character->type = type;
  
  return character;
 }

void character_free(t_character *character)
 {
  if(character)
   {
    sprite_free(character->sprite);
    free(character);
   }
 }

void character_render(t_character *character)
 {
  if(character->moving)
   {
    sprite_play_animation(character->sprite, character->x, character->y, character->direction);
   }
  else
   {
    sprite_draw_frame(character->sprite, character->x, character->y, character->direction);
   }
 }

void character_move(t_character *character)
 {
  if(character->type == 0)
   {
    player_move(character);
   }
 }

