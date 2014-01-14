/*
 * =====================================================================================
 *
 *       Filename:  sprite.c
 *
 *    Description:  Simple sprite system
 *
 *        Version:  1.0
 *        Created:  06/01/2014 20:44:13
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#include <nds.h>
#include "libs5.h"
#include "timer.h"
#include "sprite.h"

s_animation   *animation_new(uint16_t size,
                             uint16_t *animation_table,
                             uint16_t delay)
 {
  s_animation *animation;
  
  animation = (s_animation *)malloc(sizeof(s_animation));
  animation->timer = timer_new();
  animation->size = size;
  animation->delay = delay;
  animation->animation_table = animation_table;
  animation->next = NULL;
  
  return animation;
 }

void animation_free(s_animation *animation)
 {
  if(animation->next)
   {
    animation_free(animation->next);
   }
  if(animation)
   {
    if(animation->animation_table)
     {
      free(animation->animation_table);
     }
    free(animation);
   }
 }

void sprite_system_init()
 {
  enableSprites(0, 0);
  enableSprites(1, 0);
 }

s_sprite   *sprite_new(uint8_t      screen,
                       uint8_t      id,
                       s5_dimension size,
                       uint8_t      base_tile,
                       uint16_t     tile_size,
                       uint16_t     nb_tiles,
                       uint8_t      palette,
                       const void   *tiles_data,
                       const void   *pal_data)
 {
  s_sprite *sprite;
  
  sprite = (s_sprite *)malloc(sizeof(s_sprite));
  sprite->screen = screen;
  sprite->id = id;
  sprite->size = size;
  sprite->color = SprColors_16;
  sprite->base_tile = base_tile;
  sprite->tile_size = tile_size;
  sprite->palette = palette;
  sprite->animations = NULL;
  
  loadTiles(screen, base_tile, nb_tiles, sprite->color, tiles_data);
  loadPalette(screen, palette, pal_data);
  
  return sprite;
 }

void sprite_free(s_sprite *sprite)
 {
  animation_free(sprite->animations);
  clearSprite(sprite->screen, sprite->id);
  free(sprite);
 }

void sprite_clear(s_sprite *sprite)
 {
  clearSprite(sprite->screen, sprite->id);
 }

void sprite_drawFrame(s_sprite *sprite,
                      int16_t x,
                      int16_t y,
                      uint8_t frame)
 {
  drawSprite(sprite->screen, sprite->id, x, y, sprite->size, sprite->color, sprite->base_tile + frame * sprite->tile_size, sprite->palette);
 }

void          sprite_add_animation(s_sprite *sprite,
                                   uint8_t  size,
                                   uint8_t  *anim,
                                   uint16_t delay)
 {
  s_animation *it;
  
  it = sprite->animations;
  if(it)
   {
    while(it->animations)
     {
      it = it->animations;
     }
    it->animations = animation_new(size, anim, delay);
   }
  else
   {
    sprite->animations = animation_new(size, anim, delay);
   }
 }

void sprite_get_animation(s_sprite *sprite, uint8_t anim)
 {
  s_animation *ret;
  
  
 }

void sprite_reset_animation(s_sprite *sprite, uint8_t anim)
 {
  
 }

void sprite_start_animation(s_sprite *sprite, uint8_t anim)
 {
  
 }

void sprite_stop_animation(s_sprite *sprite, uint8_t anim)
 {
  
 }

void sprite_is_animation_at_end(s_sprite *sprite, uint8_t anim)
 {
  
 }

void sprite_play_animation(s_sprite *sprite, int16_t x, int16_t y, uint8_t anim)
 {
  
 }
 
