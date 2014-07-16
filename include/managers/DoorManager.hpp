/*
 * =====================================================================================
 *
 *       Filename:  DoorManager.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  16/07/2014 18:35:53
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#ifndef DOORMANAGER_HPP_
#define DOORMANAGER_HPP_

#include <vector>

#include "Door.hpp"

namespace DoorManager {
	void init();
	void free();
	
	Door *findDoor(u16 x, u16 y, u16 zone, u16 mapX, u16 mapY);
	
	extern std::vector<Door> doors;
};

#endif // DOORMANAGER_HPP_
