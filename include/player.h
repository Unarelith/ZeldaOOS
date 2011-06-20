#ifndef PLAYER_H
#define PLAYER_H

#include "main.h"
#include "sprite3D.h"

#include "link_png.h"

// All player's directions
enum PlayerDirection {
	DIR_UP = 3,
	DIR_DOWN = 0,
	DIR_LEFT = 2,
	DIR_RIGHT = 1
};

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
		PlayerDirection s_direction;
};

#endif // PLAYER_H
