/*
 * =====================================================================================
 *
 *       Filename:  SpriteAnimation.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  16/07/2014 15:48:10
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#ifndef SPRITEANIMATION_HPP_
#define SPRITEANIMATION_HPP_

#include "Timer.hpp"

struct SpriteAnimation {
	SpriteAnimation(u16 _size, u8 *_tabAnim, u16 _delay) :
		size(_size), tabAnim(_tabAnim), delay(_delay), isPlaying(false) {}
	
	u16 size;
	u8 *tabAnim;
	u16 delay;
	Timer timer;
	bool isPlaying;
};

#endif // SPRITEANIMATION_HPP_
