#include "sprite3D.h"

Sprite3D_Animation::Sprite3D_Animation(int* tabAnim, int delay) {
	s_tabAnim = tabAnim;
	s_delay = delay;
	s_tmr = new Timer();
	s_isPlayed = false;
}

Sprite3D_Animation::~Sprite3D_Animation() {
	delete s_tmr;
}

Sprite3D::Sprite3D(const char* filename, int filesize, u16 width, u16 height) {
	s_width = width;
	s_height = height;
	s_img = ulLoadImageFilePNG(filename, filesize, UL_IN_RAM, UL_PF_PAL8);
	if(!s_img) {
		ulDebug("unable to load a sprite");
	}
}

Sprite3D::Sprite3D(UL_IMAGE* img, u16 width, u16 height) {
	s_width = width;
	s_height = height;
	s_img = img;
	if(!s_img) {
		ulDebug("unable to load a sprite");
	}
}

Sprite3D::~Sprite3D() {
	ulDeleteImage(s_img);
}

void Sprite3D::drawFrame(s16 x, s16 y, int frame) {
	u16 boardWidth = s_img->sizeX / s_width;
	s16 yy = floor(frame / boardWidth);
	s16 xx = frame - (yy * boardWidth);
	s16 sourcex = xx * s_width;
	s16 sourcey = yy * s_height;
	
	ulSetImageTileSize(s_img, sourcex, sourcey, s_width, s_height);
	ulDrawImageXY(s_img, x + s_img->centerX, y + s_img->centerY);
}

void Sprite3D::addAnimation(int* tabAnim, int delay) {
	Sprite3D_Animation tmp(tabAnim, delay);
	s_animations.push_back(tmp);
}

void Sprite3D::resetAnimation(int anim) {
	s_animations.at(anim).tmr()->reset();
}

void Sprite3D::startAnimation(int anim) {
	s_animations.at(anim).tmr()->start();
}

void Sprite3D::stopAnimation(int anim) {
	s_animations.at(anim).tmr()->stop();
}

bool Sprite3D::animationAtEnd(int anim) {
	return floor(s_animations.at(anim).tmr()->time() / s_animations.at(anim).delay() + 1) >= sizeof(s_animations.at(anim).tabAnim()) / sizeof(s_animations.at(anim).tabAnim()[0]);
}

void Sprite3D::playAnimation(s16 x, s16 y, int anim) {
	if(!s_animations.at(anim).isPlayed()) {
		resetAnimation(anim);
		startAnimation(anim);
		s_animations.at(anim).isPlayed(true);
	}
	
	if(floor(s_animations.at(anim).tmr()->time() / s_animations.at(anim).delay()) >= sizeof(s_animations.at(anim).tabAnim()) / sizeof(s_animations.at(anim).tabAnim()[0])) {
		resetAnimation(anim);
		startAnimation(anim);
	}
	
	int animToDraw = s_animations.at(anim).tabAnim()[(int)floor(s_animations.at(anim).tmr()->time() / s_animations.at(anim).delay()) + 1];
	drawFrame(x, y, animToDraw);
}
