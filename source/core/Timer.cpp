/*
 * =====================================================================================
 *
 *       Filename:  Timer.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  16/07/2014 15:39:36
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#include "Timer.hpp"

u32 Timer::systemTime = 0;

Timer::Timer() {
	reset();
}

Timer::~Timer() {
}

void Timer::stop() {
	if(m_isStarted) {
		m_isStarted = false;
		m_tick = systemTime - m_t;
	}
}

void Timer::start() {
	if(!m_isStarted) {
		m_isStarted = true;
		m_t = systemTime - m_tick;
	}
}

void Timer::reset() {
	m_t = systemTime;
	m_tick = 0;
	
	m_isStarted = false;
}

void OnTimer() {
	Timer::systemTime++;
}

void Timer::initSystemTimer() {
	TIMER1_CR = 0;
	TIMER1_DATA = TIMER_FREQ_1024(1000);
	TIMER1_CR = TIMER_ENABLE | TIMER_DIV_1024 | TIMER_IRQ_REQ;
	irqSet(IRQ_TIMER1, OnTimer);
	irqEnable(IRQ_TIMER1);
	systemTime = 0;
}

