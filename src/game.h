#ifndef GAME_H
#define GAME_H

#include <SDL/SDL.h>
#include "tetrion.h"
#include "tetramino.h"
#include "nextview.h"
#include "scoreview.h"
#include "timer.h"

class Game
{
public:

    enum {
        InitialTiming = 1000,
        FPS = 30
    };

    enum State {
        NotStarted,
        InProgress,
        Paused
    };

    Game();
    ~Game();

    void Start();
    void Pause();
    void Resume();
    int GetScore() const { return _score; }
    State GetState() const { return _state; }

protected:
    void Play();
    void Reset();

private:
    SDL_Surface *_screen;
    Tetrion *_tetrion;
    Tetramino *_current;
    Tetramino *_next;
    NextView *_nextView;
    ScoreView *_scoreView;
    Timer *_timer;
    int _score;
    State _state;
};

#endif // GAME_H
