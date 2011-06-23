#include "sprite.h" 

Sprite::Sprite(int i, SpriteSize size, SpriteColorFormat format, OamState* oam) {
	s_oam = oam;
    s_size = size;
    s_format = format;
    s_gfx = oamAllocateGfx(s_oam, s_size, s_format); // Allocate memory space for sprite gfx
    s_i = i;
}

Sprite::~Sprite() {
	oamClearSprite(s_oam, s_i);
	u16 u;
	for(u = 0 ; u < 8 * 8 ; u++) {
		s_gfx[u] = 0;
	}
	oamFreeGfx(s_oam, s_gfx);
	oamUpdate(s_oam);
}

void Sprite::draw(s16 x, s16 y, int paletteAlpha) {
    s_x = x;
    s_y = y;
	
	// Draw the sprite on the screen
    oamSet(s_oam, s_i, s_x, s_y, 0,
           paletteAlpha, s_size, s_format, s_gfx, -1,
           false, false, false, false, false);
}
