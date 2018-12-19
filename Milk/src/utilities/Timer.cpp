#include "Timer.h"

Timer::Timer()
{
	_startTicks = 0;
	_pausedTicks = 0;

	_paused = false;
	_started = false;
}

Timer::~Timer()
{
}

void Timer::start()
{
	_started = true;

	_paused = false;

	_startTicks = SDL_GetTicks();
	_pausedTicks = 0;
}

void Timer::stop()
{
	_started = false;

	_paused = false;

	_startTicks = 0;
	_pausedTicks = 0;
}

void Timer::pause()
{
	if (_started && !_paused)
	{
		_paused = true;

		_pausedTicks = SDL_GetTicks() - _startTicks;
		_startTicks = 0;
	}
}

void Timer::unpause()
{
	if (_started && _paused)
	{
		_paused = false;

		_startTicks = SDL_GetTicks() - _pausedTicks;

		_pausedTicks = 0;
	}
}

Uint32 Timer::getTicks()
{
	//The actual timer time
	Uint32 time = 0;

	if (_started)
	{
		if (_paused)
		{
			time = _pausedTicks;
		}
		else
		{
			time = SDL_GetTicks() - _startTicks;
		}
	}

	return time;
}

bool Timer::isStarted()
{
	return _started;
}

bool Timer::isPaused()
{
	return _paused && _started;
}
