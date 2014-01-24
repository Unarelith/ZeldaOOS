/*
 * =====================================================================================
 *
 *       Filename:  player.c
 *
 *    Description:  Player structure
 *
 *        Version:  1.0
 *        Created:  16/01/2014 20:19:50
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
#include "tools.h"
#include "tileset.h"
#include "map.h"
#include "map_manager.h"
#include "door.h"
#include "door_manager.h"
#include "timer.h"
#include "animation.h"
#include "sprite.h"
#include "character.h"
#include "player.h"

#include "link.h"

static uint8_t g_link_animations[12][4] = {
	{4,0},
	{5,1},
	{6,2},
	{7,3}
};

t_character   *player_new()
 {
  t_character *player;
  
  player = character_new(SCREEN_UP, (10 << 4), (5 << 4), 0, 0, SprSize_16x16, 0, 4, 32, 0, linkTiles, linkPal, 0);
  sprite_add_animation(player->sprite, 2, g_link_animations[0], 100);
  sprite_add_animation(player->sprite, 2, g_link_animations[1], 100);
  sprite_add_animation(player->sprite, 2, g_link_animations[2], 100);
  sprite_add_animation(player->sprite, 2, g_link_animations[3], 100);
  
  return player;
 }

void player_move(t_character *player)
 {
  player->moving = false;
  
  if(keysHeld() & KEY_LEFT)
   {
    player->vx = -1;
    player->moving = true;
  		if(!(keysHeld() & KEY_DOWN) && !(keysHeld() & KEY_UP) && !(keysHeld() & KEY_RIGHT))
     {
      player->direction = 2;
     }
   }
  if(keysHeld() & KEY_RIGHT)
   {
    player->vx = 1;
    player->moving = true;
  		if(!(keysHeld() & KEY_DOWN) && !(keysHeld() & KEY_UP) && !(keysHeld() & KEY_LEFT))
     {
      player->direction = 1;
     }
   }
  if(keysHeld() & KEY_UP)
   {
    player->vy = -1;
    player->moving = true;
  		if(!(keysHeld() & KEY_DOWN) && !(keysHeld() & KEY_LEFT) && !(keysHeld() & KEY_RIGHT))
     {
      player->direction = 3;
     }
   }
  if(keysHeld() & KEY_DOWN)
   {
    player->vy = 1;
    player->moving = true;
  		if(!(keysHeld() & KEY_UP) && !(keysHeld() & KEY_LEFT) && !(keysHeld() & KEY_RIGHT))
     {
      player->direction = 0;
     }
   }
		
		character_test_collisions(player);
  
  player->x += player->vx;
  player->y += player->vy;
  
  player->vx = 0;
  player->vy = 0;
		
		if(player->x > 256 - 16 + 2)
		 {
				map_change_map(g_current_map, 1, 0);
			}
		else if(player->x < 0 - 2)
		 {
			 map_change_map(g_current_map, -1, 0);
			}
		else if(player->y > 192 - 16 + 1)
		 {
				map_change_map(g_current_map, 0, 1);
			}
	 else if(player->y < 0 - 2)
		 {
				map_change_map(g_current_map, 0, -1);
			}
 }

void       player_door_collisions(t_character *player)
 {
		uint16_t door_id;
		
	 if(in_tiles((player->x + 8) >> 4, (player->y + 8) >> 4, g_change_map_tiles) && !player->in_door)
		 {
				player->vx = 0;
				player->vy = 0;
				
				door_id = door_manager_find_door_id(player->x, player->y, g_current_map->area, g_current_map->x, g_current_map->y);
				
				map_manager_init_transition();
				g_current_map = map_get_by_id(g_doors[g_doors[door_id]->next_door_id]->map_id);
				if(!g_current_map)
				 {
						fprintf(stderr, "Fatal error, could not load map with id: %d\n", g_doors[g_doors[door_id]->next_door_id]->map_id);
						while(1)
						 {
								swiWaitForVBlank();
							}
					}
				player->x = g_doors[g_doors[door_id]->next_door_id]->x;
				player->y = g_doors[g_doors[door_id]->next_door_id]->y;
				player->direction = g_doors[g_doors[door_id]->next_door_id]->direction;
				character_render(player);
				map_load(g_current_map);
				map_manager_transition();
				player->in_door = true;
				nds_delay(250);
			}
  if((!in_tiles((player->x +  2) >> 4, (player->y +  2) >> 4, g_change_map_tiles))
  && (!in_tiles((player->x + 14) >> 4, (player->y + 14) >> 4, g_change_map_tiles)))
		 {
				player->in_door = false;
			}
	}

