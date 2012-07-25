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
#ifndef GAME_H
#define GAME_H

#define SCREEN_UP 0
#define SCREEN_DOWN 1

class Game {
	public:
		Game();
		~Game();
		
		void mainLoop();
		
		// Scroll between maps
		static void scroll();
		
		// Static variables
		static Map *currentMap;
		static Map **maps;
		static Tileset *tilesets;
		static u8 transBg; // Indoor maps transition BG id
		static Player *talek;
		
	private:
		u8 m_bg; // BG id
		u8 m_bgSub; // Sub BG id
		u8 m_mapBg; // Map BG id
};

#endif // GAME_H
