/*---------------------------------------------------------------------------------

    The Legend of Zelda: Oracle of Secrets
    Copyright (C) 2011 Pixelda quent42340@gmail.com

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
#ifndef WEAPON_H
#define WEAPON_H

enum W_KEY {
	W_KEY_B = 8,
	W_KEY_A = 48,
	W_KEY_X = 88,
	W_KEY_Y = 128
};

class Weapon {
	public:
		// Construct & Destruct
		Weapon(Sprite* icon, Sprite* animation);
		~Weapon();
		
		// Setting functions
		void setKey(W_KEY key) { s_key = key; }
		
		// Drawing functions
		void drawIcon();
		void playAnimation();
		
	private:
		Sprite* s_icon; // Weapon's icon
		Sprite* s_animation; // Weapons's animation
		W_KEY s_key; // Weapon's action key
		
};

#endif // WEAPON_H
