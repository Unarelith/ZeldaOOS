#include "player.h"

Player::Player() : Sprite3D((const char*)link_png, sizeof(link_png), 48, 48) {
	s_x = 65;
	s_y = 65;
	s_vx = 0;
	s_vy = 0;
	s_direction = DIR_LEFT;
	
	// Fill animations table
	int animations[4][2] = {
		{4,0},
		{5,1},
		{6,2},
		{7,3}
		/*{8,12,16,16},
		{9,13,17,17},
		{10,14,18,18},
		{11,15,19,19},
		{20,24},
		{21,25},
		{22,26},
		{23,27}*/
	};
	
	// Add animations to player's sprite
	addAnimation(2, animations[0], 200);
	addAnimation(2, animations[1], 200);
	addAnimation(2, animations[2], 200);
	addAnimation(2, animations[3], 200);
	/*addAnimation(4, animations[4], 50);
	addAnimation(4, animations[5], 50);
	addAnimation(4, animations[6], 50);
	addAnimation(4, animations[7], 50);
	addAnimation(2, animations[8], 100);
	addAnimation(2, animations[9], 100);
	addAnimation(2, animations[10], 100);
	addAnimation(2, animations[11], 100);*/
}

Player::~Player() {
}

void Player::move() {
	// If up key held
	if(ul_keys.held.up) {
		// Set vertical speed vector negative
		s_vy = -1;
		
		// If all other keys are released
		if((!ul_keys.held.down) && (!ul_keys.held.left) && (!ul_keys.held.right)) {
			s_direction = DIR_UP;
		}
	}
	
	// If down key held
	if(ul_keys.held.down) {
		// Set vertical speed vector positive
		s_vy = 1;
		
		// If all other keys are released
		if((!ul_keys.held.up) && (!ul_keys.held.left) && (!ul_keys.held.right)) {
			s_direction = DIR_DOWN;
		}
	}
	
	// If left key held
	if(ul_keys.held.left) {
		// Set horizontal speed vector negative
		s_vx = -1;
		
		// If all other keys are released
		if((!ul_keys.held.up) && (!ul_keys.held.down) && (!ul_keys.held.right)) {
			s_direction = DIR_LEFT;
		}
	}
	
	// If right key held
	if(ul_keys.held.right) {
		// Set horizontal speed vector positive
		s_vx = 1;
		
		// If all other keys are released
		if((!ul_keys.held.up) && (!ul_keys.held.down) && (!ul_keys.held.left)) {
			s_direction = DIR_RIGHT;
		}
	}
	
	// Add speed vectors to coordinates ( move the player )
	s_x += s_vx;
	s_y += s_vy;
	
	// Reset speed vectors
	s_vx = 0;
	s_vy = 0;
}

void Player::draw() {
	// If all directional keys are released
	/*if((!ul_keys.held.up) && (!ul_keys.held.down) && (!ul_keys.held.left) && (!ul_keys.held.right)) {
		drawFrame(s_x - 16, s_y - 16, s_direction - 1); // Draw a simple frame
	} else {*/
		playAnimation(s_x - 16, s_y - 16, s_direction); // Play player's animation
	//}
}
