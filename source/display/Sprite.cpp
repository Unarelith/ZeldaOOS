/*
 * =====================================================================================
 *
 *       Filename:  Sprite.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  16/07/2014 15:39:48
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#include "Sprite.hpp"

Sprite::Sprite(u8 screen, u8 id, s5_dimension size, u8 baseTile, u16 tileSize, u16 nbTiles, u8 paletteSlot, const void *tilesData, const void *palData) {
	m_screen = screen;
	
	m_id = id;
	
	m_size = size;
	m_color = SprColors_16;
	
	m_baseTile = baseTile;
	m_tileSize = tileSize;
	m_paletteSlot = paletteSlot;
	
	loadTiles(m_screen, m_baseTile, nbTiles, m_color, tilesData);
	if(palData != NULL) {
		loadPalette(m_screen, m_paletteSlot, palData);
	}
}

Sprite::~Sprite() {
}

void Sprite::clear() {
	clearSprite(m_screen, m_id);
}

void Sprite::drawFrame(s16 x, s16 y, u8 frame) {
	drawSprite(m_screen, m_id, x, y, m_size, m_color, m_baseTile + frame * m_tileSize, m_paletteSlot);
}

void Sprite::addAnimation(u8 size, u8 *frames, u16 delay, s16 position[][2]) {
	m_animations.push_back(SpriteAnimation(size, frames, delay, position));
}

void Sprite::stopAnimation(u8 anim) {
	m_animations[anim].timer.stop();
}

void Sprite::startAnimation(u8 anim) {
	m_animations[anim].timer.start();
}

void Sprite::resetAnimation(u8 anim) {
	m_animations[anim].timer.reset();
}

bool Sprite::isAnimationAtEnd(u8 anim) {
	return m_animations[anim].timer.time() / m_animations[anim].delay >= m_animations[anim].size;
}

u16 Sprite::getAnimationFrame(u8 anim) {
	return m_animations[anim].timer.time() / m_animations[anim].delay;
}

void Sprite::playAnimation(s16 x, s16 y, u8 anim) {
	if(!m_animations[anim].isPlaying) {
		resetAnimation(anim);
		startAnimation(anim);
		m_animations[anim].isPlaying = true;
	}
	
	if(isAnimationAtEnd(anim)) {
		resetAnimation(anim);
		startAnimation(anim);
	}
	
	u8 frameToDraw = m_animations[anim].tabAnim[getAnimationFrame(anim)];
	
	s16 ox = 0;
	s16 oy = 0;
	
	if(m_animations[anim].position && m_animations[anim].position[getAnimationFrame(anim)]) {
		ox = m_animations[anim].position[getAnimationFrame(anim)][0];
		oy = m_animations[anim].position[getAnimationFrame(anim)][1];
	}
	
	drawFrame(x + ox, y + oy, frameToDraw);
}

