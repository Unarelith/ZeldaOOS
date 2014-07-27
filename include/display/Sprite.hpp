/*
 * =====================================================================================
 *
 *       Filename:  Sprite.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  16/07/2014 15:39:18
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#ifndef SPRITE_HPP_
#define SPRITE_HPP_

#include <vector>

#include "libs5.h"

#include "SpriteAnimation.hpp"

class Sprite {
	public:
		Sprite(u8 screen, u8 id, s5_dimension size, u8 baseTile, u16 tileSize, u16 nbTiles, u8 paletteSlot, const void *tilesData, const void *palData);
		~Sprite();
		
		void clear();
		
		void drawFrame(s16 x, s16 y, u8 frame);
		void drawPositionedFrame(s16 x, s16 y, u8 anim, u8 frame);
		
		void addAnimation(u8 size, u8 *frames, u16 delay, s16 position[][2] = NULL);
		
		void stopAnimation(u8 anim);
		void startAnimation(u8 anim);
		void resetAnimation(u8 anim);
		
		bool isAnimationAtEnd(u8 anim);
		
		u16 getAnimationFrame(u8 anim);
		
		void playAnimation(s16 x, s16 y, u8 anim);
		
	protected:
		u8 m_screen;
		
		u8 m_id;
		
		s5_dimension m_size;
		s5_colors m_color;
		
		u8 m_baseTile;
		u16 m_tileSize;
		u8 m_paletteSlot;
		
		std::vector<SpriteAnimation> m_animations;
};

#endif // SPRITE_HPP_
