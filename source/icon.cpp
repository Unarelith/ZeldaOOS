#include "icon.h"

Icon::Icon(int i, u8* s_gfx) : Sprite(i, SpriteSize_32x32, SpriteColorFormat_16Color, &oamSub) {
	
}

Icon::~Icon() {
}
