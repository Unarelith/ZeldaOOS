#include "sprite3D.h"

Sprite3D_Animation::Sprite3D_Animation(int size, int* tabAnim, int delay) {
	s_size = size;
	s_tabAnim = tabAnim;
	s_delay = delay;
	s_tmr = new Timer();
	s_isPlaying = false;
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
	/*s16 yy = floor(frame / boardWidth);
	s16 xx = frame - (yy * boardWidth);
	s16 sourcex = xx * s_width;
	s16 sourcey = yy * s_height;*/
	s16 xx = frame % boardWidth;
	s16 yy = frame / boardWidth;
	s16 sourcex = xx * s_width;
	s16 sourcey = yy * s_height;
	
	ulSetImageTileSize(s_img, sourcex, sourcey, s_width, s_height);
	ulDrawImageXY(s_img, x + s_img->centerX, y + s_img->centerY);
}

void Sprite3D::addAnimation(int size, int* tabAnim, int delay) {
	Sprite3D_Animation* tmp = new Sprite3D_Animation(size, tabAnim, delay);
	s_animations.push_back(tmp);
	printf("\x1b[5;0H addr: %d", &(s_animations.at(s_animations.size() - 1)));
	//printf("\x1b[5;0Hanimation: %d, %d / %d, %d / %d, %d", tabAnim[0], tabAnim[1], tmp->tabAnim()[0], tmp->tabAnim()[1], s_animations.at(s_animations.size() - 1).tabAnim()[0], s_animations.back().tabAnim()[1]);
}

void Sprite3D::resetAnimation(int anim) {
	s_animations.at(anim)->tmr()->reset();
}

void Sprite3D::startAnimation(int anim) {
	s_animations.at(anim)->tmr()->start();
}

void Sprite3D::stopAnimation(int anim) {
	s_animations.at(anim)->tmr()->stop();
}

bool Sprite3D::animationAtEnd(int anim) {
	return s_animations.at(anim)->tmr()->time() / s_animations.at(anim)->delay() >= s_animations.at(anim)->size();
}

void Sprite3D::playAnimation(s16 x, s16 y, int anim) {
	printf("\x1b[6;0H addr: %d", &s_animations.at(anim));
	
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
	
	// Clear the console
	//consoleClear();
	
	// This variable contains the number of the animation's frame to draw
	int animToDraw = s_animations.at(anim)->tabAnim()[(int)(s_animations.at(anim)->tmr()->time() / s_animations.at(anim)->delay())];
	drawFrame(x, y, animToDraw); // Draw the frame
	
	// Debug printing
	printf("\x1b[10;0H%d,%d\n%d,%d\n%d,%d\n%d,%d", animToDraw, s_animations.at(anim)->tmr()->time(), s_animations.at(anim)->delay(), anim, s_animations.at(anim)->tmr()->time() / s_animations.at(anim)->delay(), s_animations.at(anim)->size(), s_animations.at(anim)->tabAnim()[0], s_animations.at(anim)->tabAnim()[1]);
}
