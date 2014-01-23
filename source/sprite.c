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
#include <stdio.h>
#include <nds.h>
#include "libs5.h"
#include "timer.h"
#include "animation.h"
#include "sprite.h"

void      sprite_system_init()
 {
		uint8_t i;
		
  enableSprites(0, 0);
  enableSprites(1, 0);
	 
  for(i = 0 ; i < 128 ; i++)
		 {
    setSpritePriority(0, i, 1);
   }
 }

t_sprite   *sprite_new(uint8_t      screen,
                       uint8_t      id,
                       s5_dimension size,
                       uint8_t      base_tile,
                       uint16_t     tile_size,
                       uint16_t     nb_tiles,
                       uint8_t      palette,
                       const void   *tiles_data,
                       const void   *pal_data)
 {
  t_sprite *sprite;
  
  sprite = (t_sprite *)malloc(sizeof(t_sprite));
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

void sprite_free(t_sprite *sprite)
 {
  animation_free(sprite->animations);
  clearSprite(sprite->screen, sprite->id);
  free(sprite);
 }

void sprite_clear(t_sprite *sprite)
 {
  clearSprite(sprite->screen, sprite->id);
 }

void sprite_draw_frame(t_sprite *sprite,
                      int16_t x,
                      int16_t y,
                      uint8_t frame)
 {
  drawSprite(sprite->screen, sprite->id, x, y, sprite->size, sprite->color, sprite->base_tile + frame * sprite->tile_size, sprite->palette);
 }

void          sprite_add_animation(t_sprite *sprite,
                                   uint8_t  size,
                                   uint8_t  *anim,
                                   uint16_t delay)
 {
  t_animation *it;
  
  it = sprite->animations;
  if(it)
   {
    while(it->next)
     {
      it = it->next;
     }
    it->next = animation_new(size, anim, delay);
   }
  else
   {
    sprite->animations = animation_new(size, anim, delay);
   }
 }

t_animation   *sprite_get_animation(t_sprite *sprite, uint8_t anim)
 {
  t_animation *ret;
  uint8_t     i;
  
  i = 0;
  ret = sprite->animations;
  while(ret && i != anim)
   {
    ret = ret->next;
    i++;
   }
  return ret;
 }

void          sprite_reset_animation(t_sprite *sprite, uint8_t anim)
 {
  t_animation *animation;
  
  animation = sprite_get_animation(sprite, anim);
  if(animation)
   {
    timer_reset(animation->timer);
   }
 }

void          sprite_start_animation(t_sprite *sprite, uint8_t anim)
 {
  t_animation *animation;
  
  animation = sprite_get_animation(sprite, anim);
  if(animation)
   {
     timer_start(animation->timer);
   }
 }

void          sprite_stop_animation(t_sprite *sprite, uint8_t anim)
 {
  t_animation *animation;
  
  animation = sprite_get_animation(sprite, anim);
  if(animation)
   {
    timer_stop(animation->timer);
   }
 }

bool sprite_animation_at_end(t_sprite *sprite, uint8_t anim)
 {
  t_animation *animation;
  
  animation = sprite_get_animation(sprite, anim);
  if(animation)
   {
    return timer_get_time(animation->timer) / animation->delay >= animation->size;
   }
  else
   {
    return true;
   }
 }

void          sprite_play_animation(t_sprite *sprite,
                                    int16_t  x,
                                    int16_t  y,
                                    uint8_t  anim)
 {
  t_animation *animation;
  
  animation = sprite_get_animation(sprite, anim);
  if(animation)
   {
    if(!animation->playing)
     {
      sprite_reset_animation(sprite, anim);
      sprite_start_animation(sprite, anim);
      animation->playing = true;
     }
    
    if(sprite_animation_at_end(sprite, anim))
     {
      sprite_reset_animation(sprite, anim);
      sprite_start_animation(sprite, anim);
     }
    
    uint8_t frame = animation->animation_table[(int)(timer_get_time(animation->timer) / animation->delay)];
    sprite_draw_frame(sprite, x, y, frame);
   }
 }

