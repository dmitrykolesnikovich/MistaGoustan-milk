#ifndef _TIMER_
#define _TIMER_

#include "SDL.h"

class Timer
{
public:
	Timer();

	void start();
	void stop();
	void pause();
	void unpause();

	Uint32 getTicks();

	bool isStarted();
	bool isPaused();

private:
	Uint32 startTicks_;
	Uint32 pausedTicks_;

	bool paused_;
	bool started_;
};

#endif
