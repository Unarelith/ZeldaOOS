#include "weapon.h"

Weapon::Weapon(const u32* tiles, const u16* pal, char* name, int level) {
	s_name = name;
	s_level = level;
	s_icon = new qSprite(0, SpriteSize_8x16, SpriteColorFormat_16Color, &oamSub);
	dmaCopyHalfWords(3, tiles, s_icon->gfx(), 8 * 16 / 2);
	for(i = 0 ; i < 16 ; i++) {
		SPRITE_PALETTE_SUB[i] = pal[i];
	}
}

Weapon::~Weapon() {
	delete s_icon;
}

void Weapon::drawIcon(W_KEY position) {
	s_icon->draw(position, 179, 0);
}
