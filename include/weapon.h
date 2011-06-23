#ifndef WEAPON_H
#define WEAPON_H

#include "main.h"

#include "L1.h"

enum W_KEY {
	W_KEY_B = 9,
	W_KEY_A = 49,
	W_KEY_X = 89,
	W_KEY_Y = 129
};

class Weapon {
	public:
		// Construct & Destruct
		Weapon(const u32* tiles, const u16* pal, char* name, int level);
		~Weapon();
		
		// Update functions
		void drawIcon(W_KEY position);
		
	private:
		char* s_name; // Weapon's real name ( ex. Sword )
		int s_level; // 0: if no level, 1 if level 1, 2 is level 2, etc.
		qSprite* s_icon; // Weapon icon
		
};

#endif // WEAPON_H
