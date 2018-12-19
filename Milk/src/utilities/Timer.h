#ifndef _TIMER_
#define _TIMER_

#include <SDL.h>

class Timer
{
public:
	Timer();
	~Timer();

	void start();
	void stop();
	void pause();
	void unpause();

	Uint32 getTicks();

	bool isStarted();
	bool isPaused();

private:
	Uint32 _startTicks;
	Uint32 _pausedTicks;

	bool _paused;
	bool _started;
};

#endif
