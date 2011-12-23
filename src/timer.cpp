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
    bool ret = false;
    if (_state == Started)
    {
        ret = ((_lastTick + _interval) <= (int)SDL_GetTicks());
    }

    _state = (ret ? Idle : Started);
    return ret;
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
    if (_state != Idle)
        return SDL_GetTicks() - _lastTick;
    return 0;
}
