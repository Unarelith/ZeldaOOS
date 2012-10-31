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

enum NPCType {
	NPC_BLUE_BOY,
	NPC_BLUE_MEN,
	NPC_FARORE,
	NPC_POSTMAN,
	NPC_RED_GIRL,
	NPC_RED_WOMAN,
	NPC_YELLOW_OLDWOMAN
};

class NPC : public Sprite {
	public:
		NPC(s16 x, s16 y, PlayerDirection direction, NPCType type, u16 map);
		~NPC();
		
		// Update functions
		void draw();
		
		// Attributes functions
		PlayerDirection direction() const { return m_direction; }
		void direction(PlayerDirection direction) { m_direction = direction; }
		s16 x() const { return m_x; }
		void x(s16 x) { m_x = x; }
		s16 y() const { return m_y; }
		void y(s16 y) { m_y = y; }
		u16 map() const { return m_map; }
		
		// Sprites loading
		static void loadAllNPCs();
		
		// NPC counter
		static unsigned int nbNPCs;
		
	private:
		// NPC id
		int m_id;
		
		// NPC coordinates
		s16 m_x;
		s16 m_y;
		
		// Direction
		PlayerDirection m_direction;
		
		// Area
		s8 m_areaX;
		s8 m_areaY;
		
		// Map
		u16 m_map;
		
		// Type
		NPCType m_type;
};

#endif // NPC_H
