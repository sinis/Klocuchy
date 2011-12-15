#ifndef TIMER_H
#define TIMER_H

class Timer
{
public:
    enum State{
        Idle,
        Started,
        Paused
    };

    Timer(int interval = 0);

    void SetInterval(int interval) { _interval = interval; }
    int GetInterval() const { return _interval; }

    void Start();
    bool Finished();
    void Pause();
    void Resume();
    int Elapsed();

private:
    int _interval;
    int _lastTick;
    int _pausedAt;
    State _state;
};

#endif // TIMER_H
