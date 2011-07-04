#ifndef PLAYER_H
#define PLAYER_H

// All player's directions
enum PlayerDirection {
	DIR_UP = 3,
	DIR_DOWN = 0,
	DIR_LEFT = 2,
	DIR_RIGHT = 1
};

class Player : public Sprite {
	public:
		// Construct & Destruct
		Player();
		~Player();
		
		// Update functions
		void testCollisions();
		void move();
		void draw();
		
	private:
		// Player lifes
		int s_lifes;
		
		// Player coordinates
		s16 s_x;
		s16 s_y;
		
		// Player movement vectors
		s8 s_vx;
		s8 s_vy;
		
		// Direction
		PlayerDirection s_direction;
};

#endif // PLAYER_H
