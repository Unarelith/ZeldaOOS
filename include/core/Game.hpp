/*
 * =====================================================================================
 *
 *       Filename:  Game.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  16/07/2014 13:31:10
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#ifndef GAME_HPP_
#define GAME_HPP_

class Game {
	public:
		Game();
		~Game();
		
		void initNitroFS();
		void initVideo();
		void initSpriteSystem();
		
		void mainLoop();
		
	private:
		bool m_continue;
};

#endif // GAME_HPP_
