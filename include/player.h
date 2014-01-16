/*
 * =====================================================================================
 *
 *       Filename:  player.h
 *
 *    Description:  Player structure
 *
 *        Version:  1.0
 *        Created:  16/01/2014 20:17:58
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#ifndef PLAYER_H_
#define PLAYER_H_

t_character *player_new();

void player_move(t_character *player);

#endif // PLAYER_H_
