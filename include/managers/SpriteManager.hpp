/*
 * =====================================================================================
 *
 *       Filename:  SpriteManager.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  28/07/2014 17:05:00
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#ifndef SPRITEMANAGER_HPP_
#define SPRITEMANAGER_HPP_

#include "Sprite.hpp"

namespace SpriteManager {
	void init();
	void free();
	
	void updateAnimations();
	
	void addGrassDestroyAnimation(u16 tileX, u16 tileY);
	void addHeartAnimation(u16 tileX, u16 tileY);
	
	extern Sprite *sword;
	extern Sprite *grassDestroy;
	extern Sprite *grassEffect;
	extern Sprite *lowWaterEffect;
	extern Sprite *heart;
	
	extern std::vector<std::pair<Sprite, u32>> tmpanims;
	extern std::vector<std::pair<Sprite, u32>> anims;
};

#endif // SPRITEMANAGER_HPP_
