/*
 * =====================================================================================
 *
 *       Filename:  CharacterManager.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  16/07/2014 15:32:54
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#ifndef CHARACTERMANAGER_HPP_
#define CHARACTERMANAGER_HPP_

#include "Player.hpp"

namespace CharacterManager {
	void init();
	void free();
	
	extern Player *player;
};

#endif // CHARACTERMANAGER_HPP_
