#include "timer.h"
#include <SDL/SDL.h>

Timer::Timer(int interval):
    _interval(interval),
    _lastTick(0),
    _pausedAt(0)
{}

void Timer::Start()
{
    _lastTick = SDL_GetTicks();
}

bool Timer::Finished()
{
    return ((_lastTick + _interval) <= SDL_GetTicks());
}

void Timer::Pause()
{
    _pausedAt = SDL_GetTicks();
}

void Timer::Resume()
{
    _lastTick = SDL_GetTicks() + (_lastTick - _pausedAt);
}
