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
		
		// Get functions
		PlayerDirection direction() const { return s_direction; }
		s16 x() const { return s_x; }
		void x(s16 xx) { s_x = xx; }
		s16 y() const { return s_y; }
		void y(s16 yy) { s_y = yy; }
		s8 vx() const { return s_vx; }
		void vx(s8 vxx) { s_vx = vxx; }
		s8 vy() const { return s_vy; }
		void vy(s8 vyy) { s_vy = vyy; }
		
		// Static functions
		static bool inTable(u16 t[], u16 n);
		static bool passable(s16 caseX, s16 caseY);
		static bool inTiles(s16 caseX, s16 caseY, u16 t[]);
		
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
