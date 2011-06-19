#ifndef TIMER_H
#define TIMER_H

#include "main.h"

class Timer {
	public:
		// Construct & Destruct
		Timer();
		~Timer();
		
		// Timer control functions
		void stop();
		void start();
		void reset();
		
		// Getting function
		int time() { return (s_isStarted) ? osTime - s_t : s_tick; }
		
		// Static function
		static void initTimers();
		
		// Static variable
		static int osTime;
	
	private:
		int s_t;
		bool s_isStarted;
		int s_tick;
};

#endif // TIMER_H