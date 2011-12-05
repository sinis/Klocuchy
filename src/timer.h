#ifndef TIMER_H
#define TIMER_H

class Timer
{
public:
    Timer(int interval = 0);

    void SetInterval(int interval) { _interval = interval; }
    int GetInterval() const { return _interval; }

    void Start();
    bool Finished();
    void Pause();
    void Resume();

private:
    int _interval;
    int _lastTick;
    int _pausedAt;
};

#endif // TIMER_H
