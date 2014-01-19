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

t_character *g_player = NULL;

void character_manager_init_all()
 {
		g_player = player_new();
	}

void character_manager_free_all()
 {
		character_free(g_player);
	}

