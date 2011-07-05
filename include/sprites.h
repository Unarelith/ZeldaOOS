#ifndef SPRITE_H
#define SPRITE_H

class Sprite_Animation {
	public:
		// Construct & Destruct
		Sprite_Animation(int size, int* tabAnim, int delay);
		~Sprite_Animation();
		
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

class Sprite {
	public:
		// Construct & Destruct
		Sprite(u8 screen, int id, s5_dimension size, u8 baseTile);
		~Sprite();
		
		// Update functions
		void clear();
		void drawFrame(s16 x, s16 y, int frame, u8 palette = 0);
		void addAnimation(int size, int* tabAnim, int delay);
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
		
		s5_dimension s_size; // Sprite size
		s5_colors s_color; // Sprite color format
		
		// Animations table
		vector<Sprite_Animation*> s_animations;
};

#endif // SPRITE_H
