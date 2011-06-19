#include "timer.h"

int Timer::osTime;

Timer::Timer() {
	s_t = osTime;
	s_isStarted = false;
	s_tick = 0;
}

Timer::~Timer() {
	reset();
	stop();
}

void Timer::stop() {
	if(s_isStarted) {
		s_isStarted = false;
		s_tick = osTime - s_t;
	}
}

void Timer::start() {
	if(!s_isStarted) {
		s_isStarted = true;
		s_t = osTime - s_tick;
	}
}

void Timer::reset() {
	s_t = osTime;
	s_isStarted = false;
	s_tick = 0;
}

void OnTimer(){
	Timer::osTime++;
}

void Timer::initTimers() {
	TIMER1_CR = 0;
	TIMER1_DATA = TIMER_FREQ_1024(1000);
	TIMER1_CR = TIMER_ENABLE | TIMER_DIV_1024 | TIMER_IRQ_REQ;
	irqSet(IRQ_TIMER1, OnTimer);
	irqEnable(IRQ_TIMER1);
	osTime = 0;
}
