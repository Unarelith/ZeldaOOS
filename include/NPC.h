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
#ifndef NPC_H
#define NPC_H

class NPC : public Sprite {
	public:
		NPC(s16 x, s16 y, bool move, s8 area, PlayerDirection direction, const void *tiles, const void *pal, u16 map);
		~NPC();
		
		// Update functions
		void move();
		void draw();
		
		// Player's collisions
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
		u16 map() const { return m_map; }
		
		// Static functions
		static bool inTable(u16 t[], u16 n);
		static bool passable(s16 caseX, s16 caseY);
		static bool inTiles(s16 caseX, s16 caseY, u16 t[]);
		
		// NPC counter
		static int nbNPCs;
		
	private:
		// NPC id
		int m_id;
		
		// NPC coordinates
		s16 m_x;
		s16 m_y;
		
		// NPC movement vectors
		s8 m_vx;
		s8 m_vy;
		
		// Direction
		PlayerDirection m_direction;
		
		// Movable
		bool m_move;
		
		// Area
		s8 m_areaX;
		s8 m_areaY;
		
		// Map
		u16 m_map;
};

#endif // NPC_H
