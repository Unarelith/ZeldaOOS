/*
 * =====================================================================================
 *
 *       Filename:  Character.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  16/07/2014 15:30:11
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#ifndef CHARACTER_HPP_
#define CHARACTER_HPP_

#include "Sprite.hpp"

class Character : public Sprite {
	public:
		Character(u8 screen, s16 x, s16 y, u8 direction, u8 id, s5_dimension size, u8 baseTile, u16 tileSize, u16 nbTiles, u8 paletteSlot, const void *tilesData, const void *palData);
		~Character();
		
		void draw();
		
		enum Direction {
			Down,
			Right,
			Left,
			Up
		};
		
	protected:
		s16 m_x;
		s16 m_y;
		
		s8 m_vx;
		s8 m_vy;
		
		u8 direction;
		
		bool m_moving;
};

#endif // CHARACTER_HPP_
