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

struct s_sprite
 {
  uint8_t screen;
  
  s5_dimension size;
  s5_colors color;
  
  uint8_t id;
  uint8_t base_tile;
  uint16_t tile_size;
  uint8_t palette;
  
  t_animation *animations;
 };

typedef struct s_sprite t_sprite;

void sprite_system_init();

t_sprite *sprite_new(uint8_t screen, uint8_t id, s5_dimension size, uint8_t base_tile, uint16_t tile_size, uint16_t nb_tiles, uint8_t palette, const void *tiles_data, const void *pal_data);
void sprite_free(t_sprite *sprite);

void sprite_clear(t_sprite *sprite);
void sprite_draw_frame(t_sprite *sprite, int16_t x, int16_t y, uint8_t frame);

void sprite_add_animation(t_sprite *sprite, uint8_t size, uint8_t *anim, uint16_t delay);
t_animation *sprite_get_animation(t_sprite *sprite, uint8_t anim);
void sprite_reset_animation(t_sprite *sprite, uint8_t anim);
void sprite_start_animation(t_sprite *sprite, uint8_t anim);
void sprite_stop_animation(t_sprite *sprite, uint8_t anim);
bool sprite_animation_at_end(t_sprite *sprite, uint8_t anim);
void sprite_play_animation(t_sprite *sprite, int16_t x, int16_t y, uint8_t anim);

#endif // SPRITE_H_
