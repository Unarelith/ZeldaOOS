/*
	* =====================================================================================
	*
	*       Filename:  character_manager.c
	*
	*    Description:  A simple manager for character system
	*
	*        Version:  1.0
	*        Created:  19/01/2014 23:36:37
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

#include "grass_effect.h"
#include "water_effect.h"

t_character *g_player = NULL;

t_sprite *g_grass_effect = NULL;
t_sprite *g_low_water_effect = NULL;

static uint8_t g_low_water_effect_animations[3] = {0,1,2};

void character_manager_init_all()
 {
		g_player = player_new();
		
		g_grass_effect = sprite_new(SCREEN_UP, 0, SprSize_16x16, 0, 4, 4, 0, grass_effectTiles, NULL);
		g_low_water_effect = sprite_new(SCREEN_UP, 1, SprSize_16x16, 4, 4, 12, 0, water_effectTiles, NULL);
		sprite_add_animation(g_low_water_effect, 3, g_low_water_effect_animations, 150);
	}

void character_manager_free_all()
 {
		character_free(g_player);
	}

