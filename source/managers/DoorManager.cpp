/*
 * =====================================================================================
 *
 *       Filename:  DoorManager.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  16/07/2014 18:36:05
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#include "Character.hpp"
#include "DoorManager.hpp"

std::vector<Door> DoorManager::doors;

void DoorManager::init() {
	doors.push_back(Door(0, 0, 0, 6 << 4, 3 << 4, Character::Direction::Down, 1));
	doors.push_back(Door(1, 0, 0, (7 << 4) + 8, 10 << 4, Character::Direction::Up, 0));
	
	doors.push_back(Door(1, 0, 0, 3 << 4, 2 << 4, Character::Direction::Down, 3));
	doors.push_back(Door(1, 1, 0, 4 << 4, 8 << 4, Character::Direction::Up, 2));
	
	doors.push_back(Door(0, 1, 2, 2 << 4, 7 << 4, Character::Direction::Down, 5));
	doors.push_back(Door(2, 0, 0, (7 << 4) + 8, 10 << 4, Character::Direction::Up, 4));
	
	doors.push_back(Door(0, 0, 2, 4 << 4, 10 << 4, Character::Direction::Left, 7));
	doors.push_back(Door(3, 0, 1, 12 << 4, 8 << 4, Character::Direction::Left, 6));
	
	doors.push_back(Door(2, 1, 1, 4 << 4, 2 << 4, Character::Direction::Down, 9));
	doors.push_back(Door(3, 1, 0, 10 << 4, 1 << 4, Character::Direction::Down, 8));
}

void DoorManager::free() {
	doors.clear();
}

Door *DoorManager::findDoor(u16 x, u16 y, u16 zone, u16 mapX, u16 mapY) {
	for(auto &it : doors) {
		if((it.spawnX >> 4 == x >> 4
		||  it.spawnX >> 4 == (x >> 4) + 1
		||  it.spawnX >> 4 == (x >> 4) - 1)
		&& (it.spawnY >> 4 == y >> 4
		||  it.spawnY >> 4 == (y >> 4) + 1
		||  it.spawnY >> 4 == (y >> 4) - 1)
		&& it.zone == zone && it.mapX == mapX && it.mapY == mapY) {
			return &it;
		}
	}
	
	return nullptr;
}

