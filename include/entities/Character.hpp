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
		
		void testCollisions();
		void mapCollisions();
		
		s16 x() const { return m_x; }
		s16 y() const { return m_y; }
		
		void x(s16 x) { m_x = x; }
		void y(s16 y) { m_y = y; }
		
		void vx(s8 vx) { m_vx = vx; }
		void vy(s8 vy) { m_vy = vy; }
		
		enum Direction {
			Down,
			Right,
			Left,
			Up
		};
		
	protected:
		float m_x;
		float m_y;
		
		float m_vx;
		float m_vy;
		
		u8 m_direction;
		
		bool m_moving;
};

#endif // CHARACTER_HPP_
