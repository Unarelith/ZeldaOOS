/*
 * =====================================================================================
 *
 *       Filename:  Timer.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  16/07/2014 15:39:29
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#ifndef TIMER_HPP_
#define TIMER_HPP_

#include <nds.h>

class Timer {
	public:
		Timer();
		~Timer();
		
		void stop();
		void start();
		void reset();
		
		u32 time() { return (m_isStarted) ? systemTime - m_t : m_tick; }
		
		static u32 systemTime;
		
		static void initSystemTimer();
		
	private:
		u32 m_t;
		u32 m_tick;
		
		bool m_isStarted;
};

#endif // TIMER_HPP_
