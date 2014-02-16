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
#include "character_manager.h"
#include "player.h"
#include "tileset.h"
#include "map.h"
#include "map_manager.h"

uint8_t collision_matrix[4][4] = {
 {12,8,12,13},
 {3,8,3,13},
 {5,5,10,5},
 {5,15,10,15}
};

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
		character->in_door = false;
  
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

void character_test_collisions(t_character *character)
 {
		character_map_collisions(character);
		if(character->type == 0)
		 {
				player_door_collisions(character);
			}
	}

void      character_map_collisions(t_character *character)
 {
		uint8_t i;
		
		for(i = 0 ; i < 4 ; i++)
		 {
    if(((i==0)?(character->vx > 0):((i==1)?(character->vx < 0):((i==2)?(character->vy < 0):(character->vy > 0))))
				&& (!passable(character->x + collision_matrix[i][0], character->y + collision_matrix[i][1])
					|| !passable(character->x + collision_matrix[i][2], character->y + collision_matrix[i][3])))
			  {
						if(i < 2)
						 {
								character->vx = 0;
							}
						else
						 {
								character->vy = 0;
							}
						
      if( passable(character->x + collision_matrix[i][2], character->y + collision_matrix[i][3])
						&& !passable(character->x + collision_matrix[i][0], character->y + collision_matrix[i][1]))
						 {
        if(((i<2)?(character->vy == 0):(character->vx == 0)))
								 {
          if(i<2)
										 {
												character->vy = 1;
											}
										else
										 {
												character->vx = 1;
											}
         }
       }
      
						if( passable(character->x + collision_matrix[i][0], character->y + collision_matrix[i][1])
						&& !passable(character->x + collision_matrix[i][2], character->y + collision_matrix[i][3]))
						 {
							 if(((i<2)?(character->vy == 0):(character->vx == 0)))
								 {
										if(i<2)
										 {
												character->vy = -1;
										 }
										else
										 {
												character->vx = -1;
											}
									}
							}
			  }
			}
		if((slowing_tile(character->x +  2, character->y +  2)
		||  slowing_tile(character->x + 14, character->y +  2)
		||  slowing_tile(character->x +  2, character->y + 14)
		||  slowing_tile(character->x + 14, character->y + 14))
		&& character->vy != 0)
		 {
				character->vx /= 2;
				character->vy /= 2;
			}
		// TODO: Improve grass tile detection
		if(grass_tile(character->x +  2, character->y +  2)
		|| grass_tile(character->x + 14, character->y +  2)
		|| grass_tile(character->x +  2, character->y + 14)
		|| grass_tile(character->x + 14, character->y + 14))
		 {
				character->vx /= 4;
				character->vx *= 3;
				
				character->vy /= 4;
				character->vy *= 3;
				
				sprite_draw_frame(g_grass_effect, character->x, character->y, 0);
			}
		else
		 {
				clearSprite(SCREEN_UP, g_grass_effect->id);
			}
		// TODO: Improve low water tile detection
		if(low_water_tile(character->x +  2, character->y +  2)
		|| low_water_tile(character->x + 14, character->y +  2)
		|| low_water_tile(character->x +  2, character->y + 14)
		|| low_water_tile(character->x + 14, character->y + 14))
		 {
				sprite_play_animation(g_low_water_effect, character->x, character->y + 8, 0);
			}
		else
		 {
				clearSprite(SCREEN_UP, g_low_water_effect->id);
			}
	}

