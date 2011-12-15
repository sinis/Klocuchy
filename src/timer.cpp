#include "timer.h"
#include <SDL/SDL.h>

Timer::Timer(int interval):
    _interval(interval),
    _lastTick(0),
    _pausedAt(0),
    _state(Idle)
{}

void Timer::Start()
{
    _lastTick = SDL_GetTicks();
    _state = Started;
}

bool Timer::Finished()
{
    if (_state == Started)
    {
        _state = Idle;
        return ((_lastTick + _interval) <= SDL_GetTicks());
    }
    else return false;
}

void Timer::Pause()
{
    _pausedAt = SDL_GetTicks();
    _state = Paused;
}

void Timer::Resume()
{
    _lastTick = SDL_GetTicks() + (_lastTick - _pausedAt);
    _state = Started;
}

int Timer::Elapsed()
{
    return SDL_GetTicks() - _lastTick;
}
