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
#include "tileset.h"
#include "map.h"
#include "map_manager.h"
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

