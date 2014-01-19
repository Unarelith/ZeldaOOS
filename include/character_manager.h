/*
	* =====================================================================================
	*
	*       Filename:  character_manager.h
	*
	*    Description:  A simple manager for character system
	*
	*        Version:  1.0
	*        Created:  19/01/2014 23:36:17
	*       Revision:  none
	*       Compiler:  gcc
	*
	*         Author:  Quentin BAZIN, <quent42340@gmail.com>
	*        Company:  Deloptia
	*
	* =====================================================================================
	*/
#ifndef CHARACTER_MANAGER_H_
#define CHARACTER_MANAGER_H_

extern t_character *g_player;

void character_manager_init_all();
void character_manager_free_all();

#endif // CHARACTER_MANAGER_H_
