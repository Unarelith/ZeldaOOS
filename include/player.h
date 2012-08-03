/*---------------------------------------------------------------------------------

	Eleandra
	Copyright (C) 2012 Quentin BAZIN quent42340@gmail.com
	
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
		void move();
		void draw();
		
		// Player's collisions
		void doorCollisions();
		void testCollisions();
		
		// Attributes functions
		PlayerDirection direction() const { return m_direction; }
		void direction(PlayerDirection direction) { m_direction = direction; }
		s16 x() const { return m_x; }
		void x(s16 x) { m_x = x; }
		s16 y() const { return m_y; }
		void y(s16 y) { m_y = y; }
		s8 vx() const { return m_vx; }
		void vx(s8 vx) { m_vx = vx; }
		s8 vy() const { return m_vy; }
		void vy(s8 vy) { m_vy = vy; }
		
		// Static functions
		static bool inTable(u16 t[], u16 n);
		static bool passable(s16 caseX, s16 caseY);
		static bool inTiles(s16 caseX, s16 caseY, u16 t[]);
		
	private:
		// Player lifes
		int m_lifes;
		
		// Player coordinates
		s16 m_x;
		s16 m_y;
		
		// Player movement vectors
		s8 m_vx;
		s8 m_vy;
		
		// Direction
		PlayerDirection m_direction;
};

#endif // PLAYER_H
