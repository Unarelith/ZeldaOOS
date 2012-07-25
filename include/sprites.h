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
#ifndef SPRITE_H
#define SPRITE_H

#include <libs5.h>
#include <vector>

class Sprite_Animation {
	public:
		Sprite_Animation(int size, int *tabAnim, int delay);
		~Sprite_Animation();
		
		// Get functions
		int size() const { return s_size; }
		int *tabAnim() const { return s_tabAnim; }
		int delay() const { return s_delay; }
		Timer *tmr() const { return s_tmr; }
		bool isPlaying() const { return s_isPlaying; }
		
		// Setting functions
		void isPlaying(bool isPlaying) { s_isPlaying = isPlaying; }
		
	private:
		int s_size;
		int *s_tabAnim;
		int s_delay;
		Timer *s_tmr;
		bool s_isPlaying;
};

class Sprite {
	public:
		Sprite(u8 screen, int id, s5_dimension size, u8 baseTile, int tileSize = 4);
		~Sprite();
		
		// Clear a sprite
		void clear();
		
		// Draw sprite
		void draw(s16 x, s16 y, u8 palette = 0);
		void drawFrame(s16 x, s16 y, int frame, u8 palette = 0);
		
		// Animations
		void addAnimation(int size, int *tabAnim, int delay);
		void resetAnimation(int anim);
		void startAnimation(int anim);
		void stopAnimation(int anim);
		bool animationAtEnd(int anim);
		void playAnimation(s16 x, s16 y, int anim, u8 palette = 0);
		
		// Get functions
		int id() const { return s_id; } // Get sprite ID
		
		// Static functions
		static void loadAllIcons(u8 screen);
		
	protected:
		int s_id; // Sprite index
		u8 s_screen; // Screen on those the sprite is printing
		u8 s_baseTile; // Sprite base tile
		int s_tileSize;
		
		s5_dimension s_size; // Sprite size
		s5_colors s_color; // Sprite color format
		
		// Sprite coordinates
		s16 s_x;
		s16 s_y;
		
		// Animations table
		std::vector<Sprite_Animation*> s_animations;
};

#endif // SPRITE_H
