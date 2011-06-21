#include "player.h"
#include "game.h"

// Fill animations table
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
	
Player::Player() : Sprite3D((const char*)link_png, sizeof(link_png), 48, 48) {
	s_x = 240;
	s_y = 128;
	s_vx = 0;
	s_vy = 0;
	s_direction = DIR_LEFT;
	
	// Add animations to player's sprite
	addAnimation(2, animations[0], 200);
	addAnimation(2, animations[1], 200);
	addAnimation(2, animations[2], 200);
	addAnimation(2, animations[3], 200);
	addAnimation(4, animations[4], 50);
	addAnimation(4, animations[5], 50);
	addAnimation(4, animations[6], 50);
	addAnimation(4, animations[7], 50);
	addAnimation(2, animations[8], 100);
	addAnimation(2, animations[9], 100);
	addAnimation(2, animations[10], 100);
	addAnimation(2, animations[11], 100);
}

Player::~Player() {
}

bool in_table(u16* t, u16 n) {
	i = 0;
	while(t[i]) {
		if(t[i] == n) {
			return true;
		}
		i++;
	}
	return false;
}

bool passable(s16 caseX, s16 caseY) {
	if(in_table(Game::currentMap->tileset()->nonPassable, Game::currentMap->getTile(caseX, caseY))) {
		return false;
	} else {
		return true;
	}
}

void Player::testCollisions() {
	if(	(!passable((s_x + 1 + s_vx) / 16	, (s_y + 6) 		/ 16)) || // Left up
		(!passable((s_x - 1 + s_vx) / 16 + 1, (s_y + 6) 		/ 16)) || // Right up
		(!passable((s_x + 1 + s_vx) / 16	, (s_y - 1 + 15) 	/ 16)) || // Left down
		(!passable((s_x - 1 + s_vx) / 16 + 1, (s_y - 1 + 15) 	/ 16)))   // Right down
	{
			s_vx = 0;
	}
	if(	(!passable((s_x + 1) / 16		, (s_y + 6 + s_vy) / 16		)) || // Up left
		(!passable((s_x + 1) / 16		, (s_y - 1 + s_vy) / 16 + 1	)) || // Down left
		(!passable((s_x - 1 + 15) / 16	, (s_y + 6 + s_vy) / 16		)) || // Up right
		(!passable((s_x - 1 + 15) / 16	, (s_y - 1 + s_vy) / 16 + 1	)))   // Down right
	{
			s_vy = 0;
	}
}

void Player::move() {
	if(ul_keys.held.up) {
		// Set vertical speed vector negative
		s_vy = -1;
		
		if((!ul_keys.held.down) && (!ul_keys.held.left) && (!ul_keys.held.right)) {
			s_direction = DIR_UP; // Set direction to up
		}
	}
	
	if(ul_keys.held.down) {
		// Set vertical speed vector positive
		s_vy = 1;
		
		if((!ul_keys.held.up) && (!ul_keys.held.left) && (!ul_keys.held.right)) {
			s_direction = DIR_DOWN; // Set direction to down
		}
	}
	
	if(ul_keys.held.left) {
		// Set horizontal speed vector negative
		s_vx = -1;
		
		if((!ul_keys.held.up) && (!ul_keys.held.down) && (!ul_keys.held.right)) {
			s_direction = DIR_LEFT; // Set direction to left
		}
	}
	
	if(ul_keys.held.right) {
		// Set horizontal speed vector positive
		s_vx = 1;
		
		if((!ul_keys.held.up) && (!ul_keys.held.down) && (!ul_keys.held.left)) {
			s_direction = DIR_RIGHT; // Set direction to right
		}
	}
	
	// Test collisions
	testCollisions();
	
	// Add speed vectors to coordinates ( move the player )
	s_x += s_vx;
	s_y += s_vy;
	
	// Reset speed vectors
	s_vx = 0;
	s_vy = 0;
}

void Player::draw() {
	// If all directional keys are released
	if((!ul_keys.held.up) && (!ul_keys.held.down) && (!ul_keys.held.left) && (!ul_keys.held.right)) {
		drawFrame(s_x - 16, s_y - 16, s_direction); // Draw a simple frame
	} else {
		playAnimation(s_x - 16, s_y - 16, s_direction); // Play player's animation
	}
}
