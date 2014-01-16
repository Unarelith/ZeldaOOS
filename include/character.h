/*
 * =====================================================================================
 *
 *       Filename:  character.h
 *
 *    Description:  Character structure
 *
 *        Version:  1.0
 *        Created:  16/01/2014 18:30:33
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#ifndef CHARACTER_H_
#define CHARACTER_H_

enum e_direction
 {
  direction_up    = 3,
  direction_down  = 0,
  direction_left  = 2,
  direction_right = 1
 };

typedef enum e_direction t_direction;

struct s_character
 {
  int16_t x;
  int16_t y;
  
  t_direction direction;
  
  t_sprite *sprite;
  
  bool moving;
 };

typedef struct s_character t_character;

t_character *character_new(uint8_t screen, int16_t x, int16_t y, t_direction direction, uint8_t id, s5_dimension size, uint8_t base_tile, uint16_t tile_size, uint16_t nb_tiles, uint8_t palette, const void *tiles_data, const void *pal_data);
void character_free(t_character *character);

void character_render(t_character *character);

void character_move(t_character *character);

#endif // CHARACTER_H_
