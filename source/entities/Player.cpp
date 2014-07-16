/*
 * =====================================================================================
 *
 *       Filename:  Player.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  16/07/2014 15:32:25
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#include "Player.hpp"

#include "link.h"

Player::Player() : Character(0, (10 << 4), (5 << 4), 0, 2, SprSize_16x16, 32, 4, 32, 0, linkTiles, linkPal) {
}

Player::~Player() {
}

