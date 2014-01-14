/*
 * =====================================================================================
 *
 *       Filename:  sprite.h
 *
 *    Description:  Simple sprite system
 *
 *        Version:  1.0
 *        Created:  06/01/2014 20:35:34
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#ifndef SPRITE_H_
#define SPRITE_H_

struct s_animation
 {
  uint16_t size;
  uint16_t delay;
  
  bool     playing;
  
  s_timer  *timer;
  
  struct s_animation *next;
  
  uint8_t *animation_table;
 };

typedef struct s_animation s_animation;

s_animation *animation_new(uint16_t size, uint8_t *animation_table, uint16_t delay);
void animation_free(s_animation *animation);

struct s_sprite
 {
  uint8_t screen;
  
  s5_dimension size;
  s5_colors color;
  
  uint8_t id;
  uint8_t base_tile;
  uint16_t tile_size;
  uint8_t palette;
  
  s_animation *animations;
 };

typedef struct s_sprite s_sprite;

void sprite_system_init();

s_sprite *sprite_new(uint8_t screen, uint8_t id, s5_dimension size, uint8_t base_tile, uint16_t tile_size, uint16_t nb_tiles, uint8_t palette, const void *tiles_data, const void *pal_data);
void sprite_free(s_sprite *sprite);

void sprite_clear(s_sprite *sprite);
void sprite_draw_frame(s_sprite *sprite, int16_t x, int16_t y, uint8_t frame);

void sprite_add_animation(s_sprite *sprite, uint8_t size, uint8_t *anim, uint16_t delay);
s_animation *sprite_get_animation(s_sprite *sprite, uint8_t anim);
void sprite_reset_animation(s_sprite *sprite, uint8_t anim);
void sprite_start_animation(s_sprite *sprite, uint8_t anim);
void sprite_stop_animation(s_sprite *sprite, uint8_t anim);
bool sprite_animation_at_end(s_sprite *sprite, uint8_t anim);
void sprite_play_animation(s_sprite *sprite, int16_t x, int16_t y, uint8_t anim);

#endif // SPRITE_H_
