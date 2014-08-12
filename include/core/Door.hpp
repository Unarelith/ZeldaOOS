/*
 * =====================================================================================
 *
 *       Filename:  Door.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  16/07/2014 18:33:22
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#ifndef DOOR_HPP_
#define DOOR_HPP_

#include <nds.h>

struct Door {
	Door(u16 _zone, u16 _mapX, u16 _mapY, u16 _spawnX, u16 _spawnY, u8 _spawnDirection, u16 _nextDoorID) :
		zone(_zone), mapX(_mapX), mapY(_mapY), spawnX(_spawnX), spawnY(_spawnY), spawnDirection(_spawnDirection), nextDoorID(_nextDoorID) {}
	
	u16 zone;
	
	u16 mapX;
	u16 mapY;
	
	u16 spawnX;
	u16 spawnY;
	
	u8 spawnDirection;
	
	u16 nextDoorID;
};

#endif // DOOR_HPP_
