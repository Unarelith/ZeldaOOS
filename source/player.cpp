#include "player.h"

Player::Player() : Sprite3D((const char*)link_png, sizeof(link_png), 48, 48) {
	s_x = 65;
	s_y = 65;
	s_vx = 0;
	s_vy = 0;
	s_direction = 1;
	
	int animations[12][4] = {
		{4,0},
		{5,1},
		{6,2},
		{7,3},
		{8,12,16,16},
		{9,13,17,17},
		{10,14,18,18},
		{11,15,19,19},
		{20,24},
		{21,25},
		{22,26},
		{23,27}
	};
	
	addAnimation(NULL, 0);
	addAnimation(animations[0], 200);
	addAnimation(animations[1], 200);
	addAnimation(animations[2], 200);
	addAnimation(animations[3], 200);
	addAnimation(animations[4], 50);
	addAnimation(animations[5], 50);
	addAnimation(animations[6], 50);
	addAnimation(animations[7], 50);
	addAnimation(animations[8], 100);
	addAnimation(animations[9], 100);
	addAnimation(animations[10], 100);
	addAnimation(animations[11], 100);
}

Player::~Player() {
}

void Player::move() {
	if(ul_keys.held.up) {
		s_vy = -1;
		s_direction = 4;
	}
	if(ul_keys.held.down) {
		s_vy = 1;
		s_direction = 1;
	}
	if(ul_keys.held.left) {
		s_vx = -1;
		s_direction = 3;
	}
	if(ul_keys.held.right) {
		s_vx = 1;
		s_direction = 2;
	}
	
	s_x += s_vx;
	s_y += s_vy;
	
	s_vx = 0;
	s_vy = 0;
}

void Player::draw() {
	if((!ul_keys.held.up) && (!ul_keys.held.down) && (!ul_keys.held.left) && (!ul_keys.held.right)) {
		drawFrame(s_x - 16, s_y - 16, s_direction - 1);
	} else {
		playAnimation(s_x - 16, s_y - 16, s_direction);
	}
}
