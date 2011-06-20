#ifndef PLAYER_H
#define PLAYER_H

#include "main.h"
#include "sprite3D.h"

#include "link_png.h"

class Player : public Sprite3D {
	public:
		// Construct & Destruct
		Player();
		~Player();
		
		// Update functions
		void move();
		void draw();
		
	private:
		// Player lifes
		int s_lifes;
		
		// Player movement vectors
		s8 s_vx;
		s8 s_vy;
		
		// Direction
		int s_direction; // 1: Up / 2: Down / 3: Left / 4: Right
};

#endif // PLAYER_H
