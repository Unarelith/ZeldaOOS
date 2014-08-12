/*
 * =====================================================================================
 *
 *       Filename:  Tools.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  16/07/2014 19:02:27
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#include <sstream>

#include "Timer.hpp"
#include "Tools.hpp"

void ndsDelay(u32 delay) {
	u32 oldTime = Timer::systemTime;
	
	while(Timer::systemTime - oldTime < delay) {
		swiWaitForVBlank();
	}
}

std::string to_string(int n) {
	std::stringstream s;
	s << n;
	return s.str();
}

