#include "main.h"
#include "gfx.h"

Sprite_Animation::Sprite_Animation(int size, int* tabAnim, int delay) {
	s_size = size;
	s_tabAnim = tabAnim;
	s_delay = delay;
	s_tmr = new Timer();
	s_isPlaying = false;
}

Sprite_Animation::~Sprite_Animation() {
	delete s_tmr;
}

/*void Sprite::initGfx(u8 screen) {
	loadTiles(screen, 0, 2, SprColors_16, dongeonkeyTiles);
	loadTiles(screen, 2, 2, SprColors_16, geshaTiles);
	loadTiles(screen, 4, 2, SprColors_16, ringTiles);
	loadTiles(screen, 6, 5, SprColors_16, seedsTiles);
	loadTiles(screen, 9, 1, SprColors_16, weapon_levelTiles);
	loadTiles(screen, 10, 2, SprColors_16, bombTiles);
	loadTiles(screen, 12, 2, SprColors_16, boomrangL1Tiles);
	loadTiles(screen, 14, 2, SprColors_16, boomrangL2Tiles);
	loadTiles(screen, 16, 2, SprColors_16, bowTiles);
	loadTiles(screen, 18, 2, SprColors_16, caneL1Tiles);
	loadTiles(screen, 20, 2, SprColors_16, caneL2Tiles);
	loadTiles(screen, 22, 2, SprColors_16, catapultTiles);
	loadTiles(screen, 24, 2, SprColors_16, featherL1Tiles);
	loadTiles(screen, 26, 4, SprColors_16, fluteTiles);
	loadTiles(screen, 30, 2, SprColors_16, grapnelTiles);
	loadTiles(screen, 32, 2, SprColors_16, seedbagTiles);
	loadTiles(screen, 34, 2, SprColors_16, shieldL1Tiles);
	loadTiles(screen, 36, 2, SprColors_16, shieldL2Tiles);
	loadTiles(screen, 38, 2, SprColors_16, shieldL3Tiles);
	loadTiles(screen, 40, 2, SprColors_16, shovelTiles);
	loadTiles(screen, 42, 2, SprColors_16, strenghL1Tiles);
	loadTiles(screen, 44, 2, SprColors_16, strenghL2Tiles);
	loadTiles(screen, 46, 2, SprColors_16, swordL1Tiles);
	loadTiles(screen, 48, 2, SprColors_16, swordL2Tiles);
	loadTiles(screen, 50, 2, SprColors_16, swordL3Tiles);
	loadPalette(screen, 0, gfxPal);
}*/

Sprite::Sprite(u8 screen, int id, s5_dimension size, u8 baseTile) {
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

void Sprite::drawFrame(s16 x, s16 y, int frame, u8 palette) {
	drawSprite(s_screen, s_id, x, y, s_size, s_color, s_baseTile + frame*4, palette);
}

void Sprite::addAnimation(int size, int* tabAnim, int delay) {
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
