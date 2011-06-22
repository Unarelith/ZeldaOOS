#ifndef WEAPON_H
#define WEAPON_H

#include "main.h"

class Weapon {
	public:
		// Construct & Destruct
		Weapon(char* name, int level);
		~Weapon();
		
	private:
		char* s_name; // Weapon's real name ( ex. Sword )
		int s_level; // 0: if no level, 1 if level 1, 2 is level 2, etc.
		UL_IMAGE* s_icon; // Weapon icon
		
};

#endif // WEAPON_H
