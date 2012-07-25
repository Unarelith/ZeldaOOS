/*---------------------------------------------------------------------------------

	Eleandra
	Copyright (C) 2012 Quentin BAZIN quent42340@gmail.com
	
	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
	
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	
	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

---------------------------------------------------------------------------------*/
#include <nds.h>
#include "timer.h"
#include "sprites.h"

Sprite_Animation::Sprite_Animation(int size, int *tabAnim, int delay) {
	s_size = size;
	s_tabAnim = tabAnim;
	s_delay = delay;
	s_tmr = new Timer();
	s_isPlaying = false;
}

Sprite_Animation::~Sprite_Animation() {
	delete s_tmr;
}

Sprite::Sprite(u8 screen, int id, s5_dimension size, u8 baseTile, int tileSize) {
	s_tileSize = tileSize;
	s_baseTile = baseTile;
	s_screen = screen;
    s_size = size;
    s_color = SprColors_16;
	s_id = id;
}

Sprite::~Sprite() {
	clearSprite(s_screen, s_id);
}

void Sprite::clear() {
	clearSprite(s_screen, s_id);
}

void Sprite::draw(s16 x, s16 y, u8 palette) {
	s_x = x;
	s_y = y;
	
	drawSprite(s_screen, s_id, s_x, s_y, s_size, s_color, s_baseTile, palette);
}

void Sprite::drawFrame(s16 x, s16 y, int frame, u8 palette) {
	drawSprite(s_screen, s_id, x, y, s_size, s_color, s_baseTile + frame * s_tileSize, palette);
}

void Sprite::addAnimation(int size, int *tabAnim, int delay) {
	Sprite_Animation* tmp = new Sprite_Animation(size, tabAnim, delay);
	s_animations.push_back(tmp);
}

void Sprite::resetAnimation(int anim) {
	s_animations.at(anim)->tmr()->reset();
}

void Sprite::startAnimation(int anim) {
	s_animations.at(anim)->tmr()->start();
}

void Sprite::stopAnimation(int anim) {
	s_animations.at(anim)->tmr()->stop();
}

bool Sprite::animationAtEnd(int anim) {
	return s_animations.at(anim)->tmr()->time() / s_animations.at(anim)->delay() >= s_animations.at(anim)->size();
}

void Sprite::playAnimation(s16 x, s16 y, int anim, u8 palette) {
	// If the animation is not playing
	if(!s_animations.at(anim)->isPlaying()) {
		resetAnimation(anim); // Reset animation timer
		startAnimation(anim); // Start animation timer
		s_animations.at(anim)->isPlaying(true); // Set isPlaying boolean to true
	}
	
	// If the animation is at end
	if(s_animations.at(anim)->tmr()->time() / s_animations.at(anim)->delay() >= s_animations.at(anim)->size()) {
		resetAnimation(anim); // Reset animation timer
		startAnimation(anim); // Start animation timer
	}
	
	// This variable contains the number of the animation's frame to draw
	int animToDraw = s_animations.at(anim)->tabAnim()[(int)(s_animations.at(anim)->tmr()->time() / s_animations.at(anim)->delay())];
	drawFrame(x, y, animToDraw, palette); // Draw the frame
}

