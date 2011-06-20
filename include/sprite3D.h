#ifndef SPRITE3D_H
#define SPRITE3D_H

#include "main.h"
#include "timer.h"

class Sprite3D_Animation {
	public:
		// Construct & Destruct
		Sprite3D_Animation(int size, int* tabAnim, int delay);
		~Sprite3D_Animation();
		
		// Get functions
		int size() const { return s_size; }
		int* tabAnim() const { return s_tabAnim; }
		int delay() const { return s_delay; }
		Timer* tmr() const { return s_tmr; }
		bool isPlaying() const { return s_isPlaying; }
		
		// Setting functions
		void isPlaying(bool isPlaying) { s_isPlaying = isPlaying; }
	
	private:
		int s_size;
		int* s_tabAnim;
		int s_delay;
		Timer* s_tmr;
		bool s_isPlaying;
};

class Sprite3D {
	public:
		// Construct & Destruct
		Sprite3D(const char* filename, int filesize, u16 width, u16 height);
		Sprite3D(UL_IMAGE* img, u16 width, u16 height);
		~Sprite3D();
		
		// Update functions
        void drawFrame(s16 x, s16 y, int frame);
		void addAnimation(int size, int* tabAnim, int delay);
		void resetAnimation(int anim);
		void startAnimation(int anim);
		void stopAnimation(int anim);
		bool animationAtEnd(int anim);
		void playAnimation(s16 x, s16 y, int anim);
		
		// Get functions
        s16 x() const { return s_x; } // Get sprite x coordinate
        s16 y() const { return s_y; } // Get sprite y coordinate
        u16 width() const { return s_width; } // Get width
        u16 height() const { return s_height; } // Get height
        UL_IMAGE* img() const { return s_img; } // Get img
	
	protected:
		// Sprite size
		u16 s_width;
		u16 s_height;
		
		// Sprite coordinates
        s16 s_x;
        s16 s_y;
		
		// Image data
		UL_IMAGE* s_img;
		
		// Animations table
		vector<Sprite3D_Animation*> s_animations;
};

#endif // SPRITE3D_H
