#ifndef SCOREVIEW_H
#define SCOREVIEW_H

#include <SDL/SDL.h>

class ScoreView
{
public:
    ScoreView();
    ~ScoreView();

    void SetScore(int score);
    void SetPosition(int x, int y);
    void Show();

private:
    SDL_Surface *_screen;
    SDL_Surface *_label;
    SDL_Surface *_scoreSurface;
    SDL_Color _color;
    int _score;
    int _x;
    int _y;
};

#endif // SCOREVIEW_H