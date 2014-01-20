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

/* Character directions
 * 0: Down
 * 1: Right
 * 2: Left
 * 3: Up
 */

/* Character types
 * 0: Player
 * 1: NPC
 * 2: Monster
 */

struct s_character
 {
  int16_t x;
  int16_t y;
  
  int8_t vx;
  int8_t vy;
  
  uint8_t direction;
  
  t_sprite *sprite;
  
  bool moving;
  
  uint8_t type;
		
		bool in_door;
 };

typedef struct s_character t_character;

t_character *character_new(uint8_t screen, int16_t x, int16_t y, uint8_t direction, uint8_t id, s5_dimension size, uint8_t base_tile, uint16_t tile_size, uint16_t nb_tiles, uint8_t palette, const void *tiles_data, const void *pal_data, uint8_t type);
void character_free(t_character *character);

void character_render(t_character *character);

void character_move(t_character *character);

void character_map_collisions(t_character *character);
void character_test_collisions(t_character *character);

#endif // CHARACTER_H_
